//Примітивна довга арифметика
#include <iostream>

using namespace std;

struct BigInt {
    int d[1000015];
    int len = 0;

    void solve(int x, int n, int k) {
        long long count = 0, carry = 0;

        for (int p = 0; p < n + k - 1; ++p) {
            if (p < k) count++;   // починається новий доданок
            if (p >= n) count--;  // закінчується один зі старих

            carry += count * x;
            d[len++] = carry % 10;
            carry /= 10;
        }

        while (carry > 0) {
            d[len++] = carry % 10;
            carry /= 10;
        }
    }

    void print() {
        for (int i = len - 1; i >= 0; --i)
            cout << d[i];
    }
} ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n, k;
    cin >> x >> n >> k;

    ans.solve(x, n, k);
    ans.print();
}