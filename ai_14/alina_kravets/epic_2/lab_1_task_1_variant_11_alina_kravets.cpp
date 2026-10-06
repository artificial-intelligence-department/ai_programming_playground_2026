#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float a1 = 100.0;
    float b1 = 0.001; 
    float c1 = pow (a1, 4);
    float d1 = pow (a1, 3);
    float e1 = pow (a1, 2);
    float f1 = pow (b1, 4);
    float g1 = pow (b1, 3);
    float h1 = pow (b1, 2);
    float i1 = pow (a1-b1, 4);
    float j1 = c1 - 4*d1*b1;
    float k1 = i1 - j1;
    float l1 = 6*e1*h1 - 4*a1*g1 + f1;
    float result1 = k1/l1;
    double a2 = 100.0;
    double b2 = 0.001; 
    double c2 = pow (a2, 4);
    double d2 = pow (a2, 3);
    double e2 = pow (a2, 2);
    double f2 = pow (b2, 4);
    double g2 = pow (b2, 3);
    double h2 = pow (b2, 2);
    double i2 = pow (a2-b2, 4);
    double j2 = c2 - 4*d2*b2;
    double k2 = i2 - j2;
    double l2 = 6*e2*h2- 4*a2*g2 + f2;
    double result2 = k2/l2;

    cout << "Результат для float: " << result1 << endl;
    cout << "Результат для double: " << result2 << endl;
    return 0;
}
