#include <iostream>
using namespace std;

bool attacks(char piece, int px, int py, int x, int y) {
    int dx = x - px;
    int dy = y - py;

    if (piece == 'P') {
        return dx == 1 && (dy == 1 || dy == -1);
    }

    if (piece == 'R') {
        return (dx == 0 && dy != 0) ||
               (dy == 0 && dx != 0);
    }

    if (piece == 'N') {
        return (dx == 2 && (dy == 1 || dy == -1)) ||
               (dx == -2 && (dy == 1 || dy == -1)) ||
               (dy == 2 && (dx == 1 || dx == -1)) ||
               (dy == -2 && (dx == 1 || dx == -1));
    }

    if (piece == 'B') {
        return dx != 0 && (dx == dy || dx == -dy);
    }

    if (piece == 'K') {
        return dx >= -1 && dx <= 1 &&
               dy >= -1 && dy <= 1 &&
               (dx != 0 || dy != 0);
    }

    if (piece == 'Q') {
        return (dx == 0 && dy != 0) ||
               (dy == 0 && dx != 0) ||
               (dx != 0 && (dx == dy || dx == -dy));
    }

    return false;
}

int main() {
    char board[8][8];

    // ввід
    string row;
    for (int i = 0; i < 8; i++) {
         cin >> row;
         for (int j = 0; j < 8; j++) board[i][j] = row[j];
    }

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;

        x--;
        y--;

        // якщо зайнятя клітинка, то скіп
        if (board[x][y] != 'O') {
            cout << "X\n";
            continue;
        }

        int count[256] = {0};

        // всі фігури на дошці перевірка
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char piece = board[i][j];

                if (piece != 'O' && attacks(piece, i, j, x, y)) {
                    count[piece]++;
                }
            }
        }

        // вивід фігур за алфавітом
        bool found = false;

        for (int c = 'A'; c <= 'Z'; c++) {
            if (count[c] > 0) {
                cout << (char)c;
                found = true;
            }
        }

        if (!found) cout << "O";
        cout << '\n';
            }

    return 0;
}