/*Депутатські гроші
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int m = 0;
    while(n >= 500)
    {
        m++;
        n = n - 500;
    }
    while(n >= 200)
    {
        m++;
        n = n - 200;
    }
    while(n >= 100)
    {
        m++;
        n = n - 100;
    }
    while(n >= 50)
    {
        m++;
        n = n - 50;
    }
    while(n >= 20)
    {
        m++;
        n = n - 20;
    }
    while(n >= 10)
    {
        m++;
        n = n - 10;
    }
    while(n >= 5)
    {
        m++;
        n = n - 5;
    }
    while(n >= 2)
    {
        m++;
        n = n - 2;
    }
    while(n >= 1)
    {
        m++;
        n = n - 1;
    }
    cout << m << endl;
    return 0;
}