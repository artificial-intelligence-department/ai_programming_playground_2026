#include <iostream>

using namespace std;

int main() {
    float a = 1000;
    float b = 0.0001;

    float c = (a - b) * (a - b) * (a - b);
    float d = a * a * a;
    float e = 3 * a * b * b;
    float f = b * b * b;
    float g = 3 * a * a * b;

    float numerator = c - (d - e);
    float denominator = f - g;

    float result = numerator / denominator;

    cout << "Результат для float: " << result << endl;
    double a1 = 1000;
    double b1 = 0.0001;

    double c1 = (a1 - b1) * (a1 - b1) * (a1 - b1);
    double d1 = a1 * a1 * a1;
    double e1 = 3 * a1 * b1 * b1;
    double f1 = b1 * b1 * b1;
    double g1 = 3 * a1 * a1 * b1;

    double numerator1 = c1 - (d1 - e1);
    double denominator1 = f1 - g1;

    double result1 = numerator1 / denominator1;

    cout << "Результат для double: " << result1 << endl;
    return 0;
}