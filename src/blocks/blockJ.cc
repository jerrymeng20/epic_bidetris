/**
 * @file blockJ.cc
 * @author y3285wan
 * @brief the _Block J
 * @date 2019-11-21
 * 
 */


#include "blockJ.h"


_BlockJ::_BlockJ(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::J, Colour::Blue,
        {r-1,r,r,r}, {c,c,c+1,c+2}
    }
{
}


bool _BlockJ::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({-1,-2,-1,0}, {1,0,-1,-2}, Orientation::RIGHT);
    case Orientation::RIGHT:
        return _movement({2,1,0,-1}, {1,2,1,0}, Orientation::DOWN);
    case Orientation::DOWN:
        return _movement({0,1,0,-1}, {-2,-1,0,1}, Orientation::LEFT);
    default:
        return _movement({-1,0,1,2}, {0,-1,0,1}, Orientation::UP);
    }
}


bool _BlockJ::rotateCCW() {
    switch (orientation) {
    case Orientation::RIGHT:
        return _movement({1,2,1,0}, {-1,0,1,2}, Orientation::UP);
    case Orientation::DOWN:
        return _movement({-2,-1,0,1}, {-1,-2,-1,0}, Orientation::RIGHT);
    case Orientation::LEFT:
        return _movement({0,-1,0,1}, {2,1,0,-1}, Orientation::DOWN);
    default:
        return _movement({1,0,-1,-2}, {0,1,0,-1}, Orientation::LEFT);
    }
}


