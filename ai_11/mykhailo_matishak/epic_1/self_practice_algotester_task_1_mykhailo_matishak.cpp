/*Епік 1. Self practice: Algotester, task "A + B"
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    if (cin.fail())
    {
        cout << "Помилка: A і B мають бути цілими числами." << endl;
        return 1;
    }

    if (a < 0 || a > 100 || b < 0 || b > 100)
    {
        cout << "Помилка: A і B мають бути в межах від 0 до 100." << endl;
        return 1;
    }

    cout << a + b << endl;
    return 0;
}