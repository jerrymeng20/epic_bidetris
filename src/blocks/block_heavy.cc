/**
 * @file block_heavy.cc
 * @author y3285wan
 * @brief the heavy block
 * 
 */


#include "block_heavy.h"


BlockHeavy::BlockHeavy(std::vector<std::vector<Cell>> &alls_,
                        int r, int c, BlockType type_,
                        unsigned weight_)
    :Block{alls_, r, c, type_, weight_}
{
}


bool BlockHeavy::moveLeft() {
    return b->moveLeft() && b->moveDown() && b->moveDown();
}


bool BlockHeavy::moveRight() {
    return b->moveRight() && b->moveDown() && b->moveDown();
}

