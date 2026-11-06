#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    char a[100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    bool rows = true;
    bool cols = true;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') {
                found = true;
            }
        }

        if (!found) {
            rows = false;
        }
    }

    for (int j = 0; j < m; j++) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (a[i][j] == '1') {
                found = true;
            }
        }

        if (!found) {
            cols = false;
        }
    }

    if (rows || cols) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}