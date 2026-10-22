/*Помічники Санта Клауса
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    int a[1000];
    int b[1000];
    int c[1000];
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    int m = n - 1;
    for(int i = 0; i < n; i++)
    {
        c[i] = a[m];
        m--;
    }
    bool r = true;
    for(int i = 0; i < n; i++)
    {
        if(b[i] != c[i])
        r = false;
    }
    if(r)
    cout << "Yes" << endl;
    if(!r)
    {
        cout << "No" << endl;
        for(int i = 0; i < n; i++)
        cout << c[i] << " ";
    }

    return 0;
}