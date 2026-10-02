/*
Назва задачі: Нечесний розподіл
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

int main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    int smallest = a;
    if (b < smallest) smallest = b;
    if (c < smallest) smallest = c;
    if (d < smallest) smallest = d;

    int largest = a;
    if (b > largest) largest = b;
    if (c > largest) largest = c;
    if (d > largest) largest = d;

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
