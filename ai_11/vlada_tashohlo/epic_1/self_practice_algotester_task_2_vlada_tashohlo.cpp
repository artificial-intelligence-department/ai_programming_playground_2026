
/* 
Епік 1. self practice: Algotester, задача "Марічка і печиво"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>

int main() {
    long long n; // кількість пачок печива
    std::cin >> n;
    long long total = 0; // сумарна кількість печива, яку можна з'їсти непомітно

    for (long long i = 0; i < n; ++i) {
        long long a; // кількість печива в поточній пачці
        std::cin >> a;

        if (a > 0) { // якщо пачка не порожня, можна з'їсти всі крім одного
            total += (a - 1);
        }
    }

    std::cout << total << "\n";

    return 0;
}
