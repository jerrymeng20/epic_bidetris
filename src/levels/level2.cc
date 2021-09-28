/**
 * @file level2.cc
 * @author y58meng
 * @brief the implementation of level2 class
 * @date 2019-11-26
 * 
 */

#include "level2.h"
#include "../enums/convinient.h"
#include <cstdlib>

BlockType Level2::nextBlock(){
    int v = rand() % 7;
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
    }
}
