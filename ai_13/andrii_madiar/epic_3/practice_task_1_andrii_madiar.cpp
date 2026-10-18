/*
Аналізатор місячного бюджету
Автор: Мадяр Андрій
Група: ШІ-13
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
// рекурсивна функція суми сумує елементи з масиву від індекса N-1(останній елемент) до 0(перший елемент)
double totalSpent(double spending[], int N);
// функція для знаходження адреси елемента дня з максимальними і мінімальними витратами
void findMinMax(double spending[], int N, double &minVal, double &maxVal);
// функція для знаходження перевитрат
void overSpendings(double spending[], int N, int budget, double sum);
// функція на перевірку ексіда ліміту витрат
void checkLimit(double spending[], int N, double limit);
// функція на визначення днів з максимальними витратами
void top3(double spending[], int N);
int main(){
    int budget = 0;            // ввід бюджету
    int N = 0;                 // ввід кількості днів розрахунку
    double spending[31] = {0}; // ввід самих витрат
    int choice;
    cout << "Бюджет на місяць (грн): ";
    while (!(cin >> budget) || budget <= 0){ // перевірка на коректний ввід
        cout << "Помилка! введіть додатнє число: ";
        cin.clear();// забирає прапорець помилки
        cin.ignore(100, '\n'); // забирає від зчитування некоректні дані
    }
    cout << "Кількість днів обліку: ";
    while (!(cin >> N) || N <= 0 || N > 31){
        cout << "Помилка! введіть додатнє число між 1 і 31: "; // перевірка на коректний ввід
        cin.clear();
        cin.ignore(100, '\n');
    }
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++){ // ввід елементів множини
        while (!(cin >> spending[i]) || spending[i] < 0){ // перевірка на коректний ввід
            cout << "Помилка! введіть невід'ємне число: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
menu_start: // точка для повернення завдяки goto
    do{ // do while щоб постійно виводити меню доки користувач не захоче вийти
        cout << "\nМеню:\n"
             << "Показати витрати по днях(1)\n"
             << "Статистика витрат(2)\n"
             << "Дні з перевищенням денного ліміту(3)\n"
             << "Три найдорожчі дні(4)\n"
             << "Вихід(0)\n"; // вивід меню

        if (!(cin >> choice)){ // перевірка на коректний ввід
            cout << "Помилка! виберіть існуючий варіант\n";
            cin.clear();
            cin.ignore(100, '\n');
            goto menu_start; // вимога використання goto(некоректний ввід)
        }
        switch (choice){
        case 1:{
            cout << "День     Витрати, грн\n"; // вивід списку витрат за допомогою циклу
            for (int i = 0; i < N; i++){
                cout << setw(4) << (i + 1) << fixed << setprecision(2) << setw(15) << spending[i] << endl;
            }
            break;
        }
        case 2:{
            double minVal, maxVal;
            findMinMax(spending, N, minVal, maxVal);
            double sum = totalSpent(spending, N);
            cout << fixed << setprecision(2) << "Мінімальні витрати за день: " << setw(19) << minVal << " грн\n"
                 << "Максимальні витрати за день: " << setw(18) << maxVal << " грн\n"
                 << "Сумарні витрати: " << setw(30) << sum << " грн\n";
            overSpendings(spending, N, budget, sum);
            break;
        }
        case 3:{
            double customLimit; // додаткова змінна щоб використати функцію
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> customLimit;
            if (customLimit <= 0){
                checkLimit(spending, N, 1000.0); //виклик зі значенням за замовчуванням
            }else{
                checkLimit(spending, N, customLimit); //виклик з введеним лімітом
            }
            break;
        }
        case 4:{
            top3(spending, N); // всі дії вже у функції, а потрібні змінні вже існують
            break;
        }
        case 0:{ // просто перехід до перевірки для виходу
            break;
        }
        default:{// дії якщо користувач ввів щось що не розраховано програмою
            cout << "Помилка! зробіть вибір із запропонованих варіантів\n";
            goto menu_start;
        }
        }
    } while (choice != 0); // умова продовження головного циклу
    return 0;
}
// рекурсивна функція суми сумує елементи з масиву від індекса N-1(останній елемент) до 0(перший елемент)
double totalSpent(double spending[], int N){
    if (N <= 0) return 0; // щоб не лізло в ніеснуючі значення
    return spending[N - 1] + totalSpent(spending, N - 1);
}
// функція для знаходження адреси елемента дня з максимальними і мінімальними витратами
void findMinMax(double spending[], int N, double &minVal, double &maxVal){
    minVal = spending[0];
    maxVal = spending[0]; // присвоєння
    for (int i = 1; i < N; i++){ // пошук циклом
        if (spending[i] < minVal)minVal = spending[i];
        if (spending[i] > maxVal)maxVal = spending[i];
    }
}
// функція для знаходження перевитрат
void overSpendings(double spending[], int N, int budget, double sum){
    if (sum > budget){                                           // перевірка на перевитрату
        double overBudget = fabs(budget - sum); // розрахунок перевитрати
        cout << "Перевитрата понад бюджет: " << setw(21) << overBudget << " грн\n";
    }
    double sumSpent = 0.0;
    int countSpent = 0;
    for (int i = 0; i < N; i++){ // цикл для розрахунку днів у які були витрати
        if (spending[i] == 0)continue; // пропуск завдяки continue якщо витрат не було
        sumSpent += spending[i];
        countSpent++;
    }
    cout << "Днів з покупками:" << setw(30) << countSpent << endl;
    if (countSpent != 0){ // перевірка чи таких днів не 0 щоб не було ділення на 0
        cout << "Середні витрати за такий день:" << setw(17) << (sumSpent / countSpent) << " грн\n";
    }else
        cout << "Середні витрати за такий день:" << setw(17) << "0.0 грн\n"; // ну витрат не було тому середні витрати 0
    int temp = 0;
    double totalOut = 0.0;
    int runoutDay;
    while (temp < N){ // накопичення витрат за допомогою циклу while
        totalOut += spending[temp];
        if (totalOut > budget){// умова яка зупинить цикл якщо буде вичерпано бюджет
            runoutDay = (temp + 1); // день коли вичерпався бюджет
            break;
        }
        temp++;
    }if (temp >= 0)
        cout << "Бюджет вичерпано на дні " << runoutDay << ", накопичено " << setprecision(2) << totalOut << " грн\n";
}
// функція на перевірку ексіда ліміту витрат
void checkLimit(double spending[], int N, double limit = 1000.0){
    cout << "\nЛіміт: " << fixed << setprecision(2) << limit << " грн\n";
    int count = 0;
    for (int i = 0; i < N; i++){ // пошук відповідних днів
        if (spending[i] > limit){
            cout << "  день " << (i + 1) << ": " << spending[i] << " грн\n"; // вивід дня який перелімічено
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl; // вивід загальної кількості перелімічених
}
// функція на визначення днів з максимальними витратами
void top3(double spending[], int N){
    double copy[31] = {0}; // максимум обліку = місяць тому виділяю пам'ять на 31 елемент
    for (int i = 0; i < N; i++){
        copy[i] = spending[i];
    }for (int i = 0; i < N - 1; i++)
    { // bubble sort за допомогою вкладеного циклу
        for (int j = 0; j < N - i - 1; j++){
            if (copy[j] < copy[j + 1]){// умова перестановки
                double tempVal = copy[j]; // створюю тимчасове значення, щоб не втратити старе значення copy[j]
                copy[j] = copy[j + 1];
                copy[j + 1] = tempVal;
            }
        }
    }
    cout << "Топ 3 витрат: " << copy[0] << ", " << copy[1] << ", " << copy[2] << " грн" << endl;
}