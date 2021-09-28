/**
 * @file blockZ.cc
 * @author y3285wan
 * @brief the _Block Z
 * @date 2019-11-21
 * 
 */


#include "blockZ.h"


_BlockZ::_BlockZ(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::Z, Colour::Purple,
        {r-1,r-1,r,r}, {c,c+1,c+1,c+2}
    }
{
}


bool _BlockZ::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({-1,0,-1,0}, {1,0,-1,-2}, Orientation::RIGHT);
    default:
        return _movement({1,0,1,0}, {-1,0,1,2}, Orientation::UP);
    }
}


bool _BlockZ::rotateCCW() {
    return rotateCW();
}

