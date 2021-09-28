
#include "graphicDisplay.h"
#include "../infos/cellinfo.h"
#include "../infos/playerinfo.h"
#include "../../config.h"
#include "../observer.h"
#include "../board/board.h"
#include "../../libr/graphics/window.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../../config.h"

class Cell;
class Board;
using namespace std;

// pretty fill the rectangle
void GraphicDisplay::fill(int c, int r, int colour){
    // cout << "We are filling " << c << ", " << r << endl;
    // cout << "The width is" << c * width << endl;
    // cout << "The height is" << c * height << endl;
    int row_width = height / row;
	int row_edge_width = height - row_width * (row - 1);

    int col_width = width / (2 * col + 2);
    int col_edge_width = width - col_width * (2 * col + 1);


	if (c == col * 2 + 1 && r == row - 1){
		w.fillRectangle(c * col_width, r * row_width, col_edge_width, row_edge_width, colour);
	} else if (c == col * 2 + 1){
		w.fillRectangle(c * col_width, r * row_width, col_edge_width, row_width, colour);
	} else if (r == row - 1){
		w.fillRectangle(c * col_width, r * row_width, col_width, row_edge_width, colour);
	} else{
		w.fillRectangle(c * col_width, r * row_width, col_width, row_width, colour);
	}
}

void GraphicDisplay::fill_row(int r, int colour){
    for (int i = 0; i < col * 2 + 2; i++){
        fill(i, r, colour);
    }
}

void GraphicDisplay::drawCells(){
    for (int i = 0; i < MAINBOARD; i++){
        w.drawLine(0, height / row * (i + TOP),width, height / row * (i + TOP));
    }

    for (int i = 0; i < col * 2 + 2; i++){
        w.drawLine(width / (col * 2 + 2) * i, height / row * TOP, width / (col * 2 + 2) * i, height / row * (TOP + MAINBOARD));
    }
}

GraphicDisplay::GraphicDisplay(int width, int height, string a, string b, int c, int r): 
    width{width}, height{height}, board1{a}, board2{b}, col{c}, row{r}{
    int row_width = height / r;
    int col_width = width / (2 * c + 2);
    
    // the first 4 rows are for informations
    for (int i = 0; i < TOP - 1; i++){
        fill_row(i, Xwindow::Yellow);
    }

    // the next row is to distinguish between the board and the player info
    fill_row(TOP - 1, Xwindow::Black);

    // the next 15 rows are for mainboard
    for (int i = 0; i < MAINBOARD; i++){
        fill_row(i + TOP, Xwindow::White);
    }

    // the next row is to distinguish between the board and the next block perios
    fill_row(MAINBOARD + TOP, Xwindow::Black);

    // the last 3 rows are for next block info
    /*for (int i = 0; i < BOTTOM - 1; i++){
        fill_row(MAINBOARD + TOP + i + 1, Xwindow::White);
    }*/

    // draw the boundary between 2 players
    for (int i = 0; i < row; i++){
        for (int j = col; j < col + 2; j++){
            fill(j, i, Xwindow::Black);
        }
    }

    // draw the cells in the board
    drawCells();

    // update the player info
    w.drawString(20, 20, "Name: ", Xwindow::Black);
    w.drawString(20 + width / col, 20, board1, Xwindow::Blue);
    w.drawString(20, 20 + height / row, "Level: ", Xwindow::Black);
    w.drawString(20, 20 + height / row * 2, "Score: ", Xwindow::Black);
    w.drawString(20, 20 + height / row * 3, "HiScore: ", Xwindow::Black);

    w.drawString(20 + width / (col * 2 + 2) * (col + 2), 20, "Name: ", Xwindow::Black);
    w.drawString(20 + width / (col * 2 + 2) * (col + 2) + width / col, 20, board2, Xwindow::Blue);
    w.drawString(20 + width / (col * 2 + 2) * (col + 2), 20 + height / row, "Level: ", Xwindow::Black);
    w.drawString(20 + width / (col * 2 + 2) * (col + 2), 20 + height / row * 2, "Score: ", Xwindow::Black);
    w.drawString(20 + width / (col * 2 + 2) * (col + 2), 20 + height / row * 3, "HiScore: ", Xwindow::Black);

    // update next block
    w.drawString(20, 20 + height / row * (TOP + MAINBOARD + 1), "Next: ", Xwindow::Black);
    w.drawString(20 + width / (col * 2 + 2) * (col + 2), 20 + height / row * (TOP + MAINBOARD + 1), "Next: ", Xwindow::Black);
}

