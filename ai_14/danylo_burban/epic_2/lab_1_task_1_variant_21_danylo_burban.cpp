/*Epic 2 - Завдання 1 лабораторної 1 варіант 21
Бурбан Данило
Ші - 14*/

#include <iostream> 
#include <cmath>

using namespace std;
int main(){
    const float a_f=100;
    const float b_f=0.001;
     
    float first_f =pow(a_f-b_f, 4);
    float second_f = -(pow(a_f,4)-4*pow(a_f,3)*b_f+6*pow(a_f,2)*pow(b_f,2));
    float third_f = pow(b_f,4)-4*a_f*pow(b_f,3);

    float result_f = (first_f+second_f)/third_f;
    cout<<"result: "<<result_f<<endl;

    const double a_d=100;
    const double b_d=0.001;
     
    double first_d =pow(a_d-b_d, 4);
    double second_d = -(pow(a_d,4)-4*pow(a_d,3)*b_d+6*pow(a_d,2)*pow(b_d,2));
    double third_d = pow(b_d,4)-4*a_d*pow(b_d,3);

    double result_d = (first_d+second_d)/third_d;
    cout<<"result: "<<result_d<<endl;
}