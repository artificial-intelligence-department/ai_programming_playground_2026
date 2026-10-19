/*
    Задача: Лабораторна робота №3. Варіант №12
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a = 0.1;
    double b = 0.8;
    int k = 10;
    double h = (b - a) / k;
    int n = 35;
    double accuracy = 0.0001;
    double pi = 3.14;

    cout << fixed << setprecision(6);
    cout << "Обчислення функції:" << endl;

    for (double x = a; x <= b + h/2; x += h) {
        double Y = -0.5 * log(1 - 2 * x * cos(pi / 3) + pow(x, 2));
        double SN = 0.0;
        for (int i = 1; i < n; i++) {
            double a = (pow(x, i) * cos(i * pi / 3)) / i;
            SN += a;
        }
        double SE = 0.0;
        double a_current;
        int j = 1;
        do {
            a_current = (pow(x, j) * cos(j * pi / 3.0)) / j;
            SE += a_current;
            j++;
        } while (abs(a_current) >= accuracy);
        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << endl;
    }
    return 0;
}