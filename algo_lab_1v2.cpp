#include <iostream>
using namespace std;

int main() {
    long long h[4];
    long long d[4];

    for (int i = 0; i < 4; ++i) cin >> h[i];
    for (int i = 0; i < 4; ++i) cin >> d[i];

    for (int i = 0; i < 4; ++i) {
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    for (int i = 0; i < 4; ++i) {
        h[i] -= d[i];

        long long h_min = h[0];
        long long h_max = h[0];

        for (int j = 1; j < 4; ++j) {
            if (h[j] < h_min) h_min = h[j];
            if (h[j] > h_max) h_max = h[j];
        }

        if (h_max >= 2 * h_min) {
            cout << "NO" << endl;
            return 0;
        }
    }

    if (h[0] == h[1] && h[1] == h[2] && h[2] == h[3] && h[0] > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}