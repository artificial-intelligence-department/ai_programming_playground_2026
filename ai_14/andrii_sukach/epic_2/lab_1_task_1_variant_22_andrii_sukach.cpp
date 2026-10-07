/*Задача: Лабораторна робота №1. Завдання №1. Варіант №22
    Автор: Сукaч Андрій
    Група: ШІ-14
 Обчислити значення виразу при різних дійсних типах даних (float й double).
Обчислення варто виконувати з використанням проміжних змінних.
Порівняти й пояснити отримані результати.
Використовуючи проміжні змінні, обчислюємо значення виразу для обох типів даних */
#include <iostream>
#include <cmath>

using namespace std;
 
int main() {
    
float a1 = 100; // за умовою float
float b1= 0.001;// за умовою float
float c1 = (a1-b1);
float d1 = (pow((a1-b1),4));
float e1 = (pow(a1,4));
float f1 = (4*pow(a1,3)*b1);
float g1 = (6*pow(a1,2)*pow(b1,2));
float h1 = (4*a1*pow(b1,3));
float i1 = (pow(b1,4));
float k1 = (d1-(e1-f1)); // обчисленя чисельника для float
float j1 = (g1-h1+i1); // обчисленя знаменника для float
float ResultFloat = k1 / j1; // обчисленя результату для float
cout << "Результат для float: " << ResultFloat << endl; // виведення результату для float

double a2 = 100; // за умовою double
double b2= 0.001; // за умовою double
double c2 = (a2-b2);
double d2 = (pow((a2-b2),4));
double e2 = (pow(a2,4));
double f2 = (4*pow(a2,3)*b2);
double g2 = (6*pow(a2,2)*pow(b2,2));
double h2 = (4*a2*pow(b2,3));
double i2 = (pow(b2,4));
double k2 = (d2-(e2-f2)); // обчисленя чисельника для double
double j2 = (g2-h2+i2); // обчисленя знаменника для double
double ResultDouble = k2 / j2; // обчисленя результату для double
cout << "Результат для double: " << ResultDouble << endl; // виведення результату для double

return 0;
}

