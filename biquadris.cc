
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <memory>

#include "src/commands/commands.h"
#include "src/board/board.h"
#include "src/textDisplay/textDisplay.h"
#include "src/graphicDisplay/graphicDisplay.h"
#include "src/infos/playerinfo.h"
#include "src/query/player.h"
#include "config.h"
#include "dialogue.h"
#include "utilities/helpers1.h"


using namespace std;


#define printSentences(STR) \
    do { \
    if (*curr == cs1) { \
        *os << "[1] " << name1 << " " << (STR); \
    } else { \
        *os << "[2] " << name2 << " " << (STR); \
    } \
    } while (false)



void game(istream *is, ostream *os, stringstream &inFileStringstream, const bool wantGraph, string name1, string name2, string fileseq1, string fileseq2, int lev) {
START:
    auto player1 = queryPlayer(name1);
    auto player2 = queryPlayer(name2);

    *os << "GAME STARTED.\n";

    auto td = make_unique<TextDisplay>(TOTAL, MAX_COL, name1, name2);

    auto theGraphic = unique_ptr<GraphicDisplay>{};
    
    // default setting is without graphicdisplay
    if (wantGraph){
        theGraphic = make_unique<GraphicDisplay>(864, 600, name1, name2, MAX_COL, TOTAL);
    }

    auto cs1 = make_unique<GameSession>(make_unique<Board>(td.get(), theGraphic.get(), PlayerInfo{
        name1, fileseq1, 0, player1.hiScore, BlockType::NOTYPE, lev
    }), is, os);

    auto cs2 = make_unique<GameSession>(make_unique<Board>(td.get(), theGraphic.get(), PlayerInfo{
        name2, fileseq2, 0, player2.hiScore, BlockType::NOTYPE, lev
    }), is, os);

    cs1->registerOpponent(cs2->getBoard());
    cs2->registerOpponent(cs1->getBoard());

    *os << *td;


    bool p2FirstTurn = true;
    auto *curr = &cs1;
    bool SPsession = false;

    while (true) {
        // display current player symbol on graphics
        if (theGraphic.get()){
            theGraphic->draw_notify(curr == &cs1 ? name1 : name2);
            theGraphic->recover_notify(curr == &cs1 ? name2 : name1);
        }
        
        if ((*curr)->isLost()) {
            *os << *td;
            printSentences("loses the game!\n");
            if (theGraphic.get()){
                theGraphic->draw_failed(curr == &cs1 ? name1 : name2, curr == &cs1 ? name2 : name1);
            }
            break;
        }
        (*curr)->printDialogue();

        if (SPsession) {
            *os << diag::SP_diag;
            printSentences("special action: ");
        } else {
            printSentences("action: ");
        }

        if (inFileStringstream.eof()) {
            cs1->changeIS(&cin); cs2->changeIS(&cin);
        }
        auto cmd = (*curr)->scanCommand();
        if (cmd.ct == CommandType::SIGNAL_EXIT) {
            break;
        }
        if (cmd.ct == CommandType::RESTART) {
            goto START;
        }
        if (cmd.ct == CommandType::SEQUENCE) {
            ifstream inf{cmd.argv};
            if (!inf.is_open()) {
                *os << "We did not find that sequence file " << cmd.argv << '\n';
                continue;
            }
            inFileStringstream = stringstream{};
            inFileStringstream << inf.rdbuf();
            cs1->changeIS(&inFileStringstream); cs2->changeIS(&inFileStringstream);
            inf.close();
        }
        if (cmd.ct == CommandType::CMD_USESEQ) {
            inFileStringstream = stringstream{(*curr)->getMacro(cmd)};
            cs1->changeIS(&inFileStringstream); cs2->changeIS(&inFileStringstream);
        }
        if (cmd.ct == CommandType::CMD_HELP) {
            *os << diag::helpCmd << diag::helpSP << "continue? ";
            is->get();
        }

        if (!SPsession) {
            (*curr)->useCommand(cmd);
        } else {
            if (!(*curr)->useSpecialAction(cmd)) {
                *os << *td;
                continue;
            }
            SPsession = false;
            // if SP is successful, the inSpecialAction is set false inside gamesession
        }
        // case when after dropping, becomes an special action session
        if ((*curr)->inSpecialAction()) {
            SPsession = true;
            *os << *td;
            *os << "Special action for " << (*curr)->getBoard()->getInfo().name << " has been triggered!\n";
            continue;
        }
        // case of normal turn
        if ((*curr)->getTurnEnd()) {
            curr = (*curr == cs1) ? &cs2 : &cs1;
            if (!p2FirstTurn || curr != &cs2) {
                (*curr)->newTurn();
            }
            p2FirstTurn = false;
        }
        *os << *td;
    }

    *os << "Good bye!\n";
    cout << "\nPress any key to continue...\n";
    is->get();
}



