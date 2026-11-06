/*
Лабораторна робота №5, Завдання 1, Варіант 7
Станіслав Коваль
ШІ-12
*/

#include <iostream>
using namespace std;

void swap(int** arr, int n, int i, int j) {
    int* row = new int[n];
    int* col = new int[n];

    for (int k = 0; k < n; ++k) {
        row[k] = arr[i][k];
        col[k] = arr[k][j];
    }

    for (int k = 0; k < n; ++k) {
        arr[i][k] = col[k];
        arr[k][j] = row[k];
    }

    delete[] row;
    delete[] col;
}

void change_rowcol(int** array, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // перший елемент i-го рядка == перший елемент j-го стовпця
            if (array[i][0] == array[0][j]) {
                swap(array, n, i, j);
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Введіть розмір матриці nxn: ";
    cin >> n;
    int** arr = new int*[n];

    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    cout << endl;

    change_rowcol(arr, n);

    // 3. Очищення пам'яті
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}