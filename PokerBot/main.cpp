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

int nextBid(int stack[2], int pot, int amountToCall, bool dealer, Card *hand, Card *b){
    Board board = Board(b);
    int street = board.getStreet();
    Hole hole = Hole(hand);
    int myStack;
    int vilStack;
    if(dealer){
        myStack = stack[0];
        vilStack = stack[1];
    }else{
        myStack = stack[1];
        vilStack = stack[0];
    }
    //new Hand
    if((dealer && pot == 15) || (!dealer && pot - amountToCall == 10)){
        currentRange = Range();
    }

    pair<Range,Range> ranges = currentRange.facingBet(amountToCall,board,pot);

    int stackEff = max(myStack - amountToCall, vilStack);
    double SPR = (double)stackEff / (pot + amountToCall);
    if (((Range) ranges.first).contains(hole)){
        //bet or raise
        currentRange = ranges.first;
        return betSize(SPR,street,stackEff,amountToCall,pot);
    }else if (((Range) ranges.second).contains(hole)){
        currentRange = ranges.second;
        return amountToCall;
    }else{
        return -1;
    }

}

int winningHand(Card hands[][2], Card board[]){
    currentBoard = Board(board);
    Hole h1 = Hole(hands[0]);
    Hole h2 = Hole(hands[1]);
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
    int stack[] = {995, 990};
    int pot = 15;
    int amountToCall = 5;
    bool dealer = true;
    Card hand[] = {Card(10,3), Card(10,2)};
    Card *b = new Card[5];
    cout << nextBid(stack,pot,amountToCall,dealer,hand,b);
    stack[0] = 980;
    stack[0] = 980;
    pot = 40;
    amountToCall = 0;
    b[0] = Card(9,2);
    b[1] = Card(7,2);
    b[2] = Card(2,1);
    cout << nextBid(stack,pot,amountToCall,dealer,hand,b);

}