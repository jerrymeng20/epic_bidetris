/**
 * @file blockL.cc
 * @author y3285wan
 * @brief the _Block L
 * @date 2019-11-21
 * 
 */


#include "blockL.h"


_BlockL::_BlockL(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::L, Colour::Orange,
        {r-1,r,r,r}, {c+2,c,c+1,c+2}
    }
{
}


bool _BlockL::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({1,-2,-1,0}, {-1,0,-1,-2}, Orientation::RIGHT);
    case Orientation::RIGHT:
        return _movement({0,1,0,-1}, {-1,2,1,0}, Orientation::DOWN);
    case Orientation::DOWN:
        return _movement({-2,1,0,-1}, {0,-1,0,1}, Orientation::LEFT);
    default:
        return _movement({1,0,1,2}, {2,-1,0,1}, Orientation::UP);
    }
}


bool _BlockL::rotateCCW() {
    switch (orientation) {
    case Orientation::RIGHT:
        return _movement({-1,2,1,0}, {1,0,1,2}, Orientation::UP);
    case Orientation::DOWN:
        return _movement({0,-1,0,1}, {1,-2,-1,0}, Orientation::RIGHT);
    case Orientation::LEFT:
        return _movement({2,-1,0,1}, {0,1,0,-1}, Orientation::DOWN);
    default:
        return _movement({-1,0,-1,-2}, {-2,1,0,-1}, Orientation::LEFT);
    }
}


