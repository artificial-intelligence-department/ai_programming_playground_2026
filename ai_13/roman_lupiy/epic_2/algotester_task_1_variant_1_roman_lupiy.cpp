/*
Задача: lv1
Автор: Роман Лупій
Група: ШІ-13
Варіант: 1
*/
#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    long long h[3], m[3];
    for (int i = 0; i < 3; ++i) {
        cin >> h[i] >> m[i];
    }

    for (int mask = 0; mask < 8; ++mask) {
        long long usedH = 0;
        long long usedM = 0;
        bool possible = true;

        for (int i = 0; i < 3; ++i) {
            if (mask & (1 << i)) {
                // Це заклинання витрачає лише HP.
                if (m[i] != 0) possible = false;
                usedH += h[i];
            } else {
                // Це заклинання витрачає лише ману.
                if (h[i] != 0) possible = false;
                usedM += m[i];
            }
        }

        if (possible && usedH < H && usedM < M) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}