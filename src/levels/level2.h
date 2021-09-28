/**
 * @file level2.h
 * @author y58meng
 * @brief the documentation of level2 class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL2_H_
#define _LEVEL2_H_

#include "levelGeneric.h"
#include "../enums/convinient.h"
#include <cstdlib>

class Level2: public Spawner{
public:
    BlockType nextBlock() override;
};

# endif
