
/* 
Епік 3. Лабораторна робота 2. Варіант 15.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const double eps = 0.0001;
    double sum = 0.0;
    int n = 1;
    double a = 0.5; // a1 = (1!)^2 / 2^1

    cout << "===== Сума ряду (n!)^2 / 2^(n^2), eps = 0.0001 =====" << endl << endl;

    // while: додаємо поки точність не досягнута (a_n < eps)
    while (a >= eps) {
        sum += a;
        cout << "n = " << n << ": a = " << fixed << setprecision(8) << a
             << "  sum = " << fixed << setprecision(8) << sum << endl;
        double nn = n + 1;
        a = a * (nn * nn) / pow(2.0, 2 * n + 1); // рекурентна формула
        n++;
    }

    cout << "===== Результат =====" << endl;
    cout << "Сума ряду: " << fixed << setprecision(5) << sum << endl;
    cout << "Додано членів: " << n - 1 << endl;
    return 0;
}