/**
 * @file player.h
 * @author y3285wan
 * 
 */

#ifndef _QUERY_PLAYER_H_
#define _QUERY_PLAYER_H_


#include <string>

#include "../../config.h"



namespace util {

struct PlayerNotFound {};

}


struct PlayerSaveData
{
    std::string name;
    int hiScore;
};



/**
 * @brief gets the savedate for the player
 * if the player does not exist, create one
 */
PlayerSaveData queryPlayer(std::string &name);

/**
 * @brief updates player's hiScore to the value
 * @premise the savedata file exists
 * @return true update is successful
 * @return false update is not successful 
 */
bool updatePlayerHiScore(std::string &name, int score);



#endif