void GraphicDisplay::notify(Subject<CellInfo> &from){
    CellInfo c = from.getInfo();

    int p = 0;
    if (c.name == board2){
        p = col + 2;
    }

    int rowNum = TOP + c.row;
    int colNum = c.col + p;

    // check if is hidden
    if (((c.name == board1 && blind1) || (c.name == board2 && blind2)) && c.row >= 2 && 
        c.row <= 11 && c.col <= 9 && c.col >= 2){
        // This means this cell is hidden, we do not mutate the display of it.
        return;
    } else if (!c.occupied){
        fill(colNum, rowNum, Xwindow::White);
    } else{
        switch(c.type){
            case BlockType::I :
                fill(colNum, rowNum, Xwindow::Green);
                break;
            case BlockType::J :
                fill(colNum, rowNum, Xwindow::Cyan);
                break;
            case BlockType::L :
                fill(colNum, rowNum, Xwindow::DarkGreen);
                break;
            case BlockType::N :
                fill(colNum, rowNum, Xwindow::Brown);
                break;
            case BlockType::O :
                fill(colNum, rowNum, Xwindow::Yellow);
                break;
            case BlockType::S :
                fill(colNum, rowNum, Xwindow::Blue);
                break;
            case BlockType::T :
                fill(colNum, rowNum, Xwindow::Magenta);
                break;
            case BlockType::Z :
                fill(colNum, rowNum, Xwindow::Red);
                break;
            case BlockType::NOTYPE :
                fill(colNum, rowNum, Xwindow::White);
                break;
        }
    }

    w.drawLine(width / (col * 2 + 2) * colNum, height / row * rowNum, 
        width / (col * 2 + 2) * (colNum + 1), height / row * rowNum);
    w.drawLine(width / (col * 2 + 2) * colNum, height / row * rowNum, 
        width / (col * 2 + 2) * colNum, height / row * (rowNum + 1));
}

void GraphicDisplay::init_next(string name){
    int next = MAINBOARD + TOP + 2;
    if (name == board1){
        for (int i = 0; i < col; i++){
            fill(i, next, Xwindow::White);
            fill(i, next + 1, Xwindow::White);
        }
    } else{
        for (int i = col + 2; i < col * 2 + 2; i++){
            fill(i, next, Xwindow::White);
            fill(i, next + 1, Xwindow::White);
        }
    }
}

void GraphicDisplay::draw_notify(string name){
    int colNum = col + 2;
    if (name == board1)  colNum = 0;
    w.fillCircle(width / (col * 2 + 2) * (colNum + col - 2), height / row * 2, height / row, Xwindow::Red);
}

void GraphicDisplay::recover_notify(string name){
    int colNum = col + 2;
    if (name == board1)  colNum = 0;

    w.fillCircle(width / (col * 2 + 2) * (colNum + col - 2), height / row * 2, height / row, Xwindow::Yellow);
}

void GraphicDisplay::draw_failed(std::string failer, std::string winner){
    int colNum = col + 2; // loser
    int colNum2 = 0;  // winner
    if (failer == board1){
        colNum = 0;
        colNum2 = col + 2;
    }

    for(int i = TOP + MAINBOARD / 2 - 2; i < TOP + MAINBOARD / 2 + 3; i++){
        for (int j = colNum + col / 2 - 2; j < colNum + col / 2 + 3; j++){
            fill(j, i, Xwindow::Red);
        }
    }

    for(int i = TOP + MAINBOARD / 2 - 2; i < TOP + MAINBOARD / 2 + 3; i++){
        for (int j = colNum2 + col / 2 - 2; j < colNum2 + col / 2 + 3; j++){
            fill(j, i, Xwindow::Green);
        }
    }

    // display failer message
    w.drawString(width / (col * 4 + 4) * (2 * colNum + col - 1), (height / 2 / row) * 2 * (TOP + MAINBOARD / 2 + 1), "YOU LOSE!", Xwindow::Green);

    // display winner message
    w.drawString(width / (col * 4 + 4) * (2 * colNum2 + col - 1), (height / 2 / row) * 2 * (TOP + MAINBOARD / 2 + 1), "YOU WIN!", Xwindow::Red);
}

