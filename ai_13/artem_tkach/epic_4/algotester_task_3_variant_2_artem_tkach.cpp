/*
 * Algotester, Лабораторна робота №3, варіант 2 - "Lab 3v2"
 * Ткач Артем
 * ШІ-13
 *
 * Умова: дано 2 масиви розміром N та M з унікальними значеннями. Вивести
 * у першому рядку кількість елементів, які є в обох масивах одночасно,
 * у другому - кількість унікальних елементів в обох масивах разом
 * (тобто в масиві, який є об'єднанням двох даних).
 *
 * Обмеження: 0 <= N, M <= 100, значення елементів від 0 до 100, тому для
 * кожного масиву достатньо масиву-позначок inA[101] та inB[101].
 * 
 * https://algotester.com/en/ContestProblem/DisplayWithEditor/167968
 */

#include <iostream>

const int MAX_VALUE = 100;

// Читає розмір і елементи масиву, позначаючи присутні значення в flags
void readSet(bool flags[]) {
    int count, x;
    std::cin >> count;
    for (int i = 0; i < count; i++) {
        std::cin >> x;
        flags[x] = true;
    }
}

int main() {
    bool inA[MAX_VALUE + 1] = {};
    bool inB[MAX_VALUE + 1] = {};
    readSet(inA);
    readSet(inB);

    int common = 0;
    int total = 0;
    for (int v = 0; v <= MAX_VALUE; v++) {
        if (inA[v] && inB[v]) {
            common++;
        }
        if (inA[v] || inB[v]) {
            total++;
        }
    }

    std::cout << common << "\n";
    std::cout << total << "\n";
    return 0;
}
