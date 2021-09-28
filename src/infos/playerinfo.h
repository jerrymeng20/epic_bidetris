/**
 * @file playerinfo.h
 * @author y3285wan
 * @brief info struct of players
 * @date 2019-11-21
 * 
 */


#ifndef _PLAYERINFO_H_
#define _PLAYERINFO_H_

#include <string>
#include "../enums/convinient.h"

struct PlayerInfo
{
    std::string name;
    std::string seqfile;
    int score;
    int hiScore;
    BlockType nextBlock;
    int level;
    bool isBlind = false;
};


#endif



