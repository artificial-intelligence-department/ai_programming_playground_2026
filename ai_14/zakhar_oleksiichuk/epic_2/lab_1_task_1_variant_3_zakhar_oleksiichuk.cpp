#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Float =================
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    float f1 = pow(a_f + b_f, 3);
    float f2 = pow(a_f, 3);
    float f3 = 3 * pow(a_f, 2) * b_f;
    float f4 = 3 * a_f * pow(b_f, 2);
    float f5 = pow(b_f, 3);

    float num_f = f1 - (f2 + f3);
    float den_f = f4 + f5;
    float res_float = num_f / den_f;

    // Double =================
    double a_d = 1000.0;
    double b_d = 0.0001;

    double d1 = pow(a_d + b_d, 3);
    double d2 = pow(a_d, 3);
    double d3 = 3 * pow(a_d, 2) * b_d;
    double d4 = 3 * a_d * pow(b_d, 2);
    double d5 = pow(b_d, 3);

    double num_d = d1 - (d2 + d3);
    double den_d = d4 + d5;
    double res_double = num_d / den_d;

    cout << fixed << setprecision(8);
    cout << "Result Float:  " << res_float << endl;
    cout << "Result Double: " << res_double << endl;

    return 0;
}