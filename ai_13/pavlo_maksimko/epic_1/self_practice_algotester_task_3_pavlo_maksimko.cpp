/*Депутатські гроші - Задача 0021
Максімко - СШІ-13*/


#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int cost, amount = 0;
    
    //Введення вартості 
    cin >> cost;
    //Валідація вартості
    if(cin.fail())
    {
        cout << "Вартість повинна бути числом!" << endl;
        return 1;
    }
    if(cost < 1 || cost > pow(10, 9))
    {
        cout << "Неправильно введена вартість" << endl;
        return 1;
    }
    
    //Розділення вартості на купюри та підрахунок кількості
    while(cost > 0)
    {
        if(cost >= 500) cost -= 500;
        else if(cost >= 200 && cost < 500) cost -= 200;
        else if(cost >= 100 && cost < 200) cost -= 100;
        else if(cost >= 50 && cost < 100) cost -= 50;
        else if(cost >= 20 && cost < 50) cost -= 20;
        else if(cost >= 10 && cost < 20) cost -= 10;
        else if(cost >= 5 && cost < 10) cost -= 5;
        else if(cost >= 2 && cost < 5) cost -= 2;
        else if(cost >= 1 && cost < 2) cost--;
        amount++;
    }
    
    //Виведення кількості купюр
    cout << amount << endl;
    return 0;
}