/*
Lab 5
Лисюк Андріана
ШІ-13
Варіант 11
*/

#include <iostream>

using namespace std;

const int maxRows = 100;
const int maxCols = 100;

bool isDescending(int row[], int cols) {
    for (int i = 0; i < cols - 1; i++) {
        if (row[i + 1] > row[i]) {
            return false;
        }
    }
    return true;
}
void sortAscending(int row[], int cols) {
    for (int i = 0; i < cols - 1; i++) {
        for (int j = 0; j < cols - i - 1; j++) {
            if (row[j] > row[j + 1]) {
                int temp = row[j];
                row[j] = row[j + 1];
                row[j + 1] = temp;
            }
        }
    }
}
void printMatrix(int matrix[][maxCols], int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << matrix[r][c] << "  ";
        }
        cout << endl;
    }
}
int main() {
    int rows, cols;
    cout << "Введіть кількість рядків: ";
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    cin >> cols;
    if (rows <= 0 || rows > maxRows || cols <= 0 || cols > maxCols) {
        cout << "Некоректний розмір!" << endl;
        return 1;
    }
    int matrix[maxRows][maxCols];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << "Введіть елемент [" << r << "][" << c << "]: ";
            cin >> matrix[r][c];
        }
    }
    cout << endl << "Введена матриця:" << endl;
    printMatrix(matrix, rows, cols);
    
    for (int r = 0; r < rows; r++) {
        if (!isDescending(matrix[r], cols)) {
            sortAscending(matrix[r], cols);
        }
    }
    cout << endl << "Результат:" << endl;
    printMatrix(matrix, rows, cols);

    return 0;
}