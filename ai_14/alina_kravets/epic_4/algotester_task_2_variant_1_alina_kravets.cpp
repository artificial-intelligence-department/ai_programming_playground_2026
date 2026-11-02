/*Алготестер lab2v1
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

int check (int r[], int n, int index)
{
    int copy[n-1] = {0};
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != index)
        {
            copy[j] = r[i];
            j++;
        }
    }

    int mn = copy[0];
    int mx = copy[0];
    for (int i = 0; i < n-1; i++)
    {
        if (copy[i] > mx) mx = copy[i];
        else if (copy[i] < mn) mn = copy[i];
    }
    return mx - mn;
}

int main()
{
    const int MAX = 100000;
    int n = 0;
    int r[MAX] = {0};
    int m = 0;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> r[i];
    }

    int min = r[0];
    int max = r[0];
    for (int i = 0; i < n; i++)
    {
        if (r[i] > max) max = r[i];
        else if (r[i] < min) min = r[i];
    }
    m = max - min;

    for (int i = 0; i < n; i++)
    {
        if (check(r, n, i) < m) m = check(r, n, i);
    }

    cout << m;

    return 0;
}
