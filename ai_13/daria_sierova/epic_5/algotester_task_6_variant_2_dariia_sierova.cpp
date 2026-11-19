#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string board[8];
    for (int i = 0; i < 8; i++) {
        cin >> board[i]; // 8 вказівників на рядки
    }

    int Q;
    cin >> Q;

    while (Q--) { // поки не стане 0
        int x, y;
        cin >> x >> y;
        int target_r = x - 1; // індекси
        int target_c = y - 1;

        if (board[target_r][target_c] != 'O') {
            cout << "X\n";
            continue;
        }

        string attackers = ""; 

        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                char piece = board[r][c];
                if (piece == 'O') continue;

                int dx = abs(r - target_r); //відстань по вертикалі
                int dy = abs(c - target_c); //відстань по горизонталі
                bool attacks = false;

                if (piece == 'P') { // на рядок вище і сусідня колонка
                    if (r + 1 == target_r && dy == 1) attacks = true; 
                } else if (piece == 'R') { //прямо по горизонталі або вертикалі
                    if (r == target_r || c == target_c) attacks = true;
                } else if (piece == 'B') { // діагональ
                    if (dx == dy) attacks = true;
                } else if (piece == 'Q') { // діагональ горизонталь вертикаль
                    if (r == target_r || c == target_c || dx == dy) attacks = true;
                } else if (piece == 'N') { 
                    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) attacks = true;
                } else if (piece == 'K') {//1 клітинка будь куди
                    if (dx <= 1 && dy <= 1) attacks = true;
                }

                if (attacks) {
                    attackers += piece;
                }
            }
        }

        if (attackers.empty()) {
            cout << "O\n";
        } else {
            sort(attackers.begin(), attackers.end());
            // юнік знаходить зайвий дублікат ерейз відкидає
            attackers.erase(unique(attackers.begin(), attackers.end()), attackers.end());
            cout << attackers << endl;
        }
    }

    return 0;
}
