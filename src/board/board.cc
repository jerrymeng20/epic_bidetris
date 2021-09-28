#include "board.h"
#include "../query/player.h"

using namespace std;



unique_ptr<Block> Board::_getBl(BlockType ty) {
    int weight = playerInfo.level >= 3 ? 1 : 0;
    return isHeavied ? make_unique<BlockHeavy>(theCell, 3, 0, ty, weight)
                        : make_unique<Block>(theCell, 3, 0, ty, weight);
}


Board::Board(TextDisplay *td, GraphicDisplay *gd, PlayerInfo playerInfo, int r, int c, bool graph):
    td{td}, gd{gd}, row{r}, col{c}, graph{graph}, playerInfo{playerInfo}{
    if (playerInfo.level == 0) {
        // provide string for file name
        spawner = make_unique<LevelWrapper>(0, playerInfo.seqfile);
    } else {
        spawner = make_unique<LevelWrapper>(playerInfo.level);
    }
    init();
}

Block *Board::getCurrentBlock() {
    return currentBlock.get();
}

void Board::setCurrentBlock(BlockType ty) {
    int weight = playerInfo.level >= 3 ? 1 : 0;
    currentBlock->prepareDeletion();
    currentBlock = _getBl(ty);
    // replaces old spawned block vector with newly spawned block which is guaranteed to be at the back
    blocksRemaining.pop_back();
    blocksRemaining.emplace_back(pair<uint64_t, int>{currentBlock->getTimeStamp(), playerInfo.level});

}


//first index is row number, second is column number
//we assume rows 0-2 are the buffer rows, and that the top row is row 3
//columns
void Board::init(){
    for(int i=0; i<row; i++){
        vector<Cell> temp{};
        for(int j=0; j<col; j++){
            temp.emplace_back(Cell(playerInfo.name, i, j, BlockType::NOTYPE, Colour::NoColour, 0));
            temp[j].attach(td);
            if (gd) temp[j].attach(gd);
        }
        theCell.emplace_back(temp);
    }

    // initialize blocks
    playerInfo.nextBlock = spawner->nextBlock();
    spawn();

    this->attach(td);
    if (gd) this->attach(gd);

    this->notifyObservers();
}


void Board::levelUp() {
    if (playerInfo.level == 4) return;
    playerInfo.level += 1;
    spawner = make_unique<LevelWrapper>(playerInfo.level);
    notifyObservers();
}

void Board::levelDown() {
    if (playerInfo.level == 0) return;
    notcleared = 0;
    playerInfo.level -= 1;
    if (playerInfo.level == 0) {
        spawner = make_unique<LevelWrapper>(0, playerInfo.seqfile);
    } else {
        spawner = make_unique<LevelWrapper>(playerInfo.level);
    }
    notifyObservers();
}


bool Board::level3_4_NoRandom(string filename) {
    if (!(playerInfo.level == 3 || playerInfo.level == 4)) return false;
    // playerinfo's level not changed
    try {
        spawner = make_unique<LevelWrapper>(0, filename);
    } catch (const util::SequenceFileNotExist &err) {
        return false;
    }
    return true;
}


bool Board::level3_4_Random() {
    if (!(playerInfo.level == 3 || playerInfo.level == 4)) return false;
    spawner = make_unique<LevelWrapper>(playerInfo.level);
    return true;
}



//note that the game is lost only if the new block can't be placed at the starting position (i.e. top left corner of the board) (see piazza @2378)
bool Board::isLost(){
    currentBlock->isLost();
}

