#include <iostream>
#include <vector>
using namespace std;

// ?? Merge two sorted parts based on profit/weight ratio
void merge(vector<float>& p, vector<float>& w, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<float> Lp(n1), Lw(n1), Rp(n2), Rw(n2);

    // Copy left and right halves
    for (int i = 0; i < n1; i++) {
        Lp[i] = p[left + i];
        Lw[i] = w[left + i];
    }
    for (int i = 0; i < n2; i++) {
        Rp[i] = p[mid + 1 + i];
        Rw[i] = w[mid + 1 + i];
    }

    // Merge by decreasing profit/weight ratio
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (Lp[i] / Lw[i] >= Rp[j] / Rw[j]) { // higher ratio first
            p[k] = Lp[i];
            w[k] = Lw[i];
            i++;
        } else {
            p[k] = Rp[j];
            w[k] = Rw[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements
    while (i < n1) { p[k] = Lp[i]; w[k] = Lw[i]; i++; k++; }
    while (j < n2) { p[k] = Rp[j]; w[k] = Rw[j]; j++; k++; }
}

// ?? Recursive merge sort to sort items by ratio
void mergeSort(vector<float>& p, vector<float>& w, int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(p, w, left, mid);
        mergeSort(p, w, mid + 1, right);
        merge(p, w, left, mid, right);
    }
}

int main() {
    int m, n;
    cout << "Enter knapsack capacity: ";
    cin >> m;
    cout << "Enter number of items: ";
    cin >> n;

    vector<float> p(n), w(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and profit for item " << i + 1 << ": ";
        cin >> w[i] >> p[i];
    }

    // Sort items by profit/weight ratio in descending order
    mergeSort(p, w, 0, n - 1);

    vector<float> x(n, 0.0); // Fraction of each item taken
    int remaining = m;

    // ?? Fill the knapsack greedily
    for (int i = 0; i < n && remaining > 0; i++) {
        if (w[i] <= remaining) {       // Take the whole item
            x[i] = 1.0;
            remaining -= w[i];
        } else {                       // Take fraction
            x[i] = (float)remaining / w[i];
            remaining = 0;
        }
    }

    // Calculate total profit
    float totalProfit = 0;
    for (int i = 0; i < n; i++) {
        totalProfit += x[i] * p[i];
    }

    // ?? Output
    cout << "\nItems taken (fractional): ";
    for (float val : x)
        cout << val << " ";

    cout << "\nTotal profit: " << totalProfit << endl;
    return 0;
}

