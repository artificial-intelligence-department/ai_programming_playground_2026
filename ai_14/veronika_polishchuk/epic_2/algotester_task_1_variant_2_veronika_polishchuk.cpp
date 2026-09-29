
/*
 * Задача: Lab 1v2 (алготестер, ніжки столу)
 * Поліщук Вероніка
 * Група 14
 */

#include <iostream>

using namespace std;

int main() {

    long long h[4] , d[4];
    // Зчитуємо початкові довжини ніжок
    for (int i = 0; i < 4; i++) {
        cin >> h[i];
    }

    // Зчитуємо довжини, які треба відпиляти
    for (int i = 0; i < 4; i++) {
        cin >> d[i];
    }

    // Перевірка на ERROR
    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    bool flipped = false;

    // Симуляція покрокового відпилювання
    for (int i = 0; i < 4; ++i) {
        h[i] -= d[i];

        long long h_min = h[0];
        long long h_max = h[0];

        // Знаходимо мінімальну та максимальну ніжку
        for (int j = 1; j < 4; ++j) {
            if (h[j] < h_min) {
                h_min = h[j];
            }
            if (h[j] > h_max) {
                h_max = h[j];
            }
        }
        // Перевіряємо умову перевертання столу
        if (h_max >= 2 * h_min) {
            flipped = true;
        }
    }
    // Якщо стіл перевернувся під час відпилювання
    if (flipped) {
        cout << "NO" << endl;
        return 0;
    }

    bool all_equal = (h[0] == h[1] && h[1] == h[2] && h[2] == h[3]);

    // Перевірка, чи всі ніжки рівні і чи не дорівнюють 0
    if (all_equal && h[0] > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}