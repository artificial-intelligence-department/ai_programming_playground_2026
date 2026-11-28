#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    int max_h = max(x - 1, n - x) + max(y - 1, m - y);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int dist = abs(i - x) + abs(j - y);
            cout << max_h - dist << " ";
        }
        cout << "\n";
    }

    return 0;
}