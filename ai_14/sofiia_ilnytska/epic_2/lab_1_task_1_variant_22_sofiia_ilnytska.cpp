/*
    Задача: Лабораторна робота №1. Завдання №1. Варіант №22
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <math.h>
using namespace std;

int main() {
    // Обчислення для даних типу float
    float a1 = 100;  // Значення a за умовою
    float b1 = 0.001;  // Значення b за умовою
    float c1 = a1 - b1;
    float d1 = pow(c1, 4);
    float e1 = pow(a1, 4);
    float f1 = pow(a1, 3);
    float g1 = 4 * f1 * b1;
    float h1 = e1 - g1;
    float numerator1 = d1 - h1;  // Чисельник дробу: (a-b)^4 - (a^4 - 4a^3b)
    float i1 = pow(a1, 2);
    float j1 = pow(b1, 2);
    float k1 = 6 * i1 * j1;
    float l1 = pow(b1, 3);
    float m1 = 4 * a1 * l1;
    float n1 = pow(b1, 4);
    float denominator1 = k1 - m1 + n1;  // Знаменник дробу: 6a^2b^2 - 4ab^3 + b^4
    float fraction1 = numerator1 / denominator1;
    cout << "Результат обчислення для даних типу float: " << fraction1 << endl;

    // Обчислення для даних типу double
    double a2 = 100;  // Значення a за умовою
    double b2 = 0.001;  // Значення b за умовою
    double c2 = a2 - b2;
    double d2 = pow(c2, 4);
    double e2 = pow(a2, 4);
    double f2 = pow(a2, 3);
    double g2 = 4 * f2 * b2;
    double h2 = e2 - g2;
    double numerator2 = d2 - h2;  // Чисельник дробу: (a-b)^4 - (a^4 - 4a^3b)
    double i2 = pow(a2, 2);
    double j2 = pow(b2, 2);
    double k2 = 6 * i2 * j2;
    double l2 = pow(b2, 3);
    double m2 = 4 * a2 * l2;
    double n2 = pow(b2, 4);
    double denominator2 = k2 - m2 + n2;  // Знаменник дробу: 6a^2b^2 - 4ab^3 + b^4
    double fraction2 = numerator2 / denominator2;
    cout << "Результат обчислення для даних типу double: " << fraction2 << endl;
    return 0;
}