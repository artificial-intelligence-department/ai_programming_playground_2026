/* Задача: Лабораторна робота №1. Завдання №1. Варіант №22
    Автор:Пилип'як Олег
    Група: ШІ-12
*/
#include <iostream>
#include <cmath> //для функції pow
using namespace std;
int main() {
    // Обчислення виразу для float
    float a_f=100.0;
    float b_f=0.001;
    //Рахуємо 1 дужку (a - b)^4
    float stp_1f=pow (a_f - b_f, 4);
    //Рахуємо 2 дужку (a^4 - 4*a^3*b)
    float stp_2f=pow (a_f, 4) - 4* pow (a_f, 3)* b_f;
    //Рахуємо чисельник
    float chsl_f=stp_1f - stp_2f;
    //Рахуємо значення виразу 6*a^2*b^2
    float stp_4f=6* pow (a_f, 2)* pow (b_f, 2);
    //Рахуємо значення виразу 4*a*b^3
    float stp_5f=4* a_f* pow (b_f, 3);
    //Рахуємо знаменник
    float znam_f=stp_4f - stp_5f + pow (b_f, 4);
    //Обчислюємо кінцевий результат
    float result_f=chsl_f/znam_f;
    cout << "Результат для float: " << result_f << endl;
    // Обчислення виразу для double
    double a_d=100.0;
    double b_d=0.001;
    //Рахуємо 1 дужку (a - b)^4
    double stp_1d=pow (a_d - b_d, 4);
    //Рахуємо 2 дужку (a^4 - 4*a^3*b)
    double stp_2d=pow (a_d, 4) - 4* pow (a_d, 3)* b_d;
    //Рахуємо чисельник
    double chsl_d=stp_1d - stp_2d;
    //Рахуємо значення виразу 6*a^2*b^2
    double stp_4d=6* pow (a_d, 2)* pow (b_d, 2);
    //Рахуємо значення виразу 4*a*b^3
    double stp_5d=4* a_d* pow (b_d, 3);
    //Рахуємо знаменник
    double znam_d=stp_4d - stp_5d + pow (b_d, 4);
    //Обчислюємо кінцевий результат
    double result_d=chsl_d/znam_d;
    cout << "Результат для double: " << result_d << endl;
    return 0;
}