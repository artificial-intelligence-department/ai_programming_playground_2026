#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функція для обчислення факторіалу (2n)!
double factorial(int n) {
    double fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    double epsilon = 0.0001; // Задана точність за умовою

    double a = 0.1;
    double b = 1.0;
    int k = 10;
    double step = (b - a) / k; // Крок для табулювання (0.09)
    int n = 10;                // Фіксоване n за умовою

    cout << "  X         SN          SE          Y" << endl;
    cout << "-------------------------------------------" << endl;

    for (double x = a; x <= b + step / 2; x += step) {
        // Точне значення функції y = (e^x + e^-x) / 2
        double Y = (exp(x) + exp(-x)) / 2.0;

        // Обчислення SN (для фіксованого n = 10)
        double SN = 1.0; // Перший член ряду (при n = 0 це 1)
        for (int i = 1; i <= n; i++) {
            double term = pow(x, 2 * i) / factorial(2 * i);
            SN += term;
        }

        // Обчислення SE (поки доданок більший за epsilon)
        double SE = 1.0;
        int i = 1;
        double eTerm = pow(x, 2 * i) / factorial(2 * i);

        while (fabs(eTerm) > epsilon) {
            SE += eTerm;
            i++;
            eTerm = pow(x, 2 * i) / factorial(2 * i);
        }

        // Вивід таблички
        cout << fixed << setprecision(2) << setw(6) << x
             << setprecision(5) << setw(12) << SN
             << setw(12) << SE
             << setw(12) << Y << endl;
    }

    return 0;
}