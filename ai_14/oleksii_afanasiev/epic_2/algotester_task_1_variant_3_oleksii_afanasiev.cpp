/*
Задача: Lab 1v3 (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
    long long a, a_old;
    cin >> a_old;

    if(a_old <= 0)
    {
        cout << "ERROR";
        return 1;
    }

    for(int i = 1; i < 5; i++)
    {
        cin >> a;
        if(a <= 0)
        {
            cout << "ERROR";
            return 0;
        }
        if(a > a_old)
        {
            cout << "LOSS";
            return 0;
        }
        a_old = a;

    }
    cout << "WIN";

    return 0;
}
