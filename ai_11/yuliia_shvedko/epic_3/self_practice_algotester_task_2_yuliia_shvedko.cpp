/*3 + 1
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
using namespace std;

int main()
{
    int a[10];
    int s = 0;
    for(int i = 0; i < 4; i++)
    {
        cin >> a[i];
        s += a[i];
    }
    int min = a[0];
    for(int i = 0; i < 4; i++)
    {
        if(a[i] < min)
        min = a[i];
    }
    cout << s - min << endl;

    return 0;
}