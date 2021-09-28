
#ifndef _DIALOGUE_H_
#define _DIALOGUE_H_

#include <string>

namespace diag {

const std::string intro = 
"-------------------------------------------------------------------------\n"
"|                                                                       |\n"
"|                   WELCOME TO THE EPIC BIQUADRIS GAME                  |\n"
"|                     by y3285wan, y58meng and rzbai                    |\n"
"|                               Dec 2019                                |\n"
"-------------------------------------------------------------------------\n"
"\n";

const std::string storageNotice = 
"This game writes to your local disk to store players' savedata, do you agree?\n";

const std::string helpCmd =
"\n              === LIST OF DEFAULT COMMANDS ===\n"
"                            MOVEMENT\n"
"[left]              move the current block to the left by one unit\n"
"[right]             move the current block to the right by one unit\n"
"[down]              move the current block down by one unit\n"
"[clockwise]         rotate the current block clockwise\n"
"[counterclockwise]  rotate the current block counterclockwise\n"
"[drop]              move the current down as far as it can go and finish turn\n"
"                             MISC\n"
"[levelup]           increments your level by one\n"
"[leveldown]         lowers your level by one\n"
"[restart]           resets the whole game\n"
"[alias [al] [cmdn]] adds an alias for the command [cmdn] so that you can access it by typing [al]\n"
"[rename [cmdn] [n]] replaces the name [cmdn] with your defined [n]. the functionality will be the same\n"
"                             HACK\n"
"[sequence [file]]   start excuting commands found in [file]\n"
"[norandom [file]]   for level 3, 4, replace the randomness with provided block sequence [file]\n"
"[random]            restores randomness in level 3, 4\n"
"[I], [J], [L], ...  instantly set the current block to these block types\n"
"[defseq [name] [seq]] define a sequence of input named [name]\n"
"[useseq [name]]     use the sequence input [name]\n"
"\n"
"You can combine number of repetitions and the command. For example, 5ri moves the block 5 units right.\n"
;


const std::string helpArgv =
"\n                 === LIST OF COMMAND ARGUMENTS ===\n"
"-text               runs the program in text-only mode\n"
"-seed               sets the random number generator’s seed to xxx\n"
"-scriptfile1 [file] player 1 will use [file] as block sequence for level 0\n"
"-scriptfile2 [file] player 2 will use [file] as block sequence for level 0\n"
"-startlevel [n]     starts in level [n]\n\n"
;

const std::string SP_diag = 
"Available actions:    blind     heavy     force [blocktype]\n";

const std::string helpSP =
"\n                          SPECIAL ACTION\n"
"When a players clear two or more rows in a row, a special action is triggered to negatively influence the other player's game.\n"
"[blind]             player's board is covered by ? mark until the block is dropped\n"
"[heavy]             causes two vertical movement after horizontal moves\n"
"[force [type]]      player's next block is forcefully changed to selected one\n\n";


}

#endif
