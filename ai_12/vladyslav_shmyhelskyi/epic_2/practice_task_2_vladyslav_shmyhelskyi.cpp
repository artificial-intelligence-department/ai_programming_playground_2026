#include <iostream>

int main()
{
    using namespace std;
    // вводимо змінні
    int passwordLength;
    char passwordNumbers;
    char passwordLetters;
    char passwordSpecial;

    cout << "Довжина пароля :";
    cin >> passwordLength;
    // Ввід довжини пароля
    if (passwordLength > 64 || passwordLength < 1)
    {
        cout << "Довжина пароля повинна бути від 1 до 64" << endl; // перевірка чи пароль відповідає вимогам
        return 0;
    }

    cout << "Чи є цифри? (y/n):";
    cin >> passwordNumbers;

    if (!(passwordNumbers == 'y' || passwordNumbers == 'n'))
    {
        cout << "Відповідь повинна бути y або n" << endl; // Обмеження на ввіл (тільки так або ні)
        return 0;
    }
    cout << "Чи є великі літери? (y/n):";
    cin >> passwordLetters;
    if (!(passwordLetters == 'y' || passwordLetters == 'n'))
    {
        cout << "Відповідь повинна бути y або n" << endl; // Знову обмеження
        return 0;
    }

    cout << "Чи є спеціальні символи? (y/n):";
    cin >> passwordSpecial;
    if (!(passwordSpecial == 'y' || passwordSpecial == 'n'))
    {
        cout << "Відповідь повинна бути y або n" << endl;
        return 0;
    }

    int symbolsType = 0; // Ввід змінної,яка відповідає за типи символів(Велика літера,спеціальні символи,цифри)
    if (passwordNumbers == 'y')
    {
        symbolsType++;
    }
    if (passwordLetters == 'y')
    {
        symbolsType++;
    }
    if (passwordSpecial == 'y')
    {
        symbolsType++;
    } // З присутністю кожного типу символів,змінна міняє свою величну
    int lvl = 0; // ввід змінної,яка потім буде показувати рівень надійності
    if (passwordLength < 6)
    {
        lvl += 1;
    }
    else if ((passwordLength < 8) || (symbolsType == 0))
    {
        lvl += 2; // Введення умов,за яких lvl буде відповідати рівню надійності
    }
    else if (symbolsType == 1)
    {
        lvl += 3;
    }
    else if ((passwordLength >= 12) && (symbolsType == 3))
    {
        lvl += 5;
    }
    else
    {
        lvl += 4;
    }
    bool minRequirements;                        // введення мінімальних вимог
    if (passwordLength >= 8 && symbolsType >= 2) // Умова,яка перевіряє мінімальні вимоги
    {
        minRequirements = true;
    }
    else
        minRequirements = false;

    if (minRequirements == true)
    {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else
    {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    } // вивід

    switch (lvl)
    { // Вивід рівня надійності та рекомендацій, в залежності від значення lvl(рівня)
    case 1:
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
        break;
    case 2:
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
        break;
    case 3:
        cout << "Рівень надійності: 3 - Середній" << endl;
        cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
        break;
    case 4:
        cout << "Рівень надійності: 4 - Надійний" << endl;
        cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
        break;
    case 5:
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
        break;
    }
    if (symbolsType == 0 || (symbolsType == 1 && passwordLetters == 'y')) // введення умови, за якої буде виводитись попередження
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}