#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFINITE = 999;

typedef vector<vector<int> > matrix;

class BranchState {

public:

    int cost;
    matrix reducedMatrix;
    vector<int> path;

    BranchState(int cost, matrix reducedMatrix, vector<int> path) {
        this->cost = cost;
        this->reducedMatrix = reducedMatrix;
        this->path = path;
    }

    bool operator>(const BranchState& other) const {
        return this->cost > other.cost;
    }

};

typedef priority_queue<BranchState, vector<BranchState>, greater<BranchState> > statePriorityQueue;


int getMinValueInRow(matrix& adjMatrix, int row) {

    int columnCount = adjMatrix[row].size();
    int minValue = INFINITE;

    for (int column = 0; column < columnCount; column++) {
        minValue = min(minValue, adjMatrix[row][column]);
    }

    return minValue;
}

int getMinValueInColumn(matrix& adjMatrix, int column) {

    int rowCount = adjMatrix.size();
    int minValue = INFINITE;

    for (int row = 0; row < rowCount; row++) {
        minValue = min(minValue, adjMatrix[row][column]);
    }

    return minValue;
}

int reduceRowInPlace(matrix& adjMatrix, int row) {

    int reductionCost = getMinValueInRow(adjMatrix, row);

    if (reductionCost == 0 || reductionCost == INFINITE) {
        return 0;
    }
    else {
        int columnCount = adjMatrix[row].size();

        for (int column = 0; column < columnCount; column++) {

            if (adjMatrix[row][column] != INFINITE) {
                adjMatrix[row][column] -= reductionCost;
            }
            else continue;
        }

        return reductionCost;
    }
}

int reduceColumnInPlace(matrix& adjMatrix, int column) {

    int reductionCost = getMinValueInColumn(adjMatrix, column);

    if (reductionCost == 0 || reductionCost == INFINITE) {
        return 0;
    }
    else {

        int rowCount = adjMatrix.size();

        for (int row = 0; row < rowCount; row++) {

            if (adjMatrix[row][column] != INFINITE) {
                adjMatrix[row][column] -= reductionCost;
            }
            else continue;

        }

        return reductionCost;
    }
}

int reduceMatrixInPlace(matrix& adjMatrix) {

    int rowCount = adjMatrix.size();
    int columnCount = adjMatrix[0].size();

    int totalReductionCost = 0;

    for (int row = 0; row < rowCount; row++) {
        totalReductionCost += reduceRowInPlace(adjMatrix, row);
    }

    for (int column = 0; column < columnCount; column++) {
        totalReductionCost += reduceColumnInPlace(adjMatrix, column);
    }

    return totalReductionCost;
}

matrix copyMatrix(matrix& adjMatrix) {

    int rowCount = adjMatrix.size();
    int columnCount = adjMatrix[0].size();

    matrix copiedMatrix(rowCount, vector<int>(columnCount));

    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            copiedMatrix[row][column] = adjMatrix[row][column];
        }
    }

    return copiedMatrix;
}

bool containsNumber(vector<int>& numbers, int number) {
    for (int num : numbers) {
        if (num == number) {
            return true;
        }
    }
    return false;
}

void makeRowColumnInfinite(int startVertex, int destVertex, matrix &reducedMatrix) {

    int rowCount = reducedMatrix.size();
    int columnCount = reducedMatrix[0].size();

    for (int column = 0; column < columnCount; column++) {
        reducedMatrix[startVertex - 1][column] = INFINITE;
    }

    for (int row = 0; row < rowCount; row++) {
        reducedMatrix[row][destVertex - 1] = INFINITE;
    }

    reducedMatrix[destVertex - 1][startVertex - 1] = INFINITE;
}

