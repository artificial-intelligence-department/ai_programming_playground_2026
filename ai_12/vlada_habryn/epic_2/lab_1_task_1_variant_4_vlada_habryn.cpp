#include <iostream>
#include <cmath>
using namespace std;
int main() {
    //Обчислення виразу для типу float
    {
        float a = 1000;
    float b = 0.0001;
    float numerator = pow(a+b, 3) - pow (a,3);
    float denominator = 3*a*pow(b,2) + pow(b,3) + 3*pow(a,2)*b;
    float result_float = numerator / denominator;
    cout << "Result (float): " << result_float << endl;
    }

    //Обчислення виразу для типу double
    {
    double a = 1000;
    double b = 0.0001;
    double numerator = pow(a+b, 3) - pow (a,3);
    double denominator = 3*a*pow(b,2) + pow(b,3) + 3*pow(a,2)*b;
    double result_double = numerator / denominator;
    cout << "Result (double): " << result_double << endl;
    }

    return 0;
}