
/*
Епік 5. Алготестер 6. Варіант 3.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    // Створення динамічної матриці n x n для збереження поля
    int** grid = new int*[n];
    for (int i = 0; i < n; ++i) {
        grid[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            // Перетворюємо символ цифри на числове значення ('0' -> 0)
            grid[i][j] = c - '0';
        }
    }

    int q;
    if (!(cin >> q)) return 0;

    // Послідовна обробка кожного запиту
    while (q--) {
        int x, y;
        cin >> x >> y;
        // Переходимо від 1-індексації з умови задачі до 0-індексації в C++
        --x; --y;

        // Якщо клітинка вже містить цифру (не 0) — варіант лише один: сама ця цифра
        if (grid[x][y] != 0) {
            cout << 1 << endl;
            cout << grid[x][y] << endl;
            continue;
        }

        // Масив-прапорець для позначення цифр 1..9, які вже зустрічалися
        bool used[10] = {false};

        // Скануємо x-й рядок та y-й стовпець і позначаємо знайдені цифри
        for (int i = 0; i < n; ++i) {
            int r_val = grid[x][i]; // Елемент у тому ж рядку
            int c_val = grid[i][y]; // Елемент у тому ж стовпці

            if (r_val >= 1 && r_val <= 9) used[r_val] = true;
            if (c_val >= 1 && c_val <= 9) used[c_val] = true;
        }

        // Рахуємо, скільки цифр від 1 до n ще вільні для вставки
        int count = 0;
        for (int d = 1; d <= n; ++d) {
            if (!used[d]) count++;
        }

        // Виводимо кількість можливих цифр
        cout << count << endl;
        
        // Якщо є допустимі варіанти — виводимо їх у порядку зростання
        if (count > 0) {
            int printed = 0;
            for (int d = 1; d <= n; ++d) {
                if (!used[d]) {
                    cout << d << (++printed == count ? "" : " ");
                }
            }
            cout << endl;
        }
    }

    // Звільнення виділеної динамічної пам'яті матриці
    for (int i = 0; i < n; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
