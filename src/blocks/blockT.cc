/**
 * @file blockT.cc
 * @author y3285wan
 * @brief the _Block T
 * @date 2019-11-21
 * 
 */


#include "blockT.h"


_BlockT::_BlockT(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::T, Colour::Red,
        {r-1,r-1,r-1,r}, {c,c+1,c+2,c+1}
    }
{
}


bool _BlockT::rotateCW() {
    switch (orientation) {
    case Orientation::UP:
        return _movement({-1,0,1,-1}, {1,0,-1,-1}, Orientation::RIGHT);
    case Orientation::RIGHT:
        return _movement({2,1,0,0}, {1,0,-1,1}, Orientation::DOWN);
    case Orientation::DOWN:
        return _movement({0,-1,-2,0}, {-2,-1,0,0}, Orientation::LEFT);
    default:
        return _movement({-1,0,1,1}, {0,1,2,0}, Orientation::UP);
    }
}


bool _BlockT::rotateCCW() {
    switch (orientation) {
    case Orientation::RIGHT:
        return _movement({1,0,-1,1}, {-1,0,1,1}, Orientation::UP);
    case Orientation::DOWN:
        return _movement({-2,-1,0,0}, {-1,0,1,-1}, Orientation::RIGHT);
    case Orientation::LEFT:
        return _movement({0,1,2,0}, {2,1,0,0}, Orientation::DOWN);
    default:
        return _movement({1,0,-1,-1}, {0,-1,-2,0}, Orientation::LEFT);
    }
}


