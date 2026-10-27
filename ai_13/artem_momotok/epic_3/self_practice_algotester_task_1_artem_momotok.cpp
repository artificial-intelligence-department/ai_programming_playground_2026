/*
Складний екзамен, Момоток Артем, ШІ-13
*/
#include <iostream>
#include <string>

int main() {
    // Зчитуємо число, у якому потрібно знайти послідовність «47».
    long long n;
    std::cin >> n;

    // Перетворюємо число на рядок, щоб перевірити сусідні цифри.
    std::string num = std::to_string(n);
    // Зберігаємо результат пошуку послідовності «47».
    bool lucky = false;

    // Перевіряємо всі пари сусідніх символів у рядку.
    for (int i = 0; i + 1 < num.size(); i++) {
        if (num[i] == '4' && num[i + 1] == '7') {
            lucky = true;
            break;
        }
    }

    // Виводимо відповідь залежно від того, чи знайшли «47».
    if (lucky == true) 
        std::cout << "YES" << std::endl;
    else  
        std::cout << "NO" << std::endl;

    return 0;
}