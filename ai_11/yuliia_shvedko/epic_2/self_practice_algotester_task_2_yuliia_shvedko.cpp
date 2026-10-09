/*Цікава гра
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    int m;
    cin >> n >> m;
    int l = n*m;
    if(l % 2 != 0)
    {
        cout << "Imp" << endl;
    }
    else
    cout << "Dragon" << endl;

    return 0;
}