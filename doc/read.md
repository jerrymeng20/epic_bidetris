
The Epic Biquadris Project

Author: y3285wan, y58meng, rzbai
For: CS246 final project

# 1. Introduction
This is our Biquadris project, made by Yang Wang (y3285wan), Yanchen Meng (y58meng), and Rong Zhuo Bai (rzbai). It is a modified version of the classic video game Tetris, according to the assignment 5 of Fall 2019 CS246.

# 2. Overview
This project has many components to it.  The generic object components include the boards, the various block types (both abstract and concrete, and with the singular block required for Level 4), the cells within the boards, command types, and text and graphic displays.  When put together, the project has the text display and graphic display both attached as event listeners, each board representing the board of the players. The boards contain cells which hold the states of the blocks which allows the general gameplay and board state, as well as allowing scoring to be done. The blocks are the ones found in standard Tetris games (i.e. blocks shaped like I, J, L, O, S, T, Z), as well as the 1x1 extra block ("N") that is added when playing the game at level 4.

The specific game rules and types of inputs can be found in the assignment file, while parts not mentioned there will be introduced in Section 6.

# 3. Design

## 3.1 Overview

By strictly sticking with the project guidelines and the principles of OOP the generic project components include _abstract classes_ `observer` and `subject`, which provide the base methods of interactions between each parts, and _implementation classes_ such as 
* Gameplay components, the `GameSession` and the `Board` that manipulates a game and serve for general purposes.
* Game unit components, the `Cell` and the `Block`. In particular, we have 7 kinds of dropped blocks, I, J, L, O, S, T, Z (as found in standard Tetris game), and an N block that only works in some specific levels.
* Leveling components, the `Spawner` which is embedded to each game. We have 5 levels differing in difficulty.
* Info communicating widgets like `CellInfo`
* The displayed contents are manipulated using `TextDisplay` and etc

By isolating responsibilities we could reduce coupling and be able to work independently on modules. It is very lucky we convoyed the general class designs we created last week.

## 3.2 General designing

We used observer pattern, factory pattern and others to minimize the coupling between algorithms and displays and between boards and blocks. For example, modifying display does not require further modification of board because the communication between them is mostly controlled by a single "agent", namely a structure containing the message which can potentially affect the displayed content. This way the board does not explicitly calls display. Similar rule applies for other components, which can be found in the following sections.

We have default configuration files to store all the general settings of the program, such as the size of a game board. In the implementation, we use constants like `MAX_COL` to represent to width of a game board. In this way, once we want to change this into something else, only one change in the configuration is needed. For simplicity, we will denote 11 for columns and 18 for rows.

We could provide an entry to the game that will be responsible for assembling all the boards, levels, etc together to have an actual gaming session.

## 3.3 The program entry

### 3.3.1 `class GameSession`

This is the interaction interface provided to user to initialize a game, give commands, and execute commands turn-wise. This class scans user's input via an undetermined input stream (that is, variable), recognizes it and executes the corresponding action for the game board. All the interactions between a `main` function with a game board will go through this class.

a major challenge is to implement the command scanning. For this part, we used a `std::map` of strings and `CommandTypes` (an enumeration identifying different sorts of commands) for the game session (called a translation table). the commanding process mainly consists of two parts:
* calls `CommandStructure scanCommand();`. This will return a structure containing the command type and the provided arguments. There are two kinds of command-recognition:
    1. direct full-match. the user's input can be found in the translation table.
    2. indirect match. we attempt to see if the given input is a proper prefix of some entries in the translation table by calling the library function. Then we will have a `prefix-whole word` matching, we will use the whole word to get the command type in the translation.
* calls `bool useCommand(CommandStructure &cs);` to execute the command based on arguments scanned (if any).

In some special cases such as special ability session, similar process will be reused for the additional prompt. The process will repeat over and over again between two players until one wins.

## 3.4 Scenes behind
Based on the single-responsibility principle, the board and the blocks will only move keep track of players and move blocks. They do not need to care about how to display them in the front. This is why the title says "hehind".

### 3.4.1 `class Board`
The board has an 11x18 matrix containing cells (see section 3.4.2), including the top 3 rows reserved for block rotation. As a board represent a player here, it also contains a structure `PlayerInfo`, keeping track of information such as level, score, next block and so on. This is convenient because when on change, we only send this package to the displaying client, which will then be responsible for drawing them.