void Branch(statePriorityQueue &priorityQueue, BranchState &branch,
            int startVertex, int destVertex, int &upperBound) {

    matrix reducedMatrix = branch.reducedMatrix;
    vector<int> path = branch.path;
    int vertexCount = reducedMatrix.size();

    int costBetweenVertices = reducedMatrix[startVertex - 1][destVertex - 1];

    makeRowColumnInfinite(startVertex, destVertex, reducedMatrix);

    int reductionCost = reduceMatrixInPlace(reducedMatrix);
    int cost = costBetweenVertices + branch.cost + reductionCost;
    path.push_back(destVertex);

    if (path.size() == vertexCount) {
        upperBound = min(upperBound, cost);
    }

    priorityQueue.push(BranchState(cost, reducedMatrix, path));
}

void printTourDetails(statePriorityQueue& priorityQueue) {
    cout << "Cost of Tour: " << priorityQueue.top().cost << endl;
    cout << "Tour: ";
    for (int vertex : priorityQueue.top().path) {
        cout << vertex << " ";
    }
    cout << endl;
}

void initializeQueueWithStartVertex(matrix &adjMatrix, int sourceVertex, statePriorityQueue &priorityQueue) {

    vector<int> path(1, sourceVertex);
    matrix reducedMatrix = copyMatrix(adjMatrix);
    int reductionCost = reduceMatrixInPlace(reducedMatrix);

    priorityQueue.push(BranchState(reductionCost, reducedMatrix, path));
}

void TSPLCBranchNBound(matrix &adjMatrix, int sourceVertex) {

    int vertexCount = adjMatrix.size();
    int upperBound = INFINITE;
    
    statePriorityQueue priorityQueue;

    initializeQueueWithStartVertex(adjMatrix, sourceVertex, priorityQueue);

    while(!priorityQueue.empty() && priorityQueue.top().cost < upperBound) {

        BranchState bestBranchState = priorityQueue.top();
        int startVertex = bestBranchState.path[bestBranchState.path.size() - 1];
        
        for (int destVertex = 1; destVertex <= vertexCount; destVertex++) {
            
            if (containsNumber(bestBranchState.path, destVertex)) {
                continue;
            } else {
                Branch(priorityQueue, bestBranchState, startVertex, destVertex, upperBound);
            }
            
        }
        priorityQueue.pop();
    }

    printTourDetails(priorityQueue);
}

void input(matrix &adjMatrix, int &sourceVertex) {

    int vertexCount;
    cout << "Enter number of vertices: ";
    cin >> vertexCount;

    adjMatrix.resize(vertexCount, vector<int>(vertexCount));

    cout << "Enter adjacency matrix" << endl;
    for (int row = 1; row <= vertexCount; row++) {
        for (int column = 1; column <= vertexCount; column++) {
            printf("matrix[%i][%i]: ", row, column);
            cin >> adjMatrix[row - 1][column - 1];
        }
    }

    cout << "Enter source vertex: ";
    cin >> sourceVertex;

}

int main() {

    matrix adjMatrix(5, vector<int>(5));

    /*adjMatrix[0][0] = INFINITE;
    adjMatrix[0][1] = 20;
    adjMatrix[0][2] = 30;
    adjMatrix[0][3] = 10;
    adjMatrix[0][4] = 11;

    adjMatrix[1][0] = 15;
    adjMatrix[1][1] = INFINITE;
    adjMatrix[1][2] = 16;
    adjMatrix[1][3] = 4;
    adjMatrix[1][4] = 2;

    adjMatrix[2][0] = 3;
    adjMatrix[2][1] = 5;
    adjMatrix[2][2] = INFINITE;
    adjMatrix[2][3] = 2;
    adjMatrix[2][4] = 4;

    adjMatrix[3][0] = 19;
    adjMatrix[3][1] = 6;
    adjMatrix[3][2] = 18;
    adjMatrix[3][3] = INFINITE;
    adjMatrix[3][4] = 3;

    adjMatrix[4][0] = 16;
    adjMatrix[4][1] = 4;
    adjMatrix[4][2] = 7;
    adjMatrix[4][3] = 16;
    adjMatrix[4][4] = INFINITE;*/

    int sourceVertex;
    input(adjMatrix, sourceVertex);
    TSPLCBranchNBound(adjMatrix, sourceVertex);
    return 0;
}
