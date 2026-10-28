/*
Задача:  Лабораторна робота 5
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

const int MAX = 10;

void findSaddlePoints(int matrix[][MAX], int rows, int columns);

int main() {
    int matrix[MAX][MAX];
    int rows, columns;

	inputRows:
    cout << "Кількість рядків (1–10): ";
    if (!(cin >> rows) || rows < 1 || rows > MAX) {
        cout << "Некоректна кількість рядків. Спробуй ще раз" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputRows;
    }

	inputColumns:
    cout << "Кількість стовпців (1–10): ";
    if (!(cin >> columns) || columns < 1 || columns > MAX) {
        cout << "Некоректна кількість стовпців. Спробуй ще раз" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto inputColumns;
    }

    // Вводимо кожен елемент матриці
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
			inputElement:
            cout << "Елемент [" << i + 1 << "][" << j + 1 << "]: ";
            if (!(cin >> matrix[i][j])) {
                cout << "Введи ціле число" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                goto inputElement;
            }
        }
    }

    cout << endl;
    cout << "Матриця:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    findSaddlePoints(matrix, rows, columns);

    return 0;
}

void findSaddlePoints(int matrix[][MAX], int rows, int columns) {
    bool found = false;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            bool minRow = true;
            bool maxRow = true;
            bool minCol = true;
            bool maxCol = true;

            // Порівнюємо елемент з усіма числами його рядка
            for (int k = 0; k < columns; k++) {
                if (matrix[i][k] < matrix[i][j])
                    minRow = false;
                if (matrix[i][k] > matrix[i][j])
                    maxRow = false;
            }

            // Порівнюємо елемент з усіма числами його стовпця
            for (int k = 0; k < rows; k++) {
                if (matrix[k][j] < matrix[i][j])
                    minCol = false;
                if (matrix[k][j] > matrix[i][j])
                    maxCol = false;
            }

            if ((minRow && maxCol) || (maxRow && minCol)) {
                cout << "Сідлова точка: " << matrix[i][j] << ", рядок " << i + 1 << ", стовпець " << j + 1 << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Сідлових точок немає" << endl;
    }
}

