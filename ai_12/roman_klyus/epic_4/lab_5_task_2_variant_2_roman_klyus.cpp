#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

const int max_rows = 100;
const int max_cols = 100;

void swap_rows(int mas[][max_cols], int row1, int row2, int cols) {
    for (int j = 0; j < cols; j++) {
        int temp = mas[row1][j];
        mas[row1][j] = mas[row2][j];
        mas[row2][j] = temp;
    }
}

void sort_matrix(int mas[][max_cols], int rows, int cols) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - 1 - i; j++) {
            if (mas[j][2] > mas[j + 1][2]) {
                swap_rows(mas, j, j + 1, cols);
            }
        }
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(-10, 10);

    int rows, cols;
    cout << "Введіть кількість рядків від 1 до " << max_rows << ": ";
    cin >> rows;
    if (rows < 1 || rows > max_rows) {
        cout << "Помилка: кількість рядків має бути від 1 до " << max_rows << "\n";
        return 1;
    }

    cout << "Введіть кількість стовпців від 3 до " << max_cols << ": ";
    cin >> cols;
    if (cols < 3 || cols > max_cols) {
        cout << "Помилка: кількість стовпців має бути від 3 до " << max_cols
             << " (для сортування за третім стовпцем потрібно мінімум 3)\n";
        return 1;
    }

    int mas[max_rows][max_cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mas[i][j] = distrib(gen);
        }
    }

    cout << "\nПочаткова матриця:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(4) << mas[i][j];
        }
        cout << "\n";
    }

    sort_matrix(mas, rows, cols);
    cout << "\nВідсортована матриця:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(4) << mas[i][j];
        }
        cout << "\n";
    }

}