For each turn, the `spawn` will be activated to generate a new block on the top left as well as predict the next block (written into player info).

If the block cannot fit into the board when it spawns, the player loses, and the opposing player wins, which will be detected by `GameSession` by using `isLost` method. Then the block can be manipulated until a drop command is issued and sent from `GameSession`. The drop command effectively ends the player's turn, and the board will check for any full lines on the board, which will then be cleared and reset to empty cells. If the player clears more than lines with a block, the player gets to impose a negative effect on their opponent. Such information will also be detected by `GameSession`, thus the main function will know it is time to proceed to next player's turn.

The block-eliminating process is interesting. Since additional scores will be calculated based on if there is a _whole block_ killed, we would need to set each spawned block unique. Once a block (manipulating 4 cells) gets spawned, all of its 4 members will be given a "identification number", making them unique from other cells. During the eliminating process, we check whether this identification number exists in all cells, if not, that means all cells that used to compose this block is killed, and we are successful. Here we use Unix time in milliseconds when the blocked is spawned as the ID. We so have a 1 ms delay before each spawning to ensure this works.

The board cannot sole finish the task, so it has to accompany with its elements.

### 3.4.2 `class Cell`
The fundamental unit of the game. Each `Cell` object belongs to the board, and has attributes such as "type" (representing the type of block occupying it), "ID", and row/col numbers. Each cell can also create an info package, called `CellInfo` based on its current status. So the communication between cells and displays will be conducted using cell info, in which displaying clients will update the layout based on this information.

All cells on the board last for the whole game. They are not replaced by a newer object, but instead refreshed into a new status (example: occupied by J -> empty), or swapped with another one cell. This is described more clearly is Section 3.5.1.

## 3.5 Factories and packaging
A factory pattern must be employed to be able to spawn different kinds of objects but inherited from one common ancestor.

Different from the previous plan, we packaged several classes by grouping different subclasses into one, so the programmer does not need to worry about which type of pointer they have to use, for example, in the past, we have to store an Level4 object in a Level (superclass) pointer, now we only need to store a Level object with type 4 in the same level pointer.

### 3.5.1 `class GroupedCellsCursor` aka `class Block`
This class packages eight block type classes: `_BlockI`, `_BlockJ`, ..., `_BlockZ`, `_BlockN` inherited from an abstract interface `_Block` to achieve factory-like-spawning.

We defined base method `_movement` and `__movement` (details in src/block/) for the interface `_Block`, which can move the 4 cells into a specific location on the board (cell matrix), for example
```cpp
bool _Block::moveDown() {
     // returns false if the move is not successful
    return _movement({1,1,1,1}, {0,0,0,0}, orientation);
}
```
defines a downward move, where `orientation` means the block's orientation after move, in this case, the move does not alter the orientation. This generic method is used for translational movement and rotational movement. This method provided in the base class `_Block` is extremely useful because for its subclasses, when we need to consider special movement (like a rotation of an L block), we only need one line of (r-value) vector of displacements and all things can be done safely.

The movement of a block is grouped by 4 cells. This class will directly manipulate the game board as an iterator, 4 cursors at the same time. When a movement is needed (ie the 4 cursors _iterate_ to the next element), the swapping idiom is used to swap information between 8 associated cells (or less, if there is overlapping), then move the cursors to the target cells. By doing this, we do not kill/spawn cells, thus not worrying about re-registering subject-observer relations.

Of course, programmers do not need to know this, because all classes are packed into this single class:
```cpp
// spawning an L block at (3,0) to the matrix called theCell
auto bl = new Block(theCell, 3, 0, BlockType::L, weight);
// attempts to move down
bool successful = bl->moveDown();
```

### 3.5.2 `class LevelWrapper`
This class packs classes `Level0`, ..., `Level4` inherited from an interface `Spawner`. It is easily used like this:
```cpp
// level 0 with provided sequence file
auto spawner = new LevelWrapper (0, playerInfo.seqfile);
// predict the next block type
BlockType nextBlock = spawner->nextBlock(); // BlockType is enum
```

Based on the level in the player's info, the spawner may or may not be altered every turn. This effectively convoyed the factory method pattern, where generating blocks can be made painless.

Inside the generation, we implement the randomness by random number generator, different for each level.

## 3.6 Messenger-ization
To communicate between the game logic itself and the displayed contents or even between classes, a bridge must be built. A nice example is the info classes mentioned in previous sections, `CellInfo` and `PlayerInfo`. Letting classes message each other themselves, not by human, makes subject-observer pattern possible.

