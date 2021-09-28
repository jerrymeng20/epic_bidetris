/**
 * @file block.h
 * @author y3285wan
 * @brief all kinds of blocks
 * this is the entry for spawning blocks
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <memory>

#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"
#include "blockN.h"


class Block {
protected:
    std::unique_ptr<_Block> b;
public:
    Block(std::vector<std::vector<Cell>> &alls_,
            int r, int c, BlockType type_,
            unsigned weight_ = 0U);
    /**
     * @brief attempts to move 4 groped cells, send message to observers
     * @return true movement is successful
     * @return false movement is not successful, message not sent
     */
    virtual bool moveLeft();
    virtual bool moveRight();
    virtual bool moveDown();
    virtual bool rotateCW();
    virtual bool rotateCCW();
    /**
     * @brief finish turn
     * (drops current block to bottom)
     */
    void drop();
    /**
     * @return true cannot place block, game lost
     * @return false can place block, game can continue
     */
    bool isLost();
    /**
     * @brief replaces the controlled, block-ized cells with empty cells
     * (aka deleting block)
     */
    void prepareDeletion();
    /**
     * @brief gets timestamp (same as 4 new cells)
     */
    uint64_t getTimeStamp();
    /**
     * @return true the block is at bottom and cannot move further
     * @return false the block is able to move
     */
    bool atBottom();
};


#endif