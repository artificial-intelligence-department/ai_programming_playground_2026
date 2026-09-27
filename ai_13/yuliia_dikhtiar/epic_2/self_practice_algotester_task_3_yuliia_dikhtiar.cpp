/*
Назва задачі: Нечесний розподіл
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <algorithm>

int main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    int smallest = std::min(std::min(a, b), std::min(c, d));
    int largest = std::max(std::max(a, b), std::max(c, d));

    int marichka = smallest + largest;
    int zenyk = a + b + c + d - marichka;

    if (zenyk > marichka) {
        std::cout << "Zenyk\n";
    } else if (marichka > zenyk) {
        std::cout << "Marichka\n";
    } else {
        std::cout << "Love always wins\n";
    }

    return 0;
}
