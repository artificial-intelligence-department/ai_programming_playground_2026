// Лабораторна робота №4, варіант 3
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// з запасом, бо на 4 кроці масив стає більшим
const int MAX_SIZE = 100;

void fillRandom(int arr[], int n, int low, int high) {
    for (int i = 0; i < n; i++) {
        arr[i] = low + rand() % (high - low + 1);
    }
}

void printArray(const int arr[], int n) {
    if (n == 0) {
        cout << "(масив порожній)" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// видаляємо нулі
int removeZeros(int arr[], int n) {
    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }
    return newSize;
}

// вставка після першого парного
int insertAfterFirstEven(int arr[], int n) {
    // шукаємо перший парний
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "Парних елементів немає, тому нічого не додаємо." << endl;
        return n;
    }

    if (n >= MAX_SIZE) {
        cout << "У масиві немає місця для нового елемента." << endl;
        return n;
    }

    // якщо pos == 0, то arr[-1] немає, беру 0
    int value;
    if (pos > 0) {
        value = arr[pos - 1] + 2;
    } else {
        value = 0 + 2;
    }

    // зсув вправо, з кінця
    for (int i = n; i > pos + 1; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos + 1] = value;

    return n + 1;
}

int main() {
    srand(time(0));

    int arr[MAX_SIZE];
    int n;

    cout << "Введіть кількість елементів (від 1 до " << MAX_SIZE - 1 << "): ";
    cin >> n;

    if (n < 1 || n > MAX_SIZE - 1) {
        cout << "Некоректна кількість елементів." << endl;
        return 1;
    }

    // від -10 до 10, щоб нулі випадали частіше
    fillRandom(arr, n, -10, 10);

    cout << "Початковий масив:" << endl;
    printArray(arr, n);

    n = removeZeros(arr, n);
    cout << "Після видалення нулів:" << endl;
    printArray(arr, n);

    n = insertAfterFirstEven(arr, n);
    cout << "Після додавання елемента після першого парного:" << endl;
    printArray(arr, n);

    return 0;
}