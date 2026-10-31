#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    char grid[100][100];
    int row_counts[100][26] = {0};
    int col_counts[100][26] = {0};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];

            int idx = grid[i][j] - 'a';
            row_counts[i][idx]++;
            col_counts[j][idx]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int idx = grid[i][j] - 'a';

            if (row_counts[i][idx] == 1 &&
                col_counts[j][idx] == 1) {
                cout << grid[i][j];
            }
        }
    }

    cout << '\n';

    return 0;
}