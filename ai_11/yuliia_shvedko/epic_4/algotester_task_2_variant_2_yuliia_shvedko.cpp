/*Задача 2, алготестер
Варіант: 2*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int *r = new int[n];
    for(int i = 0; i < n; i++)
    cin >> r[i];
    int a, b, c;
    cin >> a >> b >> c;

    int m = n;
    for(int i = 0; i < n; i++)
    {
        if(r[i] == a || r[i] == b || r[i] == c)
        m--;
    }
    if(m > 2)
    {
        int *rr = new int[m];
        int j = 0;
        for(int i = 0; i < n; i++)
        {
            if(r[i] == a || r[i] == b || r[i] == c) continue;
            rr[j] = r[i];
            j++;
        }

        delete[] r;
        r = nullptr;
        m -= 1;
        int *rrr = new int[m];
        cout << m << endl;
        for(int i = 0; i < m; i++)
        {
            rrr[i] = rr[i] + rr[i + 1];
            cout << rrr[i] << " ";
        }
        cout << endl;
        delete[] rr;
        rr = nullptr;
        delete[] rrr;
        rrr = nullptr;
    }
    else
    {
        delete[] r;
        r = nullptr;
        cout << "0" << endl;
    }
    return 0;
}