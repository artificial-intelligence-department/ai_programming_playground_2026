#include <iostream>
using namespace std;

void swapRowColumn(int **m, int size, int row, int col){
    int *temp = new int[size];

    for (int i = 0; i < size; i++)
    {
        temp[i] = m[row][i];
    }

    for (int i = 0; i < size; i++)
    {
        m[row][i] = m[i][col];
    }

    for (int i = 0; i < size; i++)
    {
        m[i][col] = temp[i];
    }

    delete[] temp;   
}
void findToSwap(int **m, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (m[i][0] == m[0][j])
            {
                swapRowColumn(m, size, i, j);
            }
        }
    }
}
void printMatrix(int** m, int size){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int rows, cols;
    cout << "Введіть кількість рядків: ";
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    cin >> cols;
    if (rows != cols)
    {
        cout << "Обмін рядка й стовпця можливий лише для квадратної матриці!" << endl;
        return 1;
    }

    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    cout << "Введіть значення для матриці " << rows << " x " << cols << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << "\nПочаткова матриця:" << endl;
    printMatrix(matrix, rows);
    findToSwap(matrix, rows);

    cout << "\nЗмінена матриця:" << endl;
    printMatrix(matrix, rows);

    for (int i = 0; i < rows; i++)  
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}