void GraphicDisplay::notify(Subject<PlayerInfo> &from){
    PlayerInfo in = from.getInfo();

    int colNum = 0;
    if (in.name == board2){
        colNum = col + 2;
    }

    // update vision: (if the player is blind)
    // if the first player is blind:
    if (in.name == board1 && in.isBlind){
        for (int i = 2; i <= 11; i++){
            for (int j = 2; j <= 8; j++){
                fill(j, i + TOP, Xwindow::Black);
            }
        }
        blind1 = true;
    }

    // if the first player is nolonger blind
    if (in.name == board1 && !in.isBlind){
        blind1 = false;
        // then the board should call updateCells to recover the vision
    }

    // if the second player is blind:
    if (in.name == board2 && in.isBlind){
        for (int i = 2; i <= 11; i++){
            for (int j = 2; j <= 8; j++){
                fill(j + col + 2, i + TOP, Xwindow::Black);
            }
        }
        blind2 = true;
    }

    // if the second player is nolonger blind
    if (in.name == board2 && !in.isBlind){
        blind2 = false;
        // then the board should call updateCells to recover the vision
    }

    // update level
    string lev = "";
    fill(colNum + 2, 1, Xwindow::Yellow);
    fill(colNum + 3, 1, Xwindow::Yellow);
    ostringstream oss1{lev};

    if (oss1 << in.level){
        lev = oss1.str();
        w.drawString(20 + width / (col * 2 + 2) * colNum + width / col, 20 + height / row, lev, Xwindow::Blue);
    }
    
    // update score
    string sec = "";
    fill(colNum + 2, 2, Xwindow::Yellow);
    fill(colNum + 3, 2, Xwindow::Yellow);
    ostringstream oss2{sec};
    
    if (oss2 << in.score){
        sec = oss2.str();
        w.drawString(20 + width / (col * 2 + 2) * colNum + width / col, 20 + height / row * 2, sec, Xwindow::Blue);
    }

    // update hiscore
    string hisec = "";
    fill(colNum + 2, 3, Xwindow::Yellow);
    fill(colNum + 3, 3, Xwindow::Yellow);
    ostringstream oss3{hisec};
    
    if (oss3 << in.hiScore){
        sec = oss3.str();
        w.drawString(20 + width / (col * 2 + 2) * colNum + width / col, 20 + height / row * 3, sec, Xwindow::Blue);
    }

    // update next block
    int next = MAINBOARD + TOP + 2;
    init_next(in.name);
    switch(in.nextBlock){
        case BlockType::I :
            // write block I
            for (int i = 0; i < 4; i++){
                fill(i + colNum, next + 1, Xwindow::Green);
            }
            break;

        case BlockType::J :
            // write block J
            for (int i = 0; i < 3; i++){
                fill(i + colNum, next + 1, Xwindow::Cyan);
            }
            fill(colNum, next, Xwindow::Cyan);
            break;
        
        case BlockType::L :
            // write block L
            for (int i = 0; i < 3; i++){
                fill(i + colNum, next + 1, Xwindow::DarkGreen);
            }
            fill(2 + colNum, next, Xwindow::DarkGreen);
            break;
        
        case BlockType::O :
            // write block O
            for (int i = 0; i < 2; i++){
                fill(i + colNum, next + 1, Xwindow::Yellow);
                fill(i + colNum, next, Xwindow::Yellow);
            }
            break;
        
        case BlockType::S :
            // write block S
            fill(1 + colNum, next, Xwindow::Blue);
            fill(2 + colNum, next, Xwindow::Blue);
            fill(0 + colNum, next + 1, Xwindow::Blue);
            fill(1 + colNum, next + 1, Xwindow::Blue);
            break;

        case BlockType::Z :
            // write block Z
            fill(1 + colNum, next + 1, Xwindow::Red);
            fill(2 + colNum, next + 1, Xwindow::Red);
            fill(0 + colNum, next, Xwindow::Red);
            fill(1 + colNum, next, Xwindow::Red);
            break;
        
        case BlockType::T :
            // write block T
            for (int i = 0; i < 3; i++){
                fill(i + colNum, next, Xwindow::Magenta);
            }
            fill(1 + colNum, next + 1, Xwindow::Magenta);
            break;
        
        default: // case BlockType::NOTYPE :
            // clear
            break;
        
    }
}

