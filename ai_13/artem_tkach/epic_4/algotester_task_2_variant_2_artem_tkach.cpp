/*
 * Algotester, Лабораторна робота №2, варіант 2 - "Lab 2v2"
 * Ткач Артем
 * ШІ-13
 *
 * Умова: є масив r розміром N та три цілих числа a, b, c. Спочатку з масиву
 * видаляються всі елементи, що дорівнюють a, b або c. Після цього масив
 * перетворюється на масив сум сусідніх елементів нового масиву
 * (розмір Nnew - 1) і виводиться на екран.
 * 
 * https://algotester.com/en/ContestProblem/DisplayWithEditor/167965
 */

#include <iostream>

int removeValues(int r[], int n, int a, int b, int c) {
    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            r[newSize] = r[i];
            newSize++;
        }
    }
    return newSize;
}

int main() {
    int n;
    std::cin >> n;

    int *r = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> r[i];
    }

    int a, b, c;
    std::cin >> a >> b >> c;

    int newSize = removeValues(r, n, a, b, c);

    int m = 0;
    if (newSize > 1) {
        m = newSize - 1;
    }

    std::cout << m << "\n";
    for (int i = 0; i < m; i++) {
        std::cout << r[i] + r[i + 1] << " ";
    }
    std::cout << "\n";

    delete[] r;
    return 0;
}
