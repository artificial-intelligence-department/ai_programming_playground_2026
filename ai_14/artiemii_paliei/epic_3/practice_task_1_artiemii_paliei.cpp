/*
    Аналізатор місячного бюджету
    Прізвище: Палєй
    Група: ШІ-14
*/

#include <iostream>
#include <cmath>
#include <stdio.h>

// Обрахунок витрат (Найбільшої і найменшої)
void calculateMinMax(double Array[], int n, double &min, double &max)
{
    min = Array[0];
    for (int i = 1; i < n; i++)
    {
        if (Array[i] < min)
            min = Array[i];
    }
    max = Array[0];
    for (int i = 1; i < n; i++)
    {
        if (Array[i] > max)
            max = Array[i];
    }
}

// Обрахунок сумарних витрат
double expensesSum(double Array[], int n)
{
    if (n == 0)
        return 0;
    return Array[n - 1] + expensesSum(Array, n - 1);
}


// Обрахунок днів з витратами
int daysWithExpenses(double Array[], int n)
{
    int day_counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (Array[i] == 0)
            continue;
        day_counter++;
    }
    return day_counter;
}

// Функція обрахунку вичерпання бюджету
void wastefulSpending(double Array[], int n, double Budget)
{
    int day_counter = 0;
    int i = 0;
    double sum = 0;
    while (i < n)
    {
        if (Budget < sum)
            break;
        sum += Array[i];
        i++;
        day_counter++;
    }
    if (sum > Budget)
        printf("Бюджет вичерпано на дні %i, накопичено %.2f грн\n", day_counter, sum);
    else
        printf("Залишок: %.2f грн\n", Budget - sum);
}

// Вивід витрат по днях
void option1(double Array[], int n)
{
    std::cout << "День\tВитрати, грн" << std::endl;
    for (int i = 0; i < n; i++)
        printf("%3i\t%.2f\n", i + 1, Array[i]);
}

// Вивід статистики витрат
void option2(double Array[], int n, double Budget)
{
    double min, max, expns, remain;
    int days;

    days = daysWithExpenses(Array, n);
    expns = expensesSum(Array, n);
    remain = Budget - expns;
    calculateMinMax(Array, n, min, max);

    printf("Мінімальні витрати за день:\t%.2f грн\n", min);
    printf("Максимальні витрати за день:\t%.2f грн\n", max);
    printf("Сумарні витрати:\t\t%.2f грн\n", expns);
    if (remain < 0)
        printf("Перевитрата понад бюджет:\t %.2f грн\n", double(abs(remain)));
    if (days > 0)
    {
        printf("Днів з покупками:\t\t%i\n", days);
        printf("Середні витрати за такий день:\t%.2f грн\n", expns / days);
    }
    else
        std::cout << "Ви нічого не витратили :)" << std::endl;
    wastefulSpending(Array, n, Budget);
}

// Вивід днів з перевищенням денного ліміту
void option3(double Array[], int n)
{
    double limit;
    int day_counter = 0;

    std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    
    while (true)
    {
        std::cin >> limit;
        if ((std::cin.fail()) || limit < 0)
        {
            std::cout << "Помилка введення. Введіть повторно валідне значення: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            break;
    }

    limit == 0 ? limit = 1000 : limit = limit;

    printf("Ліміт: %.2f грн\n", limit);

    for (int i = 0; i < n; i++)
    {
        if (Array[i] > limit)
        {
            printf("   день %i: %.2f грн\n", i + 1, Array[i]);
            day_counter++;
        }
    }
    printf("Разом днів з перевищенням: %i\n", day_counter);
}

// Вивід топ витрат
void option4(double Array[], int n)
{
    int last_element = n;
    double array_copy[31] = {0};

    for (int i = 0; i < n; i++)
        array_copy[i] = Array[i];

    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && array_copy[j - 1] > array_copy[j])
        {
            double temp = array_copy[j - 1];
            array_copy[j - 1] = array_copy[j];
            array_copy[j] = temp;
            j--;
        }
    }

    if (n < 3)
    {
        std::cout << "Топ витрат: ";
        for (int i = 0; i < n; i++)
            if (i < n - 1)
                printf("%.2f, ", array_copy[--last_element]);
            else
                printf("%.2f грн", array_copy[--last_element]);
    }
    else
    {
        std::cout << "Топ-3 витрат: ";
        for (int i = 0; i < 3; i++)
            if (i < 2)
                printf("%.2f, ", array_copy[--last_element]);
            else
                printf("%.2f грн", array_copy[--last_element]);
    }
    std::cout << std::endl;
}

int main()
{
    const int DAYS = 31;
    double budget, expenses, min, max, limit;
    int N, enter;
    double spending[DAYS] = {0};

    std::cout << "Бюджет на місяць (грн): ";
    while (true)
    {
        std::cin >> budget;
        if ((std::cin.fail()) || budget < 0)
        {
            std::cout << "Помилка введення. Введіть повторно валідне значення: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            break;
    }

    std::cout << "Кількість днів обліку (Максимум 31): ";

    while (true)
    {
        std::cin >> N;
        if ((std::cin.fail()) || (N <= 0 || N > 31))
        {
            std::cout << "Помилка введення. Введіть повторно валідне значення: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            break;
    }

    std::cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++)
    {
        std::cin >> expenses;
        if ((std::cin.fail()) || expenses < 0)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Ви ввели невалідні значення. Спробуйте ще раз ввести УСІ ваші витрати: ";
            for (int j = 0; j < N; j++)
                spending[j] = 0;
            i = -1;
        }
        else
            spending[i] = expenses;
    }


    do
    {
    menu:
        std::cout << "Пункт\tОперація" << std::endl;
        std::cout << "1\tПоказати витрати по днях" << std::endl;
        std::cout << "2\tСтатистика витрат" << std::endl;
        std::cout << "3\tДні з перевищенням денного ліміту" << std::endl;
        std::cout << "4\tТри найдорожчі дні" << std::endl;
        std::cout << "0\tВийти" << std::endl;
        std::cout << "Ваш вибір: ";

        if (!(std::cin >> enter) || (enter < 0 || enter > 4))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Введіть валідне значення.\n";
            goto menu;
        }

        switch (enter)
        {
        case 0:
            break;
        case 1:
            option1(spending, N);
            break;
        case 2:
            option2(spending, N, budget);
            break;
        case 3:
            option3(spending, N);
            break;
        case 4:
            option4(spending, N);
            break;
        default:
            std::cout << "Щось пішло не так..." << std::endl;
            return 1;
            break;
        }
    } while (enter != 0);

    return 0;
}