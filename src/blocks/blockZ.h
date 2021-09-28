/**
 * @file blockZ.h
 * @author y58meng
 * @brief the documentation of blockZ class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKZ_H_
#define _BLOCKZ_H_

#include "blockGeneric.h"

class _BlockZ: public _Block{
public:
    _BlockZ(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
