// Algotester, задача №40603 "Matrix"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40603
// Ткач Артем, ШІ-13
//
// Умова: дано бінарну матрицю n x m. За один хід можна поміняти місцями значення
// двох елементів (ходів може бути скільки завгодно). Потрібно визначити, чи можна
// розставити елементи так, щоб у матриці не було підматриці розміром a x b, усі
// елементи якої дорівнюють 1. Є t тестів.

#include <iostream>

int main() {
    int t;
    std::cin >> t;

    for (int test = 0; test < t; test++) {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;

        int zeros = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c;
                std::cin >> c;
                if (c == '0') {
                    zeros++;
                }
            }
        }

        int needZeros = (n / a) * (m / b);
        if (zeros >= needZeros) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
