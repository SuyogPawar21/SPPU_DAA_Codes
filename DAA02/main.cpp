/**
 * Name - Suyog Pawar
 * Roll no - TIB54
 */


#include <iostream>
#include <vector>

using namespace std;

class Edge {

public:
    int start;
    int end;
    int cost;

    Edge(int start, int end, int cost) {
        this->start = start;
        this->end = end;
        this->cost = cost;
    }

};

bool relaxEdge(int edgeIndex, vector<Edge> &edgeList, vector<int> &distances) {

    int startVertex = edgeList[edgeIndex].start;
    int endVertex = edgeList[edgeIndex].end;
    int cost = edgeList[edgeIndex].cost;

    if (distances[endVertex] > distances[startVertex] + cost) {
        distances[endVertex] = distances[startVertex] + cost;
        return true;
    }
    else return false;
}

void printDistances(vector<int>& distances, int vertexCount) {
    for (int i = 1; i <= vertexCount; i++) {
        cout << distances[i] << " ";
    }
    cout << endl;
}

void BellmanFord(vector<Edge>& edgeList, vector<int>& distances, int startVertex) {

    int vertexCount = distances.size() - 1;
    int edgeCount = edgeList.size();

    distances[startVertex] = 0;

    cout << 0 << " Iteration: ";
    printDistances(distances, vertexCount);

    for (int i = 0; i < vertexCount - 1; i++) {
        for (int j = 0; j < edgeCount; j++) {
            relaxEdge(j, edgeList, distances);
        }

        cout << i+1 << " Iteration: ";
        printDistances(distances, vertexCount);
    }

    bool containsNegativeEdgeCycle;

    for (int j = 0; j < edgeCount; j++) {
        if (relaxEdge(j, edgeList, distances)) {
            containsNegativeEdgeCycle = true;
        }
    }

    cout << vertexCount << " Iteration: ";
    printDistances(distances, vertexCount);

    if (containsNegativeEdgeCycle) {
        cout << "Negative Edge Cycle Detected.\nAbove Results Invalid.\n"
                "Please try another shortest distance algorithm.";
    }

}

int main() {

    vector<Edge> edgeList1 = {Edge(1, 2, 6), Edge(1, 3, 5), Edge(1, 4, 5), Edge(2, 5, -1),
                              Edge(3, 2, -2), Edge(3, 5, 1), Edge(4, 3, -2), Edge(4, 6, -1),
                              Edge(5, 7, 3), Edge(6, 7, 3)};

    vector<Edge> edgeList2 = {Edge(2, 1 ,4), Edge(2, 3, -6), Edge(3, 4, 5), Edge(4, 2, -2)};

    vector<int>	distances1(8, 9999);
    vector<int> distances2(5, 9999);

    cout << "Example without negative edge cycle.\n";
    BellmanFord(edgeList1, distances1, 1);

    cout << "Example with negative edge cycle.\n";
    BellmanFord(edgeList2, distances2, 2);
    return 0;
}