// Algotester, задача №40475 "Halloween"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40475
// Ткач Артем, ШІ-13
//
// Знаходимо найдешевшу цукерку в кожному з двох мішків (мінімум масиву)
// і виводимо суму цих двох значень.

#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    int minZenyk, minMarichka;

    std::cin >> minZenyk; // перша цукерка Зеника - початковий мінімум
    for (int i = 1; i < n; i++) {
        int a;
        std::cin >> a;
        if (a < minZenyk) {
            minZenyk = a;
        }
    }

    std::cin >> minMarichka; // перша цукерка Марічки - початковий мінімум
    for (int i = 1; i < m; i++) {
        int b;
        std::cin >> b;
        if (b < minMarichka) {
            minMarichka = b;
        }
    }

    std::cout << minZenyk + minMarichka << "\n";
    return 0;
}
