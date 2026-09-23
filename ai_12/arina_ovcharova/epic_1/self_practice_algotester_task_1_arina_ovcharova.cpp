#include <iostream>

using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    // Прапорець для перевірки, чи використовувалися мана і здоров'я одночасно
    bool bothUsedAtOnce = false;

    // Зчитуємо 3 заклинання
    for (int i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;

        // Якщо заклинання вимагає і ману, і здоров'я
        if (h > 0 && m > 0) {
            bothUsedAtOnce = true;
        }

        H -= h;
        M -= m;
    }

    // Якщо мана й HP не витрачалися одночасно і їхній залишок > 0
    if (!bothUsedAtOnce && H > 0 && M > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
