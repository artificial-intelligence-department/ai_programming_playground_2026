/*Коля, Вася і Теніс - Задача 0031
Максімко - СШІ-13*/


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    long long amount, K_letter = 0, V_letter = 0, kolya_win = 0, vasya_win = 0;
    
    //Введення кількості подач
    cin >> amount;
    //Валідація введеня кількості подач
    if(cin.fail())
    {
        cout << "Кількість подач повинна бути числом!" << endl;
        return 1;
    }

    if(amount > pow(10, 5) || amount < 1)
    {
        cout << "Кількість подач повинна бути не менше 1 і не більше 10 у 5-му степені!" << endl;
        return 1;
    }
    
    char serve[amount]; 
    
    for(int i = 0; i < amount; i++)
    {
        //Введення того, хто виграв ту чи іншу подачу
        cin >> serve[i];
        
        if(serve[i] == 'K') K_letter++;
        else if(serve[i] == 'V') V_letter++;
        else //Валідація введення переможця подач
        {
            cout << "Введені букви переможця подач повинні бути або K або V!" << endl;
            return 1;
        }
        if(abs(K_letter - V_letter) >= 2)
        {
            if(K_letter > V_letter && K_letter > 10) 
            {
                kolya_win++;
                K_letter = 0;
                V_letter = 0;
            }
            else if(V_letter > K_letter && V_letter > 10) 
            {
                vasya_win++;
                K_letter = 0;
                V_letter = 0;
            }
        }
    }
    cout << kolya_win << ":" << vasya_win << endl;
    if(K_letter > 0 || V_letter > 0)
    {
        cout << K_letter << ":" << V_letter << endl;
    }
    return 0;
}