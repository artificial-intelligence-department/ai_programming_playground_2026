#include <iostream>

using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    long long h1, m1, h2, m2, h3, m3;
    cin >> h1 >> m1;
    cin >> h2 >> m2;
    cin >> h3 >> m3;

    // Якщо хоч одне закляття забирає І хитпоінти, І ману одночасно — поразка
    if ((h1 > 0 && m1 > 0) || (h2 > 0 && m2 > 0) || (h3 > 0 && m3 > 0)) {
        cout << "NO" << endl;
        return 0;
    }

    // Віднімаємо витрати
    H = H - h1 - h2 - h3;
    M = M - m1 - m2 - m3;

    // В кінці хитпоінти та мана мають бути СУВОРO більше 0 (> 0)
    if (H > 0 && M > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}