/*
Назва: Алготестер Лабораторна 6 варіант 2
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>

using namespace std;

int my_abs(int a) {
    return a < 0 ? -a : a;
}

int main() {
    char board[8][8];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j];
        }
    }

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        int x, y;
        cin >> x >> y;

        int r = x - 1;
        int c = y - 1;

        if (board[r][c] != 'O') {
            cout << "X\n";
            continue;
        }

        bool hasB = false, hasK = false, hasN = false, hasP = false, hasQ = false, hasR = false;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char piece = board[i][j];
                if (piece == 'O') continue;

                int dr = my_abs(i - r);
                int dc = my_abs(j - c);

                if (piece == 'B' && (dr == dc)) {
                    hasB = true;
                } else if (piece == 'K' && (dr <= 1 && dc <= 1)) {
                    hasK = true;
                } else if (piece == 'N' && ((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) {
                    hasN = true;
                } else if (piece == 'P' && (i + 1 == r && dc == 1)) {
                    hasP = true;
                } else if (piece == 'Q' && (i == r || j == c || dr == dc)) {
                    hasQ = true;
                } else if (piece == 'R' && (i == r || j == c)) {
                    hasR = true;
                }
            }
        }

        if (!hasB && !hasK && !hasN && !hasP && !hasQ && !hasR) {
            cout << "O\n";
        } else {
            if (hasB) cout << 'B';
            if (hasK) cout << 'K';
            if (hasN) cout << 'N';
            if (hasP) cout << 'P';
            if (hasQ) cout << 'Q';
            if (hasR) cout << 'R';
            cout << "\n";
        }
    }

    return 0;
}