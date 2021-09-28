/**
 * @file graphicDisplay.h
 * @author y58meng
 * @brief the documentation of GraphicDisplay class
 * @date 2019-11-21
 * 
 */

#ifndef _GRAPHIC_DISPLAY_H_
#define _GRAPHIC_DISPLAY_H_

#include "../../config.h"
#include "../observer.h"
#include <iostream>
#include <string>
#include <X11/Xlib.h>
#include "../../libr/graphics/window.h"
#include "../infos/cellinfo.h"
#include "../infos/playerinfo.h"
#include "../../config.h"

class GraphicDisplay: public Observer<CellInfo>, public Observer<PlayerInfo> {
    // number of rows and cols for the graphic
    int row;
    int col;
    // size of display
    int width;
    int height;
    Xwindow w{width, height};
    // info from two players
    std::string board1;
    std::string board2;
    // trach the blindness of 2 players
    bool blind1 = false;
    bool blind2 = false;
public:
    void fill(int c, int r, int colour);  //fill in a sepcific cell
    void fill_row(int r, int colour);  // filling the entire roll
    void drawCells();  //draw the cells
    GraphicDisplay(int width, 
                   int height, 
                   std::string a = "A", 
                   std::string b = "B",
                   int c = MAX_COL, 
                   int r = TOTAL);
    void notify(Subject<CellInfo> &from);
    void init_next(std::string name);
    void draw_notify(std::string name);
    void recover_notify(std::string name);
    void draw_failed(std::string failer, std::string winner);
    void notify(Subject<PlayerInfo> &from);
    ~GraphicDisplay() = default;
};

#endif
