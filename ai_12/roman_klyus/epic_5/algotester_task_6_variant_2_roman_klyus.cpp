#include <iostream>
#include <cstdlib>
using namespace std;

bool attacks(char piece, int dx, int dy) {
    switch (piece) {
        case 'P': return dx == 1 && abs(dy) == 1;
        case 'R': return dx == 0 || dy == 0;
        case 'B': return abs(dx) == abs(dy);
        case 'Q': return attacks('R', dx, dy) || attacks('B', dx, dy);
        case 'K': return abs(dx) <= 1 && abs(dy) <= 1;
        case 'N': return abs(dx) * abs(dy) == 2;
    }
    return false;
}

bool attacked_before(char board[8][9], char piece, int x, int y) {
    for (int r {0}; r < 8; r++)
        for (int c {0}; c < 8; c++)
            if (board[r][c] == piece && attacks(piece, x - r, y - c))
                return true;
    return false;
}

int attackers(char board[8][9], int x, int y, char* res) {
    int n {0};
    for (const char *p = "BKNPQR"; *p; p++)
        if (attacked_before(board, *p, x, y))
            res[n++] = *p;
    res[n] = '\0';
    return n;
}

int main() {
    char board[8][9];
    for (int i {0}; i < 8; i++) cin >> board[i];

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        if (board[x][y] != 'O') cout << "X\n";
        else {
            char res[65];
            cout << (attackers(board, x, y, res) == 0 ? "O" : res) << '\n';
        }
    }
}