/*
Назва: Лабораторна робота №1. Варіант 4. Завдання 1.
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {

    // обчислення виразу з float
    float a_f=1000;
    float b_f=0.0001;
    float ch_1_sum_f = a_f + b_f;
    float ch_1_st_f = pow(ch_1_sum_f, 3);
    float ch_2_st_f = pow(a_f, 3);
    float ch_res_f = ch_1_st_f - ch_2_st_f;
    float zn_1_st_f = pow(b_f, 2);
    float zn_1_mn_f = 3*a_f*zn_1_st_f;
    float zn_2_st_f = pow(b_f, 3);
    float zn_3_st_f = pow(a_f, 2);
    float zn_3_mn_f = 3*b_f*zn_3_st_f;
    float zn_d1_sum_f = zn_1_mn_f + zn_2_st_f;
    float zn_res_f = zn_3_mn_f + zn_d1_sum_f;
    float res_f = ch_res_f / zn_res_f;

    cout << "float res " << res_f << fixed << setprecision(10) << endl;

    // обчислення виразу з double
    double a_d=1000;
    double b_d=0.0001;
    double ch_1_sum_d = a_d + b_d;
    double ch_1_st_d = pow(ch_1_sum_d, 3);
    double ch_2_st_d = pow(a_d, 3);
    double ch_res_d = ch_1_st_d - ch_2_st_d;
    double zn_1_st_d = pow(b_d, 2);
    double zn_1_mn_d = 3*a_d*zn_1_st_d;
    double zn_2_st_d = pow(b_d, 3);
    double zn_3_st_d = pow(a_d, 2);
    double zn_3_mn_d = 3*b_d*zn_3_st_d;
    double zn_d1_sum_d = zn_1_mn_d + zn_2_st_d;
    double zn_res_d = zn_3_mn_d + zn_d1_sum_d;
    double res_d = ch_res_d / zn_res_d;

    cout << "double res " << res_d << fixed << setprecision(10)  << endl;

}