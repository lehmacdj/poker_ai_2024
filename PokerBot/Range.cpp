//
// Created by Jonathan Ho on 11/28/16.
//
#include <iostream>
#include "Range.h"
using std::cout;
using std::endl;
using std::cin;
using std::sort;

Board currentBoard;

Range::Range(){
    vector <Hole> full_range;
    string hand_order[] = {"AA", "KK", "QQ", "AKs", "JJ", "AQs", "KQs", "AJs", "KJs", "TT", "AKo", "ATs", "QJs", "KTs", "QTs", "JTs", "99", "AQo", "A9s", "KQo",
                                 "88", "K9s", "T9s", "A8s", "Q9s", "J9s", "AJo", "A5s", "77", "A7s", "KJo", "A4s", "A3s", "A6s", "QJo", "66", "K8s", "T8s",
                                 "A2s", "98s", "J8s", "ATo", "Q8s", "K7s", "KTo", "55", "JTo", "87s", "QTo", "44", "33", "22", "K6s", "97s", "K5s", "76s",
                                 "T7s", "K4s", "K3s", "K2s", "Q7s", "86s", "65s", "J7s", "54s", "Q6s", "75s", "96s", "Q5s", "64s", "Q4s", "Q3s", "T9o",
                                 "T6s", "Q2s", "A9o", "53s", "85s", "J6s", "J9o", "K9o", "J5s", "Q9o", "43s", "74s", "J4s", "J3s", "95s", "J2s", "63s",
                                 "A8o", "52s", "T5s", "84s", "T4s", "T3s", "42s", "T2s", "98o", "T8o", "A5o", "A7o", "73s", "A4o", "32s", "94s", "93s",
                                 "J8o", "A3o", "62s", "92s", "K8o", "A6o", "87o", "Q8o", "83s", "A2o", "82s", "97o", "72s", "76o", "K7o", "65o", "T7o",
                                 "K6o", "86o", "54o", "K5o", "J7o", "75o", "Q7o", "K4o", "K3o", "96o", "K2o", "64o", "Q6o", "53o", "85o", "T6o", "Q5o",
                                 "43o", "Q4o", "Q3o", "74o", "Q2o", "J6o", "63o", "J5o", "95o", "52o", "J4o", "J3o", "42o", "J2o", "84o", "T5o" ,"T4o",
                                 "32o", "T3o", "73o", "T2o", "62o", "94o", "93o", "92o", "83o", "82o", "72o"};

    for (string &hand : hand_order) {
        if (hand.length() == 2){
            for(int i = 0; i < 3; i++){
                for(int j = i+1; j < 4; j++){
                    full_range.push_back(Hole(Card(hand[0],i), Card(hand[0], j)));
                }
            }
        }else if(hand[2] == 'o') {
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 4; j++) {
                    full_range.push_back(Hole(Card(hand[0], i), Card(hand[1], j)));
                    full_range.push_back(Hole(Card(hand[0], j), Card(hand[1], i)));
                }
            }
        }else{
            for(int i = 0; i < 4; i++){
                full_range.push_back(Hole(Card(hand[0],i), Card(hand[1],i)));
            }
        }
    }
    range = full_range;
    size = 1326;
}

Range::Range(vector <Hole> r){
    range = r;
    size = (int)r.size();
}

int Range::getSize(){
    return size;
}

Range Range::splitRange(double top, double bottom){
    int upperbound = size - (int)(round((double)size * top));
    int lowerbound = size - (int)(round((double)size * bottom));
    vector <Hole> new_range;
    for(int i = upperbound; i < lowerbound; i++){
        new_range.push_back(range[i]);
    }
    Range newrange = Range(new_range);
    return newrange;
}

string Range::toString(){

    string ret = range[0].toString();
    for(int i = 1; i < size; i++){
        ret = ret + ", " + range[i].toString();
    }
    return ret;
}

