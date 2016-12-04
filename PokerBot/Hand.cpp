
#include "Hand.h"
using std::pair;

bool hasPair(Card h []){
    for (int i = 0; i < 4; i++){
        for (int j = i+1; j < 5; j++){
            if (h[i].getRank() == h[j].getRank()) {
                return true;
            }
        }
    }
    return false;
}

bool hasTwoPair(Card h []){
    bool one = false;
    for (int i = 0; i < 4; i++){
        for (int j = i+1; j < 5; j++){
            if (h[i].getRank() == h[j].getRank()) {
                if (one) {
                    return true;
                } else {
                    one = true;
                    j = 0;
                    i+=2;
                }
            }
        }
    }
    return false;
}

bool hasTrips(Card h []){
    for (int i = 0; i < 3; i++){
        for (int j = i+1; j < 4; j++){
            for (int k = j + 1; k < 5; k++){
                if (h[i].getRank() == h[j].getRank() && h[i].getRank() == h[k].getRank()){
                    return true;
                }
            }
        }
    }
    return false;
}

bool hasStraight(Card h []){
    if(h[0].getRank() == 2 && h[1].getRank() == 3 && h[2].getRank() == 4 && h[1].getRank() == 5 && h[1].getRank() == 14){
        return true;
    }
    if (hasPair(h)){
        return false;
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 5; j++){
            int dif = abs(h[i].getRank() - h[j].getRank());
            if ( dif > 4){
                return false;
            }
        }
    }
    return true;
}

bool hasFlush(Card h []){
    int suit = h[0].getSuit();
    return suit == h[1].getSuit() && suit == h[2].getSuit() && suit == h[3].getSuit() && suit == h[4].getSuit();
}

bool hasQuads(Card h []){
    int h_0 = h[0].getRank();
    int h_1 = h[1].getRank();
    if(h_0 == h_1){
        return (h_0 == h[2].getRank() && h_0 == h[3].getRank());
    }else{
        return (h_1 == h[2].getRank() && h_1 == h[3].getRank() && h_1 == h[4].getRank());
    }
}

bool hasFullHouse(Card h []){
    return (!hasQuads(h) && hasTrips(h) && hasTwoPair(h));
}

bool hasSF(Card h []){
    return (hasStraight(h) && hasFlush(h));
}

Card *sortHand(Card *arr){
    Card *a = new Card[5];
    int ints[5];
    for(int i = 0; i < 5; i++){
        ints[i] = arr[i].getRank();
    }
    for(int i = 0; i < 5; i++){
        int max = 0;
        int index = 0;
        for(int j = 0; j < 5; j++){
            int temp = ints[j];
            if(temp > max){
                max = temp;
                index = j;
            }
        }
        ints[index] = 0;
        a[i] = arr[index];
    }
    return a;
}

//returns an int that is strictly larger than weaker hands and strictly smaller than stronger hands.
long handStrength(Card c1, Card c2, Card c3, Card c4, Card c5){
    Card *temp = new Card [5];
    temp[0] = c1;
    temp[1] = c2;
    temp[2] = c3;
    temp[3] = c4;
    temp[4] = c5;
    Card *array;
    array = sortHand(temp);
    if(hasSF(array)){
        return (long)pow(2,27) + array[0].getRank();
    }
    if(hasQuads(array)){
        if(array[0] == array[1]){
            return (long)pow(2,26) + array[4].getRank();
        }else{
            return (long)pow(2,26) + array[0].getRank();
        }
    }
    if(hasFullHouse(array)){
        return (long)pow(2,25) + array[0].getRank() * 16 + array[4].getRank();
    }
    if(hasFlush(array)){
        return (long)pow(2,24) + array[0].getRank() + array[1].getRank() + array[2].getRank() + array[3].getRank() + array[4].getRank();
    }
    if(hasStraight(array)){
        return (long)pow(2,23) + array[0].getRank();
    }
    if(hasTrips(array)){
        return (long)pow(2,22) + array[2].getRank();
    }
    if(hasTwoPair(array)){
        int kicker = 0;
        int a_1 = array[1].getRank();
        int a_3 = array[3].getRank();
        for(int i = 0; i < 3; i++){
            int temp = array[i*2].getRank();
            if(temp != a_1 && temp != a_3){
                kicker = temp;
            }
        }
        return (long)pow(2,21) + a_1 * 256 + a_3 * 16 + kicker;
    }
    if(hasPair(array)){
        int pair_index = 0;
        int ints [5];
        for(int i  = 0; i < 5; i++){
            ints[i] = array[i].getRank();
        }
        for(int i = 0; i < 4; i++){
            if(ints[i] == ints[i+1]){
                pair_index = i;
            }
        }
        int temp = ints[pair_index];
        ints[pair_index] = ints[0];
        ints[0] = temp;
        temp = ints[pair_index + 1];
        ints[pair_index] = ints[1];
        ints[1] = temp;
        return (long)pow(2,20) + ints[1] * 4096 + ints[2] * 256 + ints[3] * 16 + ints[4];
    }else{
        return array[0].getRank() + array[1].getRank() + array[2].getRank() + array[3].getRank() + array[4].getRank();
    }
}