### 3.6.1 `class TextDisplay`
The class is solely responsible for printing the _board_ into an text output stream. It is inherited from two template classes, `Observer<PlayerInfo>` and `Observer<CellInfo>` thus being able to receive two kinds of information sent by two kinds of senders. That is, this class has two `notify` methods, each responsible for one info type. This makes the class truly capable to handle all displaying tasks. In each info package, there is also the "sender" field so we can distinguish who sent the information so that we can update the display just for that player.

An 2D matrix of characters is used to store the displayed content. We overloaded the `<<` operator so that it can be printed to the output stream.

### 3.6.2 `class GraphicDisplay`
The working of this class is similar to text display, but there is one primary difference - it is slower by its natural circumstances. To deal with performance issues, we introduced "part redraw", that is, we only redraw part of the screen when receiving messages from subjects, instead of redrawing the whole screen. For example, when a block is moving, we only render again the area close to that block, letting alone the other parts.

One other issue is that if too many notifications sent to the graphic, the graphic will redraw for each, slowing down the process. We thus given up some realizations of the observer pattern. We limit the amount of infos sent by subjects by, in some place, directly letting the board tell the graphic to update at some point, instead of letting cells to send infos to graphics individually (that will be 11*18 calls).


# 4. Resilience to change
Our program supports possibilities to changes in various ways due to the low coupling of modules. As discussed in Section 3, most of our programs either interact using agents like `Info`, or by a packaged class like `LevelWrapper`. Hence the interfaces exposed between classes are relatively of less amount. In this way, minimal coupling can be achieved. Also, since our tasks are separated so aimfully, and each class is only responsible for one purpose, we have high cohesion. For example, the `GameSession` only reads and _sends_ execution signals to board. In fact, it does not even read from stdin, it just recognizes from a buffer passed to it in the constructor.

## 4.1 Examples
We give some examples regarding possible changes.

### 4.1.2 Changing config
We placed the common settings like board size in a configuration file. So it is very simple to change the game board to 100x100 in one click, instead of going over all the codes to change attributes separately.

### 4.1.3 Changing dialogue
Long dialogues that we need to print out are not scattered across every implementation file. Instead, they are stored in a file called "dialogue.h" with a namespace `diag`. Even non-programmers can understand these dialogues and change them as will.

### 4.1.4 Adding a new block type
Making a new class, inherited from `_Block` and packaged by `Block` is easy. In fact, most of the low level work is done by the superclass, we only need to consider two aspects: what does the block look like (its position layout) and how they move. To create a new Block class, say `MyI`, its constructor is very simple:
```cpp
_BlockMyI::_BlockMyI(CellGrid &alls_,
                int r, int c,
                unsigned weight_)
    :_Block{
        alls_, weight_, BlockType::MyI, Colour::Cyan,
        {r,r,r,r}, {c,c+1,c+2,c+3} // the only line that matters
    } // position of initial 4-cell configuration
{}
// this block cannot be rotated!
bool _BlockMyI::rotateCW() {
    return true;
}
```
By just writing this method, you have already `moveLeft`, `drop`, `atBottom` and so on, and with `rotateCW` overridden.

### 4.1.5 Adding commands
Since commands only exist in `GameSession`, programmers are only required to modify this single class. They just need to figure out what is the name and what it does. By filling out the map described in 3.3.1 (adding a pair of string and command type) and fill in `useCommand` for that case, it all done. Now that new command has number-prefix-notation, abbreviated forms just like others. Also, since only one class is changed, the recompilation is reduced.

### 4.1.6 Redirect IO
By the high-cohesion principle, even `GameSession` and `TextDisplay` do not print and get texts themselves. The `TextDisplay` does not display text, but the overloaded operator does. All the IO streams can be initialized and switched with the provided ones, not just `cin`. For example, the inputs feed into `GameSession` can be changed arbitrarily, even something got from Internet using a `Boost` websocket.



# 5. Answers to questions from project

### 5.1.1
__How__ could you modify your existing design to allow for some
generated blocks to disappear from the screen if not cleared before 10 more blocks have fallen?  
We will add an attribute "lifeTime", parallel with "ID" described in 3.4.2. Every turn this attribute will be incremented by one. Now the cell can also have a method called "self-eliminate", that also runs every turn, when that number is 10, this method refreshes the current cell into an empty cell.  
__Could__ the generation of such blocks be easily confined to more advanced levels?  
Add an attribute called "spawnLevel" representing the level of the cell, the method mentioned above only works when the level meets requirements

