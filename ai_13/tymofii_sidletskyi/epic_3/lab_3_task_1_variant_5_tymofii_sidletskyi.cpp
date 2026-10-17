#include <iostream>
#include <iomanip>
#include <cmath>
/* Лаб 3 варіант 5
   Тимофій Сідлецький ШІ-13
*/
using namespace std;

int main() {
    double a = 1.0;
    double b = 2.0;
    int k = 10;
    double h = (b - a) / k; // крок зміни x
    
    int n_fixed = 15;      // задане n для пункту a)
    double eps = 0.0001;   // задана точність для пункту б)

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // а) Обчислення суми SN
        double sn = 1.0; 
        double term_n = 1.0;
        for (int n = 1; n <= n_fixed; n++) {
            term_n = term_n * x / n;
            sn += term_n;
        }

        // б) Обчислення суми SE
        double se = 1.0;
        double term_e = 1.0;
        int n_e = 1;
        while (term_e > eps) {
            term_e = term_e * x / n_e;
            se += term_e;
            n_e++;
        }

        // Точне значення функції для порівняння
        double y = exp(x);

        cout << fixed << setprecision(4) << "X=" << x << "      SN=" << sn << "     SE=" << se << "     Y=" << y << endl;
    }

    return 0;
}