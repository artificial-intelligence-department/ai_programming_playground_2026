//Математична задача
#include <iostream>

using namespace std;

// перевірка чи можемо дойти до 1
bool can1(long long x) {
    if (x == 2 || x == 9) return false;
    long long rem = x % 7;
    return (rem == 1 || rem == 2 || rem == 4);
}

int main() {
    long long n;
    if (!(cin >> n)) return 0;

    if (!can1(n)) {
        cout << -1 << endl;
        return 0;
    }

    long long steps = 0;

    while (n > 1) {
        if (n % 4 == 0 && can1(n / 4)) {
            n /= 4;
            steps++;
        } else {
            n -= 7;
            steps++;
        }
    }

    cout << steps << endl;
    return 0;
}