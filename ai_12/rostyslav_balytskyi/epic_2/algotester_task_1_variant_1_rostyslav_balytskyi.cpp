#include <iostream>

using namespace std;

int main() {
// 2 цілих числа 𝐻 та 𝑀 - хітпойнти та мана персонажа
long long H, M;
cin >> H >> M;

bool win = true;
// 3 рядки по 2 цілих числа, ℎ𝑖 та 𝑚𝑖 - хітпойнти та мана, які ваш персонаж потратить за хід на 𝑖 заклинання
for (long long i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;

        // Заклинання забирає і HP, і ману одночасно
        if (h > 0 && m > 0) {
            win = false;
        }

        H -= h;
        M -= m;
    }

    // В кінці має залишитися строго додатна кількість HP та мани
    if (H <= 0 || M <= 0) {
        win = false;
    }

    if (win) {
        cout << "YES" <<endl;
    } else {
        cout << "NO" <<endl;
    }

return 0;
}