#include <iostream>
using namespace std;
int my_abs(int x) {
    return x < 0 ? -x : x;
}
bool attacks(char type, int fr, int fc, int tr, int tc) {
    int dr = tr - fr;
    int dc = tc - fc;
    if (dr == 0 && dc == 0) return false;
    switch (type) {
        case 'P':
            return dr == 1 && (dc == 1 || dc == -1);
        case 'R':
            return dr == 0 || dc == 0;
        case 'B':
            return my_abs(dr) == my_abs(dc);
        case 'Q':
            return dr == 0 || dc == 0 || my_abs(dr) == my_abs(dc);
        case 'N':
            return (my_abs(dr) == 1 && my_abs(dc) == 2) ||
                   (my_abs(dr) == 2 && my_abs(dc) == 1);
        case 'K':
            return my_abs(dr) <= 1 && my_abs(dc) <= 1;
        default:
            return false;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char board[8][9];
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        int tr = x - 1;
        int tc = y - 1;
        if (board[tr][tc] != 'O') {
            cout << "X\n";
            continue;
        }
        bool attackers[128] = {false};
        bool has_attackers = false;

        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                char p = board[r][c];
                if (p != 'O' && attacks(p, r, c, tr, tc)) {
                    attackers[(int)p] = true;
                    has_attackers = true;
                }
            }
        }
        if (!has_attackers){
            cout << "O\n";
        } else {
            for (char ch = 'A'; ch <= 'Z'; ch++) {
                if (attackers[(int)ch]) {
                    cout << ch;
                }
            }
            cout << "\n";
        }
    }
    return 0;
}
