/**
 * @file textDisplay.cc
 * @author y58meng
 * @brief the implementation of TextDisplay class
 * @date 2019-11-24
 * 
 */

#include "textDisplay.h"
#include "../../config.h"
#include "../observer.h"
#include "../board/board.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "../infos/cellinfo.h"
#include "../infos/playerinfo.h"

using namespace std;

TextDisplay::TextDisplay(int r, int c, string a, string b): 
    row{r}, col{c}, board1{a}, board2{b}{
    for (int loop = 0; loop < 2; loop++){
        // the first row
        theDisplay.emplace_back();

        if (loop == 0){
            for (int i = 0; i < board1.length(); i++){
                theDisplay[0].emplace_back(board1[i]);
            }

            for (int i = 0; i < col - board1.length(); i++){
                theDisplay[0].emplace_back(' ');
            }

        } else{
            for (int i = 0; i < board2.length(); i++){
                theDisplay[0].emplace_back(board2[i]);
            }

            for (int i = 0; i < col - board2.length(); i++){
                theDisplay[0].emplace_back(' ');
            }
        }

        // the second row
        theDisplay.emplace_back();

        string playerLv = "level";
        for (int i = 0; i < playerLv.length(); i++){
            theDisplay[1].emplace_back(playerLv[i]);
        }

        theDisplay[1].emplace_back(':');

        for (int i = 0; i < col - playerLv.length() - 1; i++){
            theDisplay[1].emplace_back(' ');
        }

        // the third row
        theDisplay.emplace_back();

        string Score = "Score";
        for (int i = 0; i < Score.length(); i++){
            theDisplay[2].emplace_back(Score[i]);
        }

        theDisplay[2].emplace_back(':');

        for (int i = 0; i < col - Score.length() - 1; i++){
            theDisplay[2].emplace_back(' ');
        }

        // the forth row
        theDisplay.emplace_back();

        string hiScore = "hiScore";
        for (int i = 0; i < hiScore.length(); i++){
            theDisplay[3].emplace_back(hiScore[i]);
        }

        theDisplay[3].emplace_back(':');

        for (int i = 0; i < col - hiScore.length() - 1; i++){
            theDisplay[3].emplace_back(' ');
        }

        // the fifth row
        theDisplay.emplace_back();
        for (int i = 0; i < col; i++){
            theDisplay[4].emplace_back('-');
        }

        // the game play
        for (int i = 0; i < MAINBOARD; i++){
            theDisplay.emplace_back();
            for (int j = 0; j < col; j++){
                theDisplay[TOP + i].emplace_back(' ');
            }
        }

        // the next block part
        int next = MAINBOARD + TOP + 1;
        theDisplay.emplace_back();
        for (int i = 0; i < col; i++){
            theDisplay[next - 1].emplace_back('-');
        }

        theDisplay.emplace_back();

        string nex = "next";
        for (int i = 0; i < nex.length(); i++){
            theDisplay[next].emplace_back(nex[i]);
        }

        theDisplay[next].emplace_back(':');

        for (int i = 0; i < col - nex.length() - 1; i++){
            theDisplay[next].emplace_back(' ');
        }

        // hold two rows to display next block
        theDisplay.emplace_back();
        for (int i = 0; i < col; i++){
            theDisplay[next + 1].emplace_back(' ');
        }

        theDisplay.emplace_back();
        for (int i = 0; i < col; i++){
            theDisplay[next + 2].emplace_back(' ');
        }

        // print the dash between 2 players
        if (loop == 0){
            for (int i = 0; i < r; i++){
                for (int j = 0; j < 4; j++){
                    theDisplay[i].emplace_back(' ');
                }
            }
        }
    }
}

void TextDisplay::notify(Subject<CellInfo> &from){
    CellInfo c = from.getInfo();

    int p = 0;
    if (c.name == board2){
        p = col + 4;
    }

    int rowNum = TOP + c.row;
    int colNum = c.col + p;

    if (c.name == board1 && isBlind1 && theDisplay[rowNum][colNum] == '?'){
        // This means this cell is hidden, we do not mutate the display of it.
        return;
    }

    if (c.name == board2 && isBlind2 && theDisplay[rowNum][colNum] == '?'){
        // This means this cell is hidden, we do not mutate the display of it.
        return;
    } else if (!c.occupied){
        theDisplay[rowNum][colNum] = ' ';
    } else{
        switch(c.type){
            case BlockType::I :
                theDisplay[rowNum][colNum] = 'I';
                break;
            case BlockType::J :
                theDisplay[rowNum][colNum] = 'J';
                break;
            case BlockType::L :
                theDisplay[rowNum][colNum] = 'L';
                break;
            case BlockType::N :
                theDisplay[rowNum][colNum] = '*';
                break;
            case BlockType::O :
                theDisplay[rowNum][colNum] = 'O';
                break;
            case BlockType::S :
                theDisplay[rowNum][colNum] = 'S';
                break;
            case BlockType::T :
                theDisplay[rowNum][colNum] = 'T';
                break;
            case BlockType::Z :
                theDisplay[rowNum][colNum] = 'Z';
                break;
            case BlockType::NOTYPE :
                theDisplay[rowNum][colNum] = ' ';
                break;
        }
    }
}

