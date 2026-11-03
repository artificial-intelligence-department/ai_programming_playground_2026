#include <iostream>

using namespace std;
// Функція повертає суму елементів одного конкретного стовпця
int colSum(int **matrix, int rows, int colNum) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += matrix[i][colNum];
    }
    return sum;
}
// Шукає перший стовпець K, де сума стовпців ліворуч більша за суму праворуч
int findColumn(int **matrix, int rows, int cols) {
    int find = -1;
    for (int K = 1; K < cols - 1; K++) {
        int leftSum = 0;
        int rightSum = 0;
        // Рахуємо суму стовпців зліва від K
        for (int i = 0; i < K; i++) {
            leftSum += colSum(matrix, rows, i);
        }
        // Рахуємо суму стовпців справа від K
        for (int j = K + 1; j < cols; j++) {
            rightSum += colSum(matrix, rows, j);
        }
        if (leftSum > rightSum) {
            find = K;
            break; // Перериваємо, бо потрібен перший такий стовпець
        }
    }
    return find;
}
// Функція для зчитування матриці з перевіркою коректності вводу
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
// Функція виводу матриці
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
    // Зчитуємо та перевіряємо розміри матриці
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
    // Виділяємо пам'ять під двовимірний динамічний масив
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    // Заповнюємо матрицю з перевіркою числових даних
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
    // Знаходимо потрібний стовпець і виводимо його номер
    int isFind;
    isFind = findColumn(matrix,  rows, cols);
    if (isFind == -1) {
        cout << "Немає стовбця який розбиває масив на 2 частини і ліва є більшою за праву" << endl;
    } else {
        cout << "Стовбець який розбиває масив на 2 частини і ліва є більшою за праву: " << isFind + 1 << endl;
    }
    // Звільняємо динамічну пам'ять
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;

    return 0;
}