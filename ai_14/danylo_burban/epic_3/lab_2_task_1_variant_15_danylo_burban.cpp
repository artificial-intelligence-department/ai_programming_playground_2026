/*Epic 3 - Завдання 1 лабораторної 2 варіант 15
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long long factorial(int x);

int main() {
    const double epsilon = pow(10, -4);

    int n = 1;
    double b = 0;
    double a = 0;

    do {
        b = a;
        a += pow(factorial(n), 2) / pow(2.0, pow(n, 2));

        cout << "step " << n << ": a = " << setprecision(10) << a << endl;

        n++;
    } while ((a - b) > epsilon);

    cout << "Sum = " << setprecision(10) << a << endl;

    return 0;
}

long long factorial(int x) {
    long long res = 1;
    for (int i = 1; i <= x; i++) {
        res = res * i;
    }
    return res;
}