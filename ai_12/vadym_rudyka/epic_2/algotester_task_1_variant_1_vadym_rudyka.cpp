#include <iostream>

using namespace std;
// 2 цілих числа 𝐻 та 𝑀 - хітпойнти та мана персонажа
int main() {
    long long H, M;
    cin >> H >> M;

    bool win = true;
// 3 рядки по 2 цілих числа, ℎ𝑖 та 𝑚𝑖 - кількість хітпойнтів та мани, які ваш персонаж потратить за хід на 𝑖 заклинання
    for (long long i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;

        // Закляття витрачає і HP, і ману
        if (h > 0 && m > 0) {
            win = false;
        }
        H -= h;
        M -= m;
    }

    // В кінці HP і мана повинні бути додатними
    if (H <= 0 || M <= 0) {
        win = false;
    }

    if (win) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}