
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>

#include "helpers1.h"
#include "../src/enums/convinient.h"


unsigned util::getUnixTime() {
    return (unsigned)std::time(nullptr);
}


uint64_t util::getUnixTimeMilisecond() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


void util::waitFor1MS() {
    std::chrono::milliseconds ts{1};
    std::this_thread::sleep_for(ts);
}


bool util::fileExists(std::string filename) {
    std::ifstream infile(filename);
    return infile.good();
}


BlockType util::charToBlockType(char c) {
    switch (c) {
    case 'I': return BlockType::I;
    case 'J': return BlockType::J;
    case 'L': return BlockType::L;
    case 'O': return BlockType::O;
    case 'S': return BlockType::S;
    case 'T': return BlockType::T;
    case 'Z': return BlockType::Z;
    default: return BlockType::NOTYPE;
    }
}

