#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (n < k || n > 3 * k) {
        cout << "Impossible" << endl;
        return 0;
    }

    int rest = n - k;   

    for (int i = 0; i < k; i++) {
        int extra = (rest > 2) ? 2 : rest;   
        rest -= extra;

        cout << 1 + extra;
        if (i < k - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}