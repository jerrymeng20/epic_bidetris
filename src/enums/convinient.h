/**
 * @file convinient.h
 * @author y3285wan
 * @brief different kinds of colours, block types, rotation types,
 * and command types
 * @date 2019-11-20
 * 
 */

#ifndef _ENUM_CONVINIENT_H_
#define _ENUM_CONVINIENT_H_


enum class Colour {
    Cyan,
    Blue,
    Orange,
    Yellow,
    Green,
    Purple,
    Red,
    Brown, // for the blocking asterisk
    NoColour
};


enum class BlockType {
    I = 67,
    J,
    L,
    O,
    S,
    Z,
    T,
    N,
    NOTYPE
};


enum class Orientation {
    UP, // default
    RIGHT,
    DOWN,
    LEFT
};


enum class CommandType {
    LEFT,
    RIGHT,
    DOWN,
    CLOCKWISE,
    COUNTERWISE,
    DROP,
    LEVELUP,
    LEVELDOWN,
    NORANDOM,
    RANDOM,
    SEQUENCE,
    RESTART,
    ERROR,
    SIGNAL_EXIT,
    SEQ_EOF,
    I = 67,
    J,
    L,
    O,
    S,
    Z,
    T,
    CMD_RENAME = 144,
    CMD_ALIAS,
    CMD_DEFSEQ,
    CMD_USESEQ,
    CMD_HELP,
    SP_BLIND = 219,
    SP_HEAVY,
    SP_FORCE,
    SP_ERROR
};


enum class InfoType {
    CELLINFO,
    PLAYERINFO
};

#endif
