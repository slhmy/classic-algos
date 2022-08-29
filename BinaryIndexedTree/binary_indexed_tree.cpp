//
// Created by slhmy on 2022/8/28.
//

#include <cstring>
#include <iostream>

using namespace std;

const int arraySize = 5;

int treeArray[arraySize + 1];

inline int lowBit(int x) {
    return x & (-x);
}

void add(int i, int val) {
    while (i <= arraySize) {
        treeArray[i] += val;
        i += lowBit(i);
    }
}

int getSum(int i) {
   int sum = 0;
   while (i > 0) {
       sum += treeArray[i];
       i -= lowBit(i);
   }
   return sum;
}

int main() {
    memset(treeArray, 0, sizeof treeArray);
    add(1, 1);
    cout << getSum(1) << endl;
    add(2, 3);
    add(5, 5);
    cout << getSum(5) << endl;
    cout << getSum(4) << endl;
}

