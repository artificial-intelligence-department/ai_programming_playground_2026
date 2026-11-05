#include <iostream>
using namespace std;

// введення матриці
void inputMatrix(int a[][20], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        cout << "Рядок " << i + 1 << ": ";
        for (int j = 0; j < cols; j++)
            cin >> a[i][j];
    }
}

// друк матриці
void printMatrix(int a[][20], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

// сума стовпця col без (col + 1) останніх елементів
int columnSum(int a[][20], int rows, int col)
{
    int sum = 0;
    for (int i = 0; i < rows - (col + 1); i++)
        sum = sum + a[i][col];
    return sum;
}

int main()
{
    int a[20][20];
    int rows, cols;

    cout << "Кількість рядків (від 2 до 20): ";
    cin >> rows;
    while (rows < 2 || rows > 20)
    {
        cout << "Неправильно, введіть ще раз: ";
        cin >> rows;
    }

    cout << "Кількість стовпців (від 2 до 20): ";
    cin >> cols;
    while (cols < 2 || cols > 20)
    {
        cout << "Неправильно, введіть ще раз: ";
        cin >> cols;
    }

    inputMatrix(a, rows, cols);

    cout << "Матриця:" << endl;
    printMatrix(a, rows, cols);

    // останній стовпець не рахуємо, тому j < cols - 1
    int maxSum = columnSum(a, rows, 0);
    int maxCol = 0;

    for (int j = 0; j < cols - 1; j++)
    {
        int sum = columnSum(a, rows, j);
        cout << "Сума стовпця " << j + 1 << " = " << sum << endl;

        if (sum > maxSum)
        {
            maxSum = sum;
            maxCol = j;
        }
    }

    cout << "Максимальна сума = " << maxSum << " (стовпець " << maxCol + 1 << ")" << endl;

    return 0;
}