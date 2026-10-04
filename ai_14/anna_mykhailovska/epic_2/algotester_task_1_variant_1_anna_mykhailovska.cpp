/*
    Algotester lab 1
    Михайловська Анна
    ШІ-14
    Варіант 1
*/
#include <iostream>
using namespace std;

int main() {
    long long H, M;
    cin >> H >> M;

    long long spentH = 0, spentM = 0;
    bool valid = true;

    for (int i = 0; i < 3; ++i) {
        long long h, m;
        cin >> h >> m;

        if (h > 0 && m > 0) valid = false;
        spentH += h;
        spentM += m;
    }

    cout << (valid && spentH < H && spentM < M ? "YES" : "NO") << '\n';
    return 0;
}