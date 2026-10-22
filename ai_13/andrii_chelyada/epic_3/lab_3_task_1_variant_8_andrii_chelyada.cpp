// lab 3 task 1 variant 8
// Челяда Андрій, ШІ-13

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double PI = acos(-1.0);   // число Пі
    double a = 0.1, b = 0.8;        // межі зміни x
    int k = 10, N = 40;             // k - кількість кроків, N - кількість членів ряду для SN
    const double eps = 0.0001;      

    double h = (b - a) / k;         // крок зміни x: (0.8 - 0.1) / 10 = 0.07

    cout << "Обчислення функції" << endl;

    // Зовнішній цикл: перебір значень x від a до b
    // (i <= k, щоб останнім значенням був саме x = b)
    for (int i = 0; i <= k; i++) {
        // x рахуємо від a, а не через x += h, щоб похибка не накопичувалась
        double x = a + i * h;

        // а) Сума для заданого n (арифметичний цикл, рівно N членів)
        double SN = 0;              // накопичувач суми
        double p = 1;               // p = x^n, спочатку x^0 = 1
        for (int n = 1; n <= N; n++) {
            p *= x;                           // x^n = x^(n-1) * x
            SN += p * sin(n * PI / 4);        // додаємо n-й член ряду
        }

        // б) Сума для заданої точності (ітераційний цикл)
        double SE = 0;              // накопичувач суми
        p = x;                      // знову починаємо з x^1
        int n = 1;                  // номер поточного члена (потрібен для sin)
        while (p >= eps) {
            SE += p * sin(n * PI / 4);        // додаємо поточний член
            p *= x;                           // переходимо до x^(n+1)
            n++;                              
        }

        // Точне значення функції
        double Y = x * sin(PI / 4) / (1 - 2 * x * cos(PI / 4) + x * x);

        // Виведення результатів для поточного x
        cout << "X = " << fixed << setprecision(4) << x << endl;
        cout << "SN = " << fixed << setprecision(4) << SN << endl;
        cout << "SE = " << fixed << setprecision(4) << SE << endl;
        cout << "Y = " << fixed << setprecision(4) << Y << endl;
        cout << endl;              
    } 

    return 0;
}