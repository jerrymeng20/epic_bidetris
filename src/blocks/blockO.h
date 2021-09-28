/**
 * @file blockO.h
 * @author y58meng
 * @brief the documentation of blockO class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKO_H_
#define _BLOCKO_H_

#include "blockGeneric.h"

class _BlockO: public _Block{
public:
    _BlockO(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
