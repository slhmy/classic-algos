#include <cstring>
#include <iostream>

using namespace std;

const int N = 5;

int treeArray[N];

// `x & (-x)` is a magic which helps you to
// get the lowest `1` bit of `x`
inline int lowBit(int x) { return x & (-x); }

void add(int i, int val) {
    while (i <= N) {
        treeArray[i - 1] += val; // 0-based index
        i += lowBit(i);
    }
}

int getSum(int i) {
    int sum = 0;
    while (i > 0) {
        sum += treeArray[i - 1]; // 0-based index
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
