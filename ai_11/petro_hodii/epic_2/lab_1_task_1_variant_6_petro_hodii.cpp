 /*
 Лабораторна робота №1, Завдання 1, варіант 6
 Годій Петро
 ШІ-11
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    //Ініціалізую змінні типу float
    float a_f = 1000.F;
    float b_f = 0.0001F;

    //Обчислюю значення виразу з використанням проміжних обчислень для типу float
    float c_f = a_f - b_f;
    float d_f = pow(c_f,3);
    float e_f = pow(a_f,3) - 3*a_f*b_f*b_f;
    float f_f = d_f - e_f;
    float g_f = pow(b_f,3) - 3*a_f*a_f*b_f;
    float h_f = f_f / g_f;

    //Виводжу результат для типу float
    cout << fixed << setprecision(9) << "Результат для float: " << h_f << endl;

    //Ініціалізую змінні типу double
    double a_d = 1000.;
    double b_d = 0.0001;
    
    //Обчислюю значення виразу з використанням проміжних обчислень для типу double
    double c_d = a_d - b_d;
    double d_d = pow(c_d,3);
    double e_d = pow(a_d,3) - 3*a_d*b_d*b_d;
    double f_d = d_d - e_d;
    double g_d = pow(b_d,3) - 3*a_d*a_d*b_d;
    double h_d = f_d / g_d;

    //Виводжу результат для типу double
    cout << fixed << setprecision(9) << "Результат для double: " << h_d << endl;

    return 0;
}
