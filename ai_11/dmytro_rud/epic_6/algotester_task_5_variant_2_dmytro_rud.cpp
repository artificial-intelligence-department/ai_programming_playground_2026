#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (grid[i][j] == 'S') {
                int k = i;
                while (k + 1 < n && grid[k + 1][j] == 'O') {
                    grid[k + 1][j] = 'S';
                    grid[k][j] = 'O';
                    k++;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << grid[i][j];
        }
        cout << "\n";
    }
    

    return 0;
}
