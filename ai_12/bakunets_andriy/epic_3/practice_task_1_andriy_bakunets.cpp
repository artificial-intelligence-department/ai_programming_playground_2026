#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX = 31;  // найбільша кількість днів обліку

// Показує витрати за кожен день
// sp - масив витрат, n - кількість днів
void showSpending(const double sp[], int n) {
    cout << "\nВитрати по днях:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "День " << i + 1 << " - "
             << sp[i] << " грн" << endl;
    }
}

// Знаходить найменші та найбільші витрати
// minv і maxv передані за посиланням, щоб функція могла їх змінити
void findMinMax(const double sp[], int n,
                double &minv, double &maxv) {
    minv = sp[0];  // minv - найменші витрати
    maxv = sp[0];  // maxv - найбільші витрати

    for (int i = 1; i < n; i++) {
        if (sp[i] < minv) {
            minv = sp[i];
        }

        if (sp[i] > maxv) {
            maxv = sp[i];
        }
    }
}

// Обчислює суму витрат рекурсивно
// cnt - скільки перших елементів масиву ще треба додати
double sumRecursive(const double sp[], int cnt) {
    if (cnt == 0) {
        return 0;  // умова зупинки рекурсії
    }

    // Додає останню витрату до суми попередніх
    return sp[cnt - 1] + sumRecursive(sp, cnt - 1);
}

// Показує статистику витрат
// bud - бюджет на весь період
void showStats(const double sp[], int n, double bud) {
    double minv;  // minv - найменші витрати за день
    double maxv;  // maxv - найбільші витрати за день

    findMinMax(sp, n, minv, maxv);

    double tot = sumRecursive(sp, n);  // tot - сума всіх витрат

    cout << "\nНайменші витрати: " << minv << " грн" << endl;
    cout << "Найбільші витрати: " << maxv << " грн" << endl;
    cout << "Усього витрачено: " << tot << " грн" << endl;

    double rest = bud - tot;  // rest - залишок або перевитрата

    if (rest < 0) {
        // fabs повертає додатне значення модуля числа
        cout << "Перевитрата: " << fabs(rest) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << rest << " грн" << endl;
    }

    double ptot = 0;  // ptot - сума витрат у дні з покупками
    int pdays = 0;    // pdays - кількість днів із покупками

    for (int i = 0; i < n; i++) {
        if (sp[i] == 0) {
            continue;  // пропускаємо день без покупок
        }

        ptot += sp[i];
        pdays++;
    }

    cout << "Днів із покупками: " << pdays << endl;

    if (pdays > 0) {
        cout << "Середні витрати за день із покупками: "
             << ptot / pdays << " грн" << endl;
    } else {
        cout << "Днів із покупками немає." << endl;
    }

    double acc = 0;  // acc - витрати, накопичені день за днем
    int d = 0;       // d - номер дня, який перевіряємо

    // Накопичуємо витрати, поки бюджет не буде вичерпано
    while (d < n) {
        acc += sp[d];
        d++;

        if (acc >= bud) {
            break;  // зупиняємо цикл у день вичерпання бюджету
        }
    }

    if (acc >= bud) {
        cout << "Бюджет вичерпано на дні " << d << "." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні." << endl;
    }
}

// Показує дні, коли витрати перевищили ліміт
// lim - денний ліміт; якщо не передано, стандартне значення — 1000 грн
void showOverLimit(const double sp[], int n, double lim = 1000) {
    cout << "\nДні з витратами понад " << lim << " грн:" << endl;

    int odays = 0;  // odays - кількість днів понад ліміт

    for (int i = 0; i < n; i++) {
        if (sp[i] > lim) {
            cout << "День " << i + 1 << " - "
                 << sp[i] << " грн" << endl;
            odays++;
        }
    }

    cout << "Усього таких днів: " << odays << endl;
}

