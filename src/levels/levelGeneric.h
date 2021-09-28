/**
 * @file levelGeneric.h
 * @author y58meng
 * @brief the documentation of Spawner class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL_GRNERIC_H_
#define _LEVEL_GRNERIC_H_

#include "../enums/convinient.h"

class Spawner{
public:
    virtual BlockType nextBlock() = 0;
    virtual ~Spawner() = default;
};

#endif
