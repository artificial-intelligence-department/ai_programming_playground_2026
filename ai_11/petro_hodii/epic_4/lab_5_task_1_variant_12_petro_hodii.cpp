#include <iostream>

using namespace std;

int findMax(int** mas, int num, int col){
    int max = mas[num-1][0];
    for(int i = 0; i < col; i++){
        if(mas[num - 1][i] > max){max = mas[num - 1][i];}
    }

    return max;
}

int** shift(int** mas, int row, int col){
    int** matrix = new int*[row];
    for(int i = 0; i < row; i++){
        matrix[i] = new int[col];
    }

    for(int i = 0; i < row; i++){
        int shift_num = findMax(mas, i+1, col)%col;
        for(int j = 0; j < col; j++){
            matrix[i][(j+shift_num)%col] = mas[i][j];
        }
    }

    for(int i = 0; i < row; i++){
        delete[] mas[i];
    }
    delete[] mas;
    return matrix;
}


int main(){
    int rows, cols, number;
    cout << "Введіть кількість рядків: ";
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    cin >> cols;

    int** matrix = new int*[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new int[cols];
    }

    cout << "Введіть матрицю:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> matrix[i][j];
        }
    }

    cout << "Введіть номер рядка, в якому треба знайти максимальне число: ";
    cin >> number;

    cout << "Максимальний елемент у рядку " << number << " дорівнює: " << findMax(matrix, number, cols) << endl;
    matrix = shift(matrix, rows, cols);

    cout << "Матриця після циклічного зсуву вправо:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < rows; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;

    return 0;
}