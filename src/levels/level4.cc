/**
 * @file level4.cc
 * @author y58meng
 * @brief the implementation of level4 class
 * @date 2019-11-28
 * 
 */

#include "level4.h"
#include "../enums/convinient.h"
#include <cstdlib>

BlockType Level4::nextBlock(){
    int v = rand() % 9;
    switch(v){
        case 0:
            return BlockType::I;
            break;
        case 1:
            return BlockType::J;
            break;
        case 2:
            return BlockType::L;
            break;
        case 3:
            return BlockType::O;
            break;
        case 4:
            return BlockType::S;
            break;
        case 5:
            return BlockType::T;
            break;
        case 6:
            return BlockType::Z;
            break;
        case 7:
            return BlockType::S;
            break;
        case 8:
            return BlockType::Z;
            break;
    }
}
