/*Epic 3 - Завдання 1 лабораторної 2 варіант 15
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double epsilon = 0.0001;

    int n = 1;
    double term = 0.5; 
    double sum = term;

    cout << "step " << n << ": a = " << setprecision(10) << term << endl;

    while (term >= epsilon) {
        n++;
        term = term * (n * n) / pow(2.0, 2 * n - 1);
        sum += term;

        cout << "step " << n << ": a = " << setprecision(10) << term << endl;
    }

    cout << "\nSum = " << setprecision(10) << sum << endl;

    return 0;
}