#include <iostream>
#include <cmath>     // Для використання функції pow()
#include <iomanip>

using namespace std;

int main() {
    const double EPSILON = 0.0001;
    double sum = 0.0;
    int n = 1;
    double a = pow(10, n) / 1.0; 

    while (a >= EPSILON) {
        sum += a;
        a = a * 10.0 / (n + 1);
        n++;
    }

    cout << "Задана точність епсилон: " << EPSILON << endl;
    cout << "Кількість просумованих членів: " << n - 1 << endl;
    cout << "Сума ряду: " << fixed << setprecision(4) << sum << endl;


    return 0;
}