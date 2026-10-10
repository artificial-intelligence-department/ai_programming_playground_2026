/*Чи вже осінь? - Задача 2001
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    int tests;
    cin >> tests;
    if(cin.fail())
    {
        cout << "Кількість тестів повинні бути числом!" << endl;
        return 0;
    }

    for(int i = 0; i < tests; i++)
    {
        int month;
        cin >> month;
        if(cin.fail())
        {
            cout << "Номер місяця повинен бути числом!" << endl;
            return 0;
        }

        switch(month)
        {
            case 9:
                cout << "yes" << endl;
                break;
            case 10:
                cout << "yes" << endl;
                break;
            case 11: 
                cout << "yes" << endl;
                break;
            default:
                cout << "no" << endl;
                break;
        }
    }

    return 0;
}