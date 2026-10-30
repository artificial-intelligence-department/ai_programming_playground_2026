/*
Назва задачі:Аналізатор місячного бюджету
Автор:Катерина Лисенко
Номер групи:ШІ-12
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>
using namespace std;
void PrintSpendings(float spending[], int N) { // функція для виводу таблиці витрат
cout << "\n " << left << setw(12) << "День" << "Витрати, грн" << endl;
 for (int i=0; i < N; i++) {
    cout << left << setw(12) << (i+1) << fixed << setprecision(2) << spending[i] << endl;
}
}
float CountTotalRecursive(float spending[], int N) { //  рекрусивна функція підрахунку сумарних витрат
     if (N <= 0) return 0;
    return spending[N - 1] + CountTotalRecursive(spending, N - 1);
}
void GetMinMax(float spending[], int N, float &min_val, float &max_val) { // знаходження мінімального та максимального елемента
    max_val = spending[0];
    min_val = spending[0];
    for (int i=1; i < N; i++) {
       if (spending[i] < min_val) min_val = spending[i];
       if (spending[i] > max_val) max_val = spending[i];
   }
   }
void ShowStatistics(float spending[], int N, float budget) { // функція виводу статистики та аналізу бюджету
   float min_val, max_val;
 GetMinMax( spending, N, min_val, max_val);

float total = CountTotalRecursive( spending,N);
float sum_active=0;
float active_days=0;
for ( int i=0; i < N; i++) {
 if (spending[i] == 0) continue;
 sum_active += spending[i];
 active_days++;
}
float average= (active_days > 0) ? (sum_active/active_days) : 0; // обчислення середнього чеку
float sum_so_far = 0;
int day_exceeded = -1;
int i = 0;
while (i < N) {
 sum_so_far += spending[i];
  if ( sum_so_far > budget){
      day_exceeded = i + 1;
      break;
    }
   i++;
}
// вивід аналітичних результатів
cout << "\nМінімальні витрати за день: " << fixed << setprecision(2) << min_val << "грн." << endl;
cout << "Максимальні витрати за день: " << fixed << setprecision(2) << max_val << "грн." << endl;
cout << "Сумарні витрати: " << fixed << setprecision(2) << total << "грн." << endl;
if (total > budget) {
    cout << "Перевитрата понад бюджет" << (total - budget) << "грн." << endl;
} else {
    cout << " Залишок бюджету: " << (budget - total) << "грн." << endl;
}
cout << "Днів з покупками: " << active_days << endl;
cout << "Cередні витрати за такий день: " << average << endl;
if (day_exceeded != -1) {
cout << "Бюджет вичерпано на день: " << day_exceeded << "накопичено: " << sum_so_far << "грн." << endl;
} else {
cout << "Бюджету вистачило на всі дні. Залишок: " << (budget - total) << "грн." << endl;
}
}
// перевірка перевищення денного бюджету
void ShowExceededLimit(float spending[], int N, float limit = 1000.0f) {
    cout << fixed << setprecision(2);
   cout << "\n Ліміт: " << limit << " грн" << endl;
   int count = 0;
   for (int i = 0; i < N; i++) {
    if (spending[i] > limit) {
     cout << " день " << (i + 1) << ": " << spending[i] << " грн" << endl;
    count++;
 }
}
 cout << "Разом днів з перевищенням: " << count << endl;
}

// 4. Три найдорожчі дні (соортування копії масиву)
void ShowTop3Spendings(float spending[], int N) {
 double sorted_spending[31] = {0};
 for (int i = 0; i < N; i++) {
        sorted_spending[i] = spending[i];
    }

    // Сортує витрати за спаданням методом бульбашки
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if (sorted_spending[j] < sorted_spending[j+1]) {
                 // Міняємо сусідні елементи місцями
                double temporary = sorted_spending[j];
                sorted_spending[j] = sorted_spending[j+1];
                sorted_spending[j+1] = temporary;
            }
        }
    }
    int count;
    if (N < 3) {
        count = N;
    } else {
        count = 3;
    }
    cout << "Топ-3 витрат: " << endl;
    // Виводить три найбільші витрати або меншу кількість, якщо днів мало
    for (int i = 0; i < count; i++) {
        cout << "  " << i + 1 << ". " << fixed << setprecision(2) << sorted_spending[i] << " грн" << endl;
    }
}


int main() {
 float budget;
 int N;
 float spending[31];

 cout << "Бюджет на місяць: ";
 cin >> budget;
 cout << "Кількість днів обліку: ";
 cin >> N;

 if (N < 1 || N > 31) {
 cout << "Кількість днів не може бути менше 1 більше 31!" << endl;
 return 0;
 }

 cout << "Витрати по днях (грн): ";
 for (int i = 0; i < N; i++) {
 cin >> spending[i];
 }

 int choice;

main_menu: // Мітка для goto (вимога №9)
 do {
 cout << "\n--- МЕНЮ ---" << endl;
 cout << "1. Показати витрати по днях" << endl;
 cout << "2. Статистика витрат" << endl;
 cout << "3. Дні з перевищенням денного ліміту" << endl;
 cout << "4. Три найдорожчі дні" << endl;
 cout << "0. Вийти" << endl;
 cout << "Виберіть опцію: ";

 if (!(cin >> choice)) { // Перевірка на нечислове введення
 cin.clear();
 cin.ignore(1000, '\n');
 cout << "Некоректне введення! Повернення до меню." << endl;
 goto main_menu;
 }

 switch (choice) {
 case 1:
 PrintSpendings(spending, N);
 break;
 case 2:
 ShowStatistics(spending, N, budget);
 break;
 case 3: {
 float user_limit;
 cout << "Введіть денний ліміт (грн, 0 = за замовчуванням): ";
 cin >> user_limit;
 if (user_limit == 0) {
 ShowExceededLimit(spending, N); // Виклик із значенням за замовчуванням (1000).
 } else {
 ShowExceededLimit(spending, N, user_limit);
 }
 break;
 }
 case 4:
 ShowTop3Spendings(spending, N);
 break;
 case 0:
 cout << "Завершення роботи." << endl;
 break;
 default:
 cout << "Невірний пункт меню! Спробуйте ще раз." << endl;
 goto main_menu; // Використання goto для повернення до меню
 }
 } while (choice != 0);

 return 0;
}