/**
 * @file commands.h
 * @author y58meng
 * @brief the implementation of Command class
 * @date 2019-11-28
 * 
 */

#include "commands.h"
#include "../../utilities/helpers1.h"
#include <sstream>

using namespace std;



CommandType GameSession::commandFinder(std::string &input) {
    if (input == "") return CommandType::SEQ_EOF;
    // whole match
    if (util::keyInMap(translation, input)) return translation[input];
    // partial match
    for (auto &ts: translation) {
        if (!ts.first.compare(0, input.length(), input)) {
            dialogue += "Command [" + ts.first + "] recognised for " + theBoard->getInfo().name + ".\n";
            return ts.second;
        }
    }
    return CommandType::ERROR;
}


void GameSession::_renameCommand(CommandStructure &cs) {
    if (cs.argv == "" || cs.argv2 == "") {
        dialogue += "usage: rename [command name] [another name]\n";
        return;
    }
    if (util::keyInMap(translation, cs.argv2)) {
        dialogue += "That target command name \"" + cs.argv2 + "\" already exists.\n";
        return;
    }
    if (!util::keyInMap(translation, cs.argv)) {
        dialogue += "Command \"" + (cs.argv == "" ? "empty" : cs.argv) + "\" does not exist.\n";
        return;
    }
    translation[cs.argv2] = translation[cs.argv];
    translation.erase(cs.argv);
    dialogue += "Renamed command \"" + cs.argv + "\" to \"" + cs.argv2 + "\".\n";
}


void GameSession::_aliaseCommand(CommandStructure &cs) {
    if (cs.argv == "" || cs.argv2 == "") {
        dialogue += "usage: alias [alias] [command name]\n";
        return;
    }
    if (util::keyInMap(translation, cs.argv)) {
        dialogue += "That command name \"" + cs.argv + "\" already exists.\n";
        return;
    }
    if (!util::keyInMap(translation, cs.argv2)) {
        dialogue += "Target command \"" + (cs.argv2 == "" ? "empty" : cs.argv2) + "\" does not exist.\n";
        return;
    }
    translation[cs.argv] = translation[cs.argv2];
    dialogue += "Added command \"" + cs.argv + "\".\n";
}





GameSession::GameSession(std::unique_ptr<Board> &&b, std::istream *ins, std::ostream *ous): 
    theBoard{std::move(b)}, is{ins}, os{ous}
{
}


void GameSession::registerOpponent(Board *o) {
    oppnent = o;
}


CommandStructure GameSession::scanCommand(){
    CommandStructure res = { CommandType::ERROR, 1, "", "" };
    string s;
    std::getline(*is, s);
    istringstream iss{s};
    if (s[0] >= '0' && s[0] <= '9') {
        int n;
        iss >> n;
        res.n = n;
    }
    iss >> s;
    res.ct = commandFinder(s);
    if (iss >> s) res.argv = s;
    if (iss >> s) res.argv2 = s;
    while (iss >> s) res.argv2 += '\n' + s;
    return res;
}

