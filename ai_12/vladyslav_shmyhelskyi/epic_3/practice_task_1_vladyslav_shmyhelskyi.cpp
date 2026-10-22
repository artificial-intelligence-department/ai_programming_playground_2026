/*
Аналізатор місячного бюджету
Шмигельський Владислав
ШІ-12
*/
#include <iostream>
#include <iomanip>

using namespace std;

void limit(int N, int spending[], int spentlimit = 1000) // Функція,яка перевіряє перевищення ліміту
{
    int cnt = 0;
    if (spentlimit <= 0)
    {
        spentlimit = 1000;
    }
    cout << "Ліміт: " << fixed << setprecision(2) << (double)spentlimit << " грн" << endl;
    for (int i = 0; i < N; i++)
    {
        if (spending[i] > spentlimit)
        {
            cout << "день " << i + 1 << " - " << fixed << setprecision(2) << (double)spending[i] << " грн" << endl;
            cnt++;
        }
    }
    cout << "Разом днів з перевищенням: " << cnt << endl;
}

void min_max(int &MinSpent, int &MaxSpent, int N, int spending[])
{
    for (int i = 0; i < N; i++)
    {
        if (MinSpent > spending[i])
        {
            MinSpent = spending[i];
        }
    } // Цикли,які визначають мінімальне і максимальне значення витрачених коштів за день
    for (int i = 0; i < N; i++)
    {
        if (MaxSpent < spending[i])
        {
            MaxSpent = spending[i];
        }
    }
}

int summa(int N, int spending[])
{
    if (N <= 0)
    {
        return 0;
    }
    // Рекурсивна функція,яка повертає значення суми всіх елементів масиву
    // Функція розгортає себе з кінця до початоку поки не виконається умова,а потім згортає і додає всі елементи
    return spending[N - 1] + summa(N - 1, spending);
}

void case1(int N, int spending[])
{ // Функція,яка відповідає за вибір опції 1,виводить всі дні і витрати
    cout << left << setw(12) << "Номер дня" << "  Витрати, грн" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << left << setw(12) << i + 1;
        cout << left << setw(12) << fixed << setprecision(2) << (double)spending[i] << endl;
    }
}

void case2(int N, int spending[], int budget)
{ // функція відповідає за вибір опції 2
    int MinSpent = spending[0];
    int MaxSpent = spending[0];
    int totalsumma = summa(N, spending);
    min_max(MinSpent, MaxSpent, N, spending); // всередині функції викликаєтсья ще одна функція,яка визначає min,max
    cout << "Мінімальні витрати за день:   " << fixed << setprecision(2) << (double)MinSpent << " грн" << endl;
    cout << "Максимальні витрати за день:  " << fixed << setprecision(2) << (double)MaxSpent << " грн" << endl;
    cout << "Сумарні витрати:              " << fixed << setprecision(2) << (double)totalsumma << " грн" << endl;
    int difference = budget - totalsumma; // Виклик ще одніє функції,де пораховані всі витрати через рекурсію
    int rest = abs(difference);                   // рахуємо різницю по модулю
    double average;

    if (difference < 0)
    {
        cout << "Перевитрата понад бюджет:      " << fixed << setprecision(2) << (double)rest << " грн" << endl;
    } // умова,за якої в разі перевищення бюджету виводяться перевитрати
    int buydays = 0;
    double total = 0;
    for (int i = 0; i < N; i++)
    {
        if (spending[i] == 0) // к-сть днів,коли було здійснено покупки
        {
            continue;
        }
        buydays++;
        total += spending[i]; //всі потрачені гроші
    }
    cout << "Днів з покупками:              " << buydays << endl;

    
    if (buydays > 0)
    {
        average = total / buydays;
        cout << "Середні витрати за такий день: " << fixed << setprecision(2) << (double)average << " грн" << endl;
    }
    else
    {
        cout << "Витрат не було" << endl;
    }
    int i = 0;
    int total1 = 0;
    int overspent = -1;

    while (i < N)
    {
        total1 += spending[i];

        if (total1 > budget) // зупиняємось на дні,коли було вичерпано бюджет 
        {
            overspent = i + 1;
            break;
        }

        i++;
    }
    if (overspent != -1)
    {
        cout << "Бюджет вичерпано на " << overspent << " дні, накопичено " << fixed << setprecision(2) << (double)total1 << " грн" << endl;
    }
    else
    {
        cout << "Залишок бюджету:               " << fixed << setprecision(2) << (double)difference << " грн" << endl;
    }
}

