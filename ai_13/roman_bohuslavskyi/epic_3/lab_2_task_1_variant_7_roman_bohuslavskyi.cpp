/*
Задача:  Лабораторна робота №2, Варіант №7
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    // Початкові значення
    double eps = 0.0001;
    int n = 1;
    double sum = 0;
    double current = 1.0 / ((3 * n - 2) * (3 * n + 1));

    // Обчислення суми ряду
    while (current >= eps) {
        sum += current;
        current = current * (3 * n - 2) / (3 * n + 4);
        n++;
    }

    // Вивід результату
    cout << endl;
    cout << "Сума ряду: " << sum << endl;

    return 0;
}
