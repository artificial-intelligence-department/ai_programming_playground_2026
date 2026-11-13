#include <iostream>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    int a[m];
    int cur[n];
    int pos[n];

    for (int i = 0; i < m; i++) cin >> a[i];

    for (int b = 0; b < m; b += n) {
        for (int p = 0; p < n; p++) {
            cur[p] = p;
            pos[p] = p;
        }
        for (int p = 1; p < n; p++) {
            int target = a[b + p];
            int j = pos[target];
            cout << j - p << endl;

            int x = cur[p], y = cur[j];
            cur[p] = y;
            cur[j] = x;
            pos[y] = p;
            pos[x] = j;
        }
    }
    return 0;
}
