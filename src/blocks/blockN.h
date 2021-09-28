/**
 * @file blockN.h
 * @author y58meng
 * @brief the documentation of blockN class
 * @date 2019-11-21
 * 
 */

// y58meng: This block class is created for level 4(the single block 
//          that is shown as * in text), I denote its type as n and it
//          is a special case(when initialize, it only takes one cell
//          ptr, and the others are initialized to nullptr)

#ifndef _BLOCKN_H_
#define _BLOCKN_H_

#include "blockGeneric.h"

class _BlockN: public _Block{
public:
    _BlockN(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool moveLeft();
    bool moveRight();
    bool moveDown();
    bool rotateCW();
    bool rotateCCW();
    void drop();
};

#endif
