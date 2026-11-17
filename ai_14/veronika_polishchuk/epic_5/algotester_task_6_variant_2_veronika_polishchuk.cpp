//Алготестер лабораторна 6, варіант 2

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    string board[8]; // Масив із 8 рядків, що представляють шахову дошку

    // Зчитування початкового стану шахівниці 8x8
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    
    int q;
    cin >> q; // Кількість запитів для перевірки

    // Обробка кожного запиту
    for (int k = 0; k < q; k++) {
        int x, y;
        cin >> x >> y; // Координати клітинки (у форматі 1-8)
        
        // Переведення в індексацію масиву від 0 до 7
        int r = x - 1;
        int c = y - 1;

        // Якщо цільова клітинка не порожня (не 'O'), це помилка / неможливий хід
        if (board[r][c] != 'O') {
            cout << "X" << endl;
            continue;
        }
        
        string result = ""; // Рядок для збереження символів фігур, що атакують клітинку

        // Проходимо по кожній клітинці дошки у пошуках фігур
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                char piece = board[i][j];

                // Якщо поточна клітинка порожня, пропускаємо її
                if (piece == 'O') continue;

                bool isAttacked = false;

                // Перевірка атак для кожної фігури окремо
                if (piece == 'P') { // Пішак (Pawn)
                    if ((r - i == 1) && abs(j - c) == 1) isAttacked = true;
                }
                else if (piece == 'R') { // Тура (Rook) - горизонталь або вертикаль
                    if (i == r || j == c) isAttacked = true;
                }
                else if (piece == 'N') { // Кінь (Knight) - ходи буквою "Г"
                    int dr = abs(i - r);
                    int dc = abs(j - c);
                    if ((dr == 2 && dc == 1) || (dr == 1 && dc == 2)) isAttacked = true;
                }
                else if (piece == 'B') { // Слон (Bishop) - діагоналі
                    if (abs(i - r) == abs(j - c)) isAttacked = true;
                }
                else if (piece == 'K') { // Король (King) - на 1 клітинку в будь-який бік
                    if (abs(i - r) <= 1 && abs(j - c) <= 1 && !(i == r && j == c)) isAttacked = true;
                }
                else if (piece == 'Q') { // Ферзь (Queen) - прямі лінії або діагоналі
                    if ((i == r || j / c == c || /* або */ (i == r || j == c)) || (abs(i - r) == abs(j - c))) {
                        // Виправлено для читабельності: умова для ферзя це комбінація тури та слона
                        isAttacked = (i == r || j == c) || (abs(i - r) == abs(j - c));
                    }
                }

                // Якщо фігура б'є цільову клітинку, додаємо її до загального рядка результатів
                if (isAttacked) {
                    result += piece;
                }
            }
        }

        // Якщо жодна фігура не атакує цю клітинку
        if (result == ""){
            cout << "O" << endl;
        }
        else {
            // Ручне сортування символів у рядку за алфавітом (сортування бульбашкою)
            int len = result.length();
            for (int i = 0; i < len - 1; i++) {
                for (int j = 0; j < len - i - 1; j++) {
                    if (result[j] > result[j + 1]) {
                        char temp = result[j];
                        result[j] = result[j + 1];
                        result[j + 1] = temp;
                    }
                }
            }

            // Видалення дублікатів (якщо кілька однакових фігур атакують клітинку)
            string unique_result = "";
            for (int i = 0; i < len; i++){
                if (i == 0 || result[i] != result[i-1]) {
                    unique_result += result[i];
                }
            }
            
            // Виведення унікальних відсортованих назв фігур-атакуючих
            cout << unique_result << endl;
        }
    }

    return 0;
}