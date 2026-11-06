/*Лабораторна 5
Варіант: 9*/

#include <iostream>
using namespace std;

int matriX(int **m, int n);

int main()
{
    cout << "Введіть кількість матриць: ";
    int n;
    cin >> n;
    if(cin.fail() || n < 1)
    {
        cout << "Кількість матриць має бути додатнім цілим числом!" << endl;
        return 1;
    }
    int *sums = new int[n];
    for(int i = 0; i < n; i++)
    {
        cout << "Введіть розмір матриці(n x n): ";
        int m;
        cin >> m;
        if(cin.fail() || m < 1)
        {
            cout << "Розмір матриці має бути додатнім цілим числом!" << endl;
            return 1;
        }
        cout << "Матриця " << i + 1 << endl;
        int **matrix = new int*[m];
        for(int j = 0; j < m; j++)
        matrix[j] = new int[m];

        for(int j = 0; j < m; j++)
        {
            for(int t = 0; t < m; t++)
            {
                cin >> matrix[j][t];
                if(cin.fail())
                {
                    cout << "Елементи матриці мають бути цілими числами!" << endl;
                    for(int n = 0; n < m; n++)
                    delete[] matrix[n];
                    delete[] matrix;
                    matrix = nullptr;
                    return 1;
                }
            }
        }
        cout << endl;
        cout << "Сума елементів під головною діагоналлю: " << matriX(matrix, m) << endl;
        cout << endl;
        sums[i] = matriX(matrix, m);

        for(int j = 0; j < m; j++)
        delete[] matrix[j];
        delete[] matrix;
        matrix = nullptr;
    }
    int max = sums[0];
    for(int i = 0; i < n; i++)
    {
        if(sums[i] > max)
        max = sums[i];
    }
    cout << "Найбільша сума: " << max << endl;

    delete[] sums;
    sums = nullptr;
}

int matriX(int **m, int n)
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        int *r = m[i];
        for(int j = 0; j < n; j++)
        {
            if(i > j)
            sum += *(m[i] + j);
        }
    }
    return sum;
}