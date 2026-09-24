#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

int main() {
    long long n, b, y;
    cin >> n >> b >> y;

    long long x = n - 1;

    long long g = gcd(b, y);
    long long lcm = b / g * y;

    long long answer = x / b + x / y - x / lcm;

    cout << answer << '\n';

    return 0;
}