#include <iostream>
#include <iomanip>
/* Лаб 2 варіант 9
   Тимофій Сідлецький ШІ-13
*/
using namespace std;
// Початкова формула ряду: an = 10^n / n!
// Рекурентна формула: an+1 = an * 10 / (n + 1)
int main() {
    const double eps = 0.0001;
    int n = 0;
    double a = 1.0;
    double sum = a;

    while (a >= eps) {
        n++;
        a = a * 10.0 / n; 
        sum += a;
    }

    cout << fixed << setprecision(4) << "Отримана сума ряду: " << sum << endl;

    return 0;
}