/*
Algotester Task 6 Variant 2
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
int my_abs(int a) {
    return a < 0 ? -a : a;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string board[8];
    for (int i = 0; i < 8; ++i) {
        cin >> board[i];
    }
    int Q;
    if (!(cin >> Q)) return 0;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        int tx = x - 1;
        int ty = y - 1;
        if (board[tx][ty] != 'O') {
            cout << "X\n";
            continue;
        }
        string attacks = "";
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (r == tx && c == ty) continue;
                char piece = board[r][c];
                if (piece == 'O') continue;
                bool hits = false;
                if (piece == 'P') {
                    if (tx == r + 1 && (ty == c - 1 || ty == c + 1)) {
                        hits = true;
                    }
                } else if (piece == 'R') {
                    if (tx == r || ty == c) {
                        hits = true;
                    }
                } else if (piece == 'B') {
                    if (my_abs(tx - r) == my_abs(ty - c)) {
                        hits = true;
                    }
                } else if (piece == 'Q') {
                    if (tx == r || ty == c || my_abs(tx - r) == my_abs(ty - c)) {
                        hits = true;
                    }
                } else if (piece == 'N') {
                    int dr = my_abs(tx - r);
                    int dc = my_abs(ty - c);
                    if ((dr == 2 && dc == 1) || (dr == 1 && dc == 2)) {
                        hits = true;
                    }
                } else if (piece == 'K') {
                    int dr = my_abs(tx - r);
                    int dc = my_abs(ty - c);
                    if (dr <= 1 && dc <= 1) {
                        hits = true;
                    }
                }
                if (hits) {
                    attacks += piece;
                }
            }
        }
        if (attacks.empty()) {
            cout << "O\n";
        } else {
            int len = attacks.length();
            for (int i = 0; i < len; ++i) {
                for (int j = i + 1; j < len; ++j) {
                    if (attacks[i] > attacks[j]) {
                        char temp = attacks[i];
                        attacks[i] = attacks[j];
                        attacks[j] = temp;
                    }
                }
            }
            string unique_attacks = "";
            unique_attacks += attacks[0];
            for (int i = 1; i < len; ++i) {
                if (attacks[i] != attacks[i - 1]) {
                    unique_attacks += attacks[i];
                }
            }
            cout << unique_attacks << "\n";
        }
    }
}