/*
    Лабораторна робота №1 Завдання 1 Варіант 20
    Прізвище: Палєй
    Група: ШІ-14
*/
#include <iostream>
#include <cmath>

int main()
{
    const int POWER3 = 3; // Степінь = 3
    const int POWER4 = 4; // Степінь = 4

    // Блок коду з обчисленням значення виразу для дійсного типу даних float

    float a1 = 100.0f; // a, тип даних - float
    float b1 = 0.001f; // b, тип даних - float

    // Обчислення чисельника
    float a1_plus_b1 = a1 + b1;         // a+b
    float c1 = pow(a1_plus_b1, POWER4); // c1 = (a+b) ^ POWER4
    float d1 = pow(a1, POWER4);         // d1 = a ^ POWER4
    float e1 = pow(a1, POWER3);         // e1 = a ^ POWER3
    float f1 = 4 * e1 * b1;             // f1 = 4*e1*b
    float g1 = c1 - (d1 + f1);          // g1 = c1 - (d1 + f1)

    // Обчислення знаменника
    float h1 = 6 * a1 * a1 * b1 * b1; // h1 = 6*a*a*b*b
    float i1 = pow(b1, POWER3);       // i1 = b ^ POWER3
    float j1 = 4 * a1 * i1;           // j1 = 4*a*i1
    float k1 = pow(b1, POWER4);       // k1 = b ^ POWER4
    float l1 = h1 + j1 + k1;          // l1 = h1+j1+k1

    // Результат даних типу float
    float float_result = g1 / l1;

    // Блок коду з обчисленням значення виразу для дійсного типу даних double

    double a2 = 100.0; // a, тип даних - double
    double b2 = 0.001; // b, тип даних - double

    // Обчислення чисельника
    double a2_plus_b2 = a2 + b2;         // a+b
    double c2 = pow(a2_plus_b2, POWER4); // c2 = (a+b) ^ POWER4
    double d2 = pow(a2, POWER4);         // d2 = a ^ POWER4
    double e2 = pow(a2, POWER3);         // e2 = a ^ POWER3
    double f2 = 4 * e2 * b2;             // f2 = 4*e2*b
    double g2 = c2 - (d2 + f2);          // g2 = c2 - (d2 + f2)

    // Обчислення знаменника
    double h2 = 6 * a2 * a2 * b2 * b2; // h2 = 6*a*a*b*b
    double i2 = pow(b2, POWER3);       // i2 = b ^ POWER3
    double j2 = 4 * a2 * i2;           // j2 = 4*a*i2
    double k2 = pow(b2, POWER4);       // k2 = b ^ POWER4
    double l2 = h2 + j2 + k2;          // l2 = h2+j2+k2

    // Результат даних типу float
    double double_result = g2 / l2;

    std::cout << "Значення виразу зі змінними типу float: " << float_result << std::endl;
    std::cout << "Значення виразу зі змінними типу double: " << double_result << std::endl;
    return 0;
}