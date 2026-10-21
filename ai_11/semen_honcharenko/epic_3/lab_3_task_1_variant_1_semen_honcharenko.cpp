/*
    Лабораторна робота 3. Завдання 1. Варіант 21.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream> // input/output library
#include <cmath> // math library
#include <iomanip> // output manipulations library
using namespace std;

int main() {
    // declaring consts
    const double a = 0.1; // min x value
    const double b = 1; // max x value
    const double k = 10; // given k value
    const double d = ((b-a)/k); // step value
    const double eps = 0.0001; // given epsilon value

    double x = a; // declaring x (first x = a)

    for (int i = 0; i <= 10; i++) { // calculating cycle (11 times)
        double a_current = 0;
        double sum_n = 0; // declaring SN
        double sum_e = 0; // declaring SE
        for (int n = 0; n < 40; n++) { // calculating cycle (40 times)
            a_current = pow(-1, n)*pow(x, 2*n+1)/(2*n+1);
            sum_n += a_current;
        }
        a_current = x;
        int n = 0;
        while (abs(a_current) >= eps) {
            a_current = pow(-1, n)*pow(x, 2*n+1)/(2*n+1);
            sum_e += a_current;
            n++;
        }
        double y = atan(x);
        cout << fixed << setprecision(5);
        cout << "X=" << x << setw(10)
             << "SN=" << sum_n << setw(10)
             << "SE=" << sum_e << setw(10)
             << "Y=" << y << endl;
        x += d;
    }
    return 0;
}