/*
Завдання: Фарбування паркану
*/
#include <iostream>

using namespace std;

int main() {
    long long n, b, y;
    if (!(cin >> n >> b >> y)) return 0;

    if (n < 1 || b < 1 || b > 1000000000 || y < 1 || y > 1000000000) {
        cout << "Не коректне значення";
        return 0;
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    long long lim = n - 1;
    long long cb = lim / b;
    long long cy = lim / y;
    long long temp_b = b;
    long long temp_y = y;

    while (temp_y != 0) {
        long long temp = temp_y;
        temp_y = temp_b % temp_y;
        temp_b = temp;
    }
    long long g = temp_b;

    long long lcm = b / g * y;

    long long cp = (lcm <= lim) ? (lim / lcm) : 0;
    long long ans = cb + cy - cp;

    cout << ans << "\n";

    return 0;
}