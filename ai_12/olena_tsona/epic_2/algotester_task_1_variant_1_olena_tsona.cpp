#include <iostream>

using namespace std;

int main() {

    long long H, M;
    cin >> H >> M;

    bool correct = true;

    for (int i = 0; i < 3; ++i) {
        long long h, m;
        cin >> h >> m;

        if (h > 0 && m > 0) {
            correct = false;
        }

        H -= h;
        M -= m;
    }

    if (correct && H > 0 && M > 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}