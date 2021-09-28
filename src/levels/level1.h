/**
 * @file level1.h
 * @author y58meng
 * @brief the documentation of level1 class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include "levelGeneric.h"
#include "../enums/convinient.h"
#include <cstdlib>

class Level1: public Spawner{
public:
    BlockType nextBlock() override;
};

# endif
