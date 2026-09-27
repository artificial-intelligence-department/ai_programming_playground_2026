/*
Назва задачі: Задача про задачі
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a + b <= 47 || a + c <= 47 || b + c <= 47) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
