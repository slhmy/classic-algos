//
// Created by slhmy on 2022/8/27.
//

#include <iostream>

const int ELEMENT_COUNT = 10;

// this is the main data structure for union find set
// it record parent for each query element
int parent[ELEMENT_COUNT];

// to optimize the merge choice
// use a `rank` array to record info like size/depth of current set
// you will need to select one in size/depth to help you make decision
int rank[ELEMENT_COUNT];

void init()
{
    for (int i = 0; i < ELEMENT_COUNT; i++)
    {
        parent[i] = i;
        rank[i] = 1;
    }
}

// `find` is the function we use when we want to get the root element of current set
// we need to provide any one of the element in this set
int find(int e)
{
    // `parent[e] = find(parent[e])` do compress operation while finding the root
    // this will reduce the cost when another query occurs
    return e == parent[e] ? e : parent[e] = find(parent[e]);
}

// `merge` is the function we use when we want to merge two sets together
// each set should provide an element
void merge(int e1, int e2)
{
    int p1 = find(e1);
    int p2 = find(e2);

    // by comparing the `rank` of each set
    // we choose the merge way & update `rank` if necessary
    if (rank[p1] < rank[p2])
    {
        parent[p1] = p2;
        // depth not changed
        rank[p1] += rank[p2];
    }
    else
    {
        parent[p2] = p1;
        // depth[p2] = max(depth[p2], depth[p1]+1);
        rank[p2] += rank[p1];
    }
}

int main()
{
    init();
    std::cout << find(1) << std::endl;
    merge(1, 2);
    merge(3, 4);
    std::cout << find(2) << std::endl;
    std::cout << find(3) << std::endl;
    merge(2, 3);
    std::cout << find(4) << std::endl;
}