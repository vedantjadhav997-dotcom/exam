#include <bits/stdc++.h>
using namespace std;
class NQP {
private:
    int n;
    vector<int> x;

public:
    NQP() {
        cout << "Enter length or width of chessboard: ";
        cin >> n;
        x.resize(n);
    }

    bool place(int k, int i) {
        for (int j = 0; j < k; j++) {
            if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
                return false;
            }
        }
        return true;
    }

    void printArr() {
        cout << "\nOne of the possible solutions:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (x[i] == j) {
                    cout << "? ";  // Unicode queen symbol
                } else {
                    cout << "_ ";
                }
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << "Row " << i + 1 << " ? Column " << x[i] + 1 << endl;
        }
        cout << endl;
    }

    void NQueen(int k) {
        for (int i = 0; i < n; i++) {
        	
            if (place(k, i)) {
                x[k] = i; // Place queen at (k, i)
                if (k == n - 1) {
                    printArr(); // Print the board if all queens placed
                } else {
                    NQueen(k + 1); // Recur for next row
                }
            }
        }
    }
};

int main() {
    NQP queen;
    queen.NQueen(0);
    return 0;
}

