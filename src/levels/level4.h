/**
 * @file level4.h
 * @author y58meng
 * @brief the documentation of level4 class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL4_H_
#define _LEVEL4_H_

#include "levelGeneric.h"
#include "../enums/convinient.h"
#include <cstdlib>

class Level4: public Spawner{
public:
    BlockType nextBlock() override;
};

# endif
