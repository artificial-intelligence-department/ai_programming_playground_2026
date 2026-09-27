/*A плюс B - Задача 0001
Максімко - СШІ-13*/


#include <iostream>

using namespace std;

int main()
{
    int a, b;
    
    //Введення даних
    cin >> a >> b;
    //Валідація введених даних
    if(cin.fail())
    {
        cout << "Введені дані мають бути числами!" << endl;
        return 1;
    }
    if(a < 0 || a > 100 || b < 0 || b > 100)
    {
        cout << "Неправильно введені дані!" << endl;
        return 1;
    }
    
    //Виведення суми
    cout << a + b << endl;
    return 0;
}