#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    float c_f = pow((a_f + b_f), 3);
    float d_f = pow(a_f, 3);
    float e_f = c_f - d_f;
    float f_f = 3 * a_f * pow(b_f, 2) + pow(b_f, 3) + 3 * pow(a_f, 2) * b_f;
    float result_float = e_f / f_f;

    cout << "Result (float): " << result_float << endl;

    double a_d = 1000.0;
    double b_d = 0.0001;

    double c_d = pow((a_d + b_d), 3);
    double d_d = pow(a_d, 3);
    double e_d = c_d - d_d;
    double f_d = 3 * a_d * pow(b_d, 2) + pow(b_d, 3) + 3 * pow(a_d, 2) * b_d;
    double result_double = e_d / f_d;

    cout << "Result (double): " << result_double << endl;

    return 0;
}