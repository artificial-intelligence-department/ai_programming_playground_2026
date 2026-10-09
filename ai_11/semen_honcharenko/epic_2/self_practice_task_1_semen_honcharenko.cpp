/*
    Алготестер. "Цікава Гра"
    Гончаренко Семен
    ШІ-11
*/

#include <iostream>
    
int main() {
    int n = 0;
    int m = 0;

    std::cin >> n;
    std::cin >> m;

    if ((n * m) % 2 == 0) {
        std::cout << "Dragon" << std::endl;
    }
    else {
        std::cout << "Imp" << std::endl;
    }
    return 0;
}