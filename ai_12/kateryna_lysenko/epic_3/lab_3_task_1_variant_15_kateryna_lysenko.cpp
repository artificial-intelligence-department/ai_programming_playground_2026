#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double a = 0.1, b = 1.0;
    const int k = 10;          // кількість кроків
    const int n = 30;          // задане n
    const double eps = 0.0001; // задана точність
    double h = (b - a) / k;    // крок

    cout << "Обчислення функції" << endl;

    for (int i = 0; i <= k; i++) {     
        double x = a + i * h;

        // а) сума для заданого n
        double an = x * x * x / 3;      // перший доданок
        double SN = an;
        for (int m = 1; m < n; m++) {
            an = -an * x * x * (4.0 * m * m - 1) / (4.0 * (m + 1) * (m + 1) - 1);
            SN += an;                   // додаємо наступний доданок.
        }

        // б) сума для заданої точності eps
        double ae = x * x * x / 3;
        double SE = 0;
        int m = 1;
        while (fabs(ae) >= eps) {       // поки доданок не став меншим за eps
            SE += ae;
            ae = -ae * x * x * (4.0 * m * m - 1) / (4.0 * (m + 1) * (m + 1) - 1);
            m++;
        }

        // точне значення функції
        double Y = (1 + x * x) / 2 * atan(x) - x / 2;
        cout << "X=" << x << " SN=" << SN << " SE=" << SE << " Y=" << Y << endl;
    }
    return 0;
}