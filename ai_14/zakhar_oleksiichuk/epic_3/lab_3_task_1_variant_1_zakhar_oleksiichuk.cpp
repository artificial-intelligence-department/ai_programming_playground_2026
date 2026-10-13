/*
Олексійчук Захар ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // Ініціалізація області визначення
    double a = 0.1;
    double b = 1.0;

    // Ініціалізація кількості членів суми, кроку циклу, епсилона та логарифму
    const int n = 10;
    const int k = 10;
    const double step = (b-a)/k;
    const double E = 0.0001;
    const double ln3 = log(3.0);

    // Зоанішній цикл
    for (int i = 0; i <= k; i++) {
        // х з кроком step
        double x = a + i * step;

        // Сума n
        double SN = 0;
        double a_n = 1.0;
        SN += a_n;

        for (int j = 1; j <= n; j++) {
            a_n = a_n * (x*ln3)/j;
            SN += a_n;
        }

        // Сума до eps
        a_n = 1.0;
        double SE = 0;
        SE += a_n;
        int m = 1;
        while (fabs(a_n) >= E) {
            a_n = a_n * (x*ln3)/m;
            SE += a_n;
            m++;
        }
        
        // Обчислення у^3
        double y = pow(3, x);

        cout << fixed << setprecision(8) << "X=" << x 
             << "  SN=" << SN 
             << "  SE=" << SE 
             << "  Y=" << y << "\n";
        cout << "====================================\n";
    }

}