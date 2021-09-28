

#ifndef _UTIL_HELPERS1_H_
#define _UTIL_HELPERS1_H_

/**
 * if you have helper functions that are entirely not relevant
 * to the tetris project (like max function), write them here
 * to increase reusability
 * 
 * this .h file should not include any libraries other than necessary ones
 */ 

#include <cstdint>
#include <string>
#include <map>

enum class BlockType;


namespace util {

/**
 * @brief Gets the (seconds) unix epoch time (as int)
 */
unsigned getUnixTime();
uint64_t getUnixTimeMilisecond();

void waitFor1MS();

bool fileExists(std::string filename);

BlockType charToBlockType(char c);

template<typename K, typename V>
bool keyInMap(std::map<K,V> &m, K &k);

}



template<typename K, typename V>
bool util::keyInMap(std::map<K,V> &m, K &k) {
    return m.find(k) != m.end();
}

#endif

