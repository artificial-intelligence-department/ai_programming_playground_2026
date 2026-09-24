#include<iostream>

int main()
{
    //Оголошення змінних
    int length, level;
    int types = 0;
    char numbers, capLetters, specSymbols;
    bool minRequirements;

    //Введення даних
    std::cout << "Довжина пароля: ";
    std::cin >> length;
    std::cout << "Чи є цифри (y/n): ";
    std::cin >> numbers;
    std::cout << "Чи є великі літери (y/n): ";
    std::cin >> capLetters;
    std::cout << "Чи є спеціальні символи (y/n): ";
    std::cin >> specSymbols;

    char typesList[3] = {numbers, capLetters, specSymbols};

    //Перевірка обмежень
    if(length < 1 || length > 64)
    {
        std::cout << "Введіть правильну довжину паролю(від 1 до 64)" << std::endl;
        return 1;
    }
    if(numbers != 'y' && numbers != 'n')
    {
        std::cout << "Введіть дійсне значення(y/n)" << std::endl;
        return 1;
    }
    if(capLetters != 'y' && capLetters != 'n')
    {
        std::cout << "Введіть дійсне значення(y/n)" << std::endl;
        return 1;
    }
    if(specSymbols != 'y' && specSymbols != 'n')
    {
        std::cout << "Введіть дійсне значення(y/n)" << std::endl;
        return 1;
    }

    //Кількість типів
    for(int i = 0; i < 3; i ++)
    {
        if(typesList[i] == 'y')
        {
            types++;
        }
    }

    //Мінімальні вимоги
    if(length >= 8 && types >= 2)
    {
        minRequirements = true;
    }
    else
    {
        minRequirements = false;
    }

    //Перевірка надійності
    if(length < 6)
    {
        level = 1;
    }
    else if(length < 8 || types == 0)
    {
        level = 2;
    }
    else if(types == 1)
    {
        level = 3;
    }
    else if(length >= 12 && types == 3)
    {
        level = 5;
    }
    else
    {
        level = 4;
    }

    if(minRequirements)
    {
        std::cout << "Мінімальні вимоги: ПРОЙДЕНО" << std::endl;
    }
    else
    {
        std::cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << std::endl;
    }
    switch(level)
    {
        case 1:
            std::cout << "Рівень надійності: 1 - Дуже слабкий" << std::endl;
            std::cout << "Пароль надто короткий. Мінімум 8 символів." << std::endl;
            break;
        case 2:
            std::cout << "Рівень надійності: 2 - Слабкий" << std::endl;
            std::cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << std::endl;
            break;
        case 3:
            std::cout << "Рівень надійності: 3 - Середній" << std::endl;
            std::cout << "Додайте ще один тип символів або збільште довжину до 12." << std::endl;
            break;
        case 4:
            std::cout << "Рівень надійності: 4 - Надійний" << std::endl;
            std::cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << std::endl;
            break;
        case 5:
            std::cout << "Рівень надійності: 5 - Дуже надійний" << std::endl;
            std::cout << "Відмінно. Змінювати нічого не потрібно." << std::endl;
            break;

        //Не виконує практичної функції, необхідне для виконання вимог до коду
        default:
            std::cout << "Щось пішло не так." << std::endl;
            return 1;
    }

    //Вивід попередження
    if(numbers == 'n')
    {
        std::cout << "Попередження: Пароль тільки з літер підбирається швидше." << std::endl;
    }

    return 0;
}