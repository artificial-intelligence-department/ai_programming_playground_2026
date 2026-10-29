/*Epic 4 - Завдання 1 лабораторної 5 варіант 3
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

void input(int matrix[20][20], int rows, int cols){
    cout << "Введіть вихідну матрицю (числа через пробіл), розмір " << rows << "x" << cols << ": " << endl;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            while (!(cin >> matrix[i][j])) {
                cout << "Помилка. Введено нечислове значення. Всі значення після нього були відкинуті" << endl;
                cin.clear();
                cin.ignore(100000, '\n');
            }
        }
    }
}

void rotate(int matrix[20][20], int rotated_matrix[20][20], int rows, int cols){
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            rotated_matrix[j][rows - 1 - i] = matrix[i][j];
        }
    }
}

void add(int matrix[20][20], int rotated_matrix[20][20], int output_matrix[20][20], int rows, int cols){
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            output_matrix[i][j] = matrix[i][j] + rotated_matrix[i][j];
        }
    }
}

void print(int output_matrix[20][20], int rows, int cols){
    cout << "\nВихідна матриця + матриця повернута на 90 градусів вправо:" << endl;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << output_matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

int main(){
    int cols = 0;
    int rows = 0;

    int matrix[20][20];
    int rotated_matrix[20][20];
    int output_matrix[20][20];

    cout << "Введіть кількість рядків вихідної матриці (1-20): ";

    if (!(cin >> rows) || !(rows >= 1) || !(rows <= 20)) {
        cout << "Помилка. Введіть ціле число від 1 до 20" << endl;
        return 1;
    } else {
        cout << "Введіть кількість стовпців вихідної матриці (1-20): ";

        if (!(cin >> cols) || !(cols >= 1) || !(cols <= 20)) {
            cout << "Помилка. Введіть ціле число від 1 до 20" << endl;
            return 1; 
        } 
    }

    if (!(rows == cols)) {
        cout << "Помилка. Матриця має бути квадратною" << endl;
        return 1;
    } else {
        input(matrix, rows, cols);
        rotate(matrix, rotated_matrix, rows, cols);
        add(matrix, rotated_matrix, output_matrix, rows, cols);
        print(output_matrix, rows, cols);
    }

}