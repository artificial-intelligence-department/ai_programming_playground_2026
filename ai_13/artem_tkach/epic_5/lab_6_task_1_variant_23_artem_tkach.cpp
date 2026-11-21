// Лабораторна робота № 6, варіант 23.
// Знайти довжину найкоротшого слова у рядку, слова відокремлені пробілами.

#include <iostream>
#include <string>

int main() {
    std::string text;
    std::getline(std::cin, text);

    int shortest = static_cast<int>(text.length());
    int currentLength = 0;

    for (char ch : text) {
        if (ch == ' ' || ch == '.') {
            if (currentLength > 0 && currentLength < shortest) {
                shortest = currentLength;
            }
            currentLength = 0;
        } else {
            ++currentLength;
        }
    }
    if (currentLength > 0 && currentLength < shortest) {
        shortest = currentLength;
    }

    std::cout << shortest << '\n';
    return 0;
}
