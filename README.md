The Epic Biquadris Project - y3285wan, y58meng, rzbai

Introduction
This is our Biquadris project, made by Yang Wang (y3285wan), Yanchen Meng (y58meng), and Rong Zhuo Bai (rzbai).  It is a modified version of the classic video game Tetris.

Overview
This project has many components to it.  The generic object components include the boards, the various block types (both abstract and concrete, and with the singular block required for Level 4), the cells within the boards, command types, and text and graphic displays.  When put together, the project has the textdisplay and graphicdisplay both attached to two board objects, each board representing the board of the players.  The boards contain cells which hold the states of the blocks which allows the general gameplay and board state, as well as allowing scoring to be done.  The blocks are the ones found in standard Tetris games (i.e. blocks shaped like I, J, L, O, S, T, Z), as well as the 1x1 extra block ("N") that is added when playing the game at level 4.

For the boards, we have a 2D vector of cells that represents the actual board.  The board is 18 cells high and 11 cells wide, including the top 3 rows reserved for block rotation as specified in the assignment.  The dimensions of the board is stored as two integers: row and col.  Since the boards reperesent the players, they also display the data for the players, such as level, score, high score, and their next block.  At the beginning of the turn, the player's next block gets spawned and a new next block appears for them.  If the block cannot fit into the board when it spawns, the player loses, and the opposing player wins.  Then the block can be manipulated (see blocks sec) until the drop command is issued.  The drop command effectively ends the player's turn, and the board will check for any full lines on the board, which will then be cleared and have the appropriate score added.  If the player clears 2+ lines with a block, the player gets to impose a condition on their opponent: they may have the opponent's next block's weight increased by 2, they may blind the centre of the opponent's board for the next block, or they may choose the opponent's next block to force a disadvantageous situation or even an immediate loss.  Then the other player's turn starts, and the process repeats until someone loses, then the other player wins.

The cells within the board contain their state with regards to which block is currently occupying said cell.  They contain on whether it is occupied by a block, and if it is, the information of the block, such as its type, colour (for GraphicsDisplay), its spawn time (used to implement scoring bonuses for block clears), and its lifetime (in case we are to destroy the block if it remains after 10 turns, as specified in a question in biquadris.pdf).  The cells can swap properties with other cells, and they can also be set to a particular state, which is useful in block movements, rotations, and clearing lines.  // insert observer pattern here

The blocks are the standard blocks from the game Tetris, plus the additional blocks found in level 4.  They consist of 4 cells (1 for the N block) which carries the information for the block, as well as a timestamp on the block to distinguish it from other blocks for blocks-based scoring.  Of course, if a new block cannot be placed, then the player loses.

The implementation for the boards, cells, and displays employ the observer pattern, where the board is observed by the display for changes and the cells are observed by the board for changes.  //expand

The levels are implementations of the abstract Spawner class, which chooses the next block type depending on the level.  Level 0 allows a fixed sequence of blocks to be spawned by the input from a text file, while levels 1-4 are randomly generated with probabilities described in biquadris.pdf.  

The commands are entered from stdin of the terminal window where the games are played.  They are translated into a enumerated CommandType class, which is then passed to the block to manipulate it.

Actual UML of the project:
[insert UML here]

Design
We have incorporated the observer pattern in our program, with the boards, cells, and displays following the observer pattern.  This allows the blocks to be moved through the cells without much trouble.  /expand

Resilience to change
// insert stuff here

Answers to questions
The answers to the questions posed in the assignment have remained much the same as we had been incorporating the aspects of the questions in the program.

__Q1.__ How could you design your system (or modify your existing design) to allow for some
generated blocks to disappear from the screen if not cleared before 10 more blocks have fallen?
Could the generation of such blocks be easily confined to more advanced levels?

The easiest thing to do with regards to making old blocks disappear is to implement a "timestamp" for each block, where the "time" is incremented after each block falls.  Then the cells are checked for time each time a block falls, and if the current time > cell's timestamp + 10 then the remaining cells of the block disappears.  _(clarify this part)_ The generation of such blocks can be confined to more advanced levels, since this feature can be enabled or disabled with another conditional check on level, so this can be restricted to higher levels.

__Q2.__ How could you design your program to accommodate the possibility of introducing
additional levels into the system, with minimum recompilation?

Per our implementation, we can make a new `Spawner` object that has different block spawn distributions, as well as any other challenges for the player at higher levels.

__Q3.__ How could you design your program to allow for multiple effects to applied simultaneously? What if we invented more kinds of effects? Can you prevent your program from having
one else-branch for every possible combination?

For visual effects such as `blind`, it can be implemented in the overridden `<<` operator before being printed to `stdout` or loaded graphically in a XWindows window, and can be done in conjunction with other visual effects.  For block effects such as `heavy`, additional fields in `Block`s or `Cell`s can be added to support those new effects.  Since the two do not interfere with each other, those can be applied simultaneously.  _(how to not make more cond branches)_

__Q4.__ How could you design your system to accommodate the addition of new command
names, or changes to existing command names, with minimal changes to source and minimal
recompilation? (We acknowledge, of course, that adding a new command probably means adding
a new feature, which can mean adding a non-trivial amount of code.) How difficult would it be to
adapt your system to support a command whereby a user could rename existing commands (e.g.
something like rename counterclockwise cc)? How might you support a “macro” language,
which would allow you to give a name to a sequence of commands? Keep in mind the effect that
all of these features would have on the available shortcuts for existing command names.

We can encapsulate the different command types in an enumerator class and we can map strings to commands so that even if the command string is different the command will remain functionally the same, and existing commands can be added and removed with ease.  

```
processor(cmd: string) -> CommandType
```
We write a function that receives string and converts it into a CommandType by matching the given string and keys of the map we mentioned above. If the given string a longest and proper prefix of key, then return that correpsonding CommandType. If nothing is matched, we `throw` and catch it as appropriate.

For renaming, we simply delete the previous key and replace it with the new command string, but maps it to the same CommandType.

For "macros", we first define a keyword that will invoke the macro feature, just like `#define int float` in C. then we take in a name, then we take in the rest of the sequence until another keyword, say `#enddefine`, is got. we create a map that maps this "name" as string to that sequence of commands as a whole string. when we want to use this definition, we create an `stringstream` that acts similar to `cin`, but reads things from that corresponding string.

Extra Credit Features
The project features usage of STL containers for memory management.  This means that the program is devoid of both delete statements and memory leaks.

Final Questions