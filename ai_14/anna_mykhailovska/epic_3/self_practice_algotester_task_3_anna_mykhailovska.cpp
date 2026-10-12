/*
    Задача: НСК
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
using namespace std;

long long nsd(long long a, long long b) {
    if (b == 0) {
        return a;
    }

    return nsd(b, a % b);
}

long long nsk(long long a, long long b, long long c) {
    long long first = a / nsd(a, b) * b;
    long long result = first / nsd(first, c) * c;

    return result;
}

int main() {
    long long a, b, c;
    cin >> a >> b >> c;

    long long answer = nsk(a, b, c);

    cout << answer << '\n';

    return 0;
}

