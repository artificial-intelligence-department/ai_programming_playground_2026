/* 
Задача: Лабораторна робота №3. Завдання 1. Варіант №5. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a = 1.0;
    double b = 2.0;
    const double k = 10.0;
    double n = 15.0;
    double eps = 0.0001;
    double y;
    double sum_n;
    double sum_eps;
    double const krok = (b - a) / k;
    double x = a;
    double S;

    cout << "     Обчислення функції     \n";
while (x <= b) {
    y = exp(x);
    S = 1.0;
    sum_n = 1.0;
    for (int i = 1; i <= n; i++) {
        S = S * (x / i);
        sum_n += S;
    }
    S = 1.0;
    sum_eps = 1.0;
    int m = 1;
    while (fabs(S) >= eps) {
       S = S * (x/m);
       sum_eps += S;
       m++; }

cout << "X = " << fixed << setprecision(1) << x << "       SN = " << fixed << setprecision(5) << sum_n << "       SE = " << fixed << setprecision(5) << sum_eps << "       Y = " << fixed << setprecision(5) << y << endl;
x = x + krok; }

return 0;
}