//
// The cards dealt onto the board. Will contain information about texture
//

#ifndef POKERBOT_BOARD_H
#define POKERBOT_BOARD_H
#import "Hole.h"

class Board {
public:
    Board();
    Board(vector <Card> b);
    Board(Card *b);
    vector<Card> getBoard();
    bool contains(int r);
    int getStreet();

private:
    vector<Card> board;
    int street; //0, 1, 2, 3
};


#endif //POKERBOT_BOARD_H
