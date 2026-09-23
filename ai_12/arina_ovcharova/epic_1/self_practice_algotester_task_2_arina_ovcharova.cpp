#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long h[4], d[4];
    for (int i = 0; i < 4; i++) cin >> h[i];
    for (int i = 0; i < 4; i++) cin >> d[i];

    bool tipped = false;

    for (int i = 0; i < 4; i++) {
        // Перевіряємо, чи не спилюємо більше ніж довжина ніжки
        if (d[i] > h[i]) {
            cout << "ERROR" << endl;
            return 0;
        }

        h[i] -= d[i]; // Відпилюємо ніжку

        // Перевіряємо, чи стіл не перевертається після цього кроку
        long long mx = *max_element(h, h + 4);
        long long mn = *min_element(h, h + 4);
        if (mx >= 2 * mn) {
            tipped = true;
        }
    }

    long long finalMin = *min_element(h, h + 4);

    // Якщо стіл перевернувся або ніжка відпиляна в нуль
    if (tipped || finalMin == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }

    return 0;
}
