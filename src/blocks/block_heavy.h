/**
 * @file block_heavy.h
 * @author y3285wan
 * @brief the heavy block
 * 
 */

#ifndef _BLOCK_HEAVY_H
#define _BLOCK_HEAVY_H

#include "block.h"


class BlockHeavy: public Block {
public:
    BlockHeavy(std::vector<std::vector<Cell>> &alls_,
            int r, int c, BlockType type_,
            unsigned weight_ = 0U);
    bool moveLeft();
    bool moveRight();
};


#endif

