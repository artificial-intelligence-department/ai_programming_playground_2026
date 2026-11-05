/*
Лабораторна робота №5
Варіант: 21
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
using namespace std;


int MaxRepeatingElement(int a[100][100], int r, int c)
{
    int maxRep = -1;
    bool found = false;

   
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int count = 0;

            for (int x = 0; x < r; x++)
            {
                for (int y = 0; y < c; y++)
                {
                    if (a[x][y] == a[i][j])
                    {
                        count++;
                    }
                }
            }

            
            if (count > 1)
            {
               
                if (!found || a[i][j] > maxRep)
                {
                    maxRep = a[i][j];
                    found = true;
                }
            }
        }
    }

    if (found)
        return maxRep;
    else
        return -1; 
}

int main()
{
    int mas[100][100], r, c;

    cout << "Введіть кількість рядків та стовпців: ";
    cin >> r >> c;

    cout << "Введіть елементи матриці:" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> mas[i][j];
        }
    }

    int result = MaxRepeatingElement(mas, r, c);

    if (result != -1)
        cout << "Максимальний з повторюваних елементів: " << result << endl;
    else
        cout << "Повторюваних елементів у матриці немає!" << endl;

    return 0;
}