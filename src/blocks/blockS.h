/**
 * @file blockS.h
 * @author y58meng
 * @brief the documentation of blockS class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "blockGeneric.h"

class _BlockS: public _Block{
public:
    _BlockS(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
