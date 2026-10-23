/*
Дмитро Плахтина
ШІ-11
Аналізатор місячного бюджету
Задача
Ви пишете програму обліку особистих витрат. Користувач задає бюджет на місяць і вводить суму витрат за кожен день.
Далі програма аналізує ці дані через меню: показує статистику, знаходить найдорожчі дні й перевіряє, чи вистачає бюджету.
Дні без покупок теж бувають. У різних обчисленнях вони враховуються по-різному.
*/
#include <iostream>
using namespace std;
// Максимальна кількість днів обліку (не більше місяця)
const int MAX_DAYS = 31;
// Пункт 1: вивід витрат по днях
void punkt1(double arr[], int days) {
    for (int i = 0; i < days; i++ ) {
        cout << "День " << i+1 << " = " << arr[i] << endl;
    }
}
// Пошук мінімальних і максимальних витрат (результат повертається через параметри-посилання)
void minMax(double arr[], int days, double &mn, double &mx) {
    mn = arr[0];
    mx = arr[0];
    for (int i = 0; i < days; i++) {
    if (arr[i] < mn) {mn = arr[i];}
    if (arr[i] > mx) {mx = arr[i];}
}
}
// Рекурсивне обчислення сумарних витрат (без циклу)
double sumRec(double arr[], int n) {
    if (n == 0) {
        return 0;
    }
    return arr[n-1] + sumRec(arr, n-1 );
}
// Пункт 2: статистика витрат
void punkt2(double arr[], int days, double budget) {
    // Мінімальні й максимальні витрати за день
    double mn, mx;
    minMax(arr, days, mn, mx);   // після цього в mn і mx лежать відповіді
    cout << "Мінімальні витрати за день: " << mn << " грн" << endl;
    cout << "Максимальні витрати за день: " << mx << " грн" << endl;
    // Сумарні витрати
    double total = sumRec(arr, days);
    cout << "Сумарні витрати: " << total << " грн." << endl;
    // Залишок бюджету або перевитрата (модуль через abs)
    double rest = budget - total;
    if (rest < 0) {
    cout << "Перевитрата понад бюджет: " << abs(rest) << " грн" << endl;
    } else {
    cout << "Залишок бюджету: " << rest << " грн" << endl;
}
    // Середні витрати за дні з покупками (дні без покупок пропускаємо через continue)
    double sum = 0;   // сума лише днів із покупками
    int count = 0;    // скільки таких днів
    for (int i = 0; i < days; i++) {
    if (arr[i] == 0) {
        continue;
    }
    sum += arr[i];
    count++;
}
cout << "Днів з покупками: " << count << endl;
if (count > 0) {
    cout << "Середня витрата за день: " << sum/count << "грн." << endl;
} else {cout << "Днів з покупками не було" << endl;}

// Пошук дня, коли бюджет вичерпано (цикл while і break)
int i = 0;
double nakopycheno = 0;
while (i < days) {
    nakopycheno = nakopycheno + arr[i];
    if (nakopycheno > budget) {
        break;
    }
    i++;
}
    // Вивід дня вичерпання бюджету або залишку
    if (nakopycheno > budget) {
        cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << nakopycheno << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << budget - nakopycheno << " грн." << endl;
    }
}
// Пункт 3: дні з перевищенням денного ліміту (ліміт за замовчуванням 1000 грн)
void punkt3(double arr[], int days, double limit = 1000) {
    cout << "Ліміт: " << limit << " грн." << endl;
    int count = 0;
    for (int i = 0; i < days; i++) {
        if (arr[i] > limit) {
            cout << "День" << i + 1 << ": " << arr[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
// Пункт 4: три найдорожчі дні
void punkt4(double arr[], int days) {
// Копія масиву, щоб початковий масив не змінився
double copy[MAX_DAYS];
for (int i = 0; i < days; i++) {
    copy[i] = arr[i];
}
// Сортування копії за спаданням вкладеними циклами
for (int i = 0; i < days - 1; i++) {
    for (int j = 0; j < days - 1 - i; j++) {
        if (copy[j] < copy[j + 1]) {
            double tmp = copy[j];
            copy[j] = copy[j + 1];
            copy[j + 1] = tmp;
        }
    }
}
// Скільки значень виводити: 3 або менше, якщо днів менше трьох
int k = 3;
if (days < 3) {
    k = days;
}
// Вивід найбільших витрат
cout << "Топ-3 витрат: " << endl;
for (int i = 0; i < k; i++) {
    cout << copy[i] << endl;
}


}
int main() {
    // Вивід дробових чисел з двома знаками після коми
    cout.setf(ios::fixed);
    cout.precision(2);
    double budget;
    int days;
    double spending[MAX_DAYS];
    bool ok;
// Ввід бюджету з перевіркою (число більше 0)
do {
    cout << "Введіть бюджет на місяць (грн): ";
    cin >> budget;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        ok = false;
    } else if (budget <= 0) {
        ok = false;
    } else {
        ok = true;
    }
    if (!ok) {
        cout << "Помилка! Бюджет має бути більше 0." << endl;
    }
} while (!ok);
// Ввід кількості днів з перевіркою (від 1 до 31)
do {
    cout << "Скільки днів ви хочете вести облік: ";
    cin >> days;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        ok = false;
    } else if (days < 1 || days > 31) {
        ok = false;
    } else {
        ok = true;
    }
    if (!ok) {
        cout << "Помилка! Введіть від 1 до 31" << endl;
    }
} while (!ok);

    // Ввід витрат по днях з перевіркою (не менше 0)
    for (int i = 0; i < days; i++) {
    do {
        cout << "Введіть витрати на день " << i + 1 << ": ";
        cin >> spending[i];
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            ok = false;
        } else if (spending[i] < 0) {
            ok = false;
        } else {
            ok = true;
        }
        if (!ok) {
            cout << "Помилка! Витрати не можуть бути від'ємними." << endl;
        }
    } while (!ok);
}
    // Меню повторюється, доки користувач не вибере 0
    int choice;
    do {
        // Мітка, до якої повертає goto
        menu:
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат"<< endl;
        cout << "3 - Дні з перевищенням денного ліміту"<< endl;
        cout << "4 - Три найдорожчі дні"<< endl;
        cout << "0 - Вихід"<< endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        // Якщо ввели не число, то очищаємо ввід і повертаємось до меню
        if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка! Введіть число." << endl;
        goto menu;
        }
        // Якщо такого пункту немає, то повертаємось до меню
        if (choice < 0 || choice > 4) {
        cout << "Помилка! Немає такого пункту." << endl;
        goto menu;
        }
        // Виконання вибраного пункту меню
        if (choice == 1) {
            punkt1(spending, days);
        } else if (choice == 2) {
            punkt2(spending, days, budget);
        } else if (choice == 3) {
            // Ввід денного ліміту з перевіркою (не менше 0)
            double limit;
            do {
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    ok = false;
                } else if (limit < 0) {
                    ok = false;
                } else {
                    ok = true;
                }
                if (!ok) {
                    cout << "Помилка! Ліміт має бути числом не менше 0." << endl;
                }
            } while (!ok);

            // Якщо ввели 0, використовуємо ліміт за замовчуванням
            if (limit == 0) {
                punkt3(spending, days);
            } else {
                punkt3(spending, days, limit);
            }

        }else if (choice == 4) {
            punkt4(spending, days);
        }else if (choice == 0) {
            cout << "До побачення!" << endl;
        }
 } while (choice != 0);
    return 0;
}