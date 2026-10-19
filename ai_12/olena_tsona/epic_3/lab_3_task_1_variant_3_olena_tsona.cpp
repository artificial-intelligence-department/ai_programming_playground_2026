/*Lab 3 Task 1 Variant 3
Цьона Олена
ШІ-12 */

#include <iostream>
#include <cmath>

using namespace std;
 
int main()
{
    double a = 0.1, b = 1;      // діапазон зміни x
    int k = 10;                 // кількість кроків
    int n = 10;                 // задане n
    double eps = 0.0001;        // задана точність епселонт
    double h = (b - a) / k;     // крок
 
    cout << "Обчислення функції y = sin(x)" << endl;
 
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;       // x = x + h
 
        // а) сума для заданого n 
        double dodanok = x;     
        double SN = dodanok;
        for (int m = 1; m <= n; m++)
        {
            dodanok = -dodanok * pow(x, 2) / ((2 * m) * (2 * m + 1));
            SN = SN + dodanok;
        }
 
        // б) сума для заданої точності епселонт
        dodanok = x;
        double SE = 0;
        int m = 0;
        while (fabs(dodanok) >= eps)
        {
            SE = SE + dodanok;
            m++;
            dodanok = -dodanok * pow(x, 2) / ((2 * m) * (2 * m + 1));
        }
 
        // точне значення функції
        double Y = sin(x);
 
        cout << "X=" << x << "   SN=" << SN
             << "   SE=" << SE << "   Y=" << Y << endl;
    }
 
    return 0;
}