/*
Назва задачі: Lab 1 Task 1
Варіант: 7
Автор: Діхтяр Юлія
Група: ai-13
*/

/*
Умова:
((a - b)^3 - a^3) / (b^3 - 3*a*b^2 - 3*a^2*b)

a = 1000, b = 0.0001

Обчислити вираз із використанням проміжних змінних
для типів double і float та порівняти результати.
*/

/*
Дії:
1. a - b = r1
2. r1^3 = r2
3. a^3 = r3
4. r2 - r3 = r4 — чисельник
5. b^3 = r5
6. 3*a*b^2 = r6
7. 3*a^2*b = r7
8. r5 - r6 - r7 = r8 — знаменник
9. r4 / r8 — результат
*/

#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    // Обчислення з типом double
    double a = 1000.0;
    double b = 0.0001;

    double r1 = a - b;
    double r2 = std::pow(r1, 3);
    double r3 = std::pow(a, 3);
    double r4 = r2 - r3;

    double r5 = std::pow(b, 3);
    double r6 = 3 * a * std::pow(b, 2);
    double r7 = 3 * std::pow(a, 2) * b;
    double r8 = r5 - r6 - r7;
    double resultDouble = r4 / r8;

    // Обчислення з типом float
    float c = 1000.0f;
    float d = 0.0001f;

    float f1 = c - d;
    float f2 = std::pow(f1, 3);
    float f3 = std::pow(c, 3);
    float f4 = f2 - f3;

    float f5 = std::pow(d, 3);
    float f6 = 3 * c * std::pow(d, 2);
    float f7 = 3 * std::pow(c, 2) * d;
    float f8 = f5 - f6 - f7;
    float resultFloat = f4 / f8;

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Double: " << resultDouble << std::endl;
    std::cout << "Float:  " << resultFloat << std::endl;

    return 0;
}
