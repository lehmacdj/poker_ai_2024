
#include "Hand.h"
using std::pair;


bool hasPair(vector<Card> h);
bool hasTwoPair(vector<Card> h);
bool hasTrips(vector<Card> h);
bool hasStraight(vector<Card> h);
bool hasFlush(vector<Card> h);
bool hasQuads(vector<Card> h);
bool hasFullHouse(vector<Card> h);
bool hasSF(vector<Card> h);

bool hasTrips(vector<Card> h) {
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

bool hasTwoPair(vector<Card> h) {
    bool one = false;
    for (int i = 0; i < 4; i++){
        for (int j = i+1; j < 5; j++){
            if (h[i].getRank() == h[j].getRank()) {
                if (one) {
                    return true;
                } else {
                    one = true;
                    i+=2;
                    j = i + 1;
                }
            }
        }
    }
    return false;
}


bool hasPair(vector<Card> h) {
    for (int i = 0; i < 4; i++){
        for (int j = i+1; j < 5; j++){
            if (h[i].getRank() == h[j].getRank()) {
                return true;
            }
        }
    }
    return false;
}


bool hasStraight(vector<Card> h) {
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


bool hasQuads(vector<Card> h) {
    int h_0 = h[0].getRank();
    int h_1 = h[1].getRank();
    if(h_0 == h_1){
        return (h_0 == h[2].getRank() && h_0 == h[3].getRank());
    }else{
        return (h_1 == h[2].getRank() && h_1 == h[3].getRank() && h_1 == h[4].getRank());
    }
}


bool hasFlush(vector<Card> h) {
    int suit = h[0].getSuit();
    return suit == h[1].getSuit() && suit == h[2].getSuit() && suit == h[3].getSuit() && suit == h[4].getSuit();
}

bool hasSF(vector<Card> h) {
    return (hasStraight(h) && hasFlush(h));
}

bool hasFullHouse(vector<Card> h) {
    return (!hasQuads(h) && hasTrips(h) && hasTwoPair(h));
}

void sortHand(vector<Card> arr) {
    Card a[5];
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
    for(int i = 0; i < 5; i++){
        arr[5] = a[5];
    }
}

long handStrength(Card c1, Card c2, Card c3, Card c4, Card c5) {
    vector<Card> temp;
    temp.push_back(c1);
    temp.push_back(c2);
    temp.push_back(c3);
    temp.push_back(c4);
    temp.push_back(c5);
    sortHand(temp);
    if(hasSF(temp)){
        return (long)pow(2,27) + temp[0].getRank();
    }
    if(hasQuads(temp)){

        if(temp[0] == temp[1]){
            return (long)pow(2,26) + temp[4].getRank();
        }else{
            return (long)pow(2,26) + temp[0].getRank();
        }
    }
    if(hasFullHouse(temp)){
        return (long)pow(2,25) + temp[0].getRank() * 16 + temp[4].getRank();
    }
    if(hasFlush(temp)){
        return (long) (pow(2, 24) + temp[0].getRank() * pow(2, 16) + temp[1].getRank() * pow(2, 12) + temp[2].getRank() * 256 + temp[3].getRank() * 16 + temp[4].getRank());
    }
    if(hasStraight(temp)){
        return (long)pow(2,23) + temp[0].getRank();
    }
    if(hasTrips(temp)){
        return (long)pow(2,22) + temp[2].getRank();
    }
    if(hasTwoPair(temp)){
        int kicker = 0;
        int a_1 = temp[1].getRank();
        int a_3 = temp[3].getRank();
        for(int i = 0; i < 3; i++){
            int t = temp[i*2].getRank();
            if(t != a_1 && t != a_3){
                kicker = t;
            }
        }
        return (long)pow(2,21) + a_1 * 256 + a_3 * 16 + kicker;
    }
    if(hasPair(temp)){
        int pair_index = 0;
        int ints [5];
        for(int i  = 0; i < 5; i++){
            ints[i] = temp[i].getRank();
        }
        for(int i = 0; i < 4; i++){
            if(ints[i] == ints[i+1]){
                pair_index = i;
            }
        }
        int t = ints[pair_index];
        ints[pair_index] = ints[0];
        ints[0] = t;
        t = ints[pair_index + 1];
        ints[pair_index] = ints[1];
        ints[1] = t;
        return (long)pow(2,20) + ints[1] * 4096 + ints[2] * 256 + ints[3] * 16 + ints[4];
    }else{
        return (long) (temp[0].getRank() * pow(2, 16) + temp[1].getRank() * pow(2, 12) + temp[2].getRank() * 256 + temp[3].getRank() * 16 + temp[4].getRank());
    }
}


pair<vector<Card>, long> calcBestStrength(Hole hole, Board board) {
    int numCards = board.getStreet() + 4;
    vector<Card> b;
    for(int i = 0; i < board.getBoard().size(); i++){
        b.push_back(board.getBoard()[i]);
    }
    vector<Card> h;
    h.push_back(hole.getCards()[0]);
    h.push_back(hole.getCards()[1]);
    vector<Card> array;
    array.push_back(h[0]);
    array.push_back(h[1]);
    for(int i = 2; i < numCards; i++){
        array.push_back(b[i-2]);
    }
    vector<Card> arr;
    long max = 0;
    for(int i = 0; i < numCards - 4; i++){
        for(int j = i + 1; j < numCards - 3; j++){
            for(int k = j + 1; k < numCards - 2; k++){
                for(int l = k + 1; l < numCards - 1; l++){
                    for(int m = l + 1; m < numCards; m++){
                        long str = handStrength(array[i], array[j], array[k], array[l], array[m]);
                        if(str > max){
                            max = str;
                            arr.push_back(array[i]); arr.push_back(array[j]);arr.push_back(array[k]);arr.push_back(array[l]);arr.push_back(array[m]);
                        }
                    }
                }
            }
        }
    }
    return pair<vector<Card>,long>(arr,max);
}

Hand::Hand(Hole h, Board *b) {
    holecards = h;
    board = *b;
    pair<vector<Card>,long> p = calcBestStrength(h,*b);
    best = p.first;
    bestStrength = p.second;
}

vector<Card> Hand::bestHand() {
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
    vector<Card> hole;
    vector<Card> b;
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
    vector<Card> hole;
    int numBoard = board.getStreet() + 3;
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

Hand::Hand() {
}

