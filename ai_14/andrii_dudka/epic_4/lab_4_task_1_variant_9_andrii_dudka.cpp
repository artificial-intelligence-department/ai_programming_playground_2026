// variant 9

#include <iostream>
#include <cstdlib>

using namespace std;

int randomNumber() {
    return rand() % 101 - 50;
}

int main() {
    int n, m;

    cout << "Введіть кількість елементів масиву (1–100): ";
    if (!(cin >> n) || n < 1 || n > 100) {
        cout << "Некоректна кількість елементів!";
        return 1;
    }

    int arr[100];

    for (int i = 0; i < n; ++i)
        arr[i] = randomNumber();

    cout << "Згенерований масив: ";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Введіть число для видалення: ";
    if (!(cin >> m))
        return 1;

    int new_arr[100];
    int new_size = 0;
    bool removed = false;

    // Видаляємо лише перше входження числа m.
    for (int i = 0; i < n; ++i) {
        if (arr[i] == m && !removed) {
            removed = true;
        } else {
            new_arr[new_size] = arr[i];
            new_size++;
        }
    }

    if (!removed)
        cout << "Такого числа в масиві немає." << endl;

    cout << "Масив після обробки: ";
    for (int i = 0; i < new_size; ++i)
        cout << new_arr[i] << " ";
    cout << endl;

    int k;
    cout << "Введіть кількість позицій для зсуву вправо: ";
    if (!(cin >> k) || k < 0) {
        cout << "Потрібно ввести невід'ємне ціле число!";
        return 1;
    }

    if (new_size > 0) {
        k %= new_size;

        int shifted[100];

        // Виконуємо циклічний зсув вправо.
        for (int i = 0; i < new_size; ++i)
            shifted[(i + k) % new_size] = new_arr[i];

        for (int i = 0; i < new_size; ++i)
            new_arr[i] = shifted[i];

        cout << "Масив після циклічного зсуву вправо: ";
        for (int i = 0; i < new_size; ++i)
            cout << new_arr[i] << " ";
        cout << endl;
    } else {
        cout << "Масив порожній, зсув неможливий." << endl;
    }

    return 0;
}