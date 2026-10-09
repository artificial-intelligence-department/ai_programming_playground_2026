#include <iostream>
#include <cmath>
using namespace std;

int main(){
    //Вводимо змінні
    double a_d = 100;
    float a_f = 100.0f;
    double b_d = 0.001;
    float b_f = 0.001f;

    //Обрахунки для типу double
    double first_d = pow(a_d - b_d, 4);
    double second_d = pow(a_d, 4) - 4 * pow(a_d, 3) * b_d;
    double third_d = first_d - second_d;
    double fourth_d = 6 * pow(a_d, 2) * pow(b_d, 2) - 4 * a_d * pow(b_d, 3) + pow(b_d, 4);
    double result_d = third_d / fourth_d;

    //Обрахунки для типу float
    float first_f = pow(a_f - b_f, 4);
    float second_f = pow(a_f, 4) - 4 * pow(a_f, 3) * b_f;
    float third_f = first_f - second_f;
    float fourth_f = 6 * pow(a_f, 2) * pow(b_f, 2) - 4 * a_f * pow(b_f, 3) + pow(b_f, 4);
    float result_f = third_f / fourth_f;

    //Виводимо результати
    cout << "Результат для типу double: " << result_d << endl;
    cout << "Результат для типу float: " << result_f << endl;

    return 0;
}