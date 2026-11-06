
/* 
Епік 4. Лабораторна робота 4. Варіант 7.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

int inputInt(int minValue) {
    int x;

    // Повторює введення, доки не буде отримано коректне значення.
    while (!(cin >> x) || x < minValue) {
        cout << "Помилка! Введіть ціле число не менше "
             << minValue << ": ";

        // Скидає стан помилки та пропускає некоректний рядок.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return x;
}

int main() {
    cout << "Введіть кількість елементів: ";
    int n = inputInt(1);

    // Виділяє пам'ять для масиву заданого розміру.
    int* arr = new int[n];

    // Ініціалізує генератор випадкових чисел і заповнює масив.
    srand(time(0));

    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }

    // Виводить початковий масив.
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    // Знаходить індекс останнього нуля в масиві.
    int index = -1;

    for (int i = 0; i < n; ++i) {
        if (arr[i] == 0) {
            index = i;
        }
    }

    // Якщо нуль знайдено, зсуває наступні елементи вліво та зменшує розмір.
    if (index != -1) {
        for (int i = index; i < n - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --n;
    }

    // Зчитує індекс елемента, після якого буде вставлено число 100.
    cout << "Введіть індекс елемента (від 0 до " << n - 1 << "): ";

    int indx = inputInt(0);

    while (indx >= n) {
        cout << "Помилка! Індекс має бути меншим за " << n << ". Введіть ще раз: ";
        indx = inputInt(0);
    }

    // Створює новий масив на один елемент більший.
    int* newArr = new int[n + 1];

    // Копіює елементи до вказаного індексу включно.
    for (int i = 0; i <= indx; ++i) {
        newArr[i] = arr[i];
    }

    // Вставляє число 100 після елемента з індексом indx.
    newArr[indx + 1] = 100;

    // Копіює решту елементів, зсунувши їх на одну позицію вправо.
    for (int i = indx + 1; i < n; ++i) {
        newArr[i + 1] = arr[i];
    }

    // Оновлює розмір і виводить масив після вставлення.
    ++n;

    for (int i = 0; i < n; ++i) {
        cout << newArr[i] << ' ';
    }

    // Звільняє динамічно виділену пам'ять.
    delete[] arr;
    delete[] newArr;

    return 0;
}