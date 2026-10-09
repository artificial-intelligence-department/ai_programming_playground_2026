/*Хелловін
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    int m;
    cin >> n >> m;
    int a[100];
    int b[100];

    for(int i = 0; i < n; i++)
    cin >> a[i];
    int min_a = a[0];
    for(int i = 0; i < n; i++)
    {
        if(a[i] < min_a)
        min_a = a[i];
    }

    for(int i = 0; i < m; i++)
    cin >> b[i];
    int min_b = b[0];
    for(int i = 0; i < m; i++)
    {
        if(b[i] < min_b)
        min_b = b[i];
    }

    cout << min_a + min_b << endl;
}