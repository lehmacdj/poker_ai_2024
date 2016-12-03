//
// Cards held by a player
//

#ifndef POKERBOT_HOLE_H
#define POKERBOT_HOLE_H
#include "Card.h"

#import <vector>

class Hole {
public:
    Hole();
    Hole(Card card1, Card card2);
    Hole(Card cards[]);

    string toString();
    Card *getCards();
private:
    Card c1;
    Card c2;
};


#endif //POKERBOT_HAND_H
