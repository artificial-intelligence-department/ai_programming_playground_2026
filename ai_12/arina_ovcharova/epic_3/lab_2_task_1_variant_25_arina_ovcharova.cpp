#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
// Lab 2, Task 1 (варіант 25):
// Знайти суму 7 членів ряду, загальний член якого a_n = n^2 * e^(-sqrt(n)).
// Використовується цикл із параметром (for).
 
int main() {
    const int TERMS = 7;   // кількість членів ряду
    double sum = 0.0;      // сума ряду
 
    cout << fixed << setprecision(6);
    cout << "Lab 2 Task 1, variant 25\n";
    cout << "Ряд: a_n = n^2 * e^(-sqrt(n)), кількість членів: " << TERMS << "\n\n";
 
    cout << setw(3) << "n" << setw(16) << "a_n" << setw(16) << "S_n" << '\n';
 
    for (int n = 1; n <= TERMS; n++) {
        // Обчислюємо n-й член ряду за загальною формулою
        double a_n = n * n * exp(-sqrt(static_cast<double>(n)));
        sum += a_n;
        cout << setw(3) << n << setw(16) << a_n << setw(16) << sum << '\n';
    }
 
    cout << "\nСума " << TERMS << " членів ряду S = " << sum << '\n';
    return 0;
}
