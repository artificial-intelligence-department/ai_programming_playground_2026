/*Марічка і печиво - Задача 0011
Максімко - СШІ-13*/


#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long amount_packs, sum = 0; 
    
    //Введення кількості пачок печива
    cin >> amount_packs;
    
    //Валідація кількості пачок печива
    if(cin.fail())
    {
        cout << "Кількість пачок печива має бути числом!" << endl;
        return 1;
    }
    if(amount_packs < 1 || amount_packs > pow(10, 5))
    {
        cout << "Кількість пачок повинна бути не менше 1 і не більше 100000!" << endl;
        return 1;
    }
    
    long long amount_cookies[amount_packs];
    
    //Введення кількості штук печива у певній пачці та сумування печива, залишаючи 1 штуку в пачці
    for(int i = 0; i < amount_packs; i++)
    {
        cin >> amount_cookies[i];
        
        //Валідація кількості печива у певній пачці
        if(cin.fail())
        {
            cout << "Кількість печива у пачці має бути числом!" << endl;
            return 1;
        }
        if(amount_cookies[i] > pow(10, 9) || amount_cookies[i] < 0)
        {
            cout << "Кількість печива у пачці має бути не більше 10 у 9-му степені та не менше 0" << endl;
            return 1;
        }
        
        //Перевірка кількості печива у пачці на можливість з'їсти хоч 1
        if(amount_cookies[i] > 1)
        {
        sum += amount_cookies[i] - 1;
        }
    }
    
    //Виведення даних
    cout << sum;
    return 0;
}