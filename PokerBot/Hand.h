//
//
//

#ifndef POKERBOT_HAND_H
#define POKERBOT_HAND_H

#include "Board.h"
#include "Hole.h"


class Hand {
public:
    Hand(Hole h, Board b);
    bool hasPair();
    bool hasOnlyPair();
    bool hasTrips();
    bool hasTwoPair();
    bool hasQuads();
    bool hasFlush();
    bool hasStraight();
private:
    Hole holecards;
    Board board;
};


#endif //POKERBOT_HAND_H
