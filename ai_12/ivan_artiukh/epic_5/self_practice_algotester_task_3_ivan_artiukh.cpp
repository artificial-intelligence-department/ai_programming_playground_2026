//фібонета
#include <iostream>
using namespace std;

char get_sign(long long x) {
    if (x > 0) return '+';
    if (x < 0) return '-';
    return '0';
}

int main() {
long long n, a0, a1;
    if (!(cin >> n >> a0 >> a1)) return 0;

    if (n == 0) {
        cout << get_sign(a0) << "\n";
        return 0;
    }
    if (n == 1) {
        cout << get_sign(a1) << "\n";
        return 0;
    }

    for (long long i = 2; i <= n; i++) {
        if (a0 == 0 && a1 == 0) {
            cout << "0\n";
            return 0;
        }
        if (a0 >= 0 && a1 >= 0) {
            cout << "+\n";
            return 0;
        }
        if (a0 <= 0 && a1 <= 0) {
            cout << "-\n";
            return 0;
        }

        long long a2 = a0 + a1;
        a0 = a1;
        a1 = a2;
    }

    cout << get_sign(a1) << "\n";
    return 0;
}