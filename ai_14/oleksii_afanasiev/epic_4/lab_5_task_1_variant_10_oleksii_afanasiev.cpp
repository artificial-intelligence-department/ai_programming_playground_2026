/*
Задача: Lab 5 Task 1
Виконав: Афанасьєв Олексій (ШІ-14)
*/
#include <iostream>
using namespace std;

bool containsNegative(int** A, const int m, const int row)
{
    bool flag = false;
    
    for(int j = 0; j < m; j++)
    {
        if(A[row][j] < 0) return true;
    }

    return false;
}

int main()
{
    int rows, cols;

    cout << "Введіть кількість рядків: ";
    cin >> rows;

    cout << "Введіть кількість стовпців: ";
    cin >> cols;

    int** A = new int*[rows];
    for(int i = 0; i < rows; i++)
    {
        A[i] = new int[cols];
    }

    cout << endl;
    cout << "Введіть елементи матриці:" << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cin >> A[i][j];
        }
    }

    int** A_new = new int*[rows];
    
    int k = 0;
    for(int i = 0; i < rows; i++)
    {
        if(containsNegative(A, cols, i))
        {
            delete[] A[i];
        }
        else
        {
            A_new[k] = A[i];
            k++;
        }
    }

    for(int i = k; i < rows; i++)
    {
        A_new[i] = new int[cols]();
    }

    delete[] A;
    A = A_new;
    A_new = nullptr;

    cout << endl;
    cout << "Результат:" << endl;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < rows; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}
