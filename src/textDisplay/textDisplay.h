/**
 * @file textDisplay.h
 * @author y58meng
 * @brief the documentation of TextDisplay class
 * @date 2019-11-21
 * 
 */

#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "../../config.h"
#include "../observer.h"
#include <vector>
#include <iostream>

class Cell;
class Board;
struct CellInfo;
struct PlayerInfo;


class TextDisplay: public Observer<CellInfo>, public Observer<PlayerInfo> {
    int row;
    int col;
    std::string board1;
    std::string board2;
    bool isBlind1 = false;
    bool isBlind2 = false;
    std::vector<std::vector<char>> theDisplay;
public:
    TextDisplay(int r = TOTAL, 
                int c = MAX_COL, 
                std::string a = "A", 
                std::string b = "B");
    void notify(Subject<CellInfo> &from);
    void initNext(std::string name);
    void notify(Subject<PlayerInfo> &from);
    friend std::ostream &operator<<(std::ostream &out, TextDisplay td);
};

#endif
