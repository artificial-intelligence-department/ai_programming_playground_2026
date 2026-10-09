/*Жеребець і кобила - Задача 2151
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if(cin.fail())
    {
        cout << "Введені дані повинні бути числами!" << endl;
        return 0;
    }

    if(x1 > 0 && x2 > 0 && y1 > 0 && y2 > 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    else if(x1 > 0 && x2 > 0 && y1 < 0 && y2 < 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    else if(x1 < 0 && x2 < 0 && y1 > 0 && y2 > 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    else if(x1 < 0 && x2 < 0 && y1 < 0 && y2 < 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    else
    {
        cout << "No" << endl;
        return 0;
    }
}