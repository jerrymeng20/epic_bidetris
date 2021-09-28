/**
 * @file blockI.h
 * @author y58meng
 * @brief the documentation of blockI class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKI_H_
#define _BLOCKI_H_

#include "blockGeneric.h"

class _BlockI: public _Block{
public:
    _BlockI(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
