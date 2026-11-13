#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPSILON = 1e-6;

// Функція для обчислення скалярного добутку двох рядків матриці
double SKD(double** matrix, int row1, int row2, int n) { // n — розмірність матриці // a_1b_1 + a_2b_2 + a_nb_n
    double sum = 0.0;
    for (int k = 0; k < n; k++) {
        sum += matrix[row1][k] * matrix[row2][k];
    }
    return sum;
}

// Функція для перевірки, чи є матриця ортонормованою
bool isOrthonormal(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double product = SKD(matrix, i, j, n);
            
            if (i == j) {
                // Скалярний добуток рядка самого на себе має дорівнювати 1
                if (abs(product - 1.0) > EPSILON) {
                    return false;
                }
            } else {
                // Скалярний добуток різних рядків має дорівнювати 0
                if (abs(product - 0.0) > EPSILON) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Функція для виведення матриці на екран
void printMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << setprecision(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Введіть розмірність квадратної матриці (N): ";
    cin >> n;

    // Динамічне виділення пам'яті під двовимірний масив (матрицю)
    double** matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }

    cout << "Введіть елементи матриці " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    cout << endl << "Введена матриця:" << endl;
    printMatrix(matrix, n);
    cout << endl;

    // Перевірка матриці на ортонормованість
    if (isOrthonormal(matrix, n)) {
        cout << "Результат: Матриця є ОРТОНОРМОВАНОЮ." << endl;
    } else {
        cout << "Результат: Матриця НЕ є ортонормованою." << endl;
    }

    // Звільнення виділеної пам'яті
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}