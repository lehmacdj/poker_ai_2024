//
// Establishes the ai's range. This is how the ai can be unexploitable.
//

#ifndef POKERBOT_RANGE_H
#define POKERBOT_RANGE_H

#import <vector>
#import <string>
#include <algorithm>
#include <math.h>
#include "Hand.h"

using std::string;
using std::pair;
using std::vector;

class Range {
public:
    Range();
    Range(vector <Hole> r);
    int getSize();
    Range splitRange(double top, double bottom);
    string toString();
    bool contains(Hole h);
    pair<Range,Range> facingBet(int bet, Board b, int potSize);
    Range combine(Range r);
    vector <Hole> getRange();
    void sortRange(Board b);
    void add(Hole h);
private:
    vector <Hole> range;
    int size;
};


#endif //POKERBOT_RANGE_H
