/*
Лабораторна робота №2, Завдання 1, Варіант 20
Станіслав Коваль
ШІ-12
*/


#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const double eps = 0.0001;
    const double e = exp(1.0);

    double sum = 0.0;
    double a = e / 100.0;
    int n = 1;
    int count = 0;

    while (fabs(a) >= eps) {
        sum += a;
        count++;
        n++;
        a = a * e / pow(100.0, 2 * n - 1);
    }

    cout << "Сума ряду a_n = e^n * 100^(-n^2) = " << fixed << setprecision(4) << sum << endl;
    cout << "Кількість врахованих членів: " << count << endl;
    return 0;
}