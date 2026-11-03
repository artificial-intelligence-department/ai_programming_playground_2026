#include <iostream>
using namespace std;
void deleteRows();
int main()
{   
    cout << "Введіть кількість рядків: ";
    int rows;
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    int cols;
    cin >> cols;
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> matrix[i][j];
        }
    }
    cout << "Матриця:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << matrix[i][j];
        }
    }
}