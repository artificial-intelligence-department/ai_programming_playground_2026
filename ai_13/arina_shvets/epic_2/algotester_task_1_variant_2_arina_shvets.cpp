#include <iostream>

using namespace std;

int main() {
    long long h[4], d[4];
    for (int i = 0; i < 4; i++) cin >> h[i];
    for (int i = 0; i < 4; i++) cin >> d[i];

    // 1. Перевірка на Помилку
    for (int i = 0; i < 4; i++) {
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    // 2. Відпилюємо по одній ніжці по черзі і дивимось, чи стіл не перевернувся
    bool flip_over = false;
    for (int i = 0; i < 4; i++) {
        h[i] = h[i] - d[i];

        long long mx = h[0], mn = h[0];
        for (int j = 1; j < 4; j++) {
            if (h[j] > mx) mx = h[j];
            if (h[j] < mn) mn = h[j];
        }

        if (mx >= 2 * mn) flip_over = true;
    }

    // 3. Перевіряємо, що в кінці всі ніжки рівні і не нульові
    bool equal = (h[0] == h[1] && h[1] == h[2] && h[2] == h[3]);
    bool non_zero = (h[0] > 0);

    if (!flip_over && equal && non_zero) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}