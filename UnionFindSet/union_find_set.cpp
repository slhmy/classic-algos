//
// Created by slhmy on 2022/8/27.
//

#include <vector>
#include <iostream>

using namespace std;

const int elementCount = 10;

// this is the main data structure for union find set
// it record parent for each query element
int parent[elementCount];

// to optimize the merge choice
// use a `rank` array to record info like size/depth of current set
// you will need to select one in size/depth to help you make decision
int setSize[elementCount];

void init() {
    for (int i = 0; i < elementCount; i++) {
        parent[i] = i;
        setSize[i] = 1;
    }
}

// `find` is the function we use when we want to get the root element of current set
// we need to provide any one of the element in this set
int find(int e) {
    // `parent[e] = find(parent[e])` do compress operation while finding the root
    // this will reduce the cost when another query occurs
    return e == parent[e] ? e : parent[e] = find(parent[e]);
}

// `merge` is the function we use when we want to merge two sets together
// each set should provide an element
void merge(int e1, int e2) {
    int p1 = find(e1);
    int p2 = find(e2);

    // by comparing the `rank` of each set
    // we choose the merge way & update `rank` if necessary
    if (setSize[p1] < setSize[p2]) {
        parent[p1] = p2;
        // depth not changed
        setSize[p1] += setSize[p2];
    } else {
        parent[p2] = p1;
        // depth[p2] = max(depth[p2], depth[p1]+1);
        setSize[p2] += setSize[p1];
    }
}

int main() {
    init();
    cout << find(1) << endl;
    merge(1, 2);
    merge(3, 4);
    cout << find(2) << endl;
    cout << find(3) << endl;
    merge(2,3);
    cout << find(4) << endl;
}