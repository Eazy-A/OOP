#include <iostream>
#include <climits>
using namespace std;

int num_left_over(int coins[], int n, int left_over) {
    int count = 0;
    for (int i = n - 1; i >= 0; --i) {
        while (left_over >= coins[i]) {
            left_over -= coins[i];
            count++;
        }
    }
    return left_over == 0 ? count : -1;
}

int main() {
    int coins[100];
    int n;
    cin >> n;

    int max = INT_MIN, min = INT_MAX, mini = 0;
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    int amount;
    cin >> amount;

    // Find the largest coin
    for (int i = 0; i < n; ++i) {
        if (coins[i] > max) {
            max = coins[i];
        }
    }

    // Greedy calculation: use the largest coin as much as possible
    int greedy = amount / max;
    int left_over = amount - greedy * max;

    // Now, calculate the number of coins needed to make up the left_over
    int result = greedy + num_left_over(coins, n, left_over);

    cout << "Minimum coins required: " << result << endl;
}
