#include <iostream>

using namespace std;

struct SixFreeCounter {

    // Перевіряє, чи не містить число x цифри 6
    bool hasNoSix(long long x) const {
        if (x == 0) return true;
        while (x > 0) {
            if (x % 10 == 6) return false;
            x /= 10;
        }
        return true;
    }

    // F(n) — кількість чисел у півінтервалі [0, n) без цифри 6
    long long F(long long n) const {
        if (n <= 0) return 0;

        long long prefix = n / 10;
        long long base = prefix * 10;

        // 9 * F(prefix) — усі числа < 10 * prefix без цифри 6
        long long total = 9 * F(prefix);

        // Додаємо числа без цифри 6 у хвості [10 * prefix, n)
        for (long long x = base; x < n; x++) {
            if (hasNoSix(x)) {
                total++;
            }
        }

        return total;
    }

    
    long long countInRange(long long a, long long b) const {
        return F(b + 1) - F(a);
    }
};

int main() {

    long long a, b;
    if (cin >> a >> b) {
        SixFreeCounter solver;
        cout << solver.countInRange(a, b) << "\n";
    }

    return 0;
}