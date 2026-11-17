#include <bits/stdc++.h>
using namespace std;

#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int n = 8;
    vector<string> field(n);
    for (auto& row : field) cin >> row;

    vector<vector<string>> beats(n, vector<string>(n, ""));

    auto add = [&](int x, int y, char c) {
        if (x >= 0 && x < n && y >= 0 && y < n) beats[x][y].pb(c);
    };

    auto ray = [&](int i, int j, int dx, int dy, char c) {
        for (int x = i + dx, y = j + dy; x >= 0 && x < n && y >= 0 && y < n; x += dx, y += dy)
            add(x, y, c);
    };

    const int rdx[4] = {1, -1, 0, 0};
    const int rdy[4] = {0, 0, 1, -1};
    const int bdx[4] = {1, 1, -1, -1};
    const int bdy[4] = {1, -1, 1, -1};
    const int ndx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
    const int ndy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char curr = field[i][j];
            if (curr == 'P') {
                add(i + 1, j - 1, 'P');
                add(i + 1, j + 1, 'P');
            } else if (curr == 'R') {
                for (int d = 0; d < 4; d++) ray(i, j, rdx[d], rdy[d], 'R');
            } else if (curr == 'N') {
                for (int d = 0; d < 8; d++) add(i + ndx[d], j + ndy[d], 'N');
            } else if (curr == 'B') {
                for (int d = 0; d < 4; d++) ray(i, j, bdx[d], bdy[d], 'B');
            } else if (curr == 'Q') {
                for (int d = 0; d < 4; d++) {
                    ray(i, j, rdx[d], rdy[d], 'Q');
                    ray(i, j, bdx[d], bdy[d], 'Q');
                }
            } else if (curr == 'K') {
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++)
                        if (dx != 0 || dy != 0) add(i + dx, j + dy, 'K');
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sort(all(beats[i][j]));
            beats[i][j].erase(unique(all(beats[i][j])), beats[i][j].end());
        }
    }

    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        x--; y--;
        if (field[x][y] != 'O') {
            cout << "X\n";
        } else if (beats[x][y].empty()) {
            cout << "O\n";
        } else {
            cout << beats[x][y] << "\n";
        }
    }
    return 0;
}