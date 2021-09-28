/**
 * @file level3.h
 * @author y58meng
 * @brief the documentation of level3 class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL3_H_
#define _LEVEL3_H_

#include "levelGeneric.h"
#include "../enums/convinient.h"
#include <cstdlib>

class Level3: public Spawner{
public:
    BlockType nextBlock() override;
};

# endif
