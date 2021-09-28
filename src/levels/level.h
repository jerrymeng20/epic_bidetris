#include "levelGeneric.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

#include <memory>
#include <string>

class LevelWrapper{
    std::unique_ptr<Spawner> p;
public:
    LevelWrapper(int level, std::string s = std::string{""}){
        switch(level){
            case 0:
                p = std::make_unique<Level0>(s);
                break;
            case 1:
                p = std::make_unique<Level1>();
                break;
            case 2:
                p = std::make_unique<Level2>();
                break;
            case 3:
                p = std::make_unique<Level3>();
                break;
            default:
                p = std::make_unique<Level4>();
                break;
        }
    }
    BlockType nextBlock() {
        return p->nextBlock();
    }

};
