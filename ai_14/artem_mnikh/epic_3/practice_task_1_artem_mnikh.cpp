/*Аналізатор місячного бюджету
Artem Mnikh
AI_14
*/

#include <iomanip>
#include <iostream>

using namespace std;

// Оголошення прототипів функцій
void ShowMenu();
void SpendsList(double spends[], int n);
void sort(double arr[], int n);
void StatsList(double spends[], int n, double budget);
void TopList(double sorted_arr[], int n);
void CheckLimit(double arr[], int n, double limit = 1000.0);

int main()
{
    // Встановлення фіксованої кількості знаків після коми
    cout << fixed << setprecision(2);
    double budget;
    cout << "Бюджет на місяць (грн): ";
    // Перевірка на коректність введеного бюджету
    if (!(cin >> budget) || budget < 0)
    {
        cout << endl << "Бюджет має бути бльшим за 0";
        return 1;
    }

    int n;
    cout << endl << "Кількість днів обліку: ";
    // Обмеження на максимальну кількість днів у місяці
    if (!(cin >> n) || n > 31)
    {
        cout << endl << "Облік ведеться не довше одного місяця";
        return 1;
    }
    // Створення масиву для зберігання витрат (максимум 31 день)
    double spending[31];
    cout << endl << "Витрати по днях (грн): ";
    for (int i = 0; i < n; ++i)
    {
        if (!(cin >> spending[i]) || spending[i] < 0)
        {
            cout << endl << "Витрати не мають бути від'ємними";
            return 1;
        }
    }
    // Створення копії масиву витрат для сортування
    double copy_of_arr[31];
    for (int i = 0; i < n; ++i) copy_of_arr[i] = spending[i];
    sort(copy_of_arr, n);
    bool IsActive = true;  // Прапорець для контролю головного циклу програми
    int choice;
    // Головний цикл програми
    do
    {
    Menu:  // Мітка для повернення у разі помилки вводу
        ShowMenu();
        // Перевірка, чи введено саме число, а не символ
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введіть числo";
            goto Menu;
        }
        switch (choice)
        {
            case 1:
                SpendsList(spending, n);  // Вивід списку витрат
                break;
            case 2:
                StatsList(spending, n, budget);  // Вивід статистики
                break;
            case 3:
            {
            Lim:
                double user_limit;
                cout << "Введіть денний ліміт (грн, 0 = за замовчуванням): ";
                if (!(cin >> user_limit))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Введіть числo" << endl;
                    goto Lim;
                }
                if (user_limit < 0)
                {
                    cout << "Введіть додатне числo" << endl;
                    goto Lim;
                }
                if (user_limit == 0)
                {
                    CheckLimit(spending, n);  // Використає 1000.0 за замовчуванням
                }
                else
                {
                    CheckLimit(spending, n, user_limit);  // Використає введене користувачем
                }
                break;
            }
            case 4:
                TopList(copy_of_arr, n);  // Вивід найвищих витрат
                break;
            case 0:
                IsActive = false;  // Вихід з циклу
                break;
            default:
                cout << "Введіть число зі списку!";
                break;
        }
    } while (IsActive);
    return 0;
}
// Функція для відображення меню
void ShowMenu()
{
    cout << endl << "---- Menu ----" << endl;
    cout << "1 - Показати витрати по днях" << endl;
    cout << "2 - Статистика витрат" << endl;
    cout << "3 - Дні з перевищенням денного ліміту" << endl;
    cout << "4 - Найдорожчі дні" << endl;
    cout << "0 - Вийти" << endl;
}
// Функція для виведення витрат по кожному дню
void SpendsList(double spends[], int n)
{
    cout << "День  Витрати, грн" << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << i << "  -  " << spends[i - 1] << endl;
    }
}
// Функція сортування масиву методом бульбашки
void sort(double arr[], int n)
{
    double temp;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// Рекурсивна функція для знаходження суми елементів масиву
double sum_of_array(double arr[], int n)
{
    if (n == 1)
    {
        return arr[0];
    }
    return arr[n - 1] + sum_of_array(arr, n - 1);
}
// Функція для пошуку мінімального та максимального значень
void MinMax(double arr[], int n, double& min_val, double& max_val)
{
    min_val = arr[0];
    max_val = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
}
// Функція для формування та виведення повної статистики
void StatsList(double spends[], int n, double budget)
{
    double sum = sum_of_array(spends, n);

    // 1. Мінімум і максимум через параметри-посилання
    double min_spend, max_spend;
    MinMax(spends, n, min_spend, max_spend);
    cout << "Мінімальні витрати за день: " << min_spend << " грн\n";
    cout << "Максимальні витрати за день: " << max_spend << " грн\n";
    cout << "Сумарні витрати: " << sum << " грн\n";

    // 2. Залишок або перевитрата
    if (sum > budget)
    {
        cout << "Перевитрата понад бюджет: " << sum - budget << " грн\n";
    }
    else
    {
        cout << "Залишок бюджету: " << budget - sum << " грн\n";
    }

    // 3. Дні з покупками та середні витрати (з використанням continue)
    int day_counter = 0;
    for (int i = 0; i < n; ++i)
    {
        if (spends[i] == 0) continue;
        ++day_counter;
    }

    cout << "Днів з покупками: " << day_counter << endl;
    if (day_counter > 0)
    {
        cout << "Середні витрати за такий день: " << sum / day_counter << " грн\n";
    }
    else
    {
        cout << "Середні витрати за такий день: 0.00 грн\n";
    }

    // 4. Пошук дня вичерпання бюджету
    int i = 0;
    double target_sum = 0;
    bool isExhausted = false;

    while (i < n)
    {
        target_sum += spends[i];
        if (target_sum > budget)
        {
            cout << "Бюджет вичерпано на дні - " << i + 1 << ", накопичено " << target_sum << " грн.\n";
            isExhausted = true;
            break;
        }
        i++;
    }
    if (!isExhausted)
    {
        cout << "Бюджету вистачило на всі дні.\n";
    }
}

void TopList(double sorted_arr[], int n)
{
    int count = (n < 3) ? n : 3;  // Беремо або n, або 3
    cout << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; ++i)
    {
        cout << sorted_arr[i];
        if (i < count - 1) cout << ", ";
    }
    cout << " грн\n";
}
// Функція для перевірки перевищення денного ліміту
void CheckLimit(double arr[], int n, double limit)
{
    int counter = 0;
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] > limit)
        {
            counter++;
            cout << "День " << i + 1 << ": " << arr[i] << " грн" << endl;
        }
    }
    cout << "Разом днів з перевищенням: " << counter;
}
