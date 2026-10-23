#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    bool can[2001] = {};
    can[2 * n] = true;

    for (int i = 0; i < m; i++) {
        bool next[2001] = {};
        for (int y = 0; y <= 2 * n; y++) {
            if (!can[y]) continue;
            if (y == 0) {
                next[0] = true;
                continue;
            }
            if (y % 2 == 0) next[y / 2] = true;
            next[y - 1] = true;
        }
        for (int y = 0; y <= 2 * n; y++) can[y] = next[y];
    }

    int k = 0;
    for (int y = 0; y <= 2 * n; y++)
        if (can[y]) k++;
    cout << k << endl;

    cout << fixed << setprecision(1);
    for (int y = 0; y <= 2 * n; y++)
        if (can[y]) cout << y / 2.0 << " ";
    cout << endl;

    return 0;
}