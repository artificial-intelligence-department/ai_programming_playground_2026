#include <iostream>

using namespace std;

int main() {
    long long H, M;

    if (!(cin >> H >> M)) return 0;

    for (int i = 0; i < 3; ++i) {
        long long h, m;
        cin >> h >> m;

        if (h > 0 && m > 0) {
            cout << "NO" << endl;
            return 0;
        }

        H -= h;
        M -= m;
    }

    if (H > 0 && M > 0) {
        cout << "YES" << endl;

    } else {
        cout << "NO" << endl;
    }

    return 0;
}