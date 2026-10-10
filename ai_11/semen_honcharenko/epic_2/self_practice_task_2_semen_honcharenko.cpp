/*
    Алготестер. "Апельсини"
    Гончаренко Семен
    ШІ-11
*/

#include <iostream>

int main() {
    int a = 0;
    int b = 0;
    int c = 0;
    
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    
    if ((a + b) > c) {
        std::cout << "YES" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}