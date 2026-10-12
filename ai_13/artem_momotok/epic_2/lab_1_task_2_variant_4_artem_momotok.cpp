#include <iostream>

int main() {
    // Оголошення змінних m та n
    int n, m;

    // Введення значень
    std::cout << "Введіть значення m: ";
    std::cin >> m;
    std::cout << "Введіть значення n: ";
    std::cin >> n;

    // Виведення початкових значень змінних
    std::cout << "Початкові значення m: " << m << ", n: " << n << std::endl;
    std::cout << std::endl;

    // Операція №1
    int result1 = n++ * m;

    std::cout << "Результат операції №1:  " << result1 << std::endl;
    std::cout << "Після операції №1 значення m: " << m << ", n: " << n << std::endl;
    std::cout << std::endl;

    // Операція №2
    bool result2 = n++ < m;

    std::cout << "Результат операції №2:  " << std::boolalpha << result2 << std::endl;
    std::cout << "Після операції №2 значення m: " << m << ", n: " << n << std::endl;
    std::cout << std::endl;

    // Операція №3
    bool result3 = m-- > m;

    std::cout << "Результат операції №3:  " << std::boolalpha << result3 << std::endl;
    std::cout << "Після операції №3 значення m: " << m << ", n: " << n << std::endl;

    return 0;
}