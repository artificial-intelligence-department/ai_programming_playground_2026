/*
    Задача: lab_1_task_1_variant_21
    Автор: Сачковський Андрій
    Група: ШІ-11
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
// double
double a = 100;
double b = 0.001;

double chyselnyk = pow(a - b, 4) - (pow(a, 4) - 4 * pow(a, 3) * b + 6 * pow(a, 2) * pow(b, 2));
double znamennyk = pow(b, 4) - 4 * a * pow(b, 3);

if (znamennyk == 0) {
cout << "ділення на 0" << endl;
return 0;
}

// float
float af = 100;
float bf = 0.001;

float chyselnykf = pow(af - bf, 4) - (pow(af, 4) - 4 * pow(af, 3) * bf + 6 * pow(af, 2) * pow(bf, 2));
float znamennykf = pow(bf, 4) - 4 * af * pow(bf, 3);

if (znamennykf == 0) {
cout << "ділення на 0" << endl;
return 0;
}
double result = chyselnyk / znamennyk;
cout << "double: " << result << endl; 

float resultf = chyselnykf / znamennykf;
cout << "float: " << resultf << endl;

return 0;
}