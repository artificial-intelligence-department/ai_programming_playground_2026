/*Дракон і голод
0102 */
#include <iostream>
using namespace std;

bool check(long long n, long long m, long long s) {
    if (s < ((n + 1) / 2) * m) {
        return false;
    }

    if (n == 1 && s != m) {
        return false;
    }

    if (n == 2 && s > 2 * m) {
        return false;
    }

    return true;
}

void printSequence(long long n, long long m, long long s) {
    if (n == 1) {
        cout << m;
        return;
    }

    if (n == 2) {
        cout << s - m << " " << m;
        return;
    }

    long long need = (n + 1) / 2;
    long long extra = s - need * m;

    for (int i = 0; i < n - need; i++) {
        cout << 0 << " ";
    }

    for (int i = 0; i < need; i++) {
        if (i == 0) {
            cout << m + extra << " ";
        } else {
            cout << m << " ";
        }
    }
}

int main() {
    long long n, m, s;
    cin >> n >> m >> s;

    if (!check(n, m, s)) {
        cout << -1;
        return 0;
    }

    printSequence(n, m, s);

    return 0;
}