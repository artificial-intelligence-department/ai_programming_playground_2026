/*Лабораторна №5 варіант №5
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

const int ROWS = 5;
const int COLLUMNS = 3;

void deleteFunc(int m[][COLLUMNS], int n, int a, int b)
{
    int copy[n][COLLUMNS] = {0};
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        for (int j = 0; j < COLLUMNS; j++)
        {
            if (i < a || i > b) copy[r][c] = m[i][j];
            c++;
        }
        if (i < a || i > b) r++;
    }
    cout << "Масив після змін: { ";
    for (int i = 0; i < n; i++)
    {
        cout << "{";
        for (int j = 0; j < COLLUMNS; j++)
        {
            cout << copy[i][j];
            if (j < COLLUMNS-1) cout << ", ";
        }
        cout << "} ";
    }
    cout << "}" << endl;
}

int main()
{
    int matrix[ROWS][COLLUMNS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    int a = 1;
    int b = 2;

    cout << "Масив до змін: { ";
    for (int i = 0; i < ROWS; i++)
    {
        cout << "{";
        for (int j = 0; j < COLLUMNS; j++)
        {
            cout << matrix[i][j];
            if (j < COLLUMNS-1) cout << ", ";
        }
        cout << "} ";
    }
    cout << "}" << endl;

    deleteFunc(matrix, ROWS, a, b);

    return 0;
}
