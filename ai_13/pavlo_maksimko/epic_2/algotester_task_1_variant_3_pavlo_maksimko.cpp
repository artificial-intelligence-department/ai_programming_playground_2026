/*Задача lab 1v3
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    long long a[5];
    for(int i = 0; i < 5; i++)
    {
        cin >> a[i];
        if(a[i] <= 0)
        {
            cout << "ERROR" << endl;
            return 0;
        }
        else if(a[i - 1] < a[i] && i > 0)
        {
            cout << "LOSS" << endl;
            return 0;
        }
    }
    cout << "WIN" << endl;
    return 0;
}
