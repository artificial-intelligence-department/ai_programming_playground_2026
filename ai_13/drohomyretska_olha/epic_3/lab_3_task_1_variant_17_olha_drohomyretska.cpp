/*
Задача: Лабораторна робота №3, Варіант 17
Автор: Дрогомирецька Ольга
Група: ШІ-13
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a = 0.1;
    double b = 1.0;
    int k = 10;
    int n = 10;
    double eps = 0.0001;
    double h = (b - a) / k;

    cout << fixed << setprecision(6);
    cout << "Обчислення функції" << endl;

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        double term = 1.0;
        double SN = 1.0;
        for (int j = 1; j <= n; j++) {
            term = term * x * x / ((2.0 * j - 1) * (2.0 * j));
            SN += term;
        }
        term = 1.0;
        double SE = 0.0;
        int m = 0;
        while (term >= eps) {
            SE += term;
            m++;
            term = term * x * x / ((2.0 * m - 1) * (2.0 * m));
        }
        double Y = (exp(x) + exp(-x)) / 2;
        cout << "X= " << x << "  SN= " << SN << "  SE= " << SE << " Y= " << Y << endl;
    }
    return 0;
}