/*
    Лабораторна робота 1. Завдання 1. Варіант 1.
    Гончаренко Семен
    ШІ-11
*/

#include <iostream>
#include <cmath>

int main() {
    {
    // float calculation
    float a = 1000.0f;
    float b = 0.0001f;
    float n1 = pow(a + b, 2); // (a+b)^2
    float n2 = pow(a, 2) + 2*a*b; // a^2 + 2ab
    float n3 = pow(b, 2); // b^2

    float result = (n1 - n2) / n3; // ((a+b)^2 - (a^2 + 2ab)) / b^2
    std::cout << "float: " << result << std::endl;
}
{
    // double calculation
    double a = 1000.0;
    double b = 0.0001;
    double n1 = pow(a + b, 2); // (a+b)^2
    double n2 = pow(a, 2) + 2*a*b; // a^2 + 2ab
    double n3 = pow(b, 2); // b^2

    double result = (n1 - n2) / n3; // ((a+b)^2 - (a^2 + 2ab)) / b^2
    std::cout << "double: " << result << std::endl;
    }
    return 0;
}