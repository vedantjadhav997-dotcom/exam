#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
int n;
struct Node {
    int node, cost;
    int mat[100][100];
};
void printPath(const vector<int>& path) {
    cout << "Path: ";
    for (int v : path) cout << v << " ";
    cout << endl;
}
int reduceMatrix(int mat[][100]) {
    int cost = 0;
    for (int i = 0; i < n; i++) {
        int rowMin = *min_element(mat[i], mat[i] + n);
        if (rowMin != INF && rowMin > 0) {
            cost += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] != INF) mat[i][j] -= rowMin;
        }
    }
    for (int j = 0; j < n; j++) {
        int colMin = INF;
        for (int i = 0; i < n; i++) colMin = min(colMin, mat[i][j]);
        if (colMin != INF && colMin > 0) {
            cost += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] != INF) mat[i][j] -= colMin;
        }
    }
    return cost;
}
 
void TSP(Node curr, int visited[], vector<int>& path, int base[][100]) {
    if (path.size() == n) {
        path.push_back(0);
        printPath(path);
        return;
    }
   
    path.push_back(curr.node);
    visited[curr.node] = 1;
    int bestCost = INF;
    Node next;

    for (int i = 0; i < n; i++) if (!visited[i]) {
        Node temp = curr;
        temp.node = i;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                if (r == curr.node || c == i) temp.mat[r][c] = INF;
        temp.cost = curr.cost + reduceMatrix(temp.mat) + base[curr.node][i];
        if (temp.cost < bestCost) bestCost = temp.cost, next = temp;
    }

    if (bestCost != INF) {
        cout << "Next Node: " << next.node << " | Cost: " << next.cost << endl;
        TSP(next, visited, path, base);
    }
}

int main() {
    cout << "Enter number of nodes: ";
    cin >> n;
    int mat[100][100];
    cout << "Enter adjacency matrix (-1 for INF):\n";
    for (int i = 0, x; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> x;
            mat[i][j] = (x == -1 ? INF : x);
        }

    int reduced[100][100];
    memcpy(reduced, mat, sizeof(mat));
    int initCost = reduceMatrix(reduced);
    cout << "Initial reduction cost: " << initCost << endl;

    Node root{0, initCost};
    memcpy(root.mat, reduced, sizeof(reduced));

    int visited[100] = {0};
    vector<int> path;
    TSP(root, visited, path, mat);
}
