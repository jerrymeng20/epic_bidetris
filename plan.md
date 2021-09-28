# Plan of Attack
y58meng, y3285wan, rzbai

## Schedule of Tasks
Since we have a complete (preliminary) UML, we can create header files from the definitions in the UML. We first write our all `.cc` files with empty implementation (like if the method is `void` then we leave it blank with only two braces), this way we can easily get the game to run without having errors. We then implement specific implentations as follows:
1. We implement the commands and the boards on the command line.  This enables the basic input (from stdin) and output (related to class `TextDisplay`) interactions that allows debugging and testing of the game's main logic.
2. We should then individually finish the components we are repsonsible for, with communication.
3. We implement easier and basic parts first. IE level 0, no special actions, no rotating, no args, no blurred commands.
4. We will have a through test on this raw program .
5. Then after we have the basic functionalities running, we implement higher levels, more interactions, rotating and the UI.
6. We have another through test and we fill in the details in the documentations that we miss.
7. If time permits, we will start working on additional features such as supporting 4 players.


## Tasks for each group member
y3285wan: On the interactions of Blocks and Cells with the Board.

rzbai: Main function/class, the Board, CommandSection

y58meng: Displays, Levels (Spwaners), the `.h`file writting and empty implenmentations.

## Estimated time of completion
December 1st.

## Questions
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



