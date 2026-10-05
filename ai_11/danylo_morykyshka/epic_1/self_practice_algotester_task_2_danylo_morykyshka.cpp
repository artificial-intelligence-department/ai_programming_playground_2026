/*
    Епік 1.self practice, Algotester, задача "Музикант мобільний"
    Автор: Данило Морикишка
    Група: ШІ-11
*/

#include <iostream>

using namespace std;

int main()
{   
    // Оголошуємо змінні
    int countOfSeconds; // Кількість секунд на дзвінок
    int totalSum = 0; // Початкова загальна сума за тариф
    
    //Оголошуємо константи
    const int PRICEFOR7MINUTES = 9; // Ціна за кожну хвилину до 7 хвилин
    const int CONNECTION = 11; // Ціна за підключення тарифу
    const int PRICEAFTER7MINUTES = 5; //  Ціна за кожну хвилину після 7 хвилин

    cin >> countOfSeconds;

    // Конвертуємо секунди в хвилини

    int minutes = countOfSeconds / 60;
    
    // Перевіряємо, чи є неповна хвилина

    if (countOfSeconds % 60 != 0)
    {
        minutes++;
    }

    // Додаємо до суми ціну за підключення тарифу

    totalSum += CONNECTION;

    // Розраховуємо загальну вартість усіх хвилин

    for (int i = 0; i < minutes; i++)
    {
        // Перевіряємо, чи входить хвилина до перших семи
        if(i < 7)
        {
            totalSum += PRICEFOR7MINUTES;
        }

         // Якщо це восьма або наступна хвилина
        else
        {
            totalSum += PRICEAFTER7MINUTES;
        }
    }

    cout << totalSum;
    

}