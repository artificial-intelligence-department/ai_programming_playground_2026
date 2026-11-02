// Algotester, задача №71022 "Repeating numbers in a matrix"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/71022
// Ткач Артем, ШІ-13
//
// Умова: дано матрицю цілих чисел n x m, кожне число зустрічається в ній не більше
// двох разів. Знайти всі числа, які зустрічаються рівно двічі: вивести їх кількість k,
// а в другому рядку самі числа у довільному порядку.


#include <iostream>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    int total = n * m;
    int *values = new int[total];
    for (int i = 0; i < total; i++) {
        std::cin >> values[i];
    }

    std::sort(values, values + total);

    int *repeated = new int[total / 2 + 1];
    int k = 0;
    for (int i = 0; i + 1 < total; i++) {
        if (values[i] == values[i + 1]) {
            repeated[k] = values[i];
            k++;
            i++;  
        }
    }

    std::cout << k << "\n";
    for (int i = 0; i < k; i++) {
        std::cout << repeated[i] << " ";
    }
    std::cout << "\n";

    delete[] values;
    delete[] repeated;
    return 0;
}
