#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    bool is_ok = true;

    for (int i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;

        // Перевіряємо саме витрати даного заклинання:
        if (h > 0 && m > 0) {
            is_ok = false;
        }
        H = H - h;
        M = M - m;
    }

    if (is_ok && H > 0 && M > 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}