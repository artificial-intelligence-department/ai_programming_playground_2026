/*Задача про задачі - Задача 1761 
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    short int a, b, c;
    cin >> a >> b >> c;
    if(cin.fail())
    {
        cout << "Введені складності задач повинні бути числами!" << endl;
        return 0;
    }

    if(a > 47 || b > 47 || c > 47)
    {
        cout << "Введені складності задач повинні бути не більше 47!" << endl;
        return 0;
    }

    if(a + b <= 47 || a + c <= 47 || b + c <= 47)
    {
        cout << "YES" << endl;
        return 0;
    }
    else
    {
        cout << "NO" << endl;
        return 0;
    }
}