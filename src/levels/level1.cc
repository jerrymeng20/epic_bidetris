/**
 * @file level1.cc
 * @author y58meng
 * @brief the implementation of level1 class
 * @date 2019-11-26
 * 
 */

#include "level1.h"
#include "../enums/convinient.h"
#include <cstdlib>

BlockType Level1::nextBlock(){
    int v = rand() % 12;
    switch(v){
        case 0:
            return BlockType::S;
            break;
        case 1:
            return BlockType::Z;
            break;
        case 2:
            return BlockType::I;
            break;
        case 3:
            return BlockType::I;
            break;
        case 4:
            return BlockType::J;
            break;
        case 5:
            return BlockType::J;
            break;
        case 6:
            return BlockType::L;
            break;
        case 7:
            return BlockType::L;
            break;
        case 8:
            return BlockType::T;
            break;
        case 9:
            return BlockType::T;
            break;
        case 10:
            return BlockType::O;
            break;
        case 11:
            return BlockType::O;
            break;
    }
}
