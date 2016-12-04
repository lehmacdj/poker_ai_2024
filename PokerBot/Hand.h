//
//
//

#ifndef POKERBOT_HAND_H
#define POKERBOT_HAND_H

#import "Board.h"
#include <math.h>


class Hand {
public:
    //Creates a Hand object and calculates the best hand possible and it's strength value
    Hand();
    Hand(Hole h, Board *b);
    long bestHandStrength();
    vector<Card> bestHand();
    Board getBoard();
    Hole getHole();
    bool flushDraw();
    bool openEnder();

private:
    long bestStrength;
    vector<Card> best;
    Hole holecards;
    Board board;
};

//returns an int that is strictly larger than weaker hands and strictly smaller than stronger hands.
long handStrength(Card c1, Card c2, Card c3, Card c4, Card c5);
void sortHand(vector<Hand> arr);
//finds the best possible five card hand and returns a pair with first value Card* to an array with the five best cards and
//second value the long hand strength of the hand
pair<vector<Card>,long> calcBestStrength(Hole hole, Board board);

#endif //POKERBOT_HAND_H
