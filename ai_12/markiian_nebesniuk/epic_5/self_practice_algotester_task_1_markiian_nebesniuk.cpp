/*
Задача Алготестер "ДНК реп'яховірусу"
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string t, s;
    cin >> t >> s;

    int n = (int)t.length();
    int m = (int)s.length();

    // Якщо вірус довший за ДНК людини, підрядків такої довжини не існує
    if (m > n) {
        cout << 0 << endl;
        return 0;
    }

    // Лічильник кожної з 26 літер у поточному вікні рядка t
    int cnt[26] = {0};

    // Початкове вікно для s[0]: від t[0] до t[n - m] включно
    for (int i = 0; i <= n - m; i++) {
        cnt[t[i] - 'a']++;
    }

    long long ans = 0;

    for (int j = 0; j < m; j++) {
        // Кожен збіг із s[j] додає до відповіді його 1-індекс (j + 1)
        ans += (long long)(j + 1) * cnt[s[j] - 'a'];

        // Зсуваємо вікно на 1 позицію вправо для наступного символу s[j + 1]
        if (j + 1 < m) {
            cnt[t[j] - 'a']--;
            cnt[t[n - m + 1 + j] - 'a']++;
        }
    }

    cout << ans << endl;
    return 0;
}