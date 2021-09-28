

#ifndef _CONFIG_H_
#define _CONFIG_H_

/**
 * this is the global constant / config area
 * please include this file whenever you need to access global
 * settings
 */


/**
* This is for the board (2d matrix of cells) NOT DISPLAY MATRIX!
*/
#define MAX_ROW           18          // =. The rows of the cells
#define MAX_PLAYABLE_ROW  15          // +. This is the bottom 15 rows!
#define RESERV_ROW        3           // +. This is the top 3 rows, where new blocks are spawned below it

/**
 * Below variables are for textdisplay only
 */
#define TOP               5           // the first 4 rows showing player information
#define MAINBOARD         15          // the gameplay area
#define BOTTOM            4           // the bottom 4 rows showing nect block
#define TOTAL             24          // total number of rows in textdisplay

#define MAX_COL           11          // The cols of the cell

/**
 * player info storage settings
 */
#define PLAYERINFO_STORAGE_PATH "./savedata/hs.savedata"


#endif
