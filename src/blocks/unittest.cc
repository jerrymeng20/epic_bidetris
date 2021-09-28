#define DEBUG

/**
 * some random segfault errors have occurred when i tried to allocate a Block object
 * on heap (with new). sometimes this arises when I tried compiling, sometimes this does not
 * happen. I suspect that this is probably due to makefiles
 * (bug)
 * if anything occurs report to me
 * 
 * 
 * this file tests the correctness of the block allocations
 * 
 * 
 * another note:
 * since Blocks are distinguished by birthtime, when you spawn two blocks at the same time
 * (second-wise), and let them interact, that will cause infinite loop
 * 
 */

#include <memory>
#include <iostream>

#include "block.h"
#include "../infos/cellinfo.h"

#define SIZE 10

void printGrids(std::vector<std::vector<Cell>> &g) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            switch (g[i][j].getInfo().type) {
            case BlockType::I: std::cout << "I";break;
            case BlockType::J: std::cout << "J";break;
            case BlockType::L: std::cout << "L";break;
            case BlockType::O: std::cout << "O";break;
            case BlockType::S: std::cout << "S";break;
            case BlockType::T: std::cout << "T";break;
            case BlockType::Z: std::cout << "Z";break;
            case BlockType::N: std::cout << "*";break;
            default: std::cout <<"-";break;
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    auto g = std::vector<std::vector<Cell>>{}; // test
    for (unsigned i = 0; i < SIZE; ++i) {
        auto r = std::vector<Cell>{};
        for (unsigned j = 0; j < SIZE; ++j) {
            r.emplace_back(Cell{"player",i,j,BlockType::NOTYPE,Colour::NoColour});
        }
        g.emplace_back(r);
    }
    
    for (auto &ty: std::vector<BlockType>{
        BlockType::I, BlockType::J, BlockType::L, BlockType::O, BlockType::S, BlockType::T, BlockType::Z, BlockType::N
    }) {
        auto j = std::make_unique<Block>(g, 3, 3, ty, 0);
        printGrids(g);std::cout << "\n";
        j->rotateCW();
        printGrids(g);std::cout << "\n";
        j->rotateCW();
        printGrids(g);std::cout << "\n";
        j->rotateCW();
        printGrids(g);std::cout << "\n";
        j->rotateCW();
        printGrids(g);std::cout << "\n";
        j->rotateCCW();
        printGrids(g);std::cout << "\n";
        j->rotateCCW();
        printGrids(g);std::cout << "\n";
        j->rotateCCW();
        printGrids(g);std::cout << "\n";
        j->rotateCCW();
        printGrids(g);std::cout << "\n";
        j->moveLeft();
        printGrids(g);std::cout << "\n";
        j->moveRight();
        printGrids(g);std::cout << "\n";
        j->drop();
        printGrids(g);std::cout << "\n";
        j->prepareDeletion();
    }
}
