/*Лабораторна робота №1, завдання 1, варіант 1
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    //Обрахунок за допомогою типу даних float
    cout << "float: "; 
    float a1 = 1000;
    float b1 = 0.0001;
    float c1 = pow(a1 + b1, 2);
    float d1 = (pow(a1, 2) + 2*a1*b1);
    float e1 = pow(b1, 2);
    float f1 = c1 - d1;
    float g1 = f1/e1;
    cout << fixed << g1 << endl;

    //Обрахунок за допомогою типу даних double
    cout << "double: ";
    double a2 = 1000;
    double b2 = 0.0001;
    double c2 = pow(a2 + b2, 2);
    double d2 = (pow(a2, 2) + 2*a2*b2);
    double e2 = pow(b2, 2);
    double f2 = c2 - d2;
    double g2 = f2/e2;
    cout << fixed << g2 << endl;

    return 0;
}