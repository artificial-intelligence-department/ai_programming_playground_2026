#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    char grid[10][10];

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int q;
    cin >> q;

    for (int k = 0; k < q; k++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if (grid[x][y] != '0') {
            cout << 1 << "\n";
            cout << grid[x][y] << "\n";
            continue;
        }

        bool used[10] = {};

        for (int i = 0; i < n; i++) {
            used[grid[x][i] - '0'] = true;
            used[grid[i][y] - '0'] = true;
        }

        int ans[10];
        int count = 0;

        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                ans[count] = i;
                count++;
            }
        }

        cout << count << "\n";

        if (count > 0) {
            for (int i = 0; i < count; i++) {
                if (i > 0) cout << " ";
                cout << ans[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
