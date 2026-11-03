#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 100;

//вивід масиву
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Кільце вліво (від K до K-1)
void printLeft(const int arr[], int n, int k) {
    int curr = k;
    for (int i = 0; i < n; i++) {
        cout << arr[curr] << " ";
        curr = (curr - 1 + n) % n;
    }
    cout << endl;
}

// Кільце вправо (від K до K+1)
void printRight(const int arr[], int n, int k) {
    int curr = k;
    for (int i = 0; i < n; i++) {
        cout << arr[curr] << " ";
        curr = (curr + 1) % n;
    }
    cout << endl;
}

// Видалення всіх максимальних елементів
void removeMaxElements(int arr[], int &n) {
    if (n <= 0) return;

    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != max_val) {
            arr[newSize++] = arr[i];
        }
    }
    n = newSize;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int arr[MAX_SIZE];
    int n;

    cout << "Введіть кількість елементів масиву (1 до 100): ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        cout << "Некоректний розмір масиву!" << endl;
        return 1;
    }

    // Генерація масиву
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 50;   // 0..49
    }

    cout << "\nЗгенерований масив:\n";
    printArray(arr, n);                    

    // Введення K
    int k;
    cout << "\nВведіть початковий індекс K (0 <= K < " << n << "): ";
    cin >> k;

    while (k < 0 || k >= n) {
        cout << "Некоректний індекс! Введіть значення від 0 до " << n - 1 << ": ";
        cin >> k;
    }

    //кільце
    cout << "\nОбхід по кільцю ВЛІВО (від K=" << k << " до K-1):\n";
    printLeft(arr, n, k);

    //видалення всіх максимумів
    removeMaxElements(arr, n);

    //масив після видалення макс. елемента
    cout << "\nМасив після видалення всіх максимальних елементів:\n";
    if (n == 0) {
        cout << "Масив став порожнім!" << endl;
        return 0;
    }
    printArray(arr, n);                    

    // Нормалізуємо K під новий розмір
    k = k % n;

    //кільце вправо
    cout << "\nОбхід по кільцю ВПРАВО (від K=" << k << " до K+1):\n";
    printRight(arr, n, k);

    return 0;
}