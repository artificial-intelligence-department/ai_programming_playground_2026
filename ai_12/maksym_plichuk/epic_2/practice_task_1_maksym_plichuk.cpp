#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

/* Плічук Максим ШІ-12
    Аналізатор надійності пароля
*/

int main()
{
    int passLength;
    char hasNumbers;
    char hasBigLetters;
    char hasSpecialCharacters;

    //Введення користувачем параметрів свого паролю
    cout << "Довжина пароля: ";
    if (not(cin >> passLength))
    {
        //Якщо ввід неправильний завершення програми з рекомендацією
        cout << "Помилка: довжина мусить бути числом.";
        return 1;
    }

    if (not(passLength >= 1 and passLength <= 64))
    {
        cout << "Помилка: довжина мусить бути від 1 до 64.";
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> hasNumbers;
    if (not(hasNumbers == 'y' or hasNumbers == 'n'))
    {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'.";
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> hasBigLetters;
    if (not(hasBigLetters == 'y' or hasBigLetters == 'n'))
    {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'.";
        return 1;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> hasSpecialCharacters;
    if (not(hasSpecialCharacters == 'y' or hasSpecialCharacters == 'n'))
    {
        cout << "Помилка: відповідь мусить бути 'y' або 'n'.";
        return 1;
    }

    
    //Підрахунок кількості символів
    int charactersType = 0;
    if (hasNumbers == 'y') charactersType += 1;
    if (hasBigLetters == 'y') charactersType += 1;
    if (hasSpecialCharacters == 'y') charactersType += 1;

    //Перевірка на проходження мінімальних вимог
    bool passedMinRequirements;
    if (passLength >= 8 and charactersType >= 2)
    {
        passedMinRequirements = true;
    }
    else
    {
        passedMinRequirements = false;
    }

    //Визначення рівня безпеки
    int securityLevel = 0;
    std::string securityType;

    if (passLength < 6)
    {
        securityType = "Дуже слабкий";
        securityLevel = 1;
    }
    else if (passLength < 8 || charactersType == 0)
    {
        securityType = "Слабкий";
        securityLevel = 2;
    }
    else if (charactersType == 1)
    {
        securityType = "Середній";
        securityLevel = 3;
    }
    else if (passLength >= 12 && charactersType == 3)
    {
        securityType = "Дуже надійний";
        securityLevel = 5;
    }
    else
    {
        securityType = "Надійний";
        securityLevel = 4;
    }


    std::string recomendation;

    //Формування рекомендацій
    switch (securityLevel)
    {
        case 1:
            recomendation = "Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            recomendation = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            recomendation = "Додайте ще один тип символів або збільште довжину до 12.";
            break;
        case 4:
            recomendation = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;
        case 5:
            recomendation = "Відмінно. Змінювати нічого не потрібно.";
            break;
        default:
            recomendation = "Пароль надто короткий. Мінімум 8 символів.";
            break;
    }
    
    cout << "Мінімальні вимоги: " << (passedMinRequirements ? "ПРОЙДЕНО" : "НЕ ПРОЙДЕНО") << endl;
    cout << "Рівень надійності: " << securityLevel << " - " << securityType << endl;
    cout << "Рекомендація: " << recomendation << endl;

    //Перевірка на попередження (якщо немає ні цифр, ні спецсимволів)
    if (hasNumbers == 'n' and hasSpecialCharacters == 'n')
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}


