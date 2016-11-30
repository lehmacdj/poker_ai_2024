//
// Created by Jonathan Ho on 11/28/16.
//

#include "Hole.h"

Hole::Hole(){
    c1 = Card();
    c2 = Card();
}

Hole::Hole(Card card1, Card card2) {
    c1 = card1;
    c2 = card2;
}

Card *Hole::getCards(){
    Card arr [] = {c1, c2};
    return arr;
}
string Hole::toString(){
    string ret = c1.toString() + c2.toString();
    return ret;
}
