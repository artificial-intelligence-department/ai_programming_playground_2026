/*
    Лабораторна робота 1. Завдання 2. Варіант 1.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>

int main() {
    int n = 0;
    std::cout << "n value: ";
    std::cin >> n;
    
    int m = 0;
    std::cout << "m value: ";
    std::cin >> m;

    std::cout << "n+++m: " << (n+++m) << std::endl;
    std::cout << "n value now: " << n << std::endl << "m value now: " << m << std::endl;
    std::cout << "m-->n: " << (m-->n) << std::endl;
    std::cout << "n value now: " << n << std::endl << "m value now: " << m << std::endl;
    std::cout << "n-->m: " << (n-->m) << std::endl;
    std::cout << "n value now: " << n << std::endl << "m value now: " << m << std::endl;
    return 0;
}