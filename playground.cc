#define DEBUG

#include "src/observer.h"
#include "src/subject.h"
#include "src/infos/cellinfo.h"
#include "src/enums/convinient.h"
#include "src/cell/cell.h"
#include "src/blocks/blockGeneric.h"
#include "src/board/board.h" // test syntax
#include "src/textDisplay/textDisplay.h"
#include "src/blocks/blockGeneric.h"
#include "utilities/helpers1.h"
#include "src/blocks/blockCollection.h"


// this is how we make new block
int main(){
    auto g = std::vector<std::vector<Cell>>{}; // test
    for (unsigned i = 0; i < 20; ++i) {
        auto r = std::vector<Cell>{};
        for (unsigned j = 0; j < 20; ++j) {
            r.emplace_back(Cell{"player",i,j,BlockType::NOTYPE,Colour::NoColour});
        }
        g.emplace_back(r);
    }

    
    auto f = BlockI{&g, 1, 2, 0};
    f.moveDown();
    f.moveDown();
    f.moveDown();
    f.moveDown();
    f.rotateCW();
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (g[i][j].getInfo().type == BlockType::I) std::cout << "I";
            else if (g[i][j].getInfo().type == BlockType::J) std::cout << "J";
            else if (g[i][j].getInfo().type == BlockType::L) std::cout << "L";
            else if (g[i][j].getInfo().type == BlockType::O) std::cout << "O";
            else if (g[i][j].getInfo().type == BlockType::S) std::cout << "S";
            else if (g[i][j].getInfo().type == BlockType::T) std::cout << "T";
            else if (g[i][j].getInfo().type == BlockType::Z) std::cout << "Z";
            else std::cout <<"-";
        }
        std::cout << std::endl;
    }

    return 0;
}

