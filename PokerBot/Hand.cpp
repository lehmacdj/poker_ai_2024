//
// This stuff was taken from HW5, I'm going to change it for more useful information. Makes hands using a player's hole cards and whatever is currently on the board
//This is where we could implement Deuces.
//

#include "Hand.h"


bool Hand::hasPair(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    for (int i = 0; i < 4; i++){
        for (int j = i+1; j < 5; j++){
            if (h[i].getRank() == h[j].getRank()) {
                return true;
            }
        }
    }
    return false;
}

bool Hand::hasOnlyPair(){

    if (hasTrips()){
        return false;
    }
    else if (hasTwoPair()){
        return false;
    }else {
        std::vector<Card> h;
        for(Card c : (Card [])board.getBoard()){
            h.push_back(c);
        }
        for(Card c : (Card [])holecards.getCards()){
            h.push_back(c);
        }
        for (int i = 0; i < h.size()-1; i++) {
            for (int j = i + 1; j < h.size(); j++) {
                if (h[i].getRank() == h[j].getRank()) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool Hand::hasTrips(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    for (int i = 0; i < h.size()-2; i++){
        for (int j = i+1; j < h.size()-1; j++){
            for (int k = j + 1; k < h.size(); k++){
                if (h[i].getRank() == h[j].getRank() && h[i].getRank() == h[k].getRank()){
                    return true;
                }
            }
        }
    }
    return false;
}


bool Hand::hasTwoPair(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    if (hasTrips()) {
        return false;
    }
    bool one = false;
    for (int i = 0; i < h.size() - 1; i++){
        for (int j = i+1; j < h.size(); j++){
            if (h[i].getRank() == h[j].getRank()) {
                if (one) {
                    return true;
                } else {
                    one = true;
                }
            }
        }
    }
    return false;
}

bool Hand::hasQuads(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    for (int i = 0; i < h.size()-3; i++){
        for (int j = i+1; j < h.size()-2; j++){
            for (int k = j + 1; k < h.size()-1; k++){
                for (int l = k + 1; l < h.size(); l++){
                    if (h[i].getRank() == h[j].getRank() && h[i].getRank() == h[k].getRank() && h[i].getRank() == h[l].getRank()){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Hand::hasFlush(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    for (int i = 0; i < h.size()-4; i++){
        for (int j = i+1; j < h.size()-3; j++){
            for (int k = j + 1; k < h.size()-2; k++){
                for (int l = k + 1; l < h.size()-1; l++){
                    for(int m = l+1; m < h.size(); m++){
                        if (h[i].getSuit() == h[j].getSuit() && h[i].getSuit() == h[k].getSuit() && h[i].getSuit() == h[l].getSuit() && h[i].getSuit() == h[m].getSuit()){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Hand::hasStraight(){
    std::vector<Card> h;
    for(Card c : (Card [])board.getBoard()){
        h.push_back(c);
    }
    for(Card c : (Card [])holecards.getCards()){
        h.push_back(c);
    }
    if (hasPair()){
        return false;
    }
    for (int i = 0; i < h.size()-1; i++){
        for (int j = 0; j < h.size(); j++){
            int dif = abs(h[i].getRank() - h[j].getRank());
            if ( dif > 4){
                return false;
            }
        }
    }
    return true;
}

