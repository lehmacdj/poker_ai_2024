//
// Created by Jonathan Ho on 11/28/16.
//

#include "Hole.h"
#include "PokerAI.h"

Hole::Hole(){
    c1 = Card();
    c2 = Card();
}

Hole::Hole(Card card1, Card card2) {
    c1 = card1;
    c2 = card2;
}

vector<Card> Hole::getCards(){
    vector<Card> r;
    r.push_back(c1);
    r.push_back(c2);
    return r;
}
string Hole::toString(){
    string ret = c1.toString() + c2.toString();
    return ret;
}

Hole::Hole(vector<Card> cards) {
    c1 = cards[0];
    c2 = cards[1];
}

