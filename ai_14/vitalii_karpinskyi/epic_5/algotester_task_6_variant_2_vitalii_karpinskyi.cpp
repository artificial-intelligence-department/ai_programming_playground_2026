#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Функції для перевірки чи атакує фігура позиію
bool Pawn(int rows, int cols, int x, int y) {
    int diffC = abs(cols - y);
    if (x - rows == 1 && diffC == 1) {
        return true;
    }
    return false;
}

bool Rook(int rows, int cols, int x, int y) {
    if (rows == x || cols == y) {
        return true;
    }
    return false;
}

bool Knigth(int rows, int cols, int x, int y) {
    int diffR = abs(rows - x);
    int diffC = abs(cols - y);
    if ((diffR == 2 && diffC == 1) ||(diffR == 1 && diffC == 2)) {
        return true;
    }
    return false;
}

bool Bishop(int rows, int cols, int x, int y) {
    int diffR = abs(rows - x);
    int diffC = abs(cols - y);
    if (diffR == diffC) {
        return true;
    }
    return false;
    
}

bool King(int rows, int cols, int x, int y) {
    int diffR = abs(rows - x);
    int diffC = abs(cols - y);
    if (diffR < 2 && diffC < 2) {
        return true;
    }
    return false;
}

bool Quenn(int rows, int cols, int x, int y) {
    int diffR = abs(rows - x);
    int diffC = abs(cols - y);
    if ((rows == x || cols == y) || diffR == diffC) {
        return true;
    }
    return false;
    
}

int main() {
    // Зчитування даних
    string board[8];
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        // Якщо клітинка зайнята фігурою виводимо X
        if (board[x][y] != 'O') {
            cout << "X\n";
            continue;
        }
        // Позначаємо у масиві прапорців усі фігури, що б'ють клітинку
        bool hit[128] = {false};
        for (int rows = 0; rows < 8; rows++) {
            for (int cols = 0; cols < 8; cols++) {
                if (board[rows][cols] == 'O') {
                    continue;
                }
                if (board[rows][cols] == 'P') {
                    if (Pawn(rows, cols, x, y)) {
                        hit['P'] = true;
                    }
                } else if (board[rows][cols] == 'R') {
                    if (Rook(rows, cols, x, y)) {
                        hit['R'] = true;
                    }
                } else if (board[rows][cols] == 'N') {
                    if (Knigth(rows, cols, x, y)) {
                        hit['N'] = true;
                    }
                } else if (board[rows][cols] == 'B') {
                    if (Bishop(rows, cols, x, y)) {
                        hit['B'] = true;
                    }
                } else if (board[rows][cols] == 'K') {
                    if (King(rows, cols, x, y)) {
                        hit['K'] = true;
                    }
                } else if (board[rows][cols] == 'Q') {
                    if (Quenn(rows, cols, x, y)) {
                        hit['Q'] = true;
                    }
                }
            }
        }
        // Збираємо знайдені фігури одразу в алфавітному порядку без дублікатів
        string final = "";
        const char pieces[] = {'B', 'K', 'N', 'P', 'Q', 'R'};
        for (int j = 0; j < 6; j++) {
            if (hit[pieces[j]]) {
                final += pieces[j];
            }
        }
        if (final == "") {
            cout << "O\n";
        } else {
            cout << final << "\n";
        }
    }
    return 0;   
}