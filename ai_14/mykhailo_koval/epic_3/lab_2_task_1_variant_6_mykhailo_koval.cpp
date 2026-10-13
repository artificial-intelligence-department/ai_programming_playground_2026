#include <iostream>
#include <cmath>

int main(){
    double epsilon = 0.0001;
    double a = 1.0/2.0 + 1.0/3.0;
    double sum = 0;
    int n = 1;

    while (a > epsilon){
        sum += a;
        a = a * (3.0 + 2.0 * pow(2.0/3.0, n)) / (6.0 + 6.0 * pow(2.0/3.0, n));
        n++;
    }
    
    std::cout << "Сума ряду: " << sum << std::endl;
    return 0;
}