//finds the best possible five card hand and returns a pair with first value Card* to an array with the five best cards and
//second value the long hand strength of the hand
pair<Card*,long> calcBestStrength(Hole hole, Board board) {
    int numCards = board.getStreet() + 5;
    // Card *b = board.getBoard();
    Card *h = hole.getCards();
    Card *array = new Card[numCards];
    array[0] = h[0];
    array[1] = h[1];
    for(int i = 2; i < numCards + 2; i++){
        array[i] = h[i-2];
    }

    Card* arr = new Card[5];
    long max = 0;
    for(int i = 0; i < numCards - 4; i++){
        for(int j = i + 1; j < numCards - 3; j++){
            for(int k = j + 1; k < numCards - 2; k++){
                for(int l = k + 1; l < numCards - 1; l++){
                    for(int m = l + 1; m < numCards; m++){
                        long str = handStrength(array[i], array[j], array[k], array[l], array[m]);
                        if(str > max){
                            max = str;
                            arr[0] = array[i]; arr[1] = array[j]; arr[2] = array[k]; arr[3] = array[l]; arr[4] = array[m];
                        }
                    }
                }
            }
        }
    }
    return pair<Card*,long>(arr,max);
}

Hand::Hand(Hole h, Board b) {
    holecards = h;
    board = b;
    pair<Card*,long> p = calcBestStrength(h,b);
    best = p.first;
    bestStrength = p.second;
}

Card *Hand::bestHand() {
    return best;
}

Hole Hand::getHole() {
    return holecards;
}

Board Hand::getBoard() {
    return board;
}

long Hand::bestHandStrength() {
    return bestStrength;
}

bool Hand::flushDraw() {
    if(bestStrength > pow(2,24)){
        return false;
    }
    Card *hole;
    Card *b;
    int numBoard = board.getStreet() + 3;
    hole = holecards.getCards();
    b = board.getBoard();
    int suit = hole[0].getSuit();
    int count = 0;
    for(int i = 0; i < numBoard; i++){
        if (b[i].getSuit() == suit){
            count++;
        }
    }
    if(suit == hole[1].getSuit()){
        if(count == 2){
            return true;
        }
    }else{
        if(count == 3){
            return true;
        }
        suit = hole[1].getSuit();
        for(int i = 0; i < numBoard; i++){
            if (b[i].getSuit() == suit){
                count++;
            }
        }
        if(count == 3){
            return true;
        }
        return false;
    }
    return false;
}

bool Hand::openEnder() {
    if(bestStrength > pow(2,23)){
        return false;
    }
    Card *hole;
    // int numBoard = board.getStreet() + 3;
    hole = holecards.getCards();
    int r0 = hole[0].getRank();
    int r1 = hole[1].getRank();
    bool firstBigger = false;
    int gap = r1 - r0;
    if(gap < 0){
        firstBigger = true;
        gap = abs(gap);
    }
    switch (gap){
        case 1 :
            if(firstBigger){
                return ((board.contains(r1 - 1) && (board.contains(r1 - 2) || board.contains(r1 + 2)))
                        || ((board.contains(r1 + 2) && board.contains(r1 + 3))));
            }else{
                return ((board.contains(r0 - 1) && ((board.contains(r0 - 2) || board.contains(r0 + 2))))
                        || (board.contains(r0 + 2) && board.contains(r0 + 3)));
            }
            break;
        case 2 :
            if(firstBigger){
                return (board.contains(r1 + 1) && (board.contains(r1 - 1) || board.contains(r1 + 2)));
            }else{
                return (board.contains(r0 + 1) && (board.contains(r0 - 1) || board.contains(r0 + 2)));
            }
            break;
        case 3 :
            if(firstBigger){
                return (board.contains(r1 + 1) && board.contains(r1 + 2));
            }else{
                return (board.contains(r0 + 1) && board.contains(r0 + 2));
            }
            break;
        default:
            return ((board.contains(r1 - 1) && board.contains(r1 - 2) && board.contains(r1 - 3))
                    || (board.contains(r0 - 1) && board.contains(r0 - 2) && board.contains(r0 - 3)));
    }
}

