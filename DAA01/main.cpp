/*
 * Name - Suyog Pawar
 * Roll No - TIB54
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<double> > calculatePWRatio(vector<vector<int> >& profitWeights, int objectCount) {

    vector<vector<double> > PWRatioAndIndex;

    for (int i = 0; i < objectCount; i++) {
        double vw = (double) profitWeights[i][1] / profitWeights[i][0];
        vector<double> temp;
        temp.push_back(vw);
        temp.push_back((double) i);
        PWRatioAndIndex.push_back(temp);
    }

    sort(PWRatioAndIndex.begin(), PWRatioAndIndex.end());
    return PWRatioAndIndex;
}

double calculateMaxProfit(vector<vector<double> > PWRatioAndIndex, vector<vector<int> >& profitWeights,
                          int knapSackCapacity, int objectCount) {

    int currentTotalWeight = 0;
    double totalProfit = 0;

    cout << "Objects in Solution: ";
    for (int i = objectCount - 1; i >= 0; i--) {
        int pos = PWRatioAndIndex[i][1];
        int profit = profitWeights[pos][1];
        int weight = profitWeights[pos][0];

        if (weight + currentTotalWeight <= knapSackCapacity) {
            totalProfit += profit;
            currentTotalWeight += weight;
            cout << pos + 1 << " ";
        }
        else {
            int remainingCapacity = knapSackCapacity - currentTotalWeight;
            totalProfit += ((double) remainingCapacity / weight) * profit;
            cout << pos + 1 << " * " << (double) remainingCapacity / weight << endl;
            break;
        }
    }
    return totalProfit;
}


void input(int& knapSackCapacity, int& objectCount, vector<vector<int> >& profitWeights) {

    cout << "Enter Capacity of the bag: ";
    cin >> knapSackCapacity;
    cout << "Enter number of objects: ";
    cin >> objectCount;

    int profit, weight;
    for (int i = 0; i < objectCount; i++) {

        cout << "Enter profit of "  << i+1 << " object: ";
        cin >> profit;
        cout << "Enter weight of " << i+1 << " object: ";
        cin >> weight;

        vector<int> temp;
        temp.push_back(weight);
        temp.push_back(profit);
        profitWeights.push_back(temp);
    }
}

vector<vector<int> > maxProfitDP(int knapSackCapacity, int objectCount, vector<vector<int> >& profitWeights) {

    vector<vector<int> > memo(objectCount + 1, vector<int>(knapSackCapacity + 1));

    for (int i = 0; i <= objectCount; i++) {
        memo[i][0] = 0;
    }
    for (int i = 0; i <= knapSackCapacity; i++) {
        memo[0][i] = 0;
    }

    for (int obj = 1; obj <= objectCount; obj++) {
        for (int w = 1; w <= knapSackCapacity; w++) {
            if (w - profitWeights[obj - 1][0] >= 0) {
                memo[obj][w] = max(memo[obj - 1][w],
                                   memo[obj - 1][w - profitWeights[obj - 1][0]] + profitWeights[obj - 1][1]);
            }
            else {
                memo[obj][w] = memo[obj - 1][w];
            }
        }
    }

    return memo;
}

vector<int> findItemsInSolution(vector<vector<int> >& memo, vector<vector<int> > profitWeights,
                          int objectCount, int knapSackCapacity) {
    vector<int> solutionList;
    int remainingCapacity = knapSackCapacity;

    for (int i = objectCount; i > 0 && remainingCapacity > 0; i--) {
        if (memo[i][remainingCapacity] == memo[i - 1][remainingCapacity]) {
            continue;
        }
        else {
            solutionList.push_back(i);
            remainingCapacity -= profitWeights[i - 1][0];
        }
    }

    return solutionList;
}

void printItemsInSolution(vector<int>& solutionList) {

    int objectsInSolutionCount = solutionList.size();

    cout << "Objects in Solution: ";
    for (int i = 0; i < objectsInSolutionCount; i++) {
        cout << solutionList[i] << " ";
    }
    cout << endl;
}


int main() {

    int knapSackCapacity, objectCount;
    vector<vector<int> > profitWeights;
    vector<vector<int> > memo;
    vector<int> solutionList;
    int maxProfit;

    int choice;

    do {
        cout << "\nMenu\n1. Fractional Knapsack\n2. 0/1 Knapsack\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                input(knapSackCapacity, objectCount, profitWeights);
                maxProfit =  calculateMaxProfit(calculatePWRatio(profitWeights, objectCount),
                                           profitWeights, knapSackCapacity, objectCount);
                cout << "Max Profit: " << maxProfit << endl;
                break;
            case 2:
                input(knapSackCapacity, objectCount, profitWeights);
                memo = maxProfitDP(knapSackCapacity, objectCount,profitWeights);
                cout << "Max Profit: " << memo[objectCount][knapSackCapacity] << endl;
                solutionList = findItemsInSolution(memo, profitWeights, objectCount, knapSackCapacity);
                printItemsInSolution(solutionList);
                break;
        }
    } while (choice != 3);
    return 0;
}
