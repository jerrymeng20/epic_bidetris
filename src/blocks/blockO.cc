/**
 * @file blockO.cc
 * @author y3285wan
 * @brief the _Block O
 * @date 2019-11-21
 * 
 */


#include "blockO.h"


_BlockO::_BlockO(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::O, Colour::Yellow,
        {r-1,r-1,r,r}, {c,c+1,c,c+1}
    }
{
}


bool _BlockO::rotateCW() {
    return true;
}


bool _BlockO::rotateCCW() {
    rotateCW();
}


