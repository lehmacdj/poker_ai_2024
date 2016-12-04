#include "Range.h"
#include "PokerAI.h"
#include "stdio.h"
Range currentRange;



int max(int a, int b){
    return a > b ? a : b;
}

double potPercentage(double SPR, int street){
    if(street == 1) {
        return (sqrt(2 * SPR + 1) - 1) / 2;
    }else{
        return (cbrt(2 * SPR + 1) - 1) / 2;
    }
}

int betSize(double SPR, int street, int stackEff, int amountToCall, int pot){
    if(SPR < 1){
        return stackEff + amountToCall;
    }
    switch(street){
        case 1 :
            if(SPR < 4){
                return (int) ((pot + amountToCall) * potPercentage(SPR, street)) + amountToCall;
            }else if(SPR < 13){
                return (int) ((pot + amountToCall) * potPercentage(SPR, street)) + amountToCall;
            }
        case 2 :
            if(SPR < 4){
                return (int) ((pot + amountToCall) * potPercentage(SPR, street)) + amountToCall;
            }
        default :
            return (int) ((pot + amountToCall) * 0.76) + amountToCall;
    }
}

Card* convert_card_array(card* c, int size) {
    Card* cards = new Card[size];
    for (int i = 0; i < size; i++) {
        cards[i] = Card(c[i]);
    }
    return cards;
}

int nextMove(bool dealer, double pot, double *stack, double amountToCall, card* hand, card* b){
    Board board = Board(convert_card_array(b, 5));
    int street = board.getStreet();
    Hole hole = Hole(convert_card_array(hand, 2));
    int myStack;
    int vilStack;
    if(dealer){
        myStack = (int)stack[0];
        vilStack = (int)stack[1];
    }else{
        myStack = (int)stack[1];
        vilStack = (int)stack[0];
    }
    //new Hand
    if((dealer && pot == 15) || (!dealer && pot - amountToCall == 10)){
        currentRange = Range();
    }

    pair<Range,Range> ranges = currentRange.facingBet((int)amountToCall,board,(int)pot);

    int stackEff = (int)max(myStack - amountToCall, vilStack);
    double SPR = (double)stackEff / (pot + amountToCall);
    if (((Range) ranges.first).contains(hole)){
        //bet or raise
        currentRange = ranges.first;
        return betSize(SPR,street,stackEff,(int)amountToCall,(int)pot);
    }else if (((Range) ranges.second).contains(hole)){
        currentRange = ranges.second;
        return (int)amountToCall;
    }else{
        return -1;
    }
}

int winningHand(card* hand1, card* hand2, card* board){
    currentBoard = Board(convert_card_array(board, 5));
    Hole h1 = Hole(convert_card_array(hand1, 2));
    Hole h2 = Hole(convert_card_array(hand2, 2));
    bool h_1 = compareHoles(h1,h2);
    bool h_2 = compareHoles(h2,h1);
    if(h_1){
        return 0;
    }else if(h_2){
        return 1;
    }else{
        return -1;
    }
}

int main(){
    double stack[] = {995, 990};
    double pot = 15;
    double amountToCall = 5;
    bool dealer = true;
    Card hand[] = {Card(10,3), Card(10,2)};
    Card *b;
    b = new Card[5];
    // cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
    stack[0] = 980;
    stack[0] = 980;
    pot = 40;
    amountToCall = 0;
    b[0] = Card(9,2);
    b[1] = Card(7,2);
    b[2] = Card(2,1);
    // cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
}
