/*
Епік 4. Лабораторна робота №5. Завдання №1. Варіант №24
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

void deleteMatrix(int** &matrix, int rows);
int findHowMany(int** matrix, int valueMax, int rows, int cols);

int main () {

    int rows, cols;
    int quantity = 0;
    const int MAX_VALUE = 20;
    const int MIN_VALUE = 1;
    
    cout << "Введіть кількість рядків (ціле число, від 1 до 20): ";
    cin >> rows;
    if (cin.fail() || rows > MAX_VALUE || rows < MIN_VALUE) {
        cout << "Помилка! Введіть ціле число, від 1 до 20\n";
        return 1;
    }

    cout << "Введіть кількість стовпців (ціле число, від 1 до 20): ";
    cin >> cols;
    if (cin.fail() || cols > MAX_VALUE || cols < MIN_VALUE) {
        cout << "Помилка! Введіть ціле число, від 1 до 20\n";
        return 1;
    }

    int **matrix = new int*[rows];                       //ЗВІЛЬНИТИ ПАМʼЯТЬ
    for (int i = 0; i<rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            cout << "Введіть елемент " << i+1 << " рядка " << j+1 << " стопвця: ";
            cin >> matrix[i][j];
            if (cin.fail()) {
                cout << "Помилка! Введіть ціле число\n";
                deleteMatrix(matrix, rows);
                return 1;
            }
        }
    }

    int valueMax = matrix[0][0];

    for (int i = 0; i<rows && i<cols; i++) {
        if (valueMax < matrix[i][i]) valueMax = matrix[i][i];
    }

    quantity = findHowMany(matrix, valueMax, rows, cols);
    
    cout << "Кількість елементів, що більші від будь-якого елемента на головній діагоналі: " << quantity << "\n\n";

    deleteMatrix(matrix, rows);

    return 0;
}

void deleteMatrix(int** &matrix, int rows) {

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }

    delete[] matrix;
    matrix = nullptr;

}

int findHowMany(int** matrix, int valueMax, int rows, int cols) {
    
    int count = 0;

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            if (matrix[i][j] > valueMax) count ++;
        }
    }

    return count;
}
