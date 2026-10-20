#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Ініціалізація початкових даних згідно з варіантом 4
    double a = 0.1;
    double b = 0.8;
    int k = 10;
    double step = (b - a) / k;
    int n_given = 10;
    double epsilon = 0.0001;

    // Заголовок таблиці результатів
    cout << "Обчислення функції" << endl;

    // Зовнішній цикл для зміни параметра x
    for (double x = a; x <= b + 1e-9; x += step) {
        
        // 1. Точне значення функції Y
        double Y = x * atan(x) - log(sqrt(1 + x * x));

        // 2. Обчислення суми для заданого n (SN)
        double SN = 0.0;
        for (int n = 1; n <= n_given; ++n) {
            // Формула загального члена ряду
            double term = pow(-1, n + 1) * pow(x, 2 * n) / (2.0 * n * (2.0 * n - 1.0));
            SN += term;
        }

        // 3. Обчислення суми для заданої точності epsilon (SE)
        double SE = 0.0;
        int n = 1;
        // Обчислюємо перший елемент
        double term = pow(-1, n + 1) * pow(x, 2 * n) / (2.0 * n * (2.0 * n - 1.0));
        
        // Ітераційний цикл: сумуємо, поки похибка більша за епсилон
        while (abs(term) >= epsilon) {
            SE += term;
            n++;
            term = pow(-1, n + 1) * pow(x, 2 * n) / (2.0 * n * (2.0 * n - 1.0));
        }

        // Виведення результатів
        cout << "X=" << fixed << setprecision(4) << x 
             << "   SN=" << SN 
             << "   SE=" << SE 
             << "   Y=" << Y << endl;
    }

    return 0;
}