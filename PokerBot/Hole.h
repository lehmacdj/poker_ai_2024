//
// Cards held by a player
//

#ifndef POKERBOT_HOLE_H
#define POKERBOT_HOLE_H
#include "Card.h"
#include "Range.h"
#include "Board.h"

#import <string>
using std::string;

class Hole {
public:
    Hole();
    Hole(Card card1, Card card2);
    string toString();
    Card *getCards();
private:
    Card c1;
    Card c2;
};

bool operator==(const Hole& h1, const Hole& h2){
    return (h1.c1 == h2.c1 && h1.c2 == h2.c2);
}

#endif //POKERBOT_HAND_H
