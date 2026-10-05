/* 
Завдання 1, лабараторна робота 1
Белаш Матвій Валерійович
ШІ-12
*/
#include <iostream>
#include <cmath>

int main() {

    double a = 1000;
    double b = 0.0001;
    
    double c = a + b;
    double d = pow(c, 2);
    double e = pow(a, 2);
    double f = 2 * a * b;
    double g = e + f;
    double h = d - g;
    double i = pow(b, 2);
    int j = h / i;

    std::cout << "Result: " << j << std::endl;

    return 0;

}