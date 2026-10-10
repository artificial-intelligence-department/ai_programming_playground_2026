/*
Лабораторна робота №2, Завдання 1, Варіант 8  
Балицький Ростислав
СШІ-12
*/
#include <iostream>

using namespace std;

int main() {
    // для float
    float a = 100;
    float b = 0.001;
    float c = (a + b) * (a + b) * (a + b) * (a + b); // (a + b)^4
    float d = a * a * a * a;                         // a^4
    float e = 4 * a * a * a * b;                     // 4 * a^3 * b
    float f = 6 * a * a * b * b;                     // 6 * a^2 * b^2

    float numerator = c - (d + e + f);               // Чисельник
    float denominator = 4 * a * b * b * b + b * b * b * b; // Знаменник

    float result = numerator / denominator;

    cout << "Результат для float: " << result << endl;

    cout << endl;
    
    // для double
    double a1 = 100;
    double b1 = 0.001;

    double c1 = (a1 + b1) * (a1 + b1) * (a1 + b1) * (a1 + b1); // (a + b)^4
    double d1 = a1 * a1 * a1 * a1;                             // a^4
    double e1 = 4 * a1 * a1 * a1 * b1;                         // 4 * a^3 * b
    double f1 = 6 * a1 * a1 * b1 * b1;                         // 6 * a^2 * b^2

    double numerator1 = c1 - (d1 + e1 + f1);                   // Чисельник
    double denominator1 = 4 * a1 * b1 * b1 * b1 + b1 * b1 * b1 * b1; // Знаменник

    double result1 = numerator1 / denominator1;

    cout << "Результат для double: " << result1 << endl;

    return 0;
}
