/*
Задача: Скільки заплатити?
Автор: Роман Лупій
Група: ШІ-13
Варіант: 1
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    // Визначаємо менше та більше з двох значень
    int lo = min(a, b);
    int hi = max(a, b);

    // Перевіряємо, чи є ціле число строго між a та b
    if (lo + 1 < hi) {
        // Якщо є, виводимо найменше таке число
        cout << lo + 1 << '\n';
    } else {
        // Якщо такого числа немає, виводимо -1
        cout << -1 << '\n';
    }

    return 0;
}