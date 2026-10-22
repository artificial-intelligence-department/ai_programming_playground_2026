/*Зуби
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    unsigned int k;
    cin >> n >> k;
    unsigned int a[100000];
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int p = 0;
    int m = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] >= k)
        {
            p++;
            if(p > m)
            m = p;
        }
        else
        p = 0;
    }

    cout << m << endl;
    return 0;
}