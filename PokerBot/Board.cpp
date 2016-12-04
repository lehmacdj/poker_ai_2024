//
// Created by Jonathan Ho on 11/28/16.
//

#include "Board.h"


Board::Board(vector <Card> b){
    board = b;
}
vector<Card> Board::getBoard(){
    return board;
}

bool Board::contains(int r){
    for(int i = 0; i < 5; i++){
        if(r == board[i].getRank()){
            return true;
        }
    }
    return false;
}

int Board::getStreet() {
    return street;
}

Board::Board() {

}



Board::Board(Card *b) {
    street = 3;
    if(b[4].getRank() == 0){
        street = 2;
    }
    if(b[3].getRank() == 0){
        street = 1;
    }
    if(b[2].getRank() == 0){
        street = 0;
    }

    if(street != 0){
        for(int i = 0; i < street + 2; i++){
            board.push_back(b[i]);
        }
    }else{
    }

}

