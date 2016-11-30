//basic Card class

#ifndef POKERBOT_CARD_H
#define POKERBOT_CARD_H
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
#include <stdexcept>
#include <string>
using std::string;

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

bool operator ==(const Card& c1, const Card& c2){
    return (c1.rank == c2.rank && c1.suit == c2.suit);
}


#endif //POKERBOT_CARD_H
