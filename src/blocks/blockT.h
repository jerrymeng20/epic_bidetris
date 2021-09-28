/**
 * @file blockT.h
 * @author y58meng
 * @brief the documentation of blockT class
 * @date 2019-11-21
 * 
 */

#ifndef _BLOCKT_H_
#define _BLOCKT_H_

#include "blockGeneric.h"

class _BlockT: public _Block{
public:
    _BlockT(std::vector<std::vector<Cell>> &alls_,
            int r, int c,
            unsigned weight_ = 0U);
    bool rotateCW();
    bool rotateCCW();
};

#endif
