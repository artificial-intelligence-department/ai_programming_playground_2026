/*
Задача:  Лабораторна робота 4
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    const int MAX = 100;
    int numbers[MAX];
    int n;

inputSize:
    cout << "Кількість елементів (1–100): ";
    if (!(cin >> n) || n < 1 || n > MAX) {
        cout << "Некоректна кількість елементів. Спробуй ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputSize;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    // Заповнюємо масив випадковими числами
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 11;
    }

    cout << "Початковий масив: ";
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    int position;

inputPosition:
    cout << "Номер елемента для видалення (1–" << n << "): ";
    if (!(cin >> position) || position < 1 || position > n) {
        cout << "Некоректний номер елемента. Спробуй ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputPosition;
    }

    int index = position - 1;

    // Зсуваємо наступні елементи вліво, щоб прибрати вибраний
    for (int i = index; i < n - 1; i++) {
        numbers[i] = numbers[i + 1];
    }
    n--;

    // Знаходимо перше парне число
    int evenIndex = -1;
    for (int i = 0; i < n; i++) {
        if (numbers[i] % 2 == 0) {
            evenIndex = i;
            break;
        }
    }

    if (evenIndex != -1) {
        int insertIndex = evenIndex + 1;
        int newValue = numbers[evenIndex] + 2;

        // Зсуваємо елементи вправо, починаючи з останнього
        for (int i = n; i > insertIndex; i--) {
            numbers[i] = numbers[i - 1];
        }

        numbers[insertIndex] = newValue;
        n++;
    }
    else {
        cout << "Парних елементів немає — вставку пропущено." << endl;
    }

    cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}