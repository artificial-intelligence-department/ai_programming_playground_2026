
/* 
Епік 1. self practice: Algotester, задача "Депутатські гроші"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    
    long long count = 0;

    // Витягуємо максимальну кількість купюр найбільших номіналів.
    count += n / 500;
    n %= 500;  

    count += n / 200;
    n %= 200;

    count += n / 100;
    n %= 100;

    count += n / 50;
    n %= 50;

    count += n / 20;
    n %= 20;

    count += n / 10;
    n %= 10;

    count += n / 5;
    n %= 5;

    count += n / 2;
    n %= 2;

    // Залишок — це кількість 1-гривневих купюр.
    count += n;
    n = 0;

    std::cout << count << "\n";

    return 0;
}
