/*
    Задача: Лабораторна робота №1. Завдання №2. Варіант №25
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int n, m;
    int n1 ,m1;
    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть m: ";
    cin >> m;
    // Вираз 1: - -m - ++n
    // - -m = m; ++n = n+1; result1 = m - (n+1)
    cout << "Вираз 1: - -m - ++n" << endl;
    m1 = m; 
    n1 = n;
    cout << "Початкові значення: m = " << m << ", n = " << n << endl;
    int result1 = - -m - ++n;
    cout << "Результат виразу: " << result1 << endl;
    cout << "Змінені значення: m = " << m << ", n = " << n << endl;

    // Вираз 2: m*n < n++
    // m*n = m*n (старе n); n++ = старе n, потім n+1; result2 = (m*n) < старе n
    cout << "Вираз 2: m*n < n++" << endl;
    m = m1;
    n = n1;
    cout << "Початкові значення: m = " << m << ", n = " << n << endl;
    int left = m * n;
    bool result2 = left < n++;
    cout << "Результат виразу: " << result2 << endl;
    cout << "Змінені значення: m = " << m << ", n = " << n << endl;

    // Вираз 3: n-- > m++
    // n-- = старе n, потім n-1; m++ = старе m, потім m+1; result3 = старе n > старе m
    cout << "Вираз 3: n-- > m++" << endl;
    m = m1;
    n = n1;
    cout << "Початкові значення: m = " << m << ", n = " << n << endl;
    bool result3 = n-- > m++; 
    cout << "Результат виразу: " << result3 << endl;
    cout << "Змінені значення: m = " << m << ", n = " << n << endl;
    return 0;
}