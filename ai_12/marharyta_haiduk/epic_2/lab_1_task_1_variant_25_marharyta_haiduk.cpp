/*
    Задача: Лабораторна робота №1. Завдання №1. Варіант №25
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <cmath>
using namespace std;
int main() {
// Обчислення для типу даних float
float a = 1000;
float b = 0.0001;
float c = pow(a-b, 3);
float d = pow(a,3);
float e = pow (a,2);
float f = 3*e*b;
float numerator1 = c - (d - f);
float g = pow (b,2);
float h = 3*a*g;
float i = pow (b,3);
float denominator1 = i - h;
float result1 = numerator1 / denominator1;
cout << "Обчислення для float: " << result1 << endl;
// Обчислення для типу даних double
double A = 1000;
double B = 0.0001;
double C = pow(A-B, 3);
double D = pow(A,3);
double E = pow (A,2);
double F = 3*E*B;
double numerator2 = C - (D - F);
double G = pow (B,2);
double H = 3*A*G;
double I= pow (B,3);
double denominator2 = I - H;
double result2 = numerator2 / denominator2;
cout << "Обчислення для double: " << result2 << endl;
    return 0;
}