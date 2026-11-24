/*Алготестер lab4v3 (власна реалізація)
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

const int N = 1000;

void mergeSortDescending(int r[], int n)
{
    if (n > 1)
    {
        int m = n/2;
        int k = n - m;
        int a[m] = {0};
        int b[k] = {0};

        for (int i = 0; i < m; i++)
        {
            a[i] = r[i];
        }
        for (int i = 0; i < k; i++)
        {
            b[i] = r[i+m];
        }
        mergeSortDescending(a, m);
        mergeSortDescending(b, k);

        int i = 0;
        int j = 0;
        for (int l = 0; l < n; l++)
        {
            r[l] = ((a[i] > b[j]) && i < m) || j >= k ? a[i++] : b[j++];
        }
    }
}

void mergeSortAscending(int r[], int n)
{
    if (n > 1)
    {
        int m = n/2;
        int k = n - m;
        int a[m] = {0};
        int b[k] = {0};

        for (int i = 0; i < m; i++)
        {
            a[i] = r[i];
        }
        for (int i = 0; i < k; i++)
        {
            b[i] = r[i+m];
        }
        mergeSortAscending(a, m);
        mergeSortAscending(b, k);

        int i = 0;
        int j = 0;
        for (int l = 0; l < n; l++)
        {
            r[l] = ((a[i] < b[j]) && i < m) || j >= k ? a[i++] : b[j++];
        }
    }
}

void removeDuplicates(int a[], int &n)
{
    int copy[n] = {0};
    int j = 0;
    int duplicates = 0;

    for (int i = 0; i < n; i++)
    {
        copy[i] = a[i];
        a[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (copy[i] != copy[i+1]) a[j++] = copy[i];
        else duplicates++;
    }
    n -= duplicates;
}

int main()
{
    int n = 0;
    int a[N] = {0};

    int a_first[N] = {0};
    int first = 0;
    int a_second[N] = {0};
    int second = 0;
    int a_third[N] = {0};
    int third = 0;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] % 3 == 0)
        {
            a_first[first] = a[i];
            first++;
        }
        else if (a[i] % 3 == 1)
        {
            a_second[second] = a[i];
            second++;
        }
        else
        {
            a_third[third] = a[i];
            third++;
        }
    }

    mergeSortAscending(a_first, first);
    mergeSortDescending(a_second, second);
    mergeSortAscending(a_third, third);

    removeDuplicates(a_first, first);
    removeDuplicates(a_second, second);
    removeDuplicates(a_third, third);

    int m = first + second + third;
    cout << m << endl;
    for(int i = 0; i < first; i++)
    {
        cout << a_first[i] << " ";
    }
    for(int i = 0; i < second; i++)
    {
        cout << a_second[i] << " ";
    }
    for(int i = 0; i < third; i++)
    {
        cout << a_third[i] << " ";
    }

    return 0;
}
