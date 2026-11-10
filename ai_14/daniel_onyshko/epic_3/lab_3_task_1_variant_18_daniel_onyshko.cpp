/*
Задача: Lab 3 task 1 (variant - 18)
Виконав: Онишко Даніель (ШІ-14)
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    const double e = 0.0001;       // точність для випадку Б
    const double a = 0.1;
    const double b = 0.8;
    const int k = 10;
    const double step = (b - a) / k;
    const int n = 50;              // кількість членів для випадку А
    const double PI = acos(-1.0);

    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        // сума перших n = 50 членів ряду cos(2jx)/(4j^2 - 1)
        double sum_n = 0.0;
        for (int j = 1; j <= n; j++) {
            double a_n = cos(2 * j * x) / (4.0 * j * j - 1.0);
            sum_n += a_n;
        }

        // сума, поки модуль наступного члена >= e
        double sum_e = 0.0;
        int count = 1;
        while (true) {
            double a_e = cos(2 * count * x) / (4.0 * count * count - 1.0);
            if (fabs(a_e) < e) {
                break;
            }
            sum_e += a_e;
            count++;
            if (count > 10000) break; // захист від нескінченного циклу
        }

        // точне значення: y = 1/2 - (pi/4) * |sin x|
        double exact_y = 0.5 - (PI / 4.0) * fabs(sin(x));

        cout << "X = " << x
             << "  SN = " << sum_n
             << "  SE = " << sum_e
             << "  Y = " << exact_y << endl;
    }

    return 0;
}