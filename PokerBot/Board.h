//
// The cards dealt onto the board. Will contain information about texture
//

#ifndef POKERBOT_BOARD_H
#define POKERBOT_BOARD_H
#import "Card.h"

class Board {
public:
    Board(Card b[]);
    Card* getBoard();
    bool fourStraight();
    bool fiveStraight();
    bool threeFlush();
    bool fourFlush();
    bool paired();
    bool doublePaired();
    bool tripped();
    bool quadded();

private:
    Card board [];
    int street; //0, 1, 2
};


#endif //POKERBOT_BOARD_H
