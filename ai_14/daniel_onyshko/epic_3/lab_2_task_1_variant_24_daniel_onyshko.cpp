/*
Задача: Lab 2 task 1 (variant - 24)
Виконав: Онишко Даніель (ШІ-14)
*/
#include <iostream>
#include <iomanip>
#include <cmath> // Для функцій exp та sqrt

using namespace std;

int main() {

    int n_terms = 9; // кількість членів ряду 
    double sum = 0.0;


    cout << " n\t\t Значення члена (a_n)\n";

    // цикл для обчислення членів ряду та їх суми
    for (int n = 1; n <= n_terms; ++n) {
        double a_n = exp(-sqrt(n)); // обчислення загального члена ряду
        sum += a_n;                 // додавання до загальної суми

        cout << " " << n << "\t\t " << fixed << setprecision(6) << a_n << "\n";
    }

    cout << " Сума перших " << n_terms << " членів ряду: " << fixed << setprecision(6) << sum << "\n";
    return 0;
}   