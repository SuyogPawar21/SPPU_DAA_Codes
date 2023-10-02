/**
 * Name - Suyog Pawar
 * Roll no - TIB54
 */


#include <iostream>
#include <vector>

using namespace std;

void printSolution(vector<int>& positions, int n) {

    cout << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (positions[i] == j) {
                cout << 1 << " ";
            }
            else cout << 0 << " ";
        }
        cout << endl;
    }

}

bool checkDiagonal(vector<int>& positions, int queensPlacedCount, int column) {
    for (int i = 0; i < queensPlacedCount; i++) {
        if (abs(i - queensPlacedCount) == abs(positions[i] - column)) {
            return false;
        }
    }
    return true;
}

bool checkColumn(vector<int>& positions, int queensPlacedCount, int column) {
    for (int i = 0; i < queensPlacedCount; i++) {
        if (positions[i] == column) {
            return false;
        }
    }
    return true;
}

bool canPlaceQueen(vector<int>& positions, int queensPlacedCount, int column) {
    return checkDiagonal(positions, queensPlacedCount, column)
           && checkColumn(positions, queensPlacedCount, column);
}

void nQueens(int n, vector<int>& positions, int queensPlacedCount, int& solutionsCount) {

    if (queensPlacedCount == n) {
        solutionsCount++;
        printSolution(positions, n);
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (canPlaceQueen(positions, queensPlacedCount, i)) {
                positions[queensPlacedCount++] = i;
                nQueens(n,positions, queensPlacedCount, solutionsCount);
                queensPlacedCount--;
            }
        }
    }
}

int main() {

    int n, solutionsCount = 0;
    cout << "N: ";
    cin >> n;
    vector<int> positions(n, -1);
    nQueens(n, positions, 0, solutionsCount);
    cout << "\nNumber of Solutions: ";
    cout << solutionsCount;
    return 0;
}
