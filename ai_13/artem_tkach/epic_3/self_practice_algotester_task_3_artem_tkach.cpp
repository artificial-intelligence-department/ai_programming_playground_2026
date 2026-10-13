// Algotester, задача №40710 "Have you washed your hands yet?"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40710
// Ткач Артем, ШІ-13
//
// Зараз заражено a людей, далі щодня заражається рівно b людей.
// Загальна кількість заражених через k днів: a + b * k.
// Максимум 1000 + 1000 * 1000, але long long для запасу.

#include <iostream>

int main() {
    long long a, b, k;
    std::cin >> a >> b >> k;

    std::cout << a + b * k << "\n";
    return 0;
}
