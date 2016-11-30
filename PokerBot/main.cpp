#include <iostream>
#include "Range.h"
using std::cout;
using std::endl;
using std::cin;

int main(){
    Range r1 = Range();
    cout << r1.toString() << endl;
    cout << "done" << endl;
    Range r2 = r1.splitRange(1.0, 0.9);
    cout << "done2" << endl;
    cout << r2.getSize() << endl;
    cout << r2.toString();
    Range r3 = r1.splitRange(0.9, 0.0);
    cout << "done3" << endl;
    cout << r3.getSize() << endl;
    cout << r3.toString();
    return 0;
}