// Показує три найбільші витрати та відповідні дні
void showTop3(const double sp[], int n) {
    double srt[MAX];  // srt - копія витрат для сортування
    int dnum[MAX];    // dnum - номери днів для кожної витрати

    // Копіюємо витрати й записуємо номери днів
    for (int i = 0; i < n; i++) {
        srt[i] = sp[i];
        dnum[i] = i + 1;
    }

    // Сортуємо копію витрат від найбільших до найменших
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (srt[j] < srt[j + 1]) {
                // Міняємо місцями витрати (tmpS - тимчасова змінна)
                double tmpS = srt[j];
                srt[j] = srt[j + 1];
                srt[j + 1] = tmpS;

                // Разом із витратами міняємо номери днів (tmpD - тимчасова змінна)
                int tmpD = dnum[j];
                dnum[j] = dnum[j + 1];
                dnum[j + 1] = tmpD;
            }
        }
    }

    int topN = n;  // topN - кількість витрат для показу

    if (topN > 3) {
        topN = 3;
    }

    cout << "\nНайбільші витрати:" << endl;

    for (int i = 0; i < topN; i++) {
        cout << "День " << dnum[i] << " - "
             << srt[i] << " грн" << endl;
    }
}

int main() {
    double bud;       // bud - бюджет на період обліку
    int n;            // n - кількість днів обліку
    double sp[MAX];   // sp - витрати за кожен день

    cout << fixed << setprecision(2);  // два знаки після крапки

    // Введення та перевірка бюджету
    cout << "Бюджет: ";
    cin >> bud;

    if (cin.fail() || bud <= 0) {
        cout << "Помилка: бюджет має бути додатним числом." << endl;
        return 1;
    }

    // Введення та перевірка кількості днів
    cout << "Кількість днів: ";
    cin >> n;

    if (cin.fail() || n < 1 || n > MAX) {
        cout << "Помилка: кількість днів має бути від 1 до "
             << MAX << "." << endl;
        return 1;
    }

    // Введення та перевірка витрат за кожен день
    cout << "Введіть витрати за " << n << " днів:" << endl;

    for (int i = 0; i < n; i++) {
        cin >> sp[i];

        if (cin.fail() || sp[i] < 0) {
            cout << "Помилка: витрати мають бути числом не менше 0."
                 << endl;
            return 1;
        }
    }

    int ch;     // ch - вибраний пункт меню
    int merr;   // merr - 0 — правильний вибір, 1 — неправильний

menu:
    merr = 0;

    // Меню повторюється, поки користувач не вибере 0
    do {
        cout << "\n1 - Показати витрати по днях" << endl;
        cout << "2 - Показати статистику" << endl;
        cout << "3 - Знайти дні понад ліміт" << endl;
        cout << "4 - Показати три найбільші витрати" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";

        cin >> ch;

        // Перевіряємо, чи введено число
        if (cin.fail()) {
            cin.clear();               // очищаємо стан помилки
            cin.ignore(10000, '\n');   // прибираємо неправильне введення

            cout << "Помилка: введіть число від 0 до 4." << endl;
            goto menu;                 // повертаємося до меню
        }

        // Виконуємо дію відповідно до вибору користувача
        switch (ch) {
            case 1:
                showSpending(sp, n);
                break;

            case 2:
                showStats(sp, n, bud);
                break;

            case 3: {
                double lim;  // lim - денний ліміт, введений користувачем

                cout << "Введіть ліміт (0 — стандартний, 1000 грн): ";
                cin >> lim;

                // Перевіряємо, чи введено число
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Помилка: введіть число для ліміту." << endl;
                    break;
                }

                // Перевіряємо, чи ліміт не від'ємний
                if (lim < 0) {
                    cout << "Помилка: ліміт не може бути від'ємним."
                         << endl;
                    break;
                }

                if (lim == 0) {
                    showOverLimit(sp, n);        // стандартний ліміт
                } else {
                    showOverLimit(sp, n, lim);   // заданий ліміт
                }

                break;
            }

            case 4:
                showTop3(sp, n);
                break;

            case 0:
                cout << "Завершення роботи." << endl;
                break;

            default:
                cout << "Такого пункту меню немає." << endl;
                merr = 1;
                break;
        }

        // Для неправильного числового пункту повертаємося до меню через goto
        if (merr == 1) {
            goto menu;
        }

    } while (ch != 0);

    return 0;  // успішне завершення програми
}