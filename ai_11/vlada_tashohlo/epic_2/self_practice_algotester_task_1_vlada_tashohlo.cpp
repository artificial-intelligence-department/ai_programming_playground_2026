
/* 
Епік 2. self practice: Algotester, задача "Цікава гра"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>

int main() {
    // Зчитуємо розміри дошки: кількість рядків n та стовпців m.
    long long n, m;
    std::cin >> n >> m;

    // Загальна кількість клітинок на дошці.
    long long cells = n * m;

    // Якщо кількість клітинок непарна, перший гравець (Imp) зробить останній хід.
    // Інакше останній хід зробить Dragon.
    if (cells % 2 == 1) {
        std::cout << "Imp\n";
    } else {
        std::cout << "Dragon\n";
    }

    return 0;
}
