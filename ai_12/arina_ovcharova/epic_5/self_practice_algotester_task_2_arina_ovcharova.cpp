// Self Practice, задача 2 - "Зробити паліндром" (Algotester)
// з букв можна скласти паліндром, якщо непарну кількість разів зустрічається не більше однієї букви
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int cnt[26] = {0};
    for (size_t i = 0; i < s.length(); i++) {
        cnt[s[i] - 'a']++;
    }

    int odd = 0;
    for (int c = 0; c < 26; c++) {
        if (cnt[c] % 2 != 0) {
            odd++;
        }
    }

    // одна "непарна" буква може стати в середину
    if (odd <= 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
