/*
    Class Practice Work, Танасієнко Іван, ШІ-13
*/

#include<iostream>
#include<iomanip>

//Функція для розрахування суми
int countSum(int expenses[], int days)
{
    if(days == 0)
    {
        return 0;
    }
    //Використання рекурсії сума усі попередніх днів + теперішній день
    return countSum(expenses, days - 1) + expenses[days - 1];
}

//Виведення витрат за кожен день у вигляді таблиці
void expensesTable(int expenses[], int days)
{
    std::cout << "День     Витрати, грн" << std::endl;
    for(int i = 0; i < days; i++)
    {
        std::cout << std::fixed << std::setprecision(2) 
        << std::setw(3) << i + 1 << std::setw(10) << double(expenses[i]) << std::endl;
    }
    return;
}

/*
    Виведення статистики по витратах. 
    Виведення мінімальних витрат за день, 
    максимальних витрат за день, сумарних витрат,
    витрат понад бюджет, днів з покупками,
    середніх витрат за день, 
    дня коли бюджет вичерпано, і залишку бюджету
*/
void expensesStats(int expenses[], int days, int budget, int& min, int& max)
{
    int overlimit;
    double average;
    double sum = countSum(expenses, days);
    int spendDays = 0;
    int runOutDay = 0;
    double remaining = budget - sum;

    //Розрахунок витрати понад бюджет
    if(remaining < 0)
    {
        overlimit = abs(remaining);
    }
    
    /*
    Розрахунок мінімальних витрат за день,
    максимальних витрат за день і днів з витратами
    */
    for(int i = 0; i < days; i++)
    {
        if(expenses[i] > max)
        {
            max = expenses[i];
        }
        if(expenses[i] < min)
        {
            min = expenses[i];
        }
        if(expenses[i] == 0)
        {
            continue;
        }
        spendDays++;
    }

    // Розрахунок дня коли бюджет вичерпано

    int i = 0;
    int spends = 0;
    while(i < days)
    {
        spends = spends + expenses[i];
        if(spends >= budget)
        {
            runOutDay = i + 1;
            break;
        }
        i++;
    }
    //Розрахунок середніх витрат за день
    if(spendDays == 0)
    {
        average = 0;
    }
    else
    {
        average = sum / spendDays;
    }

    //Виведення результатів
    std::cout << std::fixed << std::setprecision(2) <<
    "Мінімальні витрати за день:" << "       " << double(min) << " грн" << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Максимальні витрати за день:" << "      " << double(max) << " грн" << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Сумарні витрати:" << "                  " << sum << " грн" << std::endl;
    if(remaining < 0)
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Перевитрата понад бюджет:" << "         " << double(overlimit) << " грн" << std::endl;
    }
    std::cout << "Днів з покупками:" << "                 " << spendDays << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Середні витрати за такий день:" << "    " << double(average) << " грн" << std::endl; 
    if(runOutDay > 0)
    {
    std::cout << std::fixed << std::setprecision(2) <<
    "Бюджет вичерпано на дні " << runOutDay << ", накопичено " << double(spends) << " грн." << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Залишок:" << "                          " << double(remaining) << " грн" << std::endl;
    }
       
    return;
}

//Розрахунок днів, коли було вичерпано заданий ліміт
void overlimit(int expenses[], int days, int defLimit = 1000)
{
    int limit;
    int overlimitDays = 0;
    //Ведення і визначення ліміту
    do
    {
    std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    std::cin >> limit;
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        limit = -1;
    }
    else if(limit == 0)
    {
        limit = defLimit;
    }
    }while(limit < 0);
    std::cout << std::fixed << std::setprecision(2) <<
    "Ліміт: " << double(limit) << " грн" << std::endl;
    //Розрахунок днів коли ліміт було вичерпано
    for(int i = 0; i < days; i++)
    {
        if(expenses[i] > limit)
        {
            std::cout << std::fixed << std::setprecision(2) << std::setw(2) <<
            "день " << i + 1 << ": " << double(expenses[i]) << " грн" << std::endl;
            overlimitDays++;
        }
    }
    std::cout << "Разом днів з перевищенням: " << overlimitDays << std::endl;

    return;
}

//Виведення трьох найбільших витрат
void topThree(int expenses[], int days)
{   
    //Копіювання масиву витрат для сортування
    int sorted[days], buffer;
    for(int i = 0; i < days; i++)
    {
        sorted[i] = expenses[i];
    }

    //Сортування копії масиву для витрат
    for(int i = 0; i < days; i++)
    {
        for(int j = 0; j < days - 1; j++)
        {
            if(sorted[j] < sorted[j + 1])
            {
                buffer = sorted[j + 1];
                sorted[j + 1] = sorted[j];
                sorted[j] = buffer;
            }
        }
    }
    //Перевірка кількості днів і виведення відповідного результату
    int top1, top2, top3;
    top1 = sorted[0];
    if(days >= 2)
    {
         top2 = sorted[1];
    }
    if(days >= 3)
    {
        top3 = sorted[2];
    }
    if(days == 1)
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Топ-1 витрат: " << double(top1) << " грн" << std::endl;
    }
    else if(days == 2)
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Топ-2 витрат: " << double(top1) << ", " 
        << double(top2) << " грн" << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Топ-3 витрат: " << double(top1) << ", " 
        << double(top2) << ", " 
        << double(top3) << " грн" << std::endl;
    }

    return;

}
int main()
{
    /*
        Введення бюджету, кількості днів та поденних витрат
        Та перевірка коректності введенних даних
    */
    int budget, days;

    std::cout << "Бюджет на місяць (грн): ";
    std::cin >> budget;
    if(budget <= 0 || std::cin.fail())
    {
        std::cout << "Бюджет має бути додатним." << std::endl;
        return 1;
    }
    std::cout << "Кількість днів обліку: ";
    std::cin >> days;
    if(days > 31 || std::cin.fail())
    {
        std::cout << "Облік ведеться не довше одного місяця." << std::endl;
        return 1;
    }
    else if(days <= 0 || std::cin.fail())
    {
        std::cout << "Кількість днів має бути більшою за 0." << std::endl;
        return 1; 
    }

    int expenses[days];

    std::cout << "Витрати по днях (грн): ";

    for(int i = 0; i < days; i++)
    {
        std::cin >> expenses[i];
        if(expenses[i] < 0 || std::cin.fail())
        {
            std::cout << "Витрати мають бути додатними." << std::endl;
            return 1;
        }
    }
    int choice;
    int min = expenses[0];
    int max = 0;
    //Виведення меню та дії з ним
    do
    {
        menu:
            std::cout << std::endl << "Пункт    Операція" << std::endl;
            std::cout << "1        Показати витрати по днях" << std::endl;
            std::cout << "2        Статистика витрат" << std::endl;
            std::cout << "3        Дні з перевищенням денного ліміту" << std::endl;
            std::cout << "4        Три найдорожчі дні" << std::endl;
            std::cout << "0        Вийти" << std::endl;
            std::cout << "Пункт: ";
            std::cin >> choice;
            std::cout << std::endl;
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                goto menu;
            }
            switch (choice)
            {
                case 1:
                    expensesTable(expenses, days);
                    break;
                case 2:
                    expensesStats(expenses, days, budget, min, max);
                    break;
                case 3:
                    overlimit(expenses, days);
                    break;
                case 4:
                    topThree(expenses, days);
                    break;
                case 0:
                    std::cout << "Вихід..." << std::endl;
                    break;
                default:
                    goto menu;
                    break;
            }
    }while(choice != 0);

    return 0;
}