## condensed key features to support

### Block 
I, J, L, O, S, Z, T (inherit from base)  
__done__

supports translation(left, down, right) and rotation (clockwise, counterclockwise)  
__done__

### Board
11 col, 15 row, additional 3 row for rotate  
__done__

if a row is full, remove row and other rows above fall down  
__done except scoring__

#### special actions
*   blind other player
*   heavy other's blocks
*   force choose other player's block
__done__

### Displaying
has level, score, playing area, next block  
__done__

#### scoring
(level when block spawned + number of lines cleared) ^ 2
+ (level when cleared block spawned + 1) ^ 2
__part__

### Levels
5 levels (inherit from base)  
__done__

### commands
(/**@class*/)
*   `left` __done__
*   `right` __done__
*   `down` __done__
*   `clockwise` __done__
*   `counterclockwise` __done__
*   `drop` (to proceed to next turn) __done__
*   `levelup` __done__
*   `leveldown` __done__
*   `norandom [file]` __done__
*   `random` __done__
*   `sequence file` __done__
*   `I`, `J`, `L`, ... __done__
*   `restart` __done__

should also support abbreviated forms (e.g. lef, ri, do, cl, co, etc.) __done__

also needs to support numerical prefixes for multiplied commands __done__

### args
(/**@main*/)
*   `-text`  __done__
*   `-seed [seed]` __done__
*   `-scriptfile1 [file]` __done__
*   `-scriptfile2 [file]` __done__
*   `startlevel [n]` __done__
