/*
Епік 2. Алготестер 1. Варіант 3.
Автор: Кобилянська Софія
Група: ші-11
*/

#include <iostream>

using namespace std;

int main()
{
    long long a1, a2, a3, a4, a5;
    if (!(cin >> a1 >> a2 >> a3 >> a4 >> a5))
        return 0;

    if (a1 <= 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }

    if (a2 <= 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }
    if (a2 > a1)
    {
        cout << "LOSS" << endl;
        return 0;
    }

    if (a3 <= 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }
    if (a3 > a2)
    {
        cout << "LOSS" << endl;
        return 0;
    }

    if (a4 <= 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }
    if (a4 > a3)
    {
        cout << "LOSS" << endl;
        return 0;
    }

    if (a5 <= 0)
    {
        cout << "ERROR" << endl;
        return 0;
    }
    if (a5 > a4)
    {
        cout << "LOSS" << endl;
        return 0;
    }

    cout << "WIN" << endl;

    return 0;
}