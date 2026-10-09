#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    float a_f = 100.f;
    float b_f = 0.001f;
    float f1 = a_f + b_f;
    float f2 = pow(f1, 4);
    float f3 = pow(a_f, 4);
    float f4 = 4 * pow(a_f, 3) * b_f;
    float f5 = 6 * pow(a_f, 2) * pow(b_f, 2);
    float f6 = f3 + f4 + f5;
    float f7 = f2 - f6;
    float f8 = 4 * a_f * pow(b_f, 3);
    float f9 = pow(b_f, 4);
    float f10 = f8 + f9;
    float f11 = f7 / f10;

    double a_d = 100.0;
    double b_d = 0.001;
    double d1 = a_d + b_d;
    double d2 = pow(d1, 4);
    double d3 = pow(a_d, 4);
    double d4 = 4 * pow(a_d, 3) * b_d;
    double d5 = 6 * pow(a_d, 2) * pow(b_d, 2);
    double d6 = d3 + d4 + d5;
    double d7 = d2 - d6;
    double d8 = 4 * a_d * pow(b_d, 3);
    double d9 = pow(b_d, 4);
    double d10 = d8 + d9;
    double d11 = d7 / d10;

	double all_in_one = (pow(a_d + b_d, 4) - (pow(a_d, 4) + 4 * pow(a_d, 3) * b_d + 
		6 * pow(a_d, 2) * pow(b_d, 2))) / (4 * a_d * pow(b_d, 3) + pow(b_d, 4));

    cout << fixed << setprecision(10);
    cout << "Float output: " << f11 << endl;
    cout << "Double output: " << d11 << endl;
    cout << "All in one output: " << all_in_one << endl;

    return 0;
}