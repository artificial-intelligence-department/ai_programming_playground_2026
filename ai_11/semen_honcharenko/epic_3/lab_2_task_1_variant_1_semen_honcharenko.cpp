/*
    Лабораторна робота 2. Завдання 1. Варіант 23.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <cmath>
using namespace std;

double factorial(int n) {
    double f = 1.0;
    for (int i = 2; i <= n; i++)
        f = f * i;
    return f;
}

int main() {
    double sum = 0;
    double a = 0;

    for (int i = 1; i <= 10; i++) {
        a = factorial(i) / pow(i, sqrt(i));
        sum += a;
    }
    cout << sum << endl;
    return 0;
}