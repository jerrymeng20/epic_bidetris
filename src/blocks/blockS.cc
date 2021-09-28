/**
 * @file blockS.cc
 * @author y3285wan
 * @brief the _Block S
 * @date 2019-11-21
 * 
 */


#include "blockS.h"


_BlockS::_BlockS(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::S, Colour::Green,
        {r-1,r-1,r,r}, {c+1,c+2,c,c+1}
    }
{
}


bool _BlockS::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({0,1,-2,-1}, {0,-1,0,-1}, Orientation::RIGHT);
    default:
        return _movement({0,-1,2,1}, {0,1,0,1}, Orientation::UP);
    }
}


bool _BlockS::rotateCCW() {
    return rotateCW();
}

