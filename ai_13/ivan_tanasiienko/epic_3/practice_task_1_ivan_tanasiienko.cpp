/*
    Class Practice Work, Танасієнко Іван, ШІ-13
*/

#include<iostream>
#include<iomanip>

int countSum(int expenses[], int days)
{
    if(days == 0)
    {
        return 0;
    }
    return countSum(expenses, days - 1) + expenses[days - 1];
}

void expensesTable(int expenses[], int days)
{
    std::cout << "День     Витрати, грн" << std::endl;
    for(int i = 0; i < days; i++)
    {
        std::cout << std::setw(3) << i + 1 << std::setw(10) << expenses[i] << std::endl;
    }
    return;
}

void expensesStats(int expenses[], int days, int budget, int& min, int& max)
{
    int collected, overlimit;
    double sum = countSum(expenses, days);
    int spendDays = 0;
    int runOutDay = 0;
    double remaining = budget - sum;
    if(remaining < 0)
    {
        overlimit = abs(remaining);
    }
    
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
    int i = 0;
    int spends = 0;
    while(i < days)
    {
        spends = spends + expenses[i];
        if(spends > budget)
        {
            runOutDay = i + 1;
            break;
        }
        i++;
    }
    double average = sum / spendDays;

    std::cout << std::fixed << std::setprecision(2) <<
    "Мінімальні витрати за день:" << std::setw(7) << min << " грн" << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Максимальні витрати за день:" << std::setw(6) << max << " грн" << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Сумарні витрати:" << std::setw(19) << sum << " грн" << std::endl;
    if(remaining < 0)
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Перевитрата понад бюджет:" << std::setw(9) << overlimit << " грн" << std::endl;
    }
    std::cout << "Днів з покупками:" << std::setw(20) << spendDays << std::endl;
    std::cout << std::fixed << std::setprecision(2) <<
    "Середні витрати за такий день:" << std::setw(4) << average << " грн" << std::endl; 
    if(runOutDay > 0)
    {
    std::cout << std::fixed << std::setprecision(2) <<
    "Бюджет вичерпано на дні " << runOutDay << ", накопичено " << spends << " грн." << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(2) <<
        "Залишок:" << std::setw(26) << remaining << " грн" << std::endl;
    }
       
    return;
}

void overlimit(int expenses[], int days)
{
    int limit;
    int overlimitDays = 0;
    do
    {
    std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    std::cin >> limit;
    if(limit == 0)
    {
        limit = 1000;
    }
    }while(limit < 0);
    std::cout << std::fixed << std::setprecision(2) <<
    "Ліміт: " << limit << " грн" << std::endl;
    for(int i = 0; i < days; i++)
    {
        if(expenses[i] > limit)
        {
            std::cout << std::fixed << std::setw(2) <<
            "день " << i + 1 << ": " << expenses[i] << " грн" << std::endl;
            overlimitDays++;
        }
    }
    std::cout << "Разом днів з перевищенням: " << overlimitDays << std::endl;

    return;
}
void topThree(int expenses[], int days)
{
    int sorted[days], buffer;
    for(int i = 0; i < days; i++)
    {
        sorted[i] = expenses[i];
    }

    for(int i = 0; i < days; i++)
    {
        for(int j = 0; j < days; j++)
        {
            if(sorted[j] < sorted[j + 1])
            {
                buffer = sorted[j + 1];
                sorted[j + 1] = sorted[j];
                sorted[j] = buffer;
            }
        }
    }
    int top1 = sorted[0];
    int top2 = sorted[1];
    int top3 = sorted[2];
    std::cout << std::fixed << std::setprecision(2) <<
    "Топ-3 витрат: " << top1 << ", " 
    << top2 << ", " 
    << top3 << " грн" << std::endl;

    return;

}
int main()
{
    int budget, days;

    std::cout << "Бюджет на місяць (грн): ";
    std::cin >> budget;
    if(budget <= 0)
    {
        std::cout << "Бюджет має бути додатним." << std::endl;
        return 1;
    }
    std::cout << "Кількість днів обліку: ";
    std::cin >> days;
    if(days > 31)
    {
        std::cout << "Облік ведеться не довше одного місяця." << std::endl;
        return 1;
    }

    int expenses[days];

    std::cout << "Витрати по днях (грн): ";

    for(int i = 0; i < days; i++)
    {
        std::cin >> expenses[i];
        if(expenses[i] < 0)
        {
            std::cout << "Витрати мають бути додатними." << std::endl;
            return 1;
        }
    }
    int choice;
    int min = expenses[0];
    int max = 0;
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
                    std::cout << "Вихід..." <<std::endl;
                    break;
                default:
                    goto menu;
                    break;
            }
    }while(choice != 0);

    return 0;
}