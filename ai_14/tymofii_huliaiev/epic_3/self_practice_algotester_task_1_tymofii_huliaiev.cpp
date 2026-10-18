#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    int p = 0;
    // Збільшуємо p, поки 2^p <= n (тобто поки не покриємо n)
    while ((1LL << p) <= n) {
        p++;
    }

    cout << p << endl;

    return 0;
}