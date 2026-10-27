/*
 * Algotester, Лабораторна робота №3, варіант 2 - "Lab 3v3"
 * Ткач Артем
 * ШІ-13
 *
 * Умова: дано стрічку s. Потрібно стиснути її: якщо якась буква іде більше
 * одного разу підряд, замінити її на букву + кількість входжень підряд.
 *
 * Приклад: AAAABBBCQQQQ -> A4B3CQ4, AA -> A2.
 *
 * Довжина стрічки до 10^5, тому читаємо її цілком через std::string.
 */

#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    std::string result = "";
    int i = 0;
    int len = s.length();

    while (i < len) {
        // Рахуємо, скільки разів поспіль повторюється поточна буква.
        int j = i;
        while (j < len && s[j] == s[i]) {
            j++;
        }
        int count = j - i;

        result += s[i];
        if (count > 1) {
            result += std::to_string(count);
        }
        i = j;
    }

    std::cout << result << "\n";
    return 0;
}
