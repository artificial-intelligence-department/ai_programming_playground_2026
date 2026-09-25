/*
Lab 1 task 1, Танасієнко Іван, ШІ-13, Варіант 19
*/
#include<iostream>
#include<cmath>
#include<iomanip>

/*
Умова:
((a + b)^4 - (a^4 + 4*a^3*b + 6*a^2*b^2)) / (4*a*b^3 + b^4)
при a = 100, b = 0.001
*/

/*
Дії
1. (a + b) = r1
2. r1^4 = r2
3. (a^4 + 4*a^3*b + 6*a^2*b^2) = r3
3.1. a ^ 4 = r3d1
3.2. 4 * a ^ 3 * b = r3d2 
3.3. 6 * a ^ 2 * b ^ 2 = r3d3
4. r2 - r3 = r4
5. (4*a*b^3 + b^4) = r5
6. r4 / r5
*/

int main()
{
    double a = 100;
    double b = 0.001;
    double r1 = a + b;
    double r2 = std::pow(r1, 4);
    double r3d1 = std::pow(a, 4);
    double r3d2 = 4 * std::pow(a, 3) * b;
    double r3d3 = 6 * std::pow(a, 2) * std::pow(b, 2);
    double r3 = r3d1 + r3d2 + r3d3;
    double r4 = r2 - r3;
    double r5d1 = 4 * a * std::pow(b, 3);
    double r5d2 = std::pow(b, 4);
    double r5 = r5d1 + r5d2;
    double r6 = r4 / r5;


    float c = 100;
    float d = 0.001;
    float f1 = c + d;
    float f2 = std::pow(f1, 4);
    float f3d1 = std::pow(c, 4);
    float f3d2 = 4 * std::pow(c, 3) * d;
    float f3d3 = 6 * std::pow(c, 2) * std::pow(d, 2);
    float f3 = f3d1 + f3d2 + f3d3;
    float f4 = f2 - f3;
    float f5d1 = 4 * c * std::pow(d, 3);
    float f5d2 = std::pow(d, 4);
    float f5 = f5d1 + f5d2;
    float f6 = f4 / f5;

    std::cout << std::fixed << std::setprecision(15) << "Double: " << r6 << std::endl << "Float:  " << f6 << std::endl;

    return 0;

}