### 5.1.2 
__How__ could you design your program to accommodate the possibility of introducing
additional levels into the system, with minimum recompilation?  
we can make a new `LevelX` class inherited from `Spawner` as in 3.5.2 that has different block spawn distributions. In this case only `LevelX.cc`, `levelwrapper.cc`, `board.cc` are (re)compiled.

### 5.1.3
__How__ could you design your program to allow for multiple effects to applied simultaneously? What if we invented more kinds of effects?  
For effects acting on a player him/herself like "blind", it will be packaged inside `PlayerInfo` and passed to the display client. We can have different message fields to achieve different effects simultaneously. For effects about Board/Blocks, there is an inherited, decorated object, say "HeavyBlock" that overwrites part of the movement method of a native Block. If we have more effects, we keep decorating.  
__Can__ you prevent your program from having one else-branch for every possible combination?  
we make decorators for blocks so all effects will be condensed inside _one_ method (which may chain other methods).

### 5.1.4
__How__ could you design your system to accommodate the addition of new command
names, or changes to existing command names, with minimal changes to source and minimal recompilation?  
See Section 4.1.5  
__How__ difficult would it be to
adapt your system to support a command whereby a user could rename existing commands?  
See Section 6.1.1 and 6.1.2.  
__How__ might you support a “macro” language,
which would allow you to give a name to a sequence of commands?  
See Section 6.1.3.

# 6. Extra credit features
### 6.1.1 Aliasing command
Using the following syntax during a game enables players to give an alias for an existing command:
```
alias [1.name you want] [2.target command]
```
When this is triggered, the translation table described in 3.3.1 will have an extra key-binding with the string `[1]` and the command type that `[2]` maps to. 

### 6.1.2 Renaming command
Using the following syntax during a game enables players to rename an existing command:
```
rename [1.command] [2.new name]
```
Same as aliasing, but also deletes the original entry.

### 6.1.3 Sequencing
Using the following syntax during a game defines a sequence
```
defseq [1.name] [2.your sequence .....
```
This reads until newline. When command "defseq" is invoked, the parts 1. command name and 2. the content of the sequence is read and packaged into a `CommandStructure`  (see 3.3.1 for detail). A secondary translation table is present in `GameSession` with a `string-string` pair, the first is the macro name, second is its content. When a name is read, the class will also look up in this table, if present, then the following sequence will be converted into a `stringstream` and passed to the `GameSession`, which reads from a given stream. When that stringstream is exhausted, the input stream is restored to the original one.

Issuing this will run the sequence of commands for both players
```
useseq [1.name]
```

### 6.1.4 Player savedata
The highest scores will be stored locally in `savedata/`, relative to the path of the program. When entering the game, the player will be notified about the local disk storage. When a new player (say with name "Alice") enters the game, a query will be generated containing her info. When the player's score is higher than the highest history score, the entry will be updated and saved.

If Alice runs the game again, she can retain her data.

### 6.1.5 Help info
Remember passing flag `-help` to the game executable displays a help command regarding usage of command arguments, and inputting `help` in the game triggers a help session.



# 7. Final questions
### 7.1.1
__What__ lessons did this project teach you about developing software in teams?  
We learned primarily two key things:  
1. The structure of the program must be determined before we do any coding. The UML diagrams are also important. Planning early not only can help us understanding the demands of clients, but also let us write more targeted and coupling-free modules. By having a good design we can separate our tasks early. For each of us, we only need to pay attention to the modules that we are responsible for and do not need to worry about other people so that we can be more concentrated and write better modules.
2. The communication is very important among our collaboration. Doing so can significantly decrease misunderstanding among developers so that the planned strategy does not end up in a mess where people write incompatible codes.

__What__ would you have done differently if you had the chance to start over?  
Our Block and Board does not convoy the decorator pattern very much so we ended up in some conditional checks when special actions are triggered. If there were a chance, our Block class could be decorated again to support more different kinds of special attributes.  
Also we would attempt to not depend on `XWindow` provided by the assignment because the colour scheme and layouts did not look very surprising to us. We would try learning the basics of XLib so that we could do the good things we wanted to see.

# 8. Attachments
*   updated UML
