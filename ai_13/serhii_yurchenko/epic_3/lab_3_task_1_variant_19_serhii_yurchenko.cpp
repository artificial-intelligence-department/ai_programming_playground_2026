/*
Lab 3 task 1 varian 19
Serhii Yurchenko
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
int main() {
    const double A = 0.1;      // початок діапазону
    const double B = 1.0;      // кінець діапазону
    const int K = 10;          // кількість кроків
    const int N = 20;          // кількість доданків для випадку а)
    const double EPS = 0.0001; // точність для випадку б)
 
    double h = (B - A) / K;
 
    cout << fixed << setprecision(6);
    cout << "Обчислення функції\n";
 
    // Зовнішній цикл: зміна параметра x
    for (int i = 0; i <= K; i++) {
        double x = A + i * h;
 
        // а) сума для заданого n (арифметичний цикл)
        double term = 1;
        double sn = 1;
        for (int n = 1; n <= N; n++) {
            term = term * 2 * x / n;
            sn += term;
        }
 
        // б) сума для заданої точності (ітераційний цикл)
        term = 1;
        double se = 0;
        int n = 0;
        while (term >= EPS) {
            se += term;
            n++;
            term = term * 2 * x / n;
        }
 
        // Точне значення функції
        double y = exp(2 * x);
 
        cout << "X=" << x << "  SN=" << sn << "  SE=" << se << "  Y=" << y << "\n";
    }
 
    return 0;
}