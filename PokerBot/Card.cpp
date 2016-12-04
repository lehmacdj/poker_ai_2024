
#include "Card.h"

Card::Card(){
    rank = 0;
    suit = 0;
}
Card::Card(int r, int s){
    rank = r;
    suit = s;
}
int Card::getRank(){
    return rank;
}

int Card::getSuit(){
    return suit;
}

Card::Card(char r, int s){
    switch ( r ) {
        case 'K':
            rank = 13;
            break;
        case 'Q':
            rank = 12;
            break;
        case 'J':
            rank = 11;
            break;
        case 'T':
            rank = 10;
            break;
        case 'A':
            rank = 14;
            break;
        default:
            rank = (int)r - 48;
            break;
    }
    suit = s;
}

string Card::toString(){
    string ret;
    switch ( rank ){
        case 13:
            ret += "K";
            break;
        case 12:
            ret += "Q";
            break;
        case 11:
            ret += "J";
            break;
        case 10:
            ret += "T";
            break;
        case 14:
            ret += "A";
            break;
        default:
            ret += (char)(rank + 48);
            break;
    }
    switch ( suit ){
        case 0:
            ret += "c";
            break;
        case 1:
            ret += "d";
            break;
        case 2:
            ret += "h";
            break;
        case 3:
            ret += "s";
            break;
        default:
            break;
    }
    return ret;
}


bool operator ==( Card c1, Card c2){
    return (c1.getRank() == c2.getRank() && c1.getSuit() == c2.getSuit());
}