#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // float
    float a1 = 1000, b1 = 0.0001;

    float c1 = pow(a1 + b1, 3);   // (a+b)^3
    float d1 = pow(a1, 3);        // a^3
    float e1 = 3 * a1 * b1 * b1;  // 3ab^2
    float f1 = pow(b1, 3);        // b^3
    float g1 = 3 * a1 * a1 * b1;  // 3a^2b

    float result1 = (c1 - d1) / (e1 + f1 + g1);

    // double
    double a2 = 1000, b2 = 0.0001;

    double c2 = pow(a2 + b2, 3);
    double d2 = pow(a2, 3);
    double e2 = 3 * a2 * b2 * b2;
    double f2 = pow(b2, 3);
    double g2 = 3 * a2 * a2 * b2;

    double result2 = (c2 - d2) / (e2 + f2 + g2);

    cout << "float:  " << setprecision(10) << result1 << endl;
    cout << "double: " << result2 << endl;

    return 0;
}