bool GameSession::useCommand(CommandStructure &cs){
    for (int _ = 0; _ < cs.n ; ++_) {
        util::waitFor1MS();

        switch(cs.ct){
        
            case CommandType::LEFT :
                theBoard->getCurrentBlock()->moveLeft();
                if (theBoard->isHeavied && theBoard->getCurrentBlock()->atBottom()) theBoard->turnEnd();
                break;

            case CommandType::RIGHT :
                theBoard->getCurrentBlock()->moveRight();
                if (theBoard->isHeavied && theBoard->getCurrentBlock()->atBottom()) theBoard->turnEnd();
                break;

            case CommandType::DOWN :
                theBoard->getCurrentBlock()->moveDown();
                if (theBoard->isHeavied && theBoard->getCurrentBlock()->atBottom()) theBoard->turnEnd();
                break;

            case CommandType::CLOCKWISE :
                theBoard->getCurrentBlock()->rotateCW();
                if (theBoard->isHeavied && theBoard->getCurrentBlock()->atBottom()) theBoard->turnEnd();
                break;

            case CommandType::COUNTERWISE :
                theBoard->getCurrentBlock()->rotateCCW();
                if (theBoard->isHeavied && theBoard->getCurrentBlock()->atBottom()) theBoard->turnEnd();
                break;

            case CommandType::DROP :
                theBoard->turnEnd();
                break;

            case CommandType::LEVELUP :
                theBoard->levelUp();
                break;          
            
            case CommandType::LEVELDOWN :
                theBoard->levelDown();
                break;          
            
            case CommandType::NORANDOM : {
                if (cs.argv == "") {
                    dialogue += "This feature must accept a filename.\n";
                    break;
                }
                if (theBoard->level3_4_NoRandom(cs.argv)) {
                    dialogue += "Sequencialised this level.\n";
                } else {
                    dialogue += "The action is not successful. Either you are not in level 3 or 4, or the file does not exist.\n";
                }
                break; }

            case CommandType::RANDOM : {
                if (theBoard->level3_4_Random()) {
                    dialogue += "This level is randomised.\n";
                } else {
                    dialogue += "The action is not successful. Are you in level 3 or 4?\n";
                }
                break; }

            case CommandType::RESTART :
                // to be hijacked by main function
                break;

            case CommandType::SEQUENCE :
                // to be hijacked by main function
                break;

            case CommandType::ERROR :
                dialogue += "Not a Valid Command! Try again.\n";
                break;
            
            case CommandType::SEQ_EOF :
                dialogue += "Finished a sequence.\n";
                break;

            case CommandType::I : case CommandType::J : case CommandType::L : case CommandType::O :
            case CommandType::S : case CommandType::Z : case CommandType::T :
                theBoard->setCurrentBlock(static_cast<BlockType>(cs.ct));
                break;
            
            case CommandType::CMD_RENAME :
                _renameCommand(cs);
                break;

            case CommandType::CMD_ALIAS :
                _aliaseCommand(cs);
                break;
            
            case CommandType::CMD_HELP :
                // to be hijacked by main function
                break;
            
            case CommandType::CMD_DEFSEQ :
                __pushMacro(cs);
                break;
            
            case CommandType::CMD_USESEQ :
                // to be hijacked by main function
                break;
            
            default :
                dialogue += "Not a Valid Command! Try again.\n";
                break;
        }
    }
    return true;
}


bool GameSession::getTurnEnd(){
    return theBoard->getTurnEnd();
}

void GameSession::newTurn(){
    dialogue = "";
    theBoard->newTurn();
}


bool GameSession::isLost() {
    return theBoard->isLost();
}


void GameSession::printDialogue() {
    if (dialogue == "") return;
    *os << dialogue;
    dialogue = "";
}


void GameSession::changeIS(std::istream *o) {
    is = o;
}


Board *GameSession::getBoard() {
    return theBoard.get();
}


bool GameSession::inSpecialAction() {
    return theBoard->inSpecialAbSession();
}


bool GameSession::useSpecialAction(CommandStructure &cs) {
    if (oppnent == nullptr) return true;
    util::waitFor1MS();

    switch (cs.ct) {
    
        case CommandType::SP_BLIND :
            oppnent->playerInfo.isBlind = true;
            break;
        
        case CommandType::SP_HEAVY :
            oppnent->isHeavied = true;
            break;
        
        case CommandType::SP_FORCE :
            if (cs.argv == "" || (cs.argv[0] != 'I' && cs.argv[0] != 'J' && cs.argv[0] != 'L' 
                && cs.argv[0] != 'O' && cs.argv[0] != 'S' && cs.argv[0] != 'T' && cs.argv[0] != 'Z')) {
                dialogue += "This skill must accept a block type!\n";
                return false;
            }
            oppnent->playerInfo.nextBlock = util::charToBlockType(cs.argv[0]);
            break;
        
        case CommandType::RESTART :
            // to be hijacked by main function
            break;

        case CommandType::SEQ_EOF :
            dialogue += "Finished a sequence.\n";
            return false;
        
        default :
            dialogue += "That is not a valid special action!\n";
            return false;
    }
    theBoard->inSpecialAction = false;
    return true;
}


bool GameSession::__pushMacro(CommandStructure &cs) {
    if (cs.argv == "" || cs.argv2 == "") {
        return false;
    }
    macros[cs.argv] = cs.argv2;
    return true;
}


std::string GameSession::getMacro(CommandStructure &cs) {
    if (!util::keyInMap(macros, cs.argv)) {
        return "  undefined  ";
    }
    return macros[cs.argv];
}

