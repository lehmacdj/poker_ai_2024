#include "Range.h"
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

int nextMove(bool dealer, double pot, double *stack, double amountToCall, Card *hand, Card *b){
    Board board = Board(b);
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

int winningHand(Card hand1[], Card hand2[], Card board[]){
    Board b = Board(board);
    Hole h1 = Hole(hand1);
    Hole h2 = Hole(hand2);
    Hand h_1 = Hand(h1,b);
    Hand h_2 = Hand(h1,b);
    long h1_strength = h_1.bestHandStrength();
    long h2_strength = h_2.bestHandStrength();
    if(h1_strength == h2_strength){
        return -1;
    }
    if(h1_strength > h2_strength){
        return 0;
    }else{
        return 1;
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
    cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
    stack[0] = 980;
    stack[1] = 980;
    pot = 40;
    amountToCall = 0;
    b[0] = Card(9,2);
    b[1] = Card(7,2);
    b[2] = Card(2,1);
    cout << nextMove(dealer,pot,stack,amountToCall,hand,b);
    b[3] = Card(5,3);
    stack[0] = 950;
    stack[1] = 950;
    pot = 100;
    cout << nextMove(dealer,pot,stack,amountToCall,hand,b);

}