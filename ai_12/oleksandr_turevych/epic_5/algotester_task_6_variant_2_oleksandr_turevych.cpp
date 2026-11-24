/*
Епік 5. Algotester Lab 6 (Варіант 2): Шахова дошка (без STL)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    char board[8][9];
    for (int i = 0; i < 8; ++i) {
        cin >> board[i];
    }

    int q;
    cin >> q;

    for (int k = 0; k < q; ++k) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if (board[x][y] != 'O') {
            cout << "X" << endl;
            continue;
        }

        bool hasB = false;
        bool hasK = false;
        bool hasN = false;
        bool hasP = false;
        bool hasQ = false;
        bool hasR = false;

        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                char piece = board[r][c];
                if (piece == 'O') {
                    continue;
                }

                int dr = abs(x - r);
                int dc = abs(y - c);

                if (piece == 'P') {
                    if (x == r + 1 && dc == 1) {
                        hasP = true;
                    }
                } else if (piece == 'R') {
                    if (r == x || c == y) {
                        hasR = true;
                    }
                } else if (piece == 'N') {
                    if ((dr == 2 && dc == 1) || (dr == 1 && dc == 2)) {
                        hasN = true;
                    }
                } else if (piece == 'B') {
                    if (dr == dc) {
                        hasB = true;
                    }
                } else if (piece == 'K') {
                    if (dr <= 1 && dc <= 1) {
                        hasK = true;
                    }
                } else if (piece == 'Q') {
                    if (r == x || c == y || dr == dc) {
                        hasQ = true;
                    }
                }
            }
        }

        if (!hasB && !hasK && !hasN && !hasP && !hasQ && !hasR) {
            cout << "O" << endl;
        } else {
            if (hasB) cout << 'B';
            if (hasK) cout << 'K';
            if (hasN) cout << 'N';
            if (hasP) cout << 'P';
            if (hasQ) cout << 'Q';
            if (hasR) cout << 'R';
            cout << endl;
        }
    }

    return 0;
}
