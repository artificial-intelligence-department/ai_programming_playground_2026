// Algotester, задача №71125 "Symbol"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/71125
// Ткач Артем, ШІ-13
//
// Зчитуємо один символ і визначаємо його тип:
// - літера (велика/мала) -> номер літери в алфавіті (1-26)
// - цифра (0-9) -> слово "digit"
// - інше -> "weird symbol"

#include <iostream>

int main() {
    char ch;
    std::cin >> ch;

    if (ch >= 'a' && ch <= 'z') {
        std::cout << (ch - 'a' + 1) << "\n";
    } else if (ch >= 'A' && ch <= 'Z') {
        std::cout << (ch - 'A' + 1) << "\n";
    } else if (ch >= '0' && ch <= '9') {
        std::cout << "digit\n";
    } else {
        std::cout << "weird symbol\n";
    }

    return 0;
}
