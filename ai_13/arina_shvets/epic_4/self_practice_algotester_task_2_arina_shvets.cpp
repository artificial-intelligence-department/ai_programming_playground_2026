#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int a[100][100];
    int row[100] = {};
    int col[100] = {};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            row[i] += a[i][j];
            col[j] += a[i][j];
        }
    }

    int maximum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int sum = row[i] + col[j] - a[i][j];

            if (sum > maximum) {
                maximum = sum;
            }
        }
    }

    cout << maximum << endl;

    return 0;
}