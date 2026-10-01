#include <iostream>
#include <cmath>
using namespace std;

int main(){
    float a = 1000;
    float b = 0.0001;
    float c = pow((a + b), 3);
    float d = pow(a, 3) + 3 * pow(a, 2) * b;
    float e = 3 * a * pow(b, 2) + pow(b, 3);
    float result = (c - d)/e;
    cout << result << endl;

    double a1 = 1000;
    double b1 = 0.0001;
    double c1 = pow((a1 + b1), 3);
    double d1 = pow(a1, 3) + 3 * pow(a1, 2) * b1;
    double e1 = 3 * a1 * pow(b1, 2) + pow(b1, 3);
    double result1 = (c1 - d1)/e1;
    cout << result1 << endl;
    return 0;
}