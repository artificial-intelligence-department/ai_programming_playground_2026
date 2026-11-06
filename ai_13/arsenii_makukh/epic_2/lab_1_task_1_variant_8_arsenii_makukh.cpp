/*
    Назва: Lab 1 Task 1 Variant 8
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*
    ((a+b)⁴ - (a⁴ + 4a³b + 6a²b²)) / (4ab³ + b⁴)
    при а=100, b=0.001
*/

int main() {
    double a1 = 100, b1 = 0.001;
    double a_1 = a1 + b1;
    double a_2 = pow(a_1, 4);
    double a_3 = pow(a1, 4);
    double a_4 = 4 * pow(a1, 3) * b1;
    double a_5 = 6 * pow(a1, 2) * pow(b1, 2);
    double a_6 = 4 * a1 * pow(b1, 3);
    double a_7 = pow(b1, 4);
    double doubl = (a_2 - (a_3 + a_4 + a_5)) / (a_6 + a_7);

    float a2 = 100.0f, b2 = 0.001f;
    float a_8 = a2 + b2;
    float a_9 = pow(a_8, 4);
    float a_10 = pow(a2, 4);
    float a_11 = 4 * pow(a2, 3) * b2;
    float a_12 = 6 * pow(a2, 2) * pow(b2, 2);
    float a_13 = 4 * a2 * pow(b2, 3);
    float a_14 = pow(b2, 4);
    float flt = (a_9 - (a_10 + a_11 + a_12)) / (a_13 + a_14);

    cout << fixed << setprecision(30) << "Результат (double): " << doubl << "\nРезультат (float): " << flt << endl;

    return 0;
}