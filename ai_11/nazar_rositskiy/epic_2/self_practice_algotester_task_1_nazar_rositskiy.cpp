#include <iostream>

int main () {
    //оголошуємо змінні
    int n, m, k;
    //Введення значення змінних
    std::cin >> n >> m >> k;
    //перевіряємо чи вийде подлілити порівно, виводимо yes якщо вийде, no якщо не вийде
    if ((n*m)%k == 0) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
}