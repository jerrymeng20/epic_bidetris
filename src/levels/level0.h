/**
 * @file level0.h
 * @author y58meng
 * @brief the documentation of level0 class
 * @date 2019-11-21
 * 
 */

#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include "levelGeneric.h"
#include "../enums/convinient.h"
#include <vector>
#include <string>


namespace util {

class SequenceFileNotExist {};

}

class Level0: public Spawner{
    std::string filename;
    std::vector<char> seq;
    int count = 0;
public:
    /**
     * @brief the text-sequence based block spawner
     *  throws if the file does not exist
     * @param filename 
     */
    Level0(std::string filename);
    BlockType nextBlock() override;
};

# endif