void case3(int N, int spending[])
{ //функція для 3 опції
    int spentlimit;
spentlimitmark:
    cout << "Денний ліміт(грн, 0 = за замовчуванням): " << endl;
    cin >> spentlimit;
    if (cin.fail()) //валідаця при вводі букв та від'ємних чисел
    {
        cout << "Введіть число" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto spentlimitmark;
    }
    if (spentlimit <= 0)
    {
        limit(N, spending); // викликаємо функцію і не передаємо їй значення ліміту якщо воно 0,щоб було 1000 за замовчуванням
    }
    else
    {
        limit(N, spending, spentlimit); // тут передаємо
    }
}

void case4Sorting(int N, int spending[])
{ //функція для 4 опції
    int top1 = 0, top2 = 0, top3 = 0;
    int copyspending[N]; // копія масиву
    for (int i = 0; i < N; i++)
    {
        copyspending[i] = spending[i]; // передаємо всі значення з оригінального масиву в копію
    }
    for (int i = 0; i < N; i++)
    {
        if (copyspending[i] > top1)
        {
            top3 = top2;
            top2 = top1;
            top1 = copyspending[i]; // визначаємо топ три 3 витрати перебравши всі  в масиві
        }
        else if (copyspending[i] > top2)
        {
            top3 = top2;
            top2 = copyspending[i];
        }
        else if (copyspending[i] > top3)
        {
            top3 = copyspending[i];
        }
    }
    cout << "Топ-3 витрат: " << fixed << setprecision(2) << (double)top1 << ", " << (double)top2 << ", " << (double)top3 << " грн" << endl;
}

void menu(int &option)
{ // функція для виводу меню
    cout << left << setw(12) << "Пункт" << "     Операція" << endl
         << endl;
    cout << left << setw(12) << "1" << "Показати витрати по днях" << endl;
    cout << left << setw(12) << "2" << "Статистика витрат" << endl;
    cout << left << setw(12) << "3" << "Дні з перевищенням денного ліміту" << endl;
    cout << left << setw(12) << "4" << "Три найдорожчі дні" << endl;
    cout << left << setw(12) << "0" << "Вийти" << endl;
    cout << "Вибір: ";
    cin >> option;
    if (cin.fail()) //валідація
    {
        cin.clear();
        cin.ignore(10000, '\n');
        option = 5;
    }
}

int main()
{

    int option;
    int budget = 0;
    int N;
budgetmark:
    cout << "Бюджет на місяць, грн" << endl;
    cin >> budget;
    if (cin.fail() || budget < 0)
    {
        cout << "Введіть додатне число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto budgetmark;
    }
Nmark:
    cout << "Кількість днів обліку" << endl;
    cin >> N;
    if (N < 1 || N > 31 || cin.fail())
    {
        cout << "Помилка.Кількість днів повинна бути від 1 до 31" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto Nmark;
    }
    int spending[N];
    cout << "Витрати по днях, грн" << endl;
    for (int i = 0; i < N; i++)
    {
    spendingmark:
        cin >> spending[i];
        if (spending[i] < 0 || cin.fail())
        {
            cout << "Введіть додатне число" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto spendingmark;
        }
    }
    do
    {   
    menumark:
        menu(option);
        switch (option)
        {

        case 1:
        {
            case1(N, spending); // викликаємо відповідну функцію для кожної опції
            break;
        }
        case 2:
        {
            case2(N, spending, budget);
            break;
        }

        case 3:
        {
            case3(N, spending);
            break;
        }

        case 4:
        {
            case4Sorting(N, spending);
            break;
        }
        case 0:
        {
            cout << "Ви вийшли." << endl;
            break;
        }
        default: // якщо користувач ввів неправильну цифру/символ переводимо в меню
        {
            cout << "Неправильний вибір" << endl; 
            goto menumark;
        }
        }
    } while (option != 0);
}   