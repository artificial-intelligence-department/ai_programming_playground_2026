/*
Назва: Лабораторна робота 5 Варіант 19
Автор: Бичковський Володимир
Група: ШІ-11
*/

#include <iostream>
#include <string>

using namespace std;

const int MAX_N = 10;

void fillMatrix(const string& str, int matrix[MAX_N][MAX_N], int n) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = str[index++] - '0';
        }
    }
}

bool First(int matrix[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (matrix[i][0] > matrix[i + 1][0]) {
            return false;
        }
    }
    return true;
}

void printMatrix(int matrix[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Введіть N: ";
    cin >> n;

    string str;
    cout << "Введіть рядок з " << n * n << " цифр: ";
    cin >> str;

    if (str.length() != n * n) {
        cout << "Помилка: довжина рядка має бути " << n * n << endl;
        return 1;
    }

    int matrix[MAX_N][MAX_N];

    fillMatrix(str, matrix, n);

    cout << "\nМатриця:" << endl;
    printMatrix(matrix, n);

    if (First(matrix, n)) {
        cout << "\nВІДПОВІДЬ: ТАК, перший стовпець розташований у порядку зростання." << endl;
    } else {
        cout << "\nВІДПОВІДЬ: НІ, перший стовпець не розташований у порядку зростання." << endl;
    }

    return 0;
}