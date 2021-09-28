/**
 * @file board.h
 * @author y58meng
 * @brief the documentation of Board class
 * @date 2019-11-21
 * 
 */


#ifndef _BOARD_H_
#define _BOARD_H_

#include "../../config.h"
#include "../observer.h"
#include "../subject.h"
#include "../enums/convinient.h"
#include "../textDisplay/textDisplay.h"
#include "../graphicDisplay/graphicDisplay.h" // plase use forward declaration
#include "../cell/cell.h"                     // in headers and include the corresponding
#include "../levels/levelGeneric.h"           // dependencies in the implementation (cc) files
#include <vector>                             // whenever possible, i won't change this now
#include <string>                             // but having too many such things might lead
#include <memory>
#include "../blocks/block.h" //I added this myself, no circular imports here - rzbai
#include "../blocks/block_heavy.h"
#include "../levels/level.h"

struct CellInfo;                              // like this - y3285wan
struct PlayerInfo;
class GameSession;


class Board: public Subject<PlayerInfo> {
    std::vector<std::vector<Cell>> theCell; // should this be a 2d array of pointers to cells? -rzbai
    bool graph;
    int row;
    int col;
    // the first is the timestamp, second is the level
    std::vector<std::pair<uint64_t, int>> blocksRemaining;
    std::unique_ptr<LevelWrapper> spawner;
    PlayerInfo playerInfo;
    TextDisplay *td;
    GraphicDisplay *gd;
    bool isHeavied = false;
    bool isTurnEnd = false;
    // consecutive turns that no rows are cleared
    int notcleared = 0;
    bool inSpecialAction = false;
    std::unique_ptr<Block> currentBlock;

    std::unique_ptr<Block> _getBl(BlockType ty);
    
public:
    // ctor of the board, may call Board::init()
    Board(TextDisplay *td, GraphicDisplay *gd, PlayerInfo playerInfo, int r = MAX_PLAYABLE_ROW, int c = MAX_COL, bool graph = true);
    // getter for current block
    Block *getCurrentBlock();
    // forcefully set the current block
    void setCurrentBlock(BlockType ty);
    // initalize the board
    void init();
    // levels up the spawner
    void levelUp();
    // levels down the spawner
    void levelDown();
    // sequencialise level 3, 4 with a file, making them non random
    bool level3_4_NoRandom(std::string filename);
    // reverts back non-randomness of level 3, 4, becoming normal
    bool level3_4_Random();
    // check if the player loses the game
    bool isLost();
    // scan the board to check if there is a roll filled with 
    // cells, then delete it
    void scan();
    // spawn a new block at the top of board
    void spawn();
    void turnEnd();
    void newTurn();
    PlayerInfo getInfo();
    PlayerInfo &setInfo();
    bool getTurnEnd();
    bool inSpecialAbSession();
    void updateCells();
    friend class GameSession;
    friend class TextDisplay;
    friend class GraphicDisplay;
};


#endif