bool operator==( Hole& h1,  Hole& h2){
    Card *h_1 = h1.getCards();
    Card *h_2 = h2.getCards();

    return (h_1[0] == h_2[0] && h_1[1] == h_2[1]) || (h_1[0] == h_2[1] && h_1[1] == h_2[0]);
}

bool Range::contains(Hole h){
    for(int i = 0; i < size; i++){
        if (h == range[i]){
            return true;
        }
    }
    return false;
}

//returns a pair<Range,Range> where the first value is the bet/raising range and the second value is the check/calling range
pair<Range,Range> Range::facingBet(int bet, Board b, int potSize) {

    double potOdds = (double)bet / potSize;
    vector <int> bluffIndices;
    switch (b.getStreet()){
        case 0 : {
            if (potSize == 15) {
                return pair<Range, Range>(splitRange(1, 0.1), splitRange(0, 0));
            } else {
                if (bet != 0) {
                    return pair<Range, Range>(splitRange(1.0, 1 - ((1 - potOdds) / 6)).combine(
                            splitRange(potOdds + ((1 - potOdds) / 6), potOdds)),
                                              splitRange(1 - ((1 - potOdds) / 6), potOdds + ((1 - potOdds) / 6)));
                } else {
                    return pair<Range, Range>(splitRange(1.0, 1 - ((1 - potOdds) / 6)).combine(
                            splitRange(potOdds + ((1 - potOdds) / 6), potOdds)),
                                              splitRange(1 - ((1 - potOdds) / 6), 0));
                }
            }
        }
        case 3 : {
            sortRange(b);
            for (unsigned int i = 0; i < size; i++) {
                Hole hole = Hole(range[i].getCards());
                Hand hand = Hand(hole, b);
                if (!splitRange(1.0, potOdds + ((1 - potOdds) / 2)).contains(hole) &&
                    (hand.flushDraw() || hand.openEnder())) {
                    bluffIndices.push_back(i);
                }
            }
            Range riverBetRange = splitRange(1.0, 1 - (bluffIndices.size() / size));
            for (int i = 0; i < bluffIndices.size() / 2; i++) {
                riverBetRange.add(range[bluffIndices[i]]);
            }
            if (bet != 0) {
                return pair<Range, Range>(riverBetRange, splitRange(1 - (bluffIndices.size() / 2 / size), potOdds));
            } else {
                return pair<Range, Range>(riverBetRange, splitRange(1 - (bluffIndices.size() / 2 / size), 0));
            }
        }
        default:
            sortRange(b);
            for(unsigned int i = 0; i < size; i++){
                Hole hole = Hole(range[i].getCards());
                Hand hand = Hand(hole,b);
                if( !splitRange(1.0,potOdds + ((1 - potOdds) / 2)).contains(hole) &&  (hand.flushDraw() || hand.openEnder()) ){
                    bluffIndices.push_back(i);
                }
            }
            Range betRange = splitRange(1.0, 1 - (bluffIndices.size() / size));
            for(int i = 0; i < bluffIndices.size(); i++){
                betRange.add(range[bluffIndices[i]]);
            }
            if(bet != 0){
                return pair<Range,Range>(betRange, splitRange(1 - (bluffIndices.size() / size), potOdds));
            }else{
                return pair<Range,Range>(betRange, splitRange(1 - (bluffIndices.size() / size), 0));
            }
    }
}

Range Range::combine(Range r) {
    vector<Hole> combined;
    for (int i = 0; i < size; i++) {
        combined.push_back(range[i]);
    }
    for (int i = 0; i < r.getSize(); i++) {
        combined.push_back(r.getRange()[i]);
    }
    return Range(combined);
}

vector<Hole> Range::getRange() {
    return range;
}

bool compareHoles(Hole h1, Hole h2) {
    return Hand(h1,currentBoard).bestHandStrength() > Hand(h2,currentBoard).bestHandStrength();
}

void Range::sortRange(Board b) {
    currentBoard = b;
    sort(range.begin(), range.end(), compareHoles);
}

void Range::add(Hole h) {
    range.push_back(h);
}


