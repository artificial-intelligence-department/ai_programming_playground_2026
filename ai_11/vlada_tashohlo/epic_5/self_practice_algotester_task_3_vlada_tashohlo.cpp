
/* 
Епік 5. self practice: Algotester, задача "Найдорожчий подарунок"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
#include <string>
using namespace std;

// Перевірка, чи є рядок p примітивним (не складається з повторень коротшого періоду)
bool isPrimitive(string& p, int len) {
    for (int d = 1; d < len; ++d) {
        if (len % d != 0) continue; // d має бути дільником len

        bool same = true;

        for (int i = 0; i < len; ++i) {
            if (p[i] != p[i % d]) {
                same = false;
                break;
            }
        }

        // Якщо рядок повністю повторює блок довжини d — він не є примітивним
        if (same) return false;
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    // Підрахунок частоти кожної з трьох літер: 'a' (0), 'b' (1), 'c' (2)
    int freq[3] = {0, 0, 0};

    for (int i = 0; i < n; ++i) {
        freq[s[i] - 'a']++;
    }

    long long answer = 0;

    // Базовий випадок: періоди довжини 1 ("a", "b" або "c")
    // Якщо взяти всі входження однієї літери: ціна = freq^2 / 1 = freq^2
    for (int i = 0; i < 3; ++i) {
        long long value = 1LL * freq[i] * freq[i];

        if (value > answer) {
            answer = value;
        }
    }

    // Попереднє обчислення степенів трійки для генерації трійкових масок
    int powers[9];
    powers[0] = 1;

    for (int i = 1; i <= 8; ++i) {
        powers[i] = powers[i - 1] * 3;
    }

    // Перебір довжин примітивних періодів від 2 до 8
    // Оскільки ціна підпослідовності: |t|^2 / len = (k * len)^2 / len = len * k^2
    for (int len = 2; len <= 8; ++len) {
        for (int mask = 0; mask < powers[len]; ++mask) {

            string p(len, 'a');
            int cnt[3] = {0, 0, 0};

            // Генерація рядка з поточної трійкової маски
            int x = mask;

            for (int i = 0; i < len; ++i) {
                int digit = x % 3;
                x /= 3;

                p[i] = 'a' + digit;
                cnt[digit]++;
            }

            // Пропускаємо складені (непримітивні) періоди
            if (!isPrimitive(p, len)) {
                continue;
            }

            // Максимально можлива кількість повторень періоду p за частотами літер
            int maxK = n;

            for (int i = 0; i < 3; ++i) {
                if (cnt[i] > 0) {
                    int limit = freq[i] / cnt[i];

                    if (limit < maxK) {
                        maxK = limit;
                    }
                }
            }

            // Відсікання: якщо навіть теоретичний максимум не перевищує поточний рекорд
            long long upperBound =
                1LL * len * maxK * maxK;

            if (upperBound <= answer) {
                continue;
            }

            // Жадібний пошук максимальної кількості входжень блоку p як підпослідовності в рядок s
            int pos = 0;
            int k = 0;

            for (int i = 0; i < n; ++i) {
                if (s[i] == p[pos]) {
                    pos++;

                    if (pos == len) {
                        k++;     // Зібрали один повний період
                        pos = 0; // Починаємо шукати наступний
                    }
                }
            }

            // Розрахунок вартості для знайденої підпослідовності
            long long value = 1LL * len * k * k;

            if (value > answer) {
                answer = value;
            }
        }
    }

    // Виведення максимальної вартості
    cout << answer << '\n';

    return 0;
}
