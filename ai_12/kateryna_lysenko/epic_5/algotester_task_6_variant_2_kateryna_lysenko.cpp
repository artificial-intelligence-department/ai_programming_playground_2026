/*
Задача: Algotester Lab 6
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

// Чи атакує фігура t, що стоїть у (pr, pc), клітинку (r, c).
// Інші фігури напад не блокують, тому перевіряємо лише геометрію.
bool attacks(char t, int pr, int pc, int r, int c) {
    int dr = r - pr, dc = c - pc;
    int ar = abs(dr), ac = abs(dc);
    if (dr == 0 && dc == 0) return false;
    switch (t) {
        case 'P': return dr == 1 && ac == 1;                 // пішак б'є вниз по діагоналі
        case 'R': return dr == 0 || dc == 0;
        case 'N': return (ar == 1 && ac == 2) || (ar == 2 && ac == 1);
        case 'B': return ar == ac;
        case 'K': return ar <= 1 && ac <= 1;
        case 'Q': return dr == 0 || dc == 0 || ar == ac;
    }
    return false;
}

int main() {
    string board[8];
    for (int i = 0; i < 8; i++) cin >> board[i];
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;                 // x — рядок, y — стовпець (нумерація з 1)
        x--; y--;
        if (board[x][y] != 'O') {
            cout << "X\n";
            continue;
        }
        string res;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] != 'O' && attacks(board[i][j], i, j, x, y))
                    res += board[i][j];
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());   // кожну літеру виводимо один раз
        cout << (res.empty() ? "O" : res) << "\n";
    }
    return 0;
}