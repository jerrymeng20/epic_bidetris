/**
 * @file blockN.cc
 * @author y3285wan
 * @brief the _Block N (asterisk)
 * @date 2019-11-21
 * 
 */


#include "blockN.h"


_BlockN::_BlockN(std::vector<std::vector<Cell>> &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::N, Colour::Brown,
        {r}, {c}
    }
{
}


bool _BlockN::moveLeft() {
    return false;
}


bool _BlockN::moveRight() {
    return false;
}


bool _BlockN::moveDown() {
    return false;
}


bool _BlockN::rotateCW() {
    return false;
}


bool _BlockN::rotateCCW() {
    return false;
}


void _BlockN::drop() {
}
