/* 
Епік 2. Практичне завдання: Аналізатор надійності пароля
Автор: Кобилянська Софія
Група: ші-11
*/


#include <iostream>

using namespace std;

int main()
{
    int length;                          // Довжина пароля
    char hasDigits;                      // Наявність цифр ('y' або 'n')
    char hasUpper;                       // Наявність великих літер ('y' або 'n')
    char hasSymbols;                     // Наявність спеціальних символів ('y' або 'n')
    int typesCount = 0;                  // Кількість типів символів
    int level = 0;                       // Рівень надійності пароля

    // Введення та перевірка довжини пароля
    cout << "Довжина пароля: " << endl;
    cin >> length;
    if (length < 1 || length > 64)
    {
        cout << "Довжина пароля має бути не менше 1 i не більше 64" << endl;
        return 1;
    }

    // Введення, перевірка та підрахунок цифр
    cout << "Чи є цифри (y/n): " << endl;
    cin >> hasDigits;
    if (hasDigits != 'y' && hasDigits != 'n')
    {
        cout << "Відповідь має бути тільки 'y' або 'n'" << endl;
        return 1;
    }
    if (hasDigits == 'y')
    {
        typesCount++;
    }

    // Введення, перевірка та підрахунок великих літер
    cout << "Чи є великі літери (y/n): " << endl;
    cin >> hasUpper;
    if (hasUpper != 'y' && hasUpper != 'n')
    {
        cout << "Відповідь має бути тільки 'y' або 'n'" << endl;
        return 1;
    }
    if (hasUpper == 'y')
    {
        typesCount++;
    }

    // Введення, перевірка та підрахунок спецсимволів
    cout << "Чи є спеціальні символи (y/n): " << endl;
    cin >> hasSymbols;
    if (hasSymbols != 'y' && hasSymbols != 'n')
    {
        cout << "Відповідь має бути тільки 'y' або 'n'" << endl;
        return 1;
    }
    if (hasSymbols == 'y')
    {
        typesCount++;
    }

    // Перевірка мінімальних вимог
    if (length >= 8 && typesCount >= 2)
    {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else
    {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня надійності
    if (length < 6)
    {
        level = 1;
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
    }
    else if (length < 8 || typesCount == 0)
    {
        level = 2;
        cout << "Рівень надійності: 2 - Слабкий" << endl;
    }
    else if (typesCount == 1)
    {
        level = 3;
        cout << "Рівень надійності: 3 - Середній" << endl;
    }
    else if (length >= 12 && typesCount == 3)
    {
        level = 5;
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
    }
    else
    {
        level = 4;
        cout << "Рівень надійності: 4 - Надійний" << endl;
    }

    // Видача рекомендації
    switch (level)
    {
    case 1:
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
        break;
    case 2:
        cout << "Рекомендація: Збільште довжину до 8+ символів i додайте цифри, великі літери або спеціальні символи." << endl;
        break;
    case 3:
        cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
        break;
    case 4:
        cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів i всі три типи символів." << endl;
        break;
    case 5:
        cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
        break;
    }

    if (hasDigits == 'n' && hasSymbols == 'n')
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}