#include <iostream>
using namespace std;

int main() {
    // H, M та витрати до 10^12, тому потрібен тип long long
    long long H, M;
    cin >> H >> M;

    // Три закляття
    for (int i = 0; i < 3; i++) {
        long long hp, mana;
        cin >> hp >> mana;

        // Закляття, яке забирає і хітпойнти, і ману одночасно, - програш
        if (hp > 0 && mana > 0) {
            cout << "NO";
            return 0;
        }

        // Віднімаємо витрачені хітпойнти та ману
        H -= hp;
        M -= mana;
    }

    // Виграш, якщо в кінці і хітпойнтів, і мани більше нуля
    if (H > 0 && M > 0)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
