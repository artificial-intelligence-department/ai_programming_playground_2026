#include <iostream>

using namespace std;

int colSum(int **matrix, int rows, int colNum) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += matrix[i][colNum];
    }
    return sum;
}

int findColumn(int **matrix, int rows, int cols) {
    int find = -1;
    for (int K = 1; K < cols - 1; K++) {
        int leftSum = 0;
        int rightSum = 0;
        for (int i = 0; i < K; i++) {
            leftSum += colSum(matrix, rows, i);
        }
        for (int j = K + 1; j < cols; j++) {
            rightSum += colSum(matrix, rows, j);
        }
        if (leftSum > rightSum) {
            find = K;
            break;
        }
    }
    return find;
}

bool inputMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
            if (cin.fail()) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;
    cout << "Введіть кількість рядків матриці (до 10): ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 10) {
        cout << "Помилка: рядків має бути від 1 до 10" << endl;
        return 0;
    }
    cout << "Введіть кількість стовпців матриці (до 10): ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 10) {
        cout << "Помилка: стовпців має бути від 1 до 10" << endl;
        return 0;
    }

    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    cout << "Введіть елементи двовимірного масиву: " << endl;
    if (!inputMatrix(matrix, rows, cols)) {
        cout << "Помилка: потрібно вводити цілі числа" << endl;
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
        return 0;
    } else {
        cout << "Введена матриця:" << endl;
        printMatrix(matrix, rows, cols);
    }

    int isFind;
    isFind = findColumn(matrix,  rows, cols);
    if (isFind == -1) {
        cout << "Немає стовбця який розбиває масив на 2 частини і ліва є більшою за праву" << endl;
    } else {
        cout << "Стовбець який розбиває масив на 2 частини і ліва є більшою за праву: " << isFind + 1 << endl;
    }

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;

    return 0;
}