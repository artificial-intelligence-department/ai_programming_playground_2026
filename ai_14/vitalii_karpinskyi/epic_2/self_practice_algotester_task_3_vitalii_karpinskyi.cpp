/*
Задача: Темрява
Карпінський Віталій
СШІ-14
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Введення даних
    long long n, k;
    cin >> n >> k;
    // Якщо значення = 0, то Соломії немає
    if (n <= 0 || k <= 0) {
        cout << fixed << setprecision(6) << 0.0 << endl;
        return 0;
    }
    // Розрахунок ймовірності
    double probability = 0.0;
    double multip = n * k;
    probability = 1.0 / multip;
    cout << fixed << setprecision(6) << probability << endl;

    return 0;
}