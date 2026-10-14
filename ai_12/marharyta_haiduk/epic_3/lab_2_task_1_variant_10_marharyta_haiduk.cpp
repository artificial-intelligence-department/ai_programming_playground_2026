/*
    Задача: Лабораторна робота №2. Завдання №1. Варіант №10
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    double eps = 0.0001;
    int n = 1;
    double a = 0.5; // a1 = 1!/2!
    double sum = 0;

    while (a >= eps) {
        sum += a;
        a = a / (2.0 * (2 * n + 1)); // a(n+1)
        n++;
    }
    cout << "Сума ряду з точністю 0.0001: " << sum << endl;
    return 0;
}