/*
    Задача: Лабораторна робота №5. Варіант №24
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
const int N = 100;
// Введення матриці
void inputMatrix(int M[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> M[i][j];
        }
    }
}
// Виведення матриці
void printMatrix(int M[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    } 
}
// Пошук максимального елемента головної діагоналі
int maxDiagonal(int M[N][N], int n)
{
    int maxD = M[0][0];
    for (int i = 1; i < n; i++)
    {
        if (M[i][i] > maxD)
        {
            maxD = M[i][i];
        }
    }
    return maxD;
}
// Підрахунок елементів, більших за максимум діагоналі
int countElements(int M[N][N], int n, int value)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] > value)
            {
                count++;
            }
        }
    }
    return count;
}
int main() {
    int n;
    int M[N][N];
    cout << "Введіть розмір матриці n: ";
    cin >> n;
    inputMatrix(M, n);
    cout << "Матриця:" << endl;
    printMatrix(M, n);
    int maxD = maxDiagonal(M, n);
    int count = countElements(M, n, maxD);
    cout << "Максимум на головній діагоналі: "<< maxD << endl;
    cout << "Кількість елементів, більших за всі діагональні: " << count << endl;
    return 0;
}