/*
    Задача: Симетрична матриця
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >>n;
    char a[1000][1000];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    bool symmetric = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != a[j][i])
            {
                symmetric = false;
            }
        }
    }
    if (symmetric)
    {
        cout << "Yes";
    } else
    {
        cout << "No";
    }
    return 0;
}