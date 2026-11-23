#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    int n, m, x, y;
    Point p;
    cin >> n >> m >> p.x >> p.y;

    int peak = max(p.x - 1, n - p.x) + max(p.y - 1, m - p.y);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h = peak - abs(i - p.x) - abs(j - p.y);
            cout << h << ' ';
        }
        cout << '\n';
    }
    return 0;
}