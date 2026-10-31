#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    const int N = 100;      // максимальна довжина
    int a[N];
    int n;                  // реальна довжина

    cout << "Введіть довжину масиву (1.." << N << "): ";
    cin >> n;
    if (n < 1 || n > N) {
        cout << "Некоректна довжина!" << endl;
        return 1;
    }

    // 1. Заповнення випадковими числами
    srand((unsigned)time(0));
    for (int i = 0; i < n; i++)
        a[i] = rand() % 101 - 50;   // числа від -50 до 50

    // 2. Друк початкового масиву
    cout << "Початковий масив:" << endl;
    printArray(a, n);

    // 3. Перевертання масиву
    for (int i = 0; i < n / 2; i++) {
        int tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }

    // Якщо кількість елементів непарна - видалити середній
    if (n % 2 != 0) {
        int mid = n / 2;
        for (int i = mid; i < n - 1; i++)
            a[i] = a[i + 1];
        n--;                        // зменшуємо реальну довжину
    }

    // 4. Додавання на початок 3 елементів зі значенням M[I+10]-2
    if (n < 13) {
        cout << "Недостатньо елементів для M[I+10] (потрібно мінімум 13, є "
             << n << ")." << endl;
    } else if (n + 3 > N) {
        cout << "Недостатньо місця в масиві для додавання 3 елементів." << endl;
    } else {
        int vals[3];
        for (int k = 0; k < 3; k++)
            vals[k] = a[k + 10] - 2;    // I = 0, 1, 2

        // зсув елементів вправо на 3 позиції
        for (int i = n - 1; i >= 0; i--)
            a[i + 3] = a[i];

        // запис нових елементів на початок
        for (int k = 0; k < 3; k++)
            a[k] = vals[k];

        n += 3;  // збільшуємо реальну довжину
    }

    // 5. Друк результату
    cout << "Отриманий масив:" << endl;
    printArray(a, n);

    return 0;
}