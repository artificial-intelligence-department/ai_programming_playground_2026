/*
Task: lab 1 task 1 option 10
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <cmath>

using namespace std;
int main (){

   //Робота програми при задаванні змінних через float 

    float a_float = 100.0f; // задаємо значення змінної a через float
    float b_float = 0.001f; // задаємо значення змінної b через float

    float num_part_1_f = pow((a_float - b_float), 4.0); //рахуємо першу частину чисельника
    float num_part_2_f = pow(a_float,4.0) - 4.0 * pow(a_float,3.0) * b_float + 6.0 * pow(a_float, 2.0) * pow(b_float, 2.0); //рахуємо другу частину чисельника


    float num_float = num_part_1_f - num_part_2_f; //Обчислення чисельника
    float denum_float = pow(b_float,4.0) - 4.0 * a_float * pow(b_float,3.0); //Обчислення знаменника

    float result_float = num_float / denum_float; //обчислюємо весь вираз



     //Робота програми при здаванні змінних через double
    double a_double = 100;
    double b_double = 0.001;

    double num_part_1_d = pow((a_double - b_double), 4.0); //рахуємо першу частину чисельника
    double num_part_2_d = pow(a_double,4.0) - 4.0 * pow(a_double,3.0) * b_double + 6.0 * pow(a_double, 2.0) * pow(b_double, 2.0); //рахуємо другу частину чисельника

    double num_double = num_part_1_d - num_part_2_d; //Обчислення чисельника
    double denum_double = pow(b_double,4.0) - 4.0 * a_double * pow(b_double,3.0); //Обчислення знаменника

    double result_double = num_double / denum_double; 



    cout << "Result float: " << result_float << endl;
    cout << "Result double: " << result_double << endl;


    return 0;
}

