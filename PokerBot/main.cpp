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

int nextMove(bool dealer, double pot, double *stack, double amountToCall, card* h, card *b){
    Card* ha = convert_card_array(h, 2);
    Card* bo = convert_card_array(b, 5);
    vector<Card> hand;
    hand.push_back(ha[0]);
    hand.push_back(ha[1]);
    Board board = Board(bo);
    int street = board.getStreet();
    Hole hole = Hole(hand);
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

    pair<Range,Range> ranges = currentRange.facingBet((int)amountToCall,&board,(int)pot);

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

int winningHand(card h1[], card h2[], card board[]){
    Card* ha1 = convert_card_array(h1, 2);
    Card* ha2 = convert_card_array(h2, 2);
    vector<Card> hand1;
    hand1.push_back(h1[0]);
    hand1.push_back(h1[1]);
    vector<Card> hand2;
    hand1.push_back(h2[0]);
    hand1.push_back(h2[1]);
    Board b = Board(convert_card_array(board, 5));
    Hole hole1 = Hole(hand1);
    Hole hole2 = Hole(hand2);
    Hand h_1 = Hand(hole1,&b);
    Hand h_2 = Hand(hole1,&b);
    long h1_strength = h_1.bestHandStrength();
    long h2_strength = h_2.bestHandStrength();
    if(h1_strength == h2_strength){
        return -1;
    }
    if(h1_strength > h2_strength){
        return 0;
    }else if(h2_strength > h1_strength){
        return 1;
    }else{
        return -1;
    }
}

// int main(){
//     double stack[] = {995, 990};
//     double pot = 15;
//     double amountToCall = 5;
//     bool dealer = true;
//     Card hand[] = {Card(14,3), Card(14,2)};
//     Card *b;
//     b = new Card[5];
// <<<<<<< HEAD
//     // cout << nextMove(dealer,pot,stack,amountToCall,hand,b) << endl;
// =======
//     // cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
//     stack[0] = 980;
// >>>>>>> 1cd3f05fe3527f7620a9e1344c185723914e56bb
//     stack[0] = 980;
//     pot = 40;
//     amountToCall = 0;
//     b[0] = Card(9,2);
//     b[1] = Card(7,2);
//     b[2] = Card(2,1);
// <<<<<<< HEAD
//     cout << nextMove(dealer,pot,stack,amountToCall,hand,b) << endl;
//     b[3] = Card(5,3);
//     stack[0] = 950;
//     stack[1] = 950;
//     pot = 100;
//     // cout << nextMove(dealer,pot,stack,amountToCall,hand,b) << endl;
//
// }
// =======
//     // cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
// }
// >>>>>>> 1cd3f05fe3527f7620a9e1344c185723914e56bb
