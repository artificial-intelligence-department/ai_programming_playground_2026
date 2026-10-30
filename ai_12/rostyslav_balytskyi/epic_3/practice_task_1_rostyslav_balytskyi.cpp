//Практисне завдання lab_3: Аналізатор місячного бюджету
//СШІ-Балицький Ростислав 
#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std;

const int MAX = 31;  // найбільша кількість днів обліку

// 1. Показати витрати по днях (цикл for)
void Spending(const double sp[], int n) {
    cout << endl << "День     Витрати, грн" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << setw(16) << sp[i] << endl;
    }
}

// Мінімум і максимум через параметри-посилання
void MinMax(const double sp[], int n, double &minv, double &maxv) {
    minv = sp[0];
    maxv = sp[0];
    for (int i = 1; i < n; i++) {
        if (sp[i] < minv) minv = sp[i];
        if (sp[i] > maxv) maxv = sp[i];
    }
}

// Сума витрат рекурсивно (без циклу)
double Recursive(const double sp[], int cnt) {
    if (cnt == 0) {
        return 0;
    }
    return sp[cnt - 1] + Recursive(sp, cnt - 1);
}

// 2. Статистика витрат
void Stats(const double sp[], int n, double bud) {
    double minv, maxv;
    MinMax(sp, n, minv, maxv);
    double tot = Recursive(sp, n);

    cout << endl << "Мінімальні витрати за день: " << minv << " грн" << endl;
    cout << "Максимальні витрати за день: " << maxv << " грн" << endl;
    cout << "Сумарні витрати: " << tot << " грн" << endl;

    double rest = bud - tot;
    if (rest < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(rest) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << rest << " грн" << endl;
    }

    // Середні витрати за дні з покупками
    double ptot = 0;
    int pdays = 0;
    for (int i = 0; i < n; i++) {
        if (sp[i] == 0) {
            continue;  // пропускаємо день без покупок
        }
        ptot += sp[i];
        pdays++;
    }
    cout << "Днів з покупками: " << pdays << endl;
    if (pdays > 0) {
        cout << "Середні витрати за такий день: " << ptot / pdays << " грн" << endl;
    } else {
        cout << "Днів з покупками немає." << endl;
    }

    // День, коли бюджет вичерпано (while + break)
    double acc = 0;
    int d = 0;
    while (d < n) {
        acc += sp[d];
        d++;
        if (acc > bud) {
            break;  // зупиняємось одразу на цьому дні
        }
    }
    if (acc > bud) {
        cout << "Бюджет вичерпано на дні " << d << ", накопичено " << acc << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні, залишок: " << bud - acc << " грн." << endl;
    }
}

// 3. Дні з перевищенням ліміту (параметр за замовчуванням 1000)
void OverLimit(const double sp[], int n, double lim = 1000) {
    cout << "Ліміт: " << lim << " грн" << endl;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (sp[i] > lim) {
            cout << "   день " << i + 1 << ": " << sp[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// 4. Три найдорожчі дні (сортування копії вкладеними циклами)
void Top3(const double sp[], int n) {
    double srt[MAX];
    for (int i = 0; i < n; i++) {
        srt[i] = sp[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (srt[j] < srt[j + 1]) {
                double tmp = srt[j];
                srt[j] = srt[j + 1];
                srt[j + 1] = tmp;
            }
        }
    }

    int topN = n;
    if (topN > 3) {
        topN = 3;
    }

    cout << "Топ-" << topN << " витрат: ";
    for (int i = 0; i < topN; i++) {
        cout << srt[i];
        if (i < topN - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {
    double bud;
    int n;
    double sp[MAX];

    cout << fixed << setprecision(2);

    // Введення бюджету
    while (true) {
        cout << "Бюджет на місяць (грн): ";
        cin >> bud;
        if (cin.fail()) {
            if (cin.eof()) return 1;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть число." << endl;
        } else if (bud <= 0) {
            cout << "Помилка: бюджет має бути більшим за 0." << endl;
        } else {
            break;
        }
    }

    // Введення кількості днів
    while (true) {
        cout << "Кількість днів обліку (1-" << MAX << "): ";
        cin >> n;
        if (cin.fail()) {
            if (cin.eof()) return 1;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть ціле число." << endl;
        } else if (n < 1 || n > MAX) {
            cout << "Помилка: кількість днів має бути від 1 до " << MAX << "." << endl;
        } else {
            break;
        }
    }

    // Введення витрат по днях
    cout << "Витрати по днях (грн), " << n << " чисел:" << endl;
    for (int i = 0; i < n; i++) {
        while (true) {
            cout << "   День " << i + 1 << ": ";
            cin >> sp[i];
            if (cin.fail()) {
                if (cin.eof()) return 1;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: введіть число." << endl;
            } else if (sp[i] < 0) {
                cout << "Помилка: витрати не можуть бути від'ємними." << endl;
            } else {
                break;
            }
        }
    }

    int ch;

menu:
    do {
        cout << endl << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> ch;

        // Нечислове введення — назад до меню через goto
        if (cin.fail()) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть число від 0 до 4." << endl;
            goto menu;
        }

        switch (ch) {
            case 1:
                Spending(sp, n);
                break;
            case 2:
                Stats(sp, n, bud);
                break;
            case 3: {
                double lim;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> lim;
                if (cin.fail()) {
                    if (cin.eof()) return 0;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Помилка: введіть число." << endl;
                } else if (lim < 0) {
                    cout << "Помилка: ліміт не може бути від'ємним." << endl;
                } else if (lim == 0) {
                    OverLimit(sp, n);       // ліміт за замовчуванням
                } else {
                    OverLimit(sp, n, lim);   // заданий ліміт
                }
                break;
            }
            case 4:
                Top3(sp, n);
                break;
            case 0:
                cout << "До побачення!" << endl;
                break;
            default:
                cout << "Такого пункту меню немає." << endl;
                goto menu;  // неправильний пункт — назад до меню
        }
    } while (ch != 0);

    return 0;
}