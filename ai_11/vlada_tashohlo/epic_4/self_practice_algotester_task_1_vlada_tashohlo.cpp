
/* 
Епік 4. self practice: Algotester, задача "Гра в дорозі"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAX_N = 100000;

int a[MAX_N];
int n;

// Обчислення слабкості для заданого x
double calculate(double x) {
    double maxPositive = 0;
    double maxNegative = 0;

    double currentPositive = 0;
    double currentNegative = 0;

    for (int i = 0; i < n; i++) {
        double val = a[i] - x;

        currentPositive = max(0.0, currentPositive + val);
        currentNegative = max(0.0, currentNegative - val);

        maxPositive = max(maxPositive, currentPositive);
        maxNegative = max(maxNegative, currentNegative);
    }

    return max(maxPositive, maxNegative);
}

int main() {
    cin >> n;

    int minA = 1000001;
    int maxA = -1000001;

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        minA = min(minA, a[i]);
        maxA = max(maxA, a[i]);
    }

    double left = minA;
    double right = maxA;

    // Тернарний пошук
    for (int i = 0; i < 100; i++) {
        double m1 = left + (right - left) / 3.0;
        double m2 = right - (right - left) / 3.0;

        if (calculate(m1) < calculate(m2)) {
            right = m2;
        } else {
            left = m1;
        }
    }

    cout << fixed << setprecision(10)
         << calculate((left + right) / 2.0);

    return 0;
}
