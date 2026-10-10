/*Складний екзамен - Задача 1872
Максімко Павло - СШІ-13*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string n;
    cin >> n;
    for(int i = 0; i < n.size() - 1; i++)
    {
        if(n[i] == '4' && n[i + 1] == '7')
        {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}