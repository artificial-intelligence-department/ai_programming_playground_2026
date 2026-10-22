//Задача 0191 - Торт для Петрика
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double n, r;
    if (cin >> n >> r) {
        double result = r / sqrt(n);
        cout << fixed << setprecision(7) << result << endl;
    }
    return 0;
}