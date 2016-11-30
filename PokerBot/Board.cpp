//
// Created by Jonathan Ho on 11/28/16.
//

#include "Board.h"


Board::Board(Card b[]){
    board = b;
}
Card *Board::getBoard(){
    Card arr[street+3];
    for (int i = 0; i < street + 3; i++){
        arr[i] = board[i];
    }
    return arr;
}

bool Board::quadded() {
    return false;
}

bool Board::fourFlush() {
    return false;
}

bool Board::threeFlush() {
    return false;
}

bool Board::tripped() {
    return false;
}

bool Board::doublePaired() {
    return false;
}

bool Board::paired() {
    return false;
}

bool Board::fiveStraight() {
    return false;
}

bool Board::fourStraight() {
    return false;
}

