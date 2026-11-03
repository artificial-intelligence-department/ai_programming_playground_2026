/*
Епік 4. Лабораторна робота № 5 (Варіант 6)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 20;

// Функція виведення матриці
void printMatrix(const int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Функція знаходження сідлових точок
void findSaddlePoints(const int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    bool found = false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int current = matrix[i][j];

            // 1) Найменший у своєму рядку і найбільший у стовпці
            bool isMinRow = true;
            for (int c = 0; c < cols; ++c) {
                if (matrix[i][c] < current) {
                    isMinRow = false;
                    break;
                }
            }

            bool isMaxCol = true;
            for (int r = 0; r < rows; ++r) {
                if (matrix[r][j] > current) {
                    isMaxCol = false;
                    break;
                }
            }

            // 2) Найбільший у своєму рядку і найменший у стовпці
            bool isMaxRow = true;
            for (int c = 0; c < cols; ++c) {
                if (matrix[i][c] > current) {
                    isMaxRow = false;
                    break;
                }
            }

            bool isMinCol = true;
            for (int r = 0; r < rows; ++r) {
                if (matrix[r][j] < current) {
                    isMinCol = false;
                    break;
                }
            }

            if ((isMinRow && isMaxCol) || (isMaxRow && isMinCol)) {
                cout << "Сідлова точка: " << current << " на позиції [" << i << "][" << j << "]" << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Сідлових точок немає" << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int rows = 3;
    int cols = 4;

    // Матриця з гарантованою сідловою точкою
    int matrix[MAX_ROWS][MAX_COLS] ={
        { 3,  8,  4,  9 },
        { 2,  5,  7,  6 },
        { 1,  6,  2,  5 }
    };

    cout << "1 - згенерувати матрицю 3x4 \n 2 - ввести матрицю вручну: \n 3 - Матриця з гарантованою сідловою точкою: (3x4)" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << " Випадкова матриця:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = rand() % 50 + 1;
            }
        }

        printMatrix(matrix, rows, cols);
        findSaddlePoints(matrix, rows, cols);

    } else if (choice == 2) {
        cout << "Введіть розміри матриці (рядки та стовпці): ";
        cin >> rows >> cols;
        if (rows > MAX_ROWS || cols > MAX_COLS) {
            cout << "Помилка: розміри перевищують допустимі межі." << endl;
            return 1;
        }
        cout << "Введіть елементи матриці:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> matrix[i][j];
            }
        }


        printMatrix(matrix, rows, cols);
        findSaddlePoints(matrix, rows, cols);

    } else if (choice == 3) {
        cout << "3. Матриця з гарантованою сідловою точкою:" << endl;
        // Матриця вже ініціалізована вище
        printMatrix(matrix, rows, cols);
        findSaddlePoints(matrix, rows, cols);

    } else {
        cout << "Невірний вибір." << endl;
        return 1;
    }

    return 0;
}
