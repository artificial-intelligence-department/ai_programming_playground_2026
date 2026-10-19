/*
    Задача: Лабораторна робота №2. Варіант №23
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <cmath>
using namespace std;

double factorial(int n) {
    double factorial = 1.0;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    return factorial;
}

int main() {
    double total_sum = 0.0;
    for (int n = 1; n <= 10; n++) {
        double numerator = factorial(n);
        double denominator = pow(n, sqrt(n));
        double a = numerator / denominator;
        total_sum += a;
    }
    cout << "Сума десяти членів ряду: " << total_sum << endl;
    return 0;
}