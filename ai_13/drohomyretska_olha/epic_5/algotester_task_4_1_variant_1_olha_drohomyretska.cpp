/*
Задача: Алготестер. Лабораторна робота №4. Рішення з STL
Варіант: 1
Автор: Ольга Дрогомирецька
Група: Ші-13
*/
#include <iostream>
#include <algorithm>
using namespace std;

void show(int result[], int size);

int main() {
    int first[100];
    int second[100];
    int result[200];

    int n, m;

    // Вводимо перший масив.
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> first[i];
    }
    // Вводимо другий масив.
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> second[i];
    }
    // Сортуємо масиви.
    sort(first, first + n);
    sort(second, second + m);

    int size;

    // Різниця першого та другого масивів.
    size = set_difference(
        first, first + n,
        second, second + m,
        result
    ) - result;

    show(result, size);

    // Різниця другого та першого масивів.
    size = set_difference(
        second, second + m,
        first, first + n,
        result
    ) - result;

    show(result, size);

    // Перетин.
    size = set_intersection(
        first, first + n,
        second, second + m,
        result
    ) - result;

    show(result, size);

    // Об'єднання.
    size = set_union(
        first, first + n,
        second, second + m,
        result
    ) - result;

    show(result, size);

    // Симетрична різниця.
    size = set_symmetric_difference(
        first, first + n,
        second, second + m,
        result
    ) - result;

    show(result, size);
    return 0;
}
// Виводимо кількість елементів та самі елементи.
void show(int result[], int size) {
    cout << size << "\n";

    for (int i = 0; i < size; i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << result[i];
    }
    cout << "\n\n";
}