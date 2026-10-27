#include <iostream>
using namespace std;


const int MAX_N = 100;

void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void printMatrix(int matrix[][MAX_N], int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void findMaxInSubmatrix(int matrix[][MAX_N], int N, int k, int& max_i, int& max_j) {
    int target_col = N - 1 - k;
    int max_val = matrix[k][0];
    max_i = k;
    max_j = 0;

    for (int i = k; i < N; ++i) {
        for (int j = 0; j <= target_col; ++j) {
            if (matrix[i][j] > max_val) {
                max_val = matrix[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
}


void swapRows(int matrix[][MAX_N], int N, int row1, int row2) {
    for (int c = 0; c < N; ++c) {
        swapValues(matrix[row1][c], matrix[row2][c]);
    }
}

void swapCols(int matrix[][MAX_N], int N, int col1, int col2) {
    for (int r = 0; r < N; ++r) {
        swapValues(matrix[r][col1], matrix[r][col2]);
    }
}

void rearrangeMatrixBySecondaryDiagonal(int matrix[][MAX_N], int N) {
    for (int k = 0; k < N; ++k) {
        int target_col = N - 1 - k;
        int max_i = k;
        int max_j = 0;

        findMaxInSubmatrix(matrix, N, k, max_i, max_j);

        if (max_i != k) {
            swapRows(matrix, N, k, max_i);
        }

        if (max_j != target_col) {
            swapCols(matrix, N, target_col, max_j);
        }
    }
}

bool isStrictlyDecreasingSecondaryDiagonal(int matrix[][MAX_N], int N) {
    for (int k = 0; k < N - 1; ++k) {
        int current = matrix[k][N - 1 - k];
        int next = matrix[k + 1][N - 1 - (k + 1)];
        
        if (current <= next) {
            return false;
        }
    }
    return true;
}

void printSecondaryDiagonal(int matrix[][MAX_N], int N) {
    cout << "Елементи на бічній діагоналі: ";
    for (int k = 0; k < N; ++k) {
        cout << matrix[k][N - 1 - k] << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Введіть розмір матриці N (від 1 до 100): ";
    if (!(cin >> N) || N <= 0 || N > MAX_N) {
        cout << "Помилка вводу. Розмір має бути від 1 до 100." << endl;
        return 1;
    }

    int matrix[MAX_N][MAX_N];

    cout << "\nВведіть елементи матриці розміром " << N << "x" << N << ":" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nПочаткова матриця:" << endl;
    printMatrix(matrix, N);

    rearrangeMatrixBySecondaryDiagonal(matrix, N);

    cout << "Матриця після перестановок:" << endl;
    printMatrix(matrix, N);

    printSecondaryDiagonal(matrix, N);

    if (isStrictlyDecreasingSecondaryDiagonal(matrix, N)) {
        cout << "Результат перевірки: Так, на бічній діагоналі строго спадаюча послідовність." << endl;
    } else {
        cout << "Результат перевірки: Ні, послідовність не є строго спадаючою (є однакові значення)." << endl;
    }

    return 0;
}