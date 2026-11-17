#include <iostream>
#include <cmath>     // для abs (модуль числа)
#include <algorithm> // для sort
#include <string>    // для роботи з рядками

using namespace std;

int main() {
    // Звичайний масив 8 на 8
    char board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> board[i][j];
        }
    }

    int q;
    cin >> q;

    // Цикл для кожного запиту
    for (int k = 0; k < q; k++) {
        int x, y;
        cin >> x >> y;

        // Координати від 0 до 7
        int r = x - 1;
        int c = y - 1;  

        // Якщо клітинка не пуста то виводимо X і йдемо далі
        if (board[r][c] != 'O') {
            cout << "X\n";
            continue;
        }

        string ans = "";

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char piece = board[i][j]; 
                
                // Пусті клітинки пропускаємо
                if (piece == 'O') continue;

                // Відстань між клітинкою запиту і фігурою
                int dx = abs(r - i);
                int dy = abs(c - j);    
                
                bool attacks = false;

                // Пішак: б'є по діагоналі "вниз" (ціль на 1 рядок нижче: r - i == 1 
                // і на 1 стовпець вліво/вправо: dy == 1)
                if (piece == 'P' && (r - i == 1) && dy == 1) attacks = true;
                
                // Тура: б'є прямо. Відстань по вертикалі 0 (стоять на одному рядку) 
                // АБО відстань по горизонталі 0 (стоять в одному стовпці)
                if (piece == 'R' && (dx == 0 || dy == 0)) attacks = true;
                
                // Слон: б'є по діагоналі. Зсув по вертикалі дорівнює зсуву по горизонталі
                if (piece == 'B' && (dx == dy)) attacks = true;
                
                // Королева: це Тура + Слон разом. Беремо їхні умови і ліпимо через АБО (||)
                if (piece == 'Q' && (dx == 0 || dy == 0 || dx == dy)) attacks = true;
                
                // Король: б'є навколо себе. Відстань до цілі не перевищує 1 клітинку в будь-якому напрямку
                if (piece == 'K' && dx <= 1 && dy <= 1) attacks = true;
                
                // Кінь: ходить літерою "г". Або 2 кроки по вертикалі і 1 по горизонталі, або навпаки
                if (piece == 'N' && ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) attacks = true;
                
                // Якщо фігура б'є і її ще немає в результаті
                if (attacks) {
                    if (ans.find(piece) == string::npos) {
                        ans += piece;
                    }
                }
            }
        }

        if (ans == "") {
            cout << "O\n";
        } else {
            sort(ans.begin(), ans.end()); 
            cout << ans << "\n";
        }
    }

    return 0;
}
