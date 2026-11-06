/*Задача 3, алготестер
Варіант: 2*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for(int i = 0; i < n; i++)
    cin >> a[i];
    int m;
    cin >> m;
    int *b = new int[m];
    for(int i = 0; i < m; i++)
    cin >> b[i];

    int s = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(a[i] == b[j])
            s++;
        }
    }

    delete[] a;
    a = nullptr;
    delete[] b;
    b = nullptr;
    int u = n + m - s;
    cout << s << endl << u << endl;
}