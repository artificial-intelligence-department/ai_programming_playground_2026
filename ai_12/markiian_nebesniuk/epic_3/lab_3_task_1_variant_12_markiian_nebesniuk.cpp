/*
Lab 3 Task 1 Variant 12
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    const double PI  = 3.14159265358979323846;
    const double a   = 0.1;
    const double b   = 0.8; 
    const int    k   = 10;
    const int    N   = 35;       // Задане n для суми SN
    const double eps = 0.0001;   // Задана точність
    const double h   = (b - a) / k;   // Крок = 0.07

    cout << "Обчислення функції" << endl;
    cout << fixed << setprecision(6);

    // Зовнішній цикл
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // Сума для заданого n (арифметичний цикл)
        double SN = 0;
        double c = 1;  // c = x^n, x^0 = 1
        for (int n = 1; n <= N; n++)
        {
            c = c * x;  // x^n = x^(n-1) * x
            SN = SN + c * cos(n * PI / 3) / n;
        }

        // Сума із заданою точністю (ітераційний цикл)
        double SE = 0;
        double term;   // Поточний доданок
        int n = 0;
        c = 1;
        do
        {
            n++;
            c = c * x;
            term = c * cos(n * PI / 3) / n;
            SE = SE + term;
        } while (abs(term) >= eps);

        // Точне значення функції
        double Y = -0.5 * log(1 - 2 * x * cos(PI / 3) + x * x);
        
        // Вивід результату
        cout << "X=" << x << "  SN=" << SN
             << "  SE=" << SE << "  Y=" << Y << endl;
    }
    return 0;
}