//basic Card class

#ifndef POKERBOT_CARD_H
#define POKERBOT_CARD_H
#include <iostream>
using namespace std;

class Card {
public:
    Card();
    Card(int rank, int suit);
    Card(char rank, int suit);
    int getRank();
    int getSuit();
    string toString();

private:
    int rank;
    int suit;
};

bool operator ==( Card c1, Card c2);

#endif //POKERBOT_CARD_H
