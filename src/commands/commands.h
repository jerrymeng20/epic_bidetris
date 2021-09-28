/**
 * @file commands.h
 * @author y58meng
 * @brief the documentation of Command class
 * @date 2019-11-21
 * 
 */

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "../enums/convinient.h"
#include "../board/board.h"

struct CommandStructure{
    CommandType ct;
    int n;
    std::string argv;
    std::string argv2;
};

class GameSession{
    std::map<std::string, std::string> macros;
    std::map<std::string, CommandType> translation = {
        {"left", CommandType::LEFT},
        {"right", CommandType::RIGHT},
        {"down", CommandType::DOWN},
        {"clockwise", CommandType::CLOCKWISE},
        {"counterclockwise", CommandType::COUNTERWISE},
        {"drop", CommandType::DROP},
        {"levelup", CommandType::LEVELUP},
        {"leveldown", CommandType::LEVELDOWN},
        {"norandom", CommandType::NORANDOM},
        {"random", CommandType::RANDOM},
        {"sequence", CommandType::SEQUENCE},
        {"restart", CommandType::RESTART},
        {"I", CommandType::I},
        {"J", CommandType::J},
        {"L", CommandType::L},
        {"O", CommandType::O},
        {"S", CommandType::S},
        {"Z", CommandType::Z},
        {"T", CommandType::T},
        {"quit", CommandType::SIGNAL_EXIT},
        // special abilities
        {"blind", CommandType::SP_BLIND},
        {"heavy", CommandType::SP_HEAVY},
        {"force", CommandType::SP_FORCE},
        // extra
        {"rename", CommandType::CMD_RENAME},
        {"alias", CommandType::CMD_ALIAS},
        {"defseq", CommandType::CMD_DEFSEQ},
        {"useseq", CommandType::CMD_USESEQ},
        {"help", CommandType::CMD_HELP}
    };
    std::unique_ptr<Board> theBoard;
    Board *oppnent = nullptr;
    std::istream *is;
    std::ostream *os;
    std::string dialogue = "";
    bool onSpecialAblSession = false;
    // blurred command finder
    CommandType commandFinder(std::string &input);
    bool __pushMacro(CommandStructure &cs);
    // renaming
    void _renameCommand(CommandStructure &cs);
    void _aliaseCommand(CommandStructure &cs);
public:
    GameSession(std::unique_ptr<Board> &&b, std::istream *ins, std::ostream *ous);
    // registers the opponent, HAS-A
    void registerOpponent(Board *o);
    // uses command with args
    bool useCommand(CommandStructure &cs);
    // reads command with args
    CommandStructure scanCommand();
    bool getTurnEnd();
    // initializes a new turn
    void newTurn();
    // determines whether the current player loses, if so, main should hijack the session
    bool isLost();
    void printDialogue();
    void changeIS(std::istream *o);
    // returns the current player's board
    Board *getBoard();

    // special ability sessions, only called when it is triggered
    bool inSpecialAction();
    bool useSpecialAction(CommandStructure &cs);

    std::string getMacro(CommandStructure &cs);

};

#endif
