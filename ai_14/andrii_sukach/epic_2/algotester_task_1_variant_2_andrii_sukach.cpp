/*
    Задача: Алготестер. Лабораторна робота №1. Завдання №1. Варіант №2
    Автор: Сукaч Андрій
    Група: ШІ-14
*/
#include <iostream>
using namespace std;

int main() {
long long h1, h2, h3, h4;
cin >> h1 >> h2 >> h3 >> h4;
long long d1, d2, d3, d4;
cin >> d1 >> d2 >> d3 >> d4;

if (d1 > h1 || d2 > h2 || d3 > h3 || d4 > h4) { // якщо пилять більше ніж довжина ніжки
    cout << "ERROR" << endl;
    return 0;
}

// Відпилюю ніжки по одному
h1 -= d1;
    long long hmin = min(min(h1, h2), min(h3, h4));
    long long hmax = max(max(h1, h2), max(h3, h4));
    if (hmax >= 2 * hmin) {
        cout << "NO" << endl;
        return 0;
    }

    //відпилюємо другу ніжку
    h2 -= d2;
    hmin = min(min(h1, h2), min(h3, h4));
    hmax = max(max(h1, h2), max(h3, h4));
    if (hmax >= 2 * hmin) {
        cout << "NO" << endl;
        return 0;
    }

    // відпилюємо третю ніжку
    h3 -= d3;
    hmin = min(min(h1, h2), min(h3, h4));
    hmax = max(max(h1, h2), max(h3, h4));
    if (hmax >= 2 * hmin) {
        cout << "NO" << endl;
        return 0;
    }

    //  відпилюємо четверту ніжку
    h4 -= d4;
    hmin = min(min(h1, h2), min(h3, h4));
    hmax = max(max(h1, h2), max(h3, h4));
    if (hmax >= 2 * hmin) {
        cout << "NO" << endl;
        return 0;
    }



//якщо ніжки однакові то YES + перевірка на перевертання
if (h1 == h2 && h2 == h3 && h3 == h4 && hmax < 2 * hmin) { // якщо всі ніжки мають однакову довжину
    cout << "YES" << endl;
} else {
    cout << "NO" << endl;
}
}