//
//
//

#ifndef POKERBOT_HAND_H
#define POKERBOT_HAND_H

#import "Board.h"
#include <math.h>


class Hand {
public:
    Hand(Hole h, Board b);
    long bestHandStrength();
    Card *bestHand();
    Board getBoard();
    Hole getHole();
    bool flushDraw();
    bool openEnder();

private:
    long bestStrength;
    Card *best;
    Hole holecards;
    Board board;
};


#endif //POKERBOT_HAND_H
