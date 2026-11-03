#include <iostream>
using namespace std;

const int MAX = 20;   // максимальний розмір


void formMatrix(int n, int a[], int m[][MAX])
{
    for (int j = 0; j < n; j++)          
    {
        int target = a[j];              

        // Заповнюємо всі елементи стовпця одиницями (крім останнього)
        for (int i = 0; i < n - 1; i++)
            m[i][j] = 1;

        // Останній елемент підбираємо так, щоб сума стала рівною target
        m[n - 1][j] = target - (n - 1);

        // Якщо останній елемент 0 
        if (m[n - 1][j] == 0)
        {
            m[n - 1][j] = 2;             
            m[0][j] = -1;                
        }
    }
}

// Функція виведення матриці
void printMatrix(int n, int m[][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << "\t";
        cout << endl;
    }
}


int main()
{
    int n;
    int a[MAX];
    int m[MAX][MAX];

    cout << "Введіть розмір N: ";
    cin >> n;

    if (n < 1 || n > MAX)
    {
        cout << "Некоректний розмір!\n";
        return 1;
    }

    cout << "Введіть " << n << " елементів одновимірного масиву:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i];

   
    formMatrix(n, a, m);

    cout << "\nСформована матриця " << n << "x" << n << ":\n";
    printMatrix(n, m);

    return 0;
}