#include <iostream>
using namespace std;

void transponation(int array[][100], int arrayT[][100], int i)
{
    int a;
    int b;

    for(a = 0; a <= i - 1; ++a)
    {
        for(b = 0; b <= i - 1; ++b)
        {
            arrayT[a][b] = array[b][a];
            cout << arrayT[a][b] << " ";
            if (b == i - 1)
            {
                cout << "\n";
            }
        }
    }
}

void symetric(int array[][100], int arrayT[][100], int i)
{
    bool sym = true;
    for(int a = 0; a < i; ++a)
    {
        for(int b = 0; b < i; ++b)
        {
            if (array[a][b] != arrayT[a][b])
            {
                sym = false;
                break;
            }            
        }
    }
    if(sym)
    {
        cout << "Матриця симетрична!\n";
    }
    else
    {
        cout << "Матриця не симетрична!\n";
    }
}

int main()
{
    
    int i;
    cout << "Введіть розмір матриці: ";
    if(!(cin >> i) || i <= 0 || i > 100) return 0;

    int array[100][100];
    int arrayT[100][100];
    int n;
    int m;
    for(m = 1; m <= i; ++m)
        {
            for(n = 1; n <= i; ++n)
            {
            cout << "Введіть значення " << m << " рядку " << n << " стовбцю: ";
            if(!(cin >> array[m-1][n-1])) return 0;
            }
        }

    cout << "Початкова матриця: \n";
    for(int a = 0; a < i; ++a)
    {
        for(int b = 0; b < i; ++b)
        {
        cout << array[a][b] << " ";
        if (b == i - 1)
        {
            cout << "\n";
        }
        }
    }
    cout << "\nТранспонована матриця: \n";

    transponation(array, arrayT, i);

    symetric(array, arrayT, i);
}