#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // float
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    float c1_f = pow(a_f - b_f, 3);
    float c2_f = pow(a_f, 3) - 3 * pow(a_f, 2) * b_f;
    float chis_f = c1_f - c2_f;

    float z1_f = pow(b_f, 3);
    float z2_f = 3 * a_f * pow(b_f, 2);
    float znam_f = z1_f - z2_f;

    float res_f = chis_f / znam_f;

    // double
    double a_d = 1000.0;
    double b_d = 0.0001;

    double c1_d = pow(a_d - b_d, 3);
    double c2_d = pow(a_d, 3) - 3 * pow(a_d, 2) * b_d;
    double chis_d = c1_d - c2_d;

    double z1_d = pow(b_d, 3);
    double z2_d = 3 * a_d * pow(b_d, 2);
    double znam_d = z1_d - z2_d;

    double res_d = chis_d / znam_d;

    // результат
    cout << "Результат float:  " << res_f << endl;
    cout << "Результат double: " << res_d << endl;

    return 0;
}

/*
ПОЯСНЕННЯ ДО ЗАВДАННЯ 1:
Математично вираз ((a-b)^3 - (a^3 - 3*a^2*b)) / (b^3 - 3*a*b^2) після спрощення 
чисельника (a-b)^3 = a^3 - 3*a^2*b + 3*a*b^2 - b^3 зводиться до:
(3*a*b^2 - b^3) / (b^3 - 3*a*b^2) = -1.

1. При використанні типу double (подвійна точність) програма видає точне 
   математичне значення: -1.0.
2. При використанні типу float (одинарна точність, близько 7 значущих цифр) 
   відбувається втрата точності через віднімання близьких за значенням 
   великих чисел (a^3 = 1000^3 = 10^9) від малих дробових значень, тому 
   результат суттєво відхиляється від істинного.
*/