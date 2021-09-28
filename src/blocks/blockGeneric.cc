/**
 * @file blockGeneric.cc
 * @author y3285wan
 * @version 0.1
 * @date 2019-11-24
 * 
 */



#include "blockGeneric.h"
#include "../../utilities/helpers1.h"
#include "../infos/cellinfo.h"

#ifdef DEBUG
#include <iostream>
#endif


bool _Block::_canPlace(int r, int c) {
    // test boundary
    if (r >= alls.size() || r < 0 || c >= alls[0].size() || c < 0) 
        return false;
    // if next cell is non empty, and it is in a different block
    CellInfo ifo = alls[r][c].getInfo();
    if (ifo.occupied && ifo.timeStamp != timestamp)
        return false;
    return true;
}


bool _Block::__movementRaw(std::vector<int> &&dr, std::vector<int> &&dc,
                            Orientation orienTo) {
    
    if (atBottom()) return false;
    #ifdef DEBUG
    static_assert(dr.size() == cells.size(), "malformed cell vector");
    #endif

    // test if out of bound / occupied
    std::vector<int> nextRows;
    std::vector<int> nextCols;
    for (int i = 0; i < dr.size(); ++i) { // 4
        CellInfo thisInfo = cells[i]->getInfo();
        int nextRow = thisInfo.row + dr[i];
        int nextCol = thisInfo.col + dc[i];

        if (!_canPlace(nextRow, nextCol)) return false;

        nextRows.emplace_back(nextRow);
        nextCols.emplace_back(nextCol);
    }
    // swap cell with empty target cells (if target is the current block, leave it
    //  for the next iteration)
    std::vector<Cell*> cp = cells;
    std::vector<int> nextRows2 = nextRows;
    std::vector<int> nextCols2 = nextCols;
    while (cp.size()) {
        for (int i = 0; i < cp.size(); ++i) {
            if (alls[nextRows2[i]][nextCols2[i]].isOccupied() &&
                &alls[nextRows2[i]][nextCols2[i]] != cp[i]) // if target = origin, avoid inf loop
                continue;
            cp[i]->swapWith(alls[nextRows2[i]][nextCols2[i]]);
            cp.erase(cp.begin()+i);
            nextRows2.erase(nextRows2.begin()+i);
            nextCols2.erase(nextCols2.begin()+i);
            break;
        }
    }
    for (int i = 0; i < cells.size(); ++i) {
        cells[i]->notifyObservers();
        cells[i] = &alls[nextRows[i]][nextCols[i]];
        cells[i]->notifyObservers();
    }
    orientation = orienTo;
    return true;
}


bool _Block::_movement(std::vector<int> &&dr, std::vector<int> &&dc,
                        Orientation orienTo) {
    int wt = static_cast<int>(weight);
    if (wt)
        __movementRaw({wt,wt,wt,wt}, {0,0,0,0}, orientation);
    return __movementRaw(std::move(dr), std::move(dc), orienTo);
}


_Block::_Block(std::vector<std::vector<Cell>> &alls_, unsigned weight_,
            BlockType type, Colour clr,
            std::vector<int> &&r, std::vector<int> &&c)
    :alls{alls_}
    ,weight{weight_}
{
    for (int i = 0; i < r.size(); ++i) {
        if (!_canPlace(r[i], c[i])) {
            unplaceable = true;
            return;
        }
    }
    uint64_t time = util::getUnixTimeMilisecond();
    timestamp = time;
    for (int i = 0; i < r.size(); ++i) {
        Cell &cell = alls[r[i]][c[i]];
        cell.refresh(type, clr, true, time);
        cells.emplace_back(&cell);
        cell.notifyObservers();
    }
}


bool _Block::moveLeft() {
    return _movement({0,0,0,0}, {-1,-1,-1,-1}, orientation);
}


bool _Block::moveRight() {
    return _movement({0,0,0,0}, {1,1,1,1}, orientation);
}


bool _Block::moveDown() {
    return _movement({1,1,1,1}, {0,0,0,0}, orientation);
}


void _Block::drop() {
    while (moveDown());
}


bool _Block::isLost() {
    return unplaceable;
}


void _Block::prepareDeletion() {
    for (auto &cell: cells) {
        CellInfo ifo = cell->getInfo();
        alls[ifo.row][ifo.col].refresh(BlockType::NOTYPE, Colour::NoColour, 0, 0);
    }
}


uint64_t _Block::getTimeStamp() {
    return timestamp;
}


bool _Block::atBottom() {
    for (int i = 0; i < cells.size(); ++i) {
        CellInfo thisInfo = cells[i]->getInfo();
        if (thisInfo.row == alls.size()-1) return true;
        CellInfo belowInfo = alls[thisInfo.row+1][thisInfo.col].getInfo();
        if (belowInfo.occupied && belowInfo.timeStamp != timestamp) return true;
    }
    return false;
}


