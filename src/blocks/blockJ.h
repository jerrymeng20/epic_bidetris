/**
 * @file blockJ.h
 * @author y58meng
 * @brief the documentation of blockJ class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKJ_H_
#define _BLOCKJ_H_

#include "blockGeneric.h"

class _BlockJ: public _Block{
public:
    _BlockJ(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
