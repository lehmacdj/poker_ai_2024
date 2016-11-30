//
// Establishes the ai's range. This is how the ai can be unexploitable.
//

#ifndef POKERBOT_RANGE_H
#define POKERBOT_RANGE_H

#include "Hole.h"
#import <vector>
#import <string>
#include <math.h>
using std::string;


class Range {
public:
    Range();
    Range(std::vector <Hole> r);
    int getSize();
    Range splitRange(double top, double bottom);
    string toString();
    bool contains(Hole h);
private:
    std::vector <Hole> range;
    int size;
};


#endif //POKERBOT_RANGE_H
