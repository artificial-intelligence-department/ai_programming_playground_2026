/*
 Lab 1. Task 1. Variant 12.
 Соломія Королюк
 ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    float a_f = 1000.0f;
    float b_f = 0.0001f;

    float n1_f = a_f + b_f;
    float n2_f = pow(n1_f, 2); //перша дужка чисельника
    float n3_f = pow(a_f, 2) + 2 * a_f * b_f; //друга дужка чисельника
    float n4_f = n2_f - n3_f; //чисельник

    float d1_f = pow(b_f, 2); //знаменник

    float result = n4_f / d1_f;

    cout << fixed << setprecision(18);

    cout << "a_f: " << a_f << endl;
    cout << "b_f: " << b_f << endl;

    cout << "(a_f + b_f): " << " " << n1_f << endl;
    cout << "(a_f + b_f)^2: " << n2_f << endl;
    cout << "a_f^2 + 2*a_f*b_f: " << n3_f << endl;
    cout << "Чисельник: " << n4_f << endl;
    cout << "Знаменник: " << d1_f << endl;

    cout << "Float result: " << result << endl;
    cout << " " << endl;

    double a_d = 1000;
    double b_d = 0.0001;

    double n1_d = a_d + b_d;
    double n2_d = pow(n1_d, 2); //перша дужка чисельника
    double n3_d = pow(a_d, 2) + 2 * a_d * b_d; //друга дужка чисельника
    double n4_d = n2_d - n3_d; //чисельник

    double d1_d = pow(b_d, 2); //знаменник

    double result_d = n4_d / d1_d;

    cout << "a_d: " << a_d << endl;
    cout << "b_d: " << b_d << endl;
    cout << "(a_d + b_d): " << " " << n1_d << endl;
    cout << "(a_d + b_d)^2: " << n2_d << endl;
    cout << "a_d^2 + 2*a_d*b_d: " << n3_d << endl;
    cout << "Чисельник: " << n4_d << endl;
    cout << "Знаменник: " << d1_d << endl;
    cout << "Double result: " << result_d << endl;

    
    return 0;
}