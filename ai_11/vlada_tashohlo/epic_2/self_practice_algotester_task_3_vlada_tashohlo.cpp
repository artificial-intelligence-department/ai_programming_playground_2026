
/* 
Епік 2. self practice: Algotester, задача "Аркуш"
Авторка: Влада Ташогло
Група: ші-11/*
*/

#include <iostream>

int main() {
    // Зчитуємо розмір аркуша: n x n.
    long long n;
    std::cin >> n;
    
    // Обчислюємо загальну кількість квадратів, зображених на аркуші.
    long long answer = n * (n + 1) * (2 * n + 1) / 6;

    std::cout << answer << "\n";

    return 0;
}
