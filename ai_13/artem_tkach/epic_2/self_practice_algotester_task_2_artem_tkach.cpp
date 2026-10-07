// Algotester, задача №40833 "Problem about problems"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40833
// Ткач Артем, ШІ-13
//
// Василь створив три задачі складністю a, b, c. Для змагання треба обрати
// РІВНО дві задачі, сума складностей яких не перевищує 47.
// Перевіряємо всі три можливі пари: (a+b), (a+c), (b+c).

#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a + b <= 47 || a + c <= 47 || b + c <= 47) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
