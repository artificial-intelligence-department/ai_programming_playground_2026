/*
Lab 2 task 1, Нагірний Назарій, ШІ-13, Варіант № 10
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const double eps = 0.0001;
    double a = 0.5; // a_1 = 1! / (2!) = 0.5
    double sum = 0.0;
    int n = 1;

    // Цикл зупиниться на першому елементі, який виявиться меншим за eps.
    while (a >= eps) {
        sum += a;
        a /= (4 * n + 2);
        n++;
    }

    cout << "Точність eps: " << eps << endl;
    cout << "Кількість врахованих членів ряду: " << n - 1 << endl;
    cout << fixed << setprecision(6);
    cout << "Сума ряду S = " << sum << endl;

    return 0;
}