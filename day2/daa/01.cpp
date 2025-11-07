#include <bits/stdc++.h>
using namespace std;

// Structure to store profit and weight of an item
struct Pair {
    int profit, weight;
    // Constructor to initialize profit and weight
    Pair(int p, int w) : profit(p), weight(w) {}
};

// Function to merge and purge two sets of pairs
vector<Pair> MP(vector<Pair> &a, vector<Pair> &b, int m) {
    vector<Pair> merged;
    int i = 0, j = 0;

    // Step 1: Merge two sorted lists based on weight
    while (i < a.size() && j < b.size()) {
        if (a[i].weight < b[j].weight)
            merged.push_back(a[i++]);
        else if (a[i].weight > b[j].weight)
            merged.push_back(b[j++]);
        else
            // If weights are equal, keep the one with higher profit
            merged.push_back((a[i].profit > b[j].profit) ? a[i++] : b[j++]);
    }

    // Add remaining elements from both vectors (if any)
    while (i < a.size()) merged.push_back(a[i++]);
    while (j < b.size()) merged.push_back(b[j++]);

    // Step 2: Purge dominated pairs (keep only best profit for a given weight)
    vector<Pair> purged;
    int bestprofit = -1;

    for (auto &p : merged) {
        // Keep only pairs that are within capacity 'm' 
        // and improve the profit compared to previous ones
        if (p.weight <= m && p.profit > bestprofit) {
            purged.push_back(p);
            bestprofit = p.profit;
        }
    }

    return purged; // Return optimized (purged) pairs
}

// Main Knapsack function
void KS(vector<int> &p, vector<int> &w, int n, int m) {
    int i;
    // S[i] stores the list of valid (profit, weight) pairs after considering first i items
    vector<vector<Pair>> S(n + 1);
    S[0].push_back(Pair(0, 0)); // Base case: no item chosen => profit = 0, weight = 0

    // Process each item one by one
    for (i = 1; i <= n; i++) {
        vector<Pair> S_prime;

        // For each pair from previous step, try adding the current item
        for (auto &prev : S[i - 1]) {
            int newprofit = prev.profit + p[i - 1];
            int newweight = prev.weight + w[i - 1];

            // Add new pair only if within knapsack capacity
            if (newweight <= m)
                S_prime.push_back(Pair(newprofit, newweight));
        }

        // Merge old and new combinations, remove dominated ones
        S[i] = MP(S[i - 1], S_prime, m);
    }

    // The last list (S[n]) contains all best possible combinations
    Pair best = S[n].back(); // The last one will have the highest profit

    cout << "Best profit = " << best.profit << endl;
    cout << "Weight = " << best.weight << endl;
}

int main() {
    int n, m, i;

    cout << "n = "; // Number of items
    cin >> n;
    cout << "m = "; // Maximum weight capacity
    cin >> m;

    vector<int> p(n), w(n);

    cout << "Enter profits: ";
    for (i = 0; i < n; i++) cin >> p[i];

    cout << "Enter weights: ";
    for (i = 0; i < n; i++) cin >> w[i];

    KS(p, w, n, m); // Solve knapsack
    return 0;
}