//checks from top down if there are full rows
// if the row is full, pull the row above down to the current row, and repeat until all rows have been pulled down by 1
//then repeat for any rows below it which may be full and can pull the rest of the board down
void Board::scan(){
    int linesCleared = 0;
    int addedScore = 0;
    for(int i=0; i<row; i++){
        bool isFull = true;
        for(int j=0; j<col; j++){
            if(!theCell[i][j].isOccupied()){
                isFull = false;
                break;
            }
        }
        if(isFull){ // if the row is full, pull the row above down to the current row, and repeat until all rows have been pulled down by 1
            ++linesCleared;
            // puts the row of cells above the play area...
            for(int k=i; k>2; k--){ //this should only go up to the top row of the play area, where it ends by top row being replaced by one of the buffer rows
                for(int j=0; j<col; j++){
                    theCell[k][j].swapWith(theCell[k-1][j]);
                }
            }
            // and then turns the row into empty row
            for(int j=0; j<col; j++){
                theCell[2][j].refresh(BlockType::NOTYPE, Colour::NoColour, false, 0UL);
            }
        }
    }
    // TODO
    // update score
    if(linesCleared > 0) { // player only gets points for lines cleared, and none otherwise
        //todo: fix score bug - blonk clear scoring issues
        // OOOOOI scores 4+9 but should score 4+5
        // iterates through the blocksRemaining vector to see if any of the remaining blocks are gone for good
        // also ensures that the iterator actually iterates through everything 
        for(int k=blocksRemaining.size()-1; k>=0; k--){
            bool hasCellsLeft = false; // suppose that the block is fully gone
            // then there shouldn't have any cells that are the remnant of the block
            // so we iterate through the board to find such cells
            for(int l=3; l<row; l++){
                auto times = blocksRemaining[k].first;
                if (find_if(theCell[l].begin(), theCell[l].end(), [times](Cell &p){
                    return p.getInfo().timeStamp == times;
                }) != theCell[l].end()) {
                    hasCellsLeft = true;
                    //break;
                }
            }
            // and of course if we actually have none of those cells left that block is considered cleared and can be scored appropriately
            if(!hasCellsLeft){
                addedScore += (blocksRemaining[k].second + 1) * (blocksRemaining[k].second + 1);
                blocksRemaining.erase(blocksRemaining.begin() + k);
            }
        }
        addedScore += (linesCleared + playerInfo.level) * (linesCleared + playerInfo.level);
        playerInfo.score += addedScore;
        if (playerInfo.score > playerInfo.hiScore){
            playerInfo.hiScore = playerInfo.score;
            updatePlayerHiScore(playerInfo.name, playerInfo.hiScore);
        }
    }

    // check if 5 turns of not clearing
    if (playerInfo.level >= 4) {
        if (linesCleared == 0) ++notcleared;
        if (notcleared == 5) {
            for (int i = row-1; i > -1; --i) {
                if (!theCell[i][col/2+1].isOccupied()) {
                    // spawn asterisk
                    theCell[i][col/2+1].refresh(BlockType::N, Colour::Brown, true, 0UL);
                    break;
                }
            }
            notcleared = 0;
        }
    }
    if (linesCleared >= 2) inSpecialAction = true;


    this->notifyObservers();
}

void Board::spawn(){
    currentBlock = _getBl(playerInfo.nextBlock);
    blocksRemaining.emplace_back(pair<uint64_t, int>{currentBlock->getTimeStamp(), playerInfo.level});

    playerInfo.nextBlock = spawner->nextBlock();

    this->notifyObservers();
}

// this works as if the block is dropped 
// so a command of "drop" ends this turn and calls this method
void Board::turnEnd(){
    currentBlock->drop();
    //blocksRemaining.push_back(pair<uint64_t, int>{currentBlock->getTimeStamp(), playerInfo.level}); //this shouldn't be duplicated
    scan();
    // implement this
    //otherBoard->newTurn();
    isTurnEnd = true;
    playerInfo.isBlind = false;
    isHeavied = false;

    this->notifyObservers();
}

void Board::newTurn(){
    isTurnEnd = false;
    inSpecialAction = false;
    updateCells();
    spawn();
}


PlayerInfo Board::getInfo(){
    return playerInfo;
}

PlayerInfo &Board::setInfo(){
    return playerInfo;
}

bool Board::getTurnEnd(){
    return isTurnEnd;
}


bool Board::inSpecialAbSession() {
    return inSpecialAction;
}

void Board::updateCells(){
    for (auto n: theCell){
        for (auto m: n){
            m.notifyObservers();
        }
    }
}

