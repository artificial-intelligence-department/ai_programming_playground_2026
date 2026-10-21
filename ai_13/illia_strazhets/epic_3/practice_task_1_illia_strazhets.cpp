/*
Назва задачі: Аналізатор місячного бюджету
Автор: Strazhets Illia
Група: AI-13
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Облік за умовою охоплює не більше місяця; 31 — максимальна кількість днів.
const int MAX_DAYS = 31;
// Власне правило валідації: обмежуємо величину кожної грошової суми.
const double MAX_MONEY = 10000000000;
double budget = 0;
double spending[MAX_DAYS] = {0};
int N = 0;

// Спільна перевірка числового вводу для бюджету, витрат, ліміту й меню.
// Допустимі межі різні для кожного поля, тому перевіряються в місці виклику.
bool readNumber(double &value)
{
    if (cin >> value)
        return true;

    if (cin.eof())
        return false; // За відсутності нових даних повторний запит не має сенсу.

    // Після нечислового вводу наступна спроба не повинна повторно читати ту саму помилку.
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
}

// Пункт 1 вимагає таблицю всіх днів, включно з днями без покупок.
// for обходить N витрат; i + 1 забезпечує нумерацію днів із 1, як в умові.
void showSpendings()
{
    cout << "День     Витрати, грн\n";
    for (int i = 0; i < N; i++)
        cout << setw(4) << i + 1 << "     " << spending[i] << '\n';
}

// За умовою мінімум і максимум має повертати одна функція через посилання.
// Нульові витрати тут враховуються: день без покупок може бути найдешевшим.
void min_maxSpendings(double &min_x, double &max_x)
{
    // Початок із реальної витрати не дає хибного мінімуму 0, коли всі витрати додатні.
    min_x = spending[0];
    max_x = spending[0];
    for (int i = 1; i < N; i++)
    {
        if (spending[i] < min_x)
            min_x = spending[i];
        if (spending[i] > max_x)
            max_x = spending[i];
    }
}

// Загальні витрати за умовою потрібно обчислити рекурсивно, без циклу.
// Кожен виклик додає один день; індекс наближається до N, тому рекурсія завершується.
double sumSpendings(int index = 0)
{
    if (index == N)
        return 0; // Зупинка перед зверненням за межі введених витрат.
    return round((spending[index] + sumSpendings(index + 1)) * 100) / 100;
}

// За умовою середнє рахується тільки за дні з покупками, тому знаменник — days, не N.
// continue виключає нульові витрати і з суми, і з кількості врахованих днів.
// Кількість цих днів передається через посилання для виводу у статистиці.
double avgSpendings(int &days)
{
    double total = 0;
    days = 0;
    for (int i = 0; i < N; i++)
    {
        if (spending[i] == 0)
            continue;
        total += spending[i];
        days++;
    }
    if (days == 0)
        return 0; // Якщо покупок не було взагалі, приймаємо середнє рівним нулю.
    return total / days;
}

// Потрібен перший день, коли накопичені витрати перевищили бюджет.
// while і break виконують цю вимогу без перегляду решти днів.
// Точна рівність бюджету ще не є перевищенням, тому порівняння строге.
void daysEnd()
{
    int i = 0;
    double total = 0;
    while (i < N)
    {
        // Порівнюємо грошові суми з точністю до копійки, щоб дрібна похибка
        // додавання double не перетворила рівність бюджету на перевищення.
        total = round((total + spending[i]) * 100) / 100;
        if (total > budget)
            break;
        i++;
    }
    if (i < N)
        cout << "Бюджет перевищено на день " << i + 1
             << ", накопичено " << total << " грн.\n";
    else
        cout << "Бюджету вистачило. Залишок: "
             << round((budget - total) * 100) / 100 << " грн.\n";
}

// Пункт 2 має окрему функцію, яка формує весь набір показників з умови.
// Статистика використовує початковий порядок днів для пошуку першого перевищення.
void statisticSpendings()
{
    double min_x, max_x;
    int days = 0;
    min_maxSpendings(min_x, max_x);
    double total = sumSpendings();
    double average = avgSpendings(days);
    double extra = 0;
    if (total > budget)
        extra = fabs(budget - total); // За умовою розмір перевитрати — модуль від’ємного залишку через математичну функцію.

    cout << "Мінімальні витрати за день: " << min_x << " грн\n";
    cout << "Максимальні витрати за день: " << max_x << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";
    cout << "Перевитрата понад бюджет: " << extra << " грн\n";
    cout << "Днів з покупками: " << days << '\n';
    cout << "Середні витрати за такий день: " << average << " грн\n";
    daysEnd();
}

// Умова вимагає саме параметр за замовчуванням: 1000 грн.
// Витрати, рівні ліміту, не є перевищенням і не входять у кількість таких днів.
void checkLimit(double dailyLimit = 1000)
{
    int days = 0;
    cout << "Ліміт: " << dailyLimit << " грн\n";
    for (int i = 0; i < N; i++)
    {
        if (spending[i] > dailyLimit)
        {
            cout << "День " << i + 1 << ": " << spending[i] << " грн\n";
            days++;
        }
    }
    cout << "Разом днів з перевищенням: " << days << '\n';
}

// Пункт 3 має окрему функцію; від’ємний ліміт відхиляється.
// Нуль за умовою означає вибір стандартного ліміту, а не заборону всіх витрат.
void dailyLimitSpendings()
{
    double limit = 0;
    while (true)
    {
        cout << "Денний ліміт (грн, 0 = 1000 грн): ";
        if (readNumber(limit) && limit >= 0 && limit <= MAX_MONEY)
            break;
        if (cin.eof())
            return; // Без нових даних неможливо виправити ліміт, тому припиняємо повторні запити.
        cout << "Помилка: введіть число від 0 до " << MAX_MONEY << ".\n";
    }
    limit = round(limit * 100) / 100;
    if (limit == 0)
        checkLimit(); // Пропущений аргумент застосовує задані у checkLimit 1000 грн.
    else
        checkLimit(limit);
}

// Пункт 4 вимагає сортувати копію, залишаючи початковий масив незмінним.
// Інакше повторний показ таблиці й пошук дня перевищення втратять правильну хронологію.
void topThreeSpendings()
{
    double copy[MAX_DAYS];
    int dayNumbers[MAX_DAYS];
    for (int i = 0; i < N; i++)
    {
        copy[i] = spending[i];
        dayNumbers[i] = i + 1;
    }

    // Спадання ставить найбільші витрати на початок, звідки зручно взяти топ-3.
    // Після кожного проходу останній елемент невпорядкованої частини вже на місці.
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (copy[j] < copy[j + 1])
            {
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
                // Зберігаємо відповідність суми початковому дню, щоб правильно підписати топ-3.
                int tempDay = dayNumbers[j];
                dayNumbers[j] = dayNumbers[j + 1];
                dayNumbers[j + 1] = tempDay;
            }
        }
    }
    // Якщо днів менше трьох, за умовою виводимо лише наявні.
    cout << "Три найдорожчі дні:\n";
    for (int i = 0; i < N && i < 3; i++)
        cout << "День " << dayNumbers[i] << ": " << copy[i] << " грн\n";
}

int main()
{
    // Формат грошових сум відповідає формату гривні з двома знаками після крапки.
    cout << fixed << setprecision(2);
    cout << "Вводьте числа через пробіли або з нового рядка. Дробова частина — через крапку.\n";

    // Правила перевірки: бюджет від 0.01 грн до MAX_MONEY,
    // грошові суми округлюємо до копійок; помилка початкових даних завершує програму.
    cout << "Бюджет на місяць (грн): ";
    if (!readNumber(budget) || !(budget >= 0.01 && budget <= MAX_MONEY))
    {
        cout << "Помилка: бюджет має бути від 0.01 до " << MAX_MONEY << " грн.\n";
        return 1;
    }
    budget = round(budget * 100) / 100;

    // Кількість днів за умовою ціла й не перевищує тривалості місяця.
    // Читання у double дозволяє відхилити 2.5, а не прийняти його як 2.
    double input = 0;
    cout << "Кількість днів обліку: ";
    if (!readNumber(input) || !(input >= 1 && input <= MAX_DAYS) || input != floor(input))
    {
        cout << "Помилка: введіть ціле число від 1 до 31.\n";
        return 1;
    }
    N = int(input); // Перетворення безпечне після перевірки цілого значення від 1 до 31.

    // За умовою бюджет і всі N витрат мають бути отримані до показу меню.
    // Нуль дозволений як день без покупок; від’ємні витрати відхиляються.
    cout << "Витрати по днях (грн), " << N << " чисел поспіль: ";
    for (int i = 0; i < N; i++)
    {
        if (!readNumber(spending[i]) || !(spending[i] >= 0 && spending[i] <= MAX_MONEY))
        {
            cout << "Помилка: витрати мають бути від 0 до " << MAX_MONEY << " грн.\n";
            return 1;
        }
        spending[i] = round(spending[i] * 100) / 100;
    }

    // do while показує меню хоча б один раз і повторює його після операцій.
    // Вибір 0 завершує роботу; кожна дія винесена в окрему функцію за умовою.
    int choice = 0;
    do
    {
    menu:
        cout << "\n---------------- Аналізатор місячного бюджету ----------------\n";
        cout << "1  Показати витрати по днях\n";
        cout << "2  Статистика витрат\n";
        cout << "3  Дні з перевищенням денного ліміту\n";
        cout << "4  Три найдорожчі дні\n";
        cout << "0  Вийти\n> ";

        if (!readNumber(input) || !(input >= 0 && input <= 4) || input != floor(input))
        {
            if (cin.eof())
                return 0;
            cout << "Помилка: введіть ціле число від 0 до 4.\n";
            goto menu; // Вимога задачі: неправильний вибір повертає до головного меню через goto.
        }
        choice = int(input);
        switch (choice)
        {
        case 1:
            showSpendings();
            break;
        case 2:
            statisticSpendings();
            break;
        case 3:
            dailyLimitSpendings();
            break;
        case 4:
            topThreeSpendings();
            break;
        case 0:
            cout << "Роботу програми завершено.\n";
            break;
        }
    } while (choice != 0);
    return 0;
}
