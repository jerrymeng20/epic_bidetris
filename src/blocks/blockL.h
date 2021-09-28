/**
 * @file blockL.h
 * @author y58meng
 * @brief the documentation of blockL class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKL_H_
#define _BLOCKL_H_

#include "blockGeneric.h"

class _BlockL: public _Block{
public:
    _BlockL(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
