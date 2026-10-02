#include <iostream>

int main() {
    int a; // Дівчата у Львові
    int b; // Дівчата у Києві
    int c; // Дівчата в Донецьку
    int d; // Дівчата в Харкові
    
    std::cin >> a >> b >> c >> d;
    if(a >= 0 && a <= 1000 && b >= 0 && b <= 1000 && c >= 0 && c <= 1000 && d >= 0 && d <= 1000){
        std::cout << a + b + c +d;
    } 
    else {}

    return 0;
}