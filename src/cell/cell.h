/**
 * @file cell.h
 * @author y3285wan
 * @brief the cells
 * @date 2019-11-21
 **/


#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include "../subject.h"
#include "../enums/convinient.h"

struct CellInfo;
class Block;


class Cell: public Subject<CellInfo> {
    // Board *theBoard;
    // use this to distinguish with other players' cells
    std::string owner;
    // the observers of Cell are Displays
    unsigned row;
    unsigned col;
    BlockType type = BlockType::NOTYPE;
    Colour colour = Colour::NoColour;
    bool occupied = false;
    // the unique (grouped block) ID to identify a block composed
    // of cells
    uint64_t timeStamp = 0UL;
    // incr by one every turn
    unsigned lifeTime = 0U;

public:
    // when initializing an empty cell, its timestamp is 0
    // (ignore this 0 value ones when checking blocks)
    Cell(std::string owner, unsigned r, unsigned c, BlockType type, Colour clr, uint64_t time = 0UL);
    /**
     * @brief call this when you want to refresh a cell (eg change a block cell
     * to an empty cell)
     */
    void refresh(BlockType type_, Colour clr_, bool occupied_, uint64_t timestamp_);
    /**
     * @brief swaps everything except coordininate
     * you don't need this
     */
    void swapWith(Cell &o);
    /**
     * call this function to mutate occupied attribute
     * or
     * @return true this cell is block-owned
     * @return false this cell is empty
     */
    bool &isOccupied();
    /**
     * @brief you need to determine the lifetime of a cell
     * call this function once a turn by incrementing it by one
     * (so that when it is 10 you trigger something)
     * 
     * this does not matter if cell is empty
     * 
     * eg. `myCell.cellLifeTime() += 1;`
     */
    unsigned &cellLifeTime();
    /**
     * @return CellInfo containing r, c, colour, etc
     */
    CellInfo getInfo();
};


#endif

