
#include <iostream>
using namespace std;

int minimIndex(int prices[], int n) {
    int minIdx = -1;
    for (int i = 0; i < n; i++) {
        if (prices[i] != -1 && (minIdx == -1 || prices[i] < prices[minIdx])) {
            minIdx = i;
        }
    }
    return minIdx;
}

int main() {
    int money, n;
    cin >> money >> n;

    int prices[1000];

    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    int count = 0;

    while (true) {
        int minIdx = minimIndex(prices, n);
        if (minIdx == -1 || prices[minIdx] > money) {
            break;
        }
        money -= prices[minIdx];
        prices[minIdx] = -1; // Mark the item as bought
        count++;
    }

    cout << count;

    return 0;
}
