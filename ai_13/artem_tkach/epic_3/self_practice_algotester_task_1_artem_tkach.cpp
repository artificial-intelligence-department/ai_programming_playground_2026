// Algotester, задача №20075 "Teeth"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/20075
// Ткач Артем, ШІ-13
//
// Зчитуємо N зубів з коефіцієнтами гостроти. Зуб "крутий", якщо A[i] >= K.
// Один прохід по масиву: рахуємо довжину поточної послідовності крутих зубів
// і запам'ятовуємо найбільшу. Некрутий зуб обриває послідовність.

#include <iostream>

int main() {
    int n;
    long long k;
    std::cin >> n >> k;

    int current = 0; // довжина поточної послідовності
    int best = 0;    // найдовша знайдена послідовність

    for (int i = 0; i < n; i++) {
        long long a;
        std::cin >> a;

        if (a >= k) {
            current++;
            if (current > best) {
                best = current;
            }
        } else {
            current = 0;
        }
    }

    std::cout << best << "\n";
    return 0;
}
