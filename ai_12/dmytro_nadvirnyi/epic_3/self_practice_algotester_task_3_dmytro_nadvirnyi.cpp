/*  Зуби
    0182    */
#include <iostream>
using namespace std;

int findBest(int n, long long k) {
    int current = 0, best = 0;
    long long a;

    for (int i = 0; i < n; i++) {
        cin >> a;

        if (a >= k) {
            current++;
        } else {
            current = 0;
        }

        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main() {
    int n;
    long long k;

    cin >> n >> k;

    cout << findBest(n, k);

    return 0;
}
