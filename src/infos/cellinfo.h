/**
 * @file cellinfo.h
 * @author y3285wan
 * @brief info struct of cells
 * @date 2019-11-21
 * 
 */


#ifndef _CELLINFO_H_
#define _CELLINFO_H_


#include <string>
#include <cstdint>
#include "../enums/convinient.h"


struct CellInfo {
    std::string name;
    unsigned row;
    unsigned col;
    BlockType type;
    Colour colour;
    bool occupied;
    uint64_t timeStamp;
};


#endif



