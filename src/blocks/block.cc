/**
 * @file block.cc
 * @author y3285wan
 * @brief all kinds of blocks
 * this is the entry for spawning blocks
 */


#include "block.h"


Block::Block(std::vector<std::vector<Cell>> &alls_,
            int r, int c, BlockType type_,
            unsigned weight_) {
    switch (type_) {
    case BlockType::I:
        b = std::make_unique<_BlockI>(alls_, r, c, weight_);break;
    case BlockType::J:
        b = std::make_unique<_BlockJ>(alls_, r, c, weight_);break;
    case BlockType::L:
        b = std::make_unique<_BlockL>(alls_, r, c, weight_);break;
    case BlockType::O:
        b = std::make_unique<_BlockO>(alls_, r, c, weight_);break;
    case BlockType::S:
        b = std::make_unique<_BlockS>(alls_, r, c, weight_);break;
    case BlockType::T:
        b = std::make_unique<_BlockT>(alls_, r, c, weight_);break;
    case BlockType::Z:
        b = std::make_unique<_BlockZ>(alls_, r, c, weight_);break;
    default:
        b = std::make_unique<_BlockN>(alls_, r, c, weight_);break;
    }
}


bool Block::moveLeft() {
    return b->moveLeft();
}


bool Block::moveRight() {
    return b->moveRight();
}


bool Block::moveDown() {
    return b->moveDown();
}


bool Block::rotateCW() {
    return b->rotateCW();
}


bool Block::rotateCCW() {
    return b->rotateCCW();
}


void Block::drop() {
    b->drop();
}


bool Block::isLost() {
    return b->isLost();
}


void Block::prepareDeletion() {
    b->prepareDeletion();
}


uint64_t Block::getTimeStamp() {
    return b->getTimeStamp();
}


bool Block::atBottom() {
    return b->atBottom();
}