void TextDisplay::initNext(string name){
    int next = MAINBOARD + TOP + 2;
    if (name == board1){
        for (int i = 0; i < col; i++){
            theDisplay[next][i] = ' ';
            theDisplay[next + 1][i] = ' ';
        }
    } else{
        for (int i = col + 4; i < col * 2 + 4; i++){
            theDisplay[next][i] = ' ';
            theDisplay[next + 1][i] = ' ';
        }
    }
}

void TextDisplay::notify(Subject<PlayerInfo> &from){
    PlayerInfo in = from.getInfo();

    int colNum = 0;
    if (in.name == board2){
        colNum = col + 4;
    }

    // update level
    theDisplay[1][col - 1 + colNum] = in.level + '0';
    
    // update score
    auto ss = to_string(in.score);
    for (int i = 0; i < ss.length(); i++){
        theDisplay[2][col - 1 - i + colNum] = ss[ss.length() - 1 - i];
    }

    // update hiscore
    auto ss2 = to_string(in.hiScore);
    for (int i = 0; i < ss2.length(); i++){
        theDisplay[3][col - 1 - i + colNum] = ss2[ss2.length() - 1 - i];
    }

    // update vision
    // if the first player is blind
    if (in.name == board1 && in.isBlind){
        for (int i = 2; i <= 11; i++){
            for (int j = 2; j <= 8; j++){
                theDisplay[i + TOP][j] = '?';
            }
        }
        isBlind1 = true;
    }

    // if the first player is no longer blind
    if (in.name == board1 && !in.isBlind){
        isBlind1 = false;
        // then the board should call updateCells() for each cell to recover the vision
    }

    // if the second player is blind
    if (in.name == board2 && in.isBlind){
        for (int i = 2; i <= 11; i++){
            for (int j = 2 + colNum; j <= 8 + colNum; j++){
                theDisplay[i + TOP][j] = '?';
            }
        }
        isBlind2 = true;
    }

    // if the first player is no longer blind
    if (in.name == board2 && !in.isBlind){
        isBlind2 = false;
        // then the board should call updateCells() for each cell to recover the vision
    }

    // update next block
    int next = MAINBOARD + TOP + 2;
    initNext(in.name);
    switch(in.nextBlock){
        case BlockType::I :
            // write block I
            for (int i = 0; i < 4; i++){
                theDisplay[next + 1][i + colNum] = 'I';
            }
            break;

        case BlockType::J :
            // write block J
            for (int i = 0; i < 3; i++){
                theDisplay[next + 1][i + colNum] = 'J';
            }
            theDisplay[next][0 + colNum] = 'J';
            break;
        
        case BlockType::L :
            // write block L
            for (int i = 0; i < 3; i++){
                theDisplay[next + 1][i + colNum] = 'L';
            }
            theDisplay[next][2 + colNum] = 'L';
            break;
        
        case BlockType::O :
            // write block O
            for (int i = 0; i < 2; i++){
                theDisplay[next][i + colNum] = 'O';
                theDisplay[next + 1][i + colNum] = 'O';
            }
            break;
        
        case BlockType::S :
            // write block S
            theDisplay[next][1 + colNum] = 'S';
            theDisplay[next][2 + colNum] = 'S';
            theDisplay[next + 1][0 + colNum] = 'S';
            theDisplay[next + 1][1 + colNum] = 'S';
            break;

        case BlockType::Z :
            // write block Z
            theDisplay[next][0 + colNum] = 'Z';
            theDisplay[next][1 + colNum] = 'Z';
            theDisplay[next + 1][1 + colNum] = 'Z';
            theDisplay[next + 1][2 + colNum] = 'Z';
            break;
        
        case BlockType::T :
            // write block T
            for (int i = 0; i < 3; i++){
                theDisplay[next][i + colNum] = 'T';
            }
            theDisplay[next + 1][1 + colNum] = 'T';
            break;
        
        default: // case BlockType::NOTYPE :
            // clear
            break;
        
    }
}

std::ostream &operator<<(std::ostream &out, TextDisplay td){
    out << '\n';
    for (int r = 0; r < td.row; r++){
		for (int c = 0; c < td.col * 2 + 4; c++){
			out << td.theDisplay[r][c];
		}
		out << std::endl;
	}
	return out;
}

