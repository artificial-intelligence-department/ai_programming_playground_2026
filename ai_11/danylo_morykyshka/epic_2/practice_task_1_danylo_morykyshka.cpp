/*
    Аналізатор надійності пароля
    Морикишка Данило
    Група: ШІ-11

*/

#include <iostream>

using namespace std;

int main()
{
    //Ініціалізовую константи, які необхідні для визначення обмежень для змінних та створення сталих значень:
    const int MIN_PASSWORD_LENGTH = 1;
    const int MAX_PASSWORD_LENGTH = 64;
    const int VERY_WEAK_LENGTH = 6;
    const int MIN_REQUIRED_LENGTH = 8;
    const int VERY_STRONG_LENGTH = 12;
    const int MIN_REQUIRED_TYPES = 2;
    const int TOTAL_SYMBOL_TYPES = 3;
    const char CONTAIN_SYMBOL = 'y';
    const char NOT_CONTAIN_SYMBOL = 'n';

    // Оголошую змінні, необхідні для перевірки надійності пароля, зчитую їхні значення та перевіряю їх на допустимість:
    cout << "Довжина пароля: ";
    int passwordLength;
    if(!(cin >> passwordLength) || passwordLength < MIN_PASSWORD_LENGTH || passwordLength > MAX_PASSWORD_LENGTH)
    {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    char ContainNumber;

    if(!(cin >> ContainNumber) || (ContainNumber != CONTAIN_SYMBOL && ContainNumber != NOT_CONTAIN_SYMBOL))
    {
        cout << "Помилка!Введіть лише значення " << CONTAIN_SYMBOL << " або " << NOT_CONTAIN_SYMBOL<< endl;
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    char uppercaseChoice;

    if(!(cin >> uppercaseChoice) || (uppercaseChoice != CONTAIN_SYMBOL && uppercaseChoice != NOT_CONTAIN_SYMBOL))
    {
        cout << "Помилка!Введіть лише значення " << CONTAIN_SYMBOL << " або " << NOT_CONTAIN_SYMBOL<< endl;
        return 1;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    char hasSpecialChars;

    if(!(cin >> hasSpecialChars) || (hasSpecialChars != CONTAIN_SYMBOL && hasSpecialChars != NOT_CONTAIN_SYMBOL))
    {
        cout << "Помилка!Введіть лише значення " << CONTAIN_SYMBOL << " або " << NOT_CONTAIN_SYMBOL<< endl;
        return 1;
    }

    cout << endl;
   // Підраховую кількість типів символів у паролі.
    int count = 0;
    if(ContainNumber == CONTAIN_SYMBOL)
    {
        count++;
    }

    if(uppercaseChoice == CONTAIN_SYMBOL)
    {
        count++;
    }

    if(hasSpecialChars == CONTAIN_SYMBOL)
    {
        count++;
    }

    // Визначаю і виводжу в консоль повідомлення чи пройдено мінімальні вимоги 
    cout << "Мінімальні вимоги: ";
    if(passwordLength >= MIN_REQUIRED_LENGTH && count >= MIN_REQUIRED_TYPES)
    {
        cout << "ПРОЙДЕНО" << endl;
    }

    else
    {
        cout << "НЕ ПРОЙДЕНО" << endl;
    }

    // Перевіряю пароль на рівень надійності, ініціалізовую змінну strengthLevel, якій буде присвоєно відповідні значення
    int strengthLevel;

    if(passwordLength < VERY_WEAK_LENGTH)
    {
        strengthLevel = 1;
        cout << "Рівень надійності: " << strengthLevel << " - Дуже слабкий" << endl;
    }

    else if(passwordLength < MIN_REQUIRED_LENGTH || count == 0)
    {
        strengthLevel = 2;
        cout << "Рівень надійності: " << strengthLevel << " - Слабкий" << endl;
    }

    else if(count == 1)
    {
        strengthLevel = 3;
        cout << "Рівень надійності: " << strengthLevel << " - Середній" << endl;
    }

    else if(passwordLength >= VERY_STRONG_LENGTH && count == TOTAL_SYMBOL_TYPES)
    {
        strengthLevel = 5;
        cout << "Рівень надійності: " << strengthLevel << " - Дуже надійний" << endl;
    }

    else 
    {
        strengthLevel = 4;
        cout << "Рівень надійності: " << strengthLevel << " - Надійний" << endl;
    }

    // За допомгою оператора switch в консоль виводитиметься відповідна рекомендація до захисту пароля

    cout << "Рекомендація: ";

    switch (strengthLevel)
    {
    case 1:
        cout << "Пароль надто короткий. Мінімум 8 символів."<< endl;
        break;
    case 2:
        cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<< endl;
        break;
    case 3:
        cout << "«Додайте ще один тип символів або збільште довжину до 12.»"<< endl;
        break;
    case 4:
        cout << "«Хороший пароль. Для максимуму 12+ символів і всі три типи символів.»"<< endl;
        break;
    case 5:
        cout << "Відмінно. Змінювати нічого не потрібно." << endl;
        break;
    default:
        break;
    }

    // Перевіряю чи потрібно виводити попередження щодо надійності пароля, якщо пароль містить лише літери
    if(ContainNumber == NOT_CONTAIN_SYMBOL && hasSpecialChars == NOT_CONTAIN_SYMBOL)
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
}
