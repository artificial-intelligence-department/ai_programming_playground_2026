#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    bool ok = true;

    for (int i = 0; i < 3; i++) {
        long long h, m;
        cin >> h >> m;

        if (h > 0 && m > 0) {
            ok = false;
        }

        H -= h;
        M -= m;
    }

    if (ok && H > 0 && M > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}