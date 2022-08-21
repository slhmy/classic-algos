#include <iostream>

const int ELEMENT_COUNT = 10;

// this is the main data structure for union find set
// it record parent for each query element
int parent[ELEMENT_COUNT];

// to optimize the merge choice
// use a `rank` array to record info like set_size/set_depth of current set
// you will need to select one in set_size/set_depth to help you make decision
int set_size[ELEMENT_COUNT];

void init() {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        parent[i] = i;
        set_size[i] = 1;
    }
}

// `find` is the function we use when we want to get the root element of current
// set we need to provide any one of the element in this set
int find(int e) {
    printf("Finding the root of element %d\n", e);
    // `parent[e] = find(parent[e])` do compress operation while finding the
    // root this will reduce the cost when another query occurs
    int res = e == parent[e] ? e : parent[e] = find(parent[e]);
    printf("The root of element %d is %d\n", e, res);

    return res;
}

// `merge` is the function we use when we want to merge two sets together
// each set should provide an element
void merge(int e1, int e2) {
    int p1 = find(e1);
    int p2 = find(e2);

    // by comparing the `rank` of each set
    // we choose the merge way & update `rank` if necessary
    if (set_size[p1] < set_size[p2]) {
        parent[p1] = p2;
        // set_depth not changed
        set_size[p1] += set_size[p2];
    } else {
        parent[p2] = p1;
        // mainly for situation `set_depth[p1] == set_depth[p2]`
        // set_depth[p2] = max(set_depth[p2], set_depth[p1]+1);
        set_size[p2] += set_size[p1];
    }

    printf("Merged element %d and %d\n", e1, e2);
}

int main() {
    printf("Init the union find set with %d elements\n", ELEMENT_COUNT);
    init();
    find(1);
    merge(1, 2);
    merge(3, 4);
    find(2);
    find(3);
    merge(2, 3);
    find(4);
}