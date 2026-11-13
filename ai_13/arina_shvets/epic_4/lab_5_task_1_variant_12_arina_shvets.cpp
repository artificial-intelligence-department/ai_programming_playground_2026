#include <iostream>

using namespace std;

int findMax(int a[][100], int row, int cols){
    int max = a[row][0];

    for (int j = 1; j < cols; j++){
        if (a[row][j] > max){
            max = a[row][j];
        }
    }

    return max;
}

void printMatrix(int a[][100], int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int rows, cols;

    cout << "Введіть кількість рядків і стовпців: ";
    cin >> rows >> cols;

    if (rows < 1 || rows > 100 || cols < 1 || cols > 100){
        return 1;
    }

    int a[100][100];

    cout << "Введіть елементи матриці:" << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cin >> a[i][j];
        }
    }

    cout << "Початкова матриця:" << endl;
    printMatrix(a, rows, cols);

    for (int i = 0; i < rows; i++){
        int steps = findMax(a, i, cols) % cols;

        if (steps < 0){
            steps += cols;
        }

        for (int k = 0; k < steps; k++){
            int last = a[i][cols - 1];

            for (int j = cols - 1; j > 0; j--){
                a[i][j] = a[i][j - 1];
            }

            a[i][0] = last;
        }
    }

    cout << "Матриця після зсуву:" << endl;
    printMatrix(a, rows, cols);

    return 0;
}