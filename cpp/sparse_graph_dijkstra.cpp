#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const int nodeCount = 10;

// the graph we deal with here is a spare graph
// adjacency table can save more memory space than adjacency list
map<int, map<int, int>> fromToMap;

void addEdge(int from, int to, int distance) {
    // avoid multi edge distances for the same `from` & `to` nodes
    if (fromToMap.count(from) && fromToMap[from].count(to)) {
        fromToMap[from][to] = min(fromToMap[from][to], distance);
    } else {
        fromToMap[from][to] = distance;
    }

    printf("Added Edge(%d, %d, %d)\n", from, to, fromToMap[from][to]);
}

// dijDistanceMap[i] record the nearest distance from the startNode to node `i`
int dijDistanceMap[nodeCount];

static bool compareDijDistance(const int &a, const int &b) {
    return dijDistanceMap[a] > dijDistanceMap[b];
}

// the strategy dijkstra algorithm used is
// trigger distance update related with node `i` while dijDistanceMap[i] has
// changed
void dijkstra() {
    for (int &dijDistance : dijDistanceMap) {
        dijDistance = INT32_MAX;
    }
    dijDistanceMap[0] = 0;

    // we always deal with the node which have the nearest distance first
    priority_queue<int, vector<int>, decltype(&compareDijDistance)>
        nearestDistanceQueue(compareDijDistance);
    // to avoid redundant update for the same node, use a visit list to control
    // it
    bool notNeedUpdate[nodeCount];
    memset(notNeedUpdate, false, sizeof notNeedUpdate);

    nearestDistanceQueue.push(0);
    while (!nearestDistanceQueue.empty()) {
        int curToNode = nearestDistanceQueue.top();
        nearestDistanceQueue.pop();

        if (notNeedUpdate[curToNode])
            continue;

        // if the node is used as a reference node
        // this indicates that it is currently the newest nearest distance
        // so, we set the node updated
        notNeedUpdate[curToNode] = true;

        printf("Calculating with dijDistanceMap[%d]=%d\n", curToNode,
               dijDistanceMap[curToNode]);

        for (auto &toNodeIt : fromToMap[curToNode]) {
            int newDistance = dijDistanceMap[curToNode] + toNodeIt.second;
            // check if dijDistance can be updated
            if (dijDistanceMap[toNodeIt.first] > newDistance) {
                printf("Updating dijDistanceMap[%d]=%d according to Edge(%d, "
                       "%d, %d)\n",
                       toNodeIt.first, newDistance, curToNode, toNodeIt.first,
                       toNodeIt.second);

                dijDistanceMap[toNodeIt.first] = newDistance;
                nearestDistanceQueue.push(toNodeIt.first);
            }
        }
    }
}

int main() {
    addEdge(0, 1, 1);
    addEdge(0, 2, 10);
    addEdge(1, 3, 100);
    addEdge(2, 3, 10);

    dijkstra();

    cout << dijDistanceMap[3] << endl;
}