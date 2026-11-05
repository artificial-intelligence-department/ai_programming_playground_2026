/*
    Лабораторна робота 5. Завдання 1. Варіант 3.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
using namespace std;

const int MAXSIZE = 100;

// matrices sum
void matrixSum(int M_1[MAXSIZE][MAXSIZE], int M_2[MAXSIZE][MAXSIZE], int M_3[MAXSIZE][MAXSIZE], int size) {
    for (int i = 0; i < size; ++i) { // i = row
        for (int j = 0; j < size; ++j) { // j = column
            M_3[i][j] = M_1[i][j] + M_2[i][j];
        }
    }
}

// matrix transpose
void matrixTranspose(int M_start[MAXSIZE][MAXSIZE], int M_Trans[MAXSIZE][MAXSIZE], int size) {
    for (int i = 0; i < size; ++i) { // i = row
        for (int j = 0; j < size; ++j) { // j = column
            M_Trans[i][j] = M_start[size-j-1][i];
        }
    }
}

// matrix output
void matrixOutput(int M[MAXSIZE][MAXSIZE], int size) {
    for (int i = 0; i < size; ++i) { // i = row
        for (int j = 0; j < size; ++j) { // j = column
            cout << M[i][j];
            if (j < size-1) {
                cout << " ";
            }
            else {
                cout << "\n";
            }
        }
    }
    cout << "\n";
}
int main() {
    int matrix[MAXSIZE][MAXSIZE] = {};
    int matrix_T[MAXSIZE][MAXSIZE] = {};
    int matrix_sum[MAXSIZE][MAXSIZE] = {};

    int size = 0;
    cout << "Matrix size: ";
    while (!(cin >> size) or size < 1 or size > MAXSIZE) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Matrix size must be from 1 to 100.\n";
    }
    cout << "\n";

    // matrix filling
    cout << "Matrix 1 elements:\n";
    for (int i = 0; i < size; ++i) { // i = row
        for (int j = 0; j < size; ++j) { // j = column
            cin >> matrix[i][j];
        }
    }
    cout << "\n";

    // transposing matrix
    cout << "Matrix transposed:\n";
    matrixTranspose(matrix, matrix_T, size);
    matrixOutput(matrix_T, size);

    // matrices sum
    cout << "Matrix sum: \n";
    matrixSum(matrix, matrix_T, matrix_sum, size);
    matrixOutput(matrix_sum, size);

    return 0;
}