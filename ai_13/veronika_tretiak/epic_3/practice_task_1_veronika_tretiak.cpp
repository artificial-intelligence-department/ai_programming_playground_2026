/*Автор: Третяк Вероніка
  Задача: Аналізатор бюджету
  Група: ШІ - 13
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

     void MinMax (double spending[], int N, double &minSpending, double &maxSpending)//Функція знаходит мінімальніі максимальні витрати за всі дні
{
    minSpending = spending[0];
    maxSpending = spending[0];

    for (int i = 0; i < N; i++){
        if (spending[i] < minSpending){
            minSpending = spending[i];
        }
        if (spending[i] > maxSpending){
            maxSpending = spending[i];
        }
    }

}


double Sumtotal(double spending[], int N){//Рекурсивна функція обчислює загальу суму витрат за N днів
    if (N == 0) {
        return 0;
    }
    return spending[N - 1] + Sumtotal(spending, N - 1);
}

void Overlimit(double spending[], int N, double limit = 1000){//Функція знаходить дні, у які витрати перевищили встановлений ліміт
    int count = 0;

    cout << "Ліміт: " << fixed << setprecision(2) << limit << " грн" << endl;

    for (int i = 0; i < N; i++){
        if (spending[i] > limit){
            cout << " День " << i + 1 << " :" << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

int main() {
    //Оголошуємо змінні для бюджету, кількості днів і виборі меню, а масив зберігає щоденні витрати
    int  budget, N, menu;
    double spending[100];
    budget_input:
    cout << "Бюджет на місяць (грн): " << endl;
    cin >> budget;
    if (cin.fail()) {//Перевіряємо коректність введення та забороняємо від'ємний або нульовий бюджет.
        cout << "Помилка: Введіть число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto budget_input;
    }
    if (budget < 0 || budget == 0) {
        cout << "Помилка:Бюджет не може бути від'ємним або дорівнювати нулю." << endl;
        goto budget_input;
    }
    days_input:
    cout << "Кількість днів обліку:" << endl;
    cin >> N;
    if (cin.fail()) {
         cout << "Помилка: Введіть число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto days_input;
    }
    if ( N < 0 || N > 100) {//Перевіряємо, чи кількість днів перебуває в допустимих межах від 1 до 100.
        cout << "Помилка: Введення не може бути від'ємним або дорівнювати нулю." << endl;
        goto days_input;}
        money_input:
    cout << "Витрати по днях (грн): " << endl;
    for (int i = 0; i < N; i++) {
        cout << "День " << i + 1 << ": ";
        cin >> spending[i];
            if (cin.fail()){
            cout << "Помилка: введіть число" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto money_input;
           
        }
         if (spending[i] < 0){
            cout << "Помилка: Введення не може бути від'ємним" << endl;
            goto money_input;
        }
    }
   do { menu_1://Повторюємо показ меню, поки користувач не вибере пункт 0 для виходу.
        cout << "МЕНЮ" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Cтатистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір:" << endl;
        cin >> menu;
            if (cin.fail()){// Перевіряємо, чи правильно введено номер пункту меню.
            cout << "Помилка: введіть число" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menu_1;
    }
            if (menu < 0){
            cout << "Помилка: Введення не може бути від'ємним" << endl;
            goto menu_1;
        }
        switch (menu){//Вибираємо та виконуємо дію відповідно до введеного номера.
            case 1://// Виводимо таблицю щоденних витрат.
            cout << "\nДень\tВитрати по днях (грн): " << endl;
            for (int i = 0; i < N; i++){
                cout << i + 1 << "\t" << fixed << setprecision(2) << spending[i] << endl;
            }
            break;
        
            case 2:{// Обчислюємо статистику витрат і визначаємо стан бюджету.
            
            double minSpending, maxSpending;
            MinMax (spending, N, minSpending, maxSpending);
            cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << minSpending << " грн" << endl;
            cout << "Максимальні витрати за день: " << fixed << setprecision(2) << maxSpending << " грн" << endl;
 
            double total = Sumtotal(spending, N);
            cout << "Сумарні витрати: " << fixed << setprecision(2) << total << " грн" << endl;

            double realmoney = budget - total;
            if ( realmoney >= 0 ){
                cout << "Залишок бюджету: " << fixed << setprecision(2) << realmoney <<" грн" << endl; 
            }
            else {
                cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << fabs(realmoney) <<" грн" << endl; 
            }
            int purchase = 0;
            for (int i = 0; i < N; i++){
            if(spending[i] > 0){
                purchase++;
            }
            }
            cout << "Днів з покупками: " << purchase << endl;
            double Sumpurchase = 0;

            for (int i = 0; i < N; i++){
                if(spending[i] == 0){
                    continue;
                }
                Sumpurchase += spending[i];
            }

            if (purchase > 0) {
                double average = Sumpurchase / purchase;

                cout << "Середні витрати за такий день: " << fixed << setprecision(2) << average << " грн" << endl;
            }
            else {
                cout << "Покупок не було." << endl;
            }
            int i = 0;
            double Sumpurchase2 = 0;
            bool budget2 = false;
            while(i < N){
                Sumpurchase2 += spending[i];
                if (Sumpurchase2 >= budget ){
                  cout << "Бюджет вичерпано на дні " << i + 1 ;
                  cout << ", накопичено  " << fixed << setprecision(2) << Sumpurchase2 << " грн" << endl;

                  budget2 = true;
                  break;
                }
                i++;
            }
            if (!budget2){
                cout << "Бюджет не вичерпано за ці дні." << endl;

                cout << "Залишок бюджету: " << fixed << setprecision(2) << budget - Sumpurchase2 << " грн" << endl;
            }
        break;}
        case 3: {//Перевіряємо у які дні вичерпано встановлений ліміт
            
        double limit;

             cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
             cin >> limit;

             if (limit < 0){
                cout << "Помилка: ліміт не може бути відʼємним." << endl;
             }
             else if(limit == 0){
                Overlimit(spending, N);
             }
             else {
                Overlimit(spending, N, limit);
             }
             break;
            }

        case 4:{//Знаходимо топ-3 найбільші витрати
         
        double sortspending[N];

        for (int i = 0; i < N; i++){
            sortspending[i] = spending[i];
        }
        for (int i = 0; i < N - 1; i++){
            for (int j = 0; j < N - 1 - i; j++){
                if(sortspending[j] < sortspending[j + 1]){
                    double tmp = sortspending[j];
                    sortspending[j] = sortspending[j + 1];
                    sortspending[j + 1] = tmp;
                }
            }
        }

        int count = N < 3 ? N : 3;
        cout << fixed << setprecision(2);
        cout << "Топ-" << count << " витрат: ";

        for(int i = 0; i < count; i++){
            cout << sortspending[i];

            if (i < count - 1){
                cout << ",  ";
            }
        }
        cout << " грн" << endl;

        break;


    }
          }
        }
    
while (menu != 0);

}