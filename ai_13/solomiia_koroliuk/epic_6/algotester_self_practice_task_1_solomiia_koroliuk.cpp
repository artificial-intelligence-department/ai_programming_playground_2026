#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

struct Exchange {
    int k;
    int a[MAXN];
    int b[MAXN];

    // Перевіряє, чи загальна сума відданих яблук (a) дорівнює загальній сумі отриманих (b)
    bool operator==(int) const {
        long long sumA = 0, sumB = 0;
        for (int i = 0; i < k; i++) {
            sumA += a[i];
            sumB += b[i];
        }
        return sumA == sumB;
    }

    bool canSolve() {

        if (!(*this == 0)) {
            return false;
        }

        // c[i] — скільки людей віддали хоча б i яблук
        int c[MAXN + 2] = {0};
        for (int i = 0; i < k; i++) {
            c[a[i]]++;
        }
        for (int i = k - 1; i >= 0; i--) {
            c[i] += c[i + 1];
        }

        // Сортуємо b за спаданням
        sort(b, b + k, greater<int>());

        // Перевіряємо на кожному кроці, чи вистачає яблук
        long long cur = 0;
        for (int i = 1; i <= k; i++) {
            cur += c[i] - b[i - 1];
            if (cur < 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Exchange ex;
    cin >> ex.k;

    for (int i = 0; i < ex.k; i++) cin >> ex.a[i];
    for (int i = 0; i < ex.k; i++) cin >> ex.b[i];

    if (ex.canSolve()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}