int main(int argc, char* argv[]){

    bool graph = true;
    srand(util::getUnixTime());

    // figure out the args
    bool wantGraph = true;

    // filenames
    string fileseq1 = "sequence1.txt";
    string fileseq2 = "sequence2.txt";

    // init level
    int lev = 0;

    // io stream
    istream *is = &cin;
    ostream *os = &cout;
    stringstream inFileStringstream;

    // command argv
    for (int i = 1; i < argc; ++i){
        string dec = argv[i];
        if (dec == "-help"){
            *os << diag::helpArgv;
            return 0;
        }
        
        if (dec == "-text"){
            wantGraph = false;
        }
        
        if (dec == "-seed") {
            if (i == argc-1) {
                *os << "You should provide a valid seed.\n";return -1;
            }
            int seed;
            if (!(istringstream{argv[i+1]} >> seed)) {
                *os << "You should provide a valid seed.\n";return -1;
            }
            srand(seed);
            ++i;
        }

        if (dec == "-scriptfile1"){
            if (i == argc - 1 || !util::fileExists(argv[i+1])){
                *os << "You should provide a valid sequence file name for player 1.\n";
                return -1;
            }
            fileseq1 = argv[i + 1];
            ++i;
        }

        if (dec == "-scriptfile2"){
            if (i == argc - 1 || !util::fileExists(argv[i+1])){
                *os << "You should provide a valid sequence file name for player 2.\n";
                return -1;
            }
            fileseq2 = argv[i + 1];
            ++i;
        }

        if (dec == "-startlevel"){
            if (i == argc - 1){
                *os << "You should provide a valid level as an int range from 0 to 4.\n";
                return -1;
            }

            int n = -1;
            if (istringstream{argv[i + 1]} >> n && n >= 0 && n <= 4){
                lev = n; 
            } else{
                *os << "You should provide a valid level as an int range from 0 to 4.\n";
                return -1;
            }
            ++i;
        }
    }

    // intro
    {
    *os << diag::intro << diag::storageNotice << "accept Y/N:";
    string s;
    while (getline(*is, s)) {
        if (s[0] == 'Y' || s[0] == 'y') {
            break;
        } else if (s[0] == 'n' || s[0] == 'N') {
            return 0;
        }
    }}


    // scan names
    string name1;
    string name2;
    *os << "Please enter the name for player 1:" << endl;
    *is >> name1;
    *os << "Please enter the name for player 2:" << endl;
    *is >> name2;
    if (name1.length() >= 10 || name2.length() >= 10) {
        *os << "names should be no more than 10 characters.\n";
        return -1;
    }
    if (name1 == name2) {
        *os << "minimun two players playing.\n"; 
        return -1;
    }

    is->ignore();


try {
    
    game(is, os, inFileStringstream, wantGraph, name1, name2, fileseq1, fileseq2, lev);

} catch (...) {
    *os << "We exprienced an internal error, sorry...\n";
}
    return 0;
}
