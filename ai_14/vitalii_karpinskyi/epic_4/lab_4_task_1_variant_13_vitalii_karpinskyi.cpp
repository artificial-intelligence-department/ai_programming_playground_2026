#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    srand(time(0));
    int N = 110;
    int arr[N];
    // Зчитуємо розмір масиву та робимо валідацію
    int n;
    cout << "Введіть кількість елементів масиву: ";
    cin >> n;
    if (cin.fail() || n < 1 || n > 100) {
        cout << "Помилка: довжина повинна бути від 1 до 100" << endl;
        return 0;
    }
    // Заповнюємо рандомними числами
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Початковий масив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Шукаємо мінімальне значення у масиві
    int min_find = arr[0];
    for (int i = 1; i < n; i++) {
        if (min_find > arr[i]) {
            min_find = arr[i];
        }
    }
    // Видаляємо всі елементи, що дорівнюють мінімуму, зсувом ліворуч
    for (int i = 0; i < n; i++) {
        if (arr[i] == min_find) {
            for (int j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            n--;
            i--; // Повертаємось на крок назад, щоб перевірити зміщений елемент
        }
    }
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    if (n == 0) {
        cout << "Масив порожній" << endl;
        return 0;
    }
    // Обчислюємо середнє арифметичне елементів
    double average = sum / n;
    // Зсуваємо елементи праворуч на 3 позиції для звільнення місця на початку
    for (int i = n - 1; i >= 0; i--) {
        arr[i + 3] = arr[i];
    }
    n += 3;
    // Вставляємо Середнє значення у перші 3 позиції
    for (int i = 0; i < 3; i++) {
        arr[i] = round(average);
    }
    cout << "Масив після всіх перетворень: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}