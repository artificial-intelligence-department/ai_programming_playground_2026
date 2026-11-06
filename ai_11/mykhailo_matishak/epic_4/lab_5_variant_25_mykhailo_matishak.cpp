/*Епік 3. Лабораторна робота 5. Варіант 25
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>

using namespace std;

void restoreMatrix(int** A, int m, int n, int* arr, int* firstRow, int* firstCol) {
    int* rowNum = new int[m];
    int* colNum = new int[n];

    for (int i = 0; i < m; i++) {
        for (int k = 0; k < m * n; k++) {
            if (arr[k] == firstCol[i]) {
                rowNum[i] = k / n;
                break;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < m * n; k++) {
            if (arr[k] == firstRow[j]) {
                colNum[j] = k % n;
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = arr[rowNum[i] * n + colNum[j]];
        }
    }

    delete[] rowNum;
    delete[] colNum;
    rowNum = nullptr;
    colNum = nullptr;
}

int main() {
    int n, m;
    cout << "Введіть кількість стовпців n: ";
    cin >> n;
    cout << "Введіть кількість рядків m: ";
    cin >> m;

    int* arr = new int[m * n];
    cout << "Введіть одновимірний масив: ";
    for (int i = 0; i < m * n; i++) {
        cin >> arr[i];
    }

    int* firstRow = new int[n];
    int* firstCol = new int[m];
    cout << "Введіть перший рядок: ";
    for (int j = 0; j < n; j++) {
        cin >> firstRow[j];
    }
    cout << "Введіть перший стовпець: ";
    for (int i = 0; i < m; i++) {
        cin >> firstCol[i];
    }

    int** A = new int*[m];
    for (int i = 0; i < m; i++) {
        A[i] = new int[n];
    }

    restoreMatrix(A, m, n, arr, firstRow, firstCol);

    cout << "Результат:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++) {
        delete[] A[i];
        A[i] = nullptr;
    }
    delete[] A;
    A = nullptr;
    delete[] arr;
    arr = nullptr;
    delete[] firstRow;
    firstRow = nullptr;
    delete[] firstCol;
    firstCol = nullptr;

    return 0;
}