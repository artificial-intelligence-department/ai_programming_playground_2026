#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    float a = 1000.0f, b = 0.0001f;

    float a_minus_b_squared = pow(a - b, 2);
    float a_squared_minus_twoab = pow(a, 2) - 2 * a * b;
    float difference = a_minus_b_squared - a_squared_minus_twoab;
    float b_squared = pow(b, 2);
    float resultfloat = difference/b_squared;
    cout << "Result (float): " << fixed << setprecision(10) << resultfloat;

    double a_double = 1000.0, b_double = 0.0001;

    double a_minus_b_squared_double = pow(a_double - b_double, 2);
    double a_squared_minus_twoab_double = pow(a_double, 2) - 2 * a_double * b_double;
    double difference_double = a_minus_b_squared_double - a_squared_minus_twoab_double;
    double b_squared_double = pow(b_double, 2);
    double resultdouble = difference_double/b_squared_double;
    cout << "\nResult (double): " << fixed << setprecision(10) << resultdouble;
    return 0;
}