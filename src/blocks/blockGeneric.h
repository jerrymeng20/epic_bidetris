/**
 * @file blockGeneric.h
 * @author y3285wan
 * @brief block - handle to cells
 * @date 2019-11-21
 * 
 */


#ifndef _BLOCKGENERIC_H_
#define _BLOCKGENERIC_H_

#include <vector>

#include "../cell/cell.h"
#include "../enums/convinient.h"


/** @typedef _Block GroupedCellsCursor 
 *  @interface mother of all blocks
*/
class _Block {
protected:
    // points to Board::theCell
    std::vector<std::vector<Cell>> &alls;
    // handles 4 cells
    std::vector<Cell*> cells;
    // timestamp same as 4 controlled cells
    uint64_t timestamp = 0UL;
    // is heavy
    unsigned weight;
    // default orientation
    Orientation orientation = Orientation::UP;
    // if unplaceable, game lost
    bool unplaceable = false;
    // ...
    bool _canPlace(int r, int c);
    bool __movementRaw(std::vector<int> &&dr, std::vector<int> &&dc,
                        Orientation orienTo);
    bool _movement(std::vector<int> &&dr, std::vector<int> &&dc,
                    Orientation orienTo);
public:
    _Block(  std::vector<std::vector<Cell>> &alls_, unsigned weight_,
            BlockType type, Colour clr,
            std::vector<int> &&r, std::vector<int> &&c);
    /**
     * @brief attempts to move 4 groped cells, send message to observers
     * @return true movement is successful
     * @return false movement is not successful, message not sent
     */
    virtual bool moveLeft();
    /**
     * @brief attempts to move 4 groped cells, send message to observers
     * @return true movement is successful
     * @return false movement is not successful, message not sent
     */
    virtual bool moveRight();
    /**
     * @brief attempts to move 4 groped cells, send message to observers
     * @return true movement is successful
     * @return false movement is not successful, message not sent
     */
    virtual bool moveDown();
    virtual bool rotateCW() = 0;
    virtual bool rotateCCW() = 0;
    /**
     * @brief finish turn
     * (drops current block to bottom)
     */
    virtual void drop();
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
    virtual ~_Block() = default;
};

#endif



