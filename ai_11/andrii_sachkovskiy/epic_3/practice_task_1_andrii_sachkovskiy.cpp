/*
 * Задача: Аналізатор місячного бюджету
 * Автор: Сачковський Андрій
 * Група: AI-11
 */
#include <iostream>
#include <cmath>      
#include <iomanip>   
using namespace std;

// ПУНКТ 1: таблиця витрат 
void tabl(double arr[], int n) {
    cout << "День     Витрати, грн\n";
    for (int i = 0; i < n; i++) {                           
        cout << setw(4) << i + 1 << setw(16) << arr[i] << endl;   //просто вивід по порядку днів і кожної суми яка потрачена в цей день 
    }
}

// ПУНКТ 3: дні з перевищенням ліміту 
void limit(double arr[], int n, double lim = 1000) {
    int d = 0;                                               // шукаємо дні з перевищенням
    cout << "Ліміт: " << lim << " грн\n";
    for (int i = 0; i < n; i++) {
        if (arr[i] > lim) {
            cout << "  день " << i + 1 << ": " << arr[i] << " грн\n";
            d++;
        }
    }
    cout << "Разом днів з перевищенням: " << d << endl;
}

// ПУНКТ 4: топ-3 
void top(double arr[], int n) {
    double copy[31];
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];                                    // копія масиву для сортування
    }
    // сортування "бульбашкою" за спаданням 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 ; j++) {
            if (copy[j] < copy[j + 1]) {                     
                double t = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = t;
            }
        }
    }

cout << "Топ-3 витрат: "; // вивід топ три або мнеше якщо днів мнеше
switch (n) {
    case 1:                                  
        cout << copy[0];
        break;
    case 2:                                  
        cout << copy[0] << ", " << copy[1];
        break;
    default:                                
        cout << copy[0] << ", " << copy[1] << ", " << copy[2];
        break;
}
cout << " грн\n";}

// ПУНКТ 2: статистика

void findMinMax(double vitrat[], int day, double &mn, double &mx) {
    mn = vitrat[0];                                        //шукаємо найбільше і найменше значення
    mx = vitrat[0];
    for (int i = 1; i < day; i++) {
        if (vitrat[i] < mn) mn = vitrat[i];
        if (vitrat[i] > mx) mx = vitrat[i];
    }
}

// рекурсивна сума 
double sumaRec(double vitrat[], int day) {
    if (day == 0) return 0;                                
    return vitrat[day - 1] + sumaRec(vitrat, day - 1);
}
  //вивід мін і макс сума залишок 
void obrahunki(double vitrat[], int day, double budget) {
    double minV, maxV;
    findMinMax(vitrat, day, minV, maxV);                  
    cout << "Мінімальні витрати за день:  " << setw(10) << minV << " грн\n";
    cout << "Максимальні витрати за день: " << setw(10) << maxV << " грн\n";

    double suma = sumaRec(vitrat, day);
    cout << "Сумарні витрати:             " << setw(10) << suma << " грн\n";

    double zalyshok = budget - suma;
    if (zalyshok < 0)
        cout << "Перевитрата понад бюджет:    " << setw(10) << fabs(zalyshok) << " грн\n"; 
    else
        cout << "Залишок бюджету:             " << setw(10) << zalyshok << " грн\n";

    // середні витрати тільки за дні з покупками
    double sumBuy = 0;
    int pokupki = 0;
    for (int i = 0; i < day; i++) {
        if (vitrat[i] == 0) continue;                 
        sumBuy += vitrat[i];
        pokupki++;
    }
    cout << "Днів з покупками:            " << setw(10) << pokupki << endl;
    if (pokupki > 0)                                         // захист від ділення на нуль
        cout << "Середні витрати за такий день: " << sumBuy / pokupki << " грн\n";
    else
        cout << "Покупок не було\n";

double nakopil = 0;                  
int i = 0;                 //підрахунок на скільки часу вистачило бюджету           
while (i < day) {
    nakopil += vitrat[i];           
    if (nakopil > budget) break;     
    i++;
}
if (i < day)
    cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << nakopil << " грн.\n";
else
    cout << "Бюджету вистачило, залишок: " << budget - nakopil << " грн\n";
}
// ГОЛОВНА ФУНКЦІЯ
int main() {
    double budget;
    int day, vibir;
    double vitrat[31];
    double lim;
//користовач водить різіні дані для майбутніх обрахунків
    cout << fixed << setprecision(2);                       

   
    cout << "Введіть бюджет на місяць, грн: ";
    cin >> budget;
    if (cin.fail() || budget <= 0) {                         
        cout << "Помилка: бюджет має бути числом більше 0\n";
        return 0;                                          
    }

    cout << "Введіть кількість днів обліку: ";
    cin >> day;
    if (cin.fail() || day < 1 || day > 31) {
        cout << "Помилка: кількість днів - ціле число від 1 до 31\n";
        return 0;
    }

    cout << "Введіть витрати по днях, грн (через пробіл):\n";
    for (int i = 0; i < day; i++) {
        cin >> vitrat[i];
        if (cin.fail() || vitrat[i] < 0) {                   
            cout << "Помилка в дні " << i + 1 << ": витрати - число 0 або більше\n";
            return 0;
        }
    }
//меню користовача
    do {
    menu:                                                  
        cout << "\nМеню:\n";
        cout << "1. Показати витрати по днях\n";
        cout << "2. Статистика витрат\n";
        cout << "3. Дні з перевищенням денного ліміту\n";
        cout << "4. Три найдорожчі дні\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> vibir;
        if (cin.fail() || vibir < 0 || vibir > 4) {          
            cout << "Неправильний пункт!\n";
            cin.clear();                                   
            cin.ignore(10000, '\n');                         
            goto menu;                                       
        }

        if (vibir == 1) tabl(vitrat, day);
        else if (vibir == 2) obrahunki(vitrat, day, budget);
        else if (vibir == 3) {
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> lim;
            if (cin.fail() || lim < 0) {
                cout << "Помилка: ліміт - число 0 або більше\n";
                return 0;
            }
            if (lim == 0) limit(vitrat, day);             
            else limit(vitrat, day, lim);                    
        }
        else if (vibir == 4) top(vitrat, day);
    } while (vibir != 0);

    cout << "До побачення!\n";
    return 0;
}