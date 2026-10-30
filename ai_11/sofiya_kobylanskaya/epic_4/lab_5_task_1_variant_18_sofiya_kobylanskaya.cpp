#include <iostream>
using namespace std;

const int N = 20;

void inputMatrix(int a[N][N], int &n)
{
    cout << "Enter the length of arrea: " << endl;
    cin >> n;
    while (cin.fail() || n > 20 || n < 1)
    {
        cout << "You only can write the number from 1 to 20. Try again: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> n;
    }
    cout << "Enter all numbers:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            while (cin.fail())
            {
                cout << "You only can write the number. Try again: " << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> a[i][j];
            }
        }
    }
}

void printMatrix(int a[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void processMatrix(int a[N][N], int n)
{
    for (int step = 0; step < n; step++)
    {
        int maxValue = a[step][0];
        int maxRow = step;
        int maxCol = 0;

        for (int i = step; i < n; i++)
        {
            for (int j = 0; j < n - step; j++)
            {
                if (a[i][j] > maxValue)
                {
                    maxValue = a[i][j];
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
        for (int j = 0; j < n; j++)
        {
            int temp = a[step][j];
            a[step][j] = a[maxRow][j];
            a[maxRow][j] = temp;
        }
        for (int i = 0; i < n; i++)
        {
            int temp = a[i][n - 1 - step];
            a[i][n - 1 - step] = a[i][maxCol];
            a[i][maxCol] = temp;
        }

        cout << "        Matrix after swapping: " << endl;
        cout << "______________________________________" << endl;
        printMatrix(a, n);
    }
}

bool checkDiagonal(int a[N][N], int n)
{
    bool isDecreasing = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i][n - 1 - i] <= a[i + 1][n - 2 - i])
        {
            isDecreasing = false;
            break;
        }
    }

    return isDecreasing;
}

int main()
{
    int a[N][N];
    int n;

    inputMatrix(a, n);

    cout << "              Your arrea" << endl;
    cout << "______________________________________" << endl;
    printMatrix(a, n);

    processMatrix(a, n);

    bool isDecreasing = checkDiagonal(a, n);

    if (isDecreasing)
    {
        cout << "The diagonal is decreasing." << endl;
    }
    else
    {
        cout << "The diagonal is not decreasing." << endl;
    }
    return 0;
}