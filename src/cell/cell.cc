/**
 * @file cell.cc
 * @author y3285wan
 * @date 2019-11-23
 * 
 */


#include <utility>

#include "cell.h"
#include "../infos/cellinfo.h"


Cell::Cell(std::string owner, unsigned r, unsigned c, BlockType type, Colour clr, uint64_t time)
    :owner{owner}
    ,row{r}
    ,col{c}
    ,type{type}
    ,colour{clr}
    ,timeStamp{time}
{
}


void Cell::refresh(BlockType type_, Colour clr_, bool occupied_, uint64_t timestamp_) {
    type = type_;
    colour = clr_;
    occupied = occupied_;
    timeStamp = timestamp_;
    lifeTime = 0;
    notifyObservers();
}


void Cell::swapWith(Cell &o) {
    std::swap(type, o.type);
    std::swap(colour, o.colour);
    std::swap(occupied, o.occupied);
    std::swap(timeStamp, o.timeStamp);
    std::swap(lifeTime, o.lifeTime);
    notifyObservers();
    o.notifyObservers();
}


bool &Cell::isOccupied() {
    return occupied;
}


unsigned &Cell::cellLifeTime() {
    return lifeTime;
}


CellInfo Cell::getInfo() {
    return {
        owner, row, col, type, colour, occupied, timeStamp
    };
}


