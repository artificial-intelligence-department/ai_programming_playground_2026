//Dragon and crossword
#include <iostream>
#include <string>

using namespace std;
int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    char table[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> table[i][j];
        }
    }
    char copytable[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            copytable[i][j] = table[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int copy = table[i][j];
            int cnt = 0;
            for (int k = 0; k < m; k++)
            {
                if (k != j && copy == table[i][k])
                {
                    copytable[i][j] = 0;
                    copytable[i][k] = 0;
                }
            }
            for (int k = 0; k < n; k++)
            {
                if (k != i && copy == table[k][j])
                {
                    copytable[i][j] = 0;
                    copytable[k][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(copytable[i][j] !=0
            )
            cout << copytable[i][j];
        }
    }

    return 0;
}