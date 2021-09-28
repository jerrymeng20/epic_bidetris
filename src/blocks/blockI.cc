/**
 * @file blockI.cc
 * @author y3285wan
 * @brief the _Block I
 * @date 2019-11-21
 * 
 */


#include "blockI.h"


_BlockI::_BlockI(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::I, Colour::Cyan,
        {r,r,r,r}, {c,c+1,c+2,c+3}
    }
{
}


bool _BlockI::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({-3,-2,-1,0}, {0,-1,-2,-3}, Orientation::RIGHT);
    default:
        return _movement({3,2,1,0}, {0,1,2,3}, Orientation::UP);
    }
}


bool _BlockI::rotateCCW() {
    return rotateCW();
}

