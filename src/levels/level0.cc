/**
 * @file level0.cc
 * @author y58meng
 * @brief the implementation of level0 class
 * @date 2019-11-26
 * 
 */

#include "level0.h"
#include "../enums/convinient.h"
#include "../../utilities/helpers1.h"
#include <fstream>
#include <string>

using namespace std;



Level0::Level0(string filename): filename{filename}{
    ifstream file{filename};
    if (!file.is_open()) {
        throw util::SequenceFileNotExist{};
    }
    char c;
    while(file >> c) {
        seq.emplace_back(c);
    }
    file.close();
    if (seq.size() == 0) seq.emplace_back('I');
}

BlockType Level0::nextBlock(){
    BlockType res = util::charToBlockType(seq[count]);
    ++count;
    if (count == seq.size()) count = 0;
    return res;
}
