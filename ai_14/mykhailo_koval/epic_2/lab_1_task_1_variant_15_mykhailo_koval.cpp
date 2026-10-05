#include <iostream>
#include <cmath>

using namespace std;

int main (){

    double a1 = 1000;
    double b1 = 0.0001;

    double c1 = pow(a1 + b1, 3) - pow(a1, 3);
        

    double s1 = pow(b1, 2);
    double k1 = 3 * a1 * s1;
    double n1 = pow(b1, 3);
    double j1 = pow(a1, 2);
    double v1 = 3 * j1 * b1;
    double q1 = k1 + n1 + v1;

    double solution_d = c1 / q1;
    cout << "Розв'язок: " << solution_d << '\n';
    
    float a = 1000;
    float b = 0.0001;

    float c = pow(a + b, 3) - pow(a, 3);
        

    float s = pow(b, 2);
    float k = 3 * a * s;
    float n = pow(b, 3);
    float j = pow(a, 2);
    float v = 3 * j * b;
    float q = k + n + v;

    float solution_f = c / q;
    cout << "Розв'язок: " << solution_f << '\n';

    return 0;
}