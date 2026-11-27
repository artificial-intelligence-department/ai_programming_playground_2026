/*
Задача:  Примітивна довга арифметика
Автор:   Катерирна Лисенко
Група:   ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;

int main() {

    long long x, n, k;
    cin >> x >> n >> k;

    long long len = n + k - 1;
    long long mn = n < k ? n : k;

    string res;                 
    res.reserve(len + 20);

    long long carry = 0;
    for (long long j = 0; j < len; j++) {
        long long c = j + 1;
        if (len - j < c) c = len - j;   // n+k-1-j
        if (mn < c) c = mn;

        long long cur = x * c + carry;
        res += char('0' + cur % 10);
        carry = cur / 10;
    }
    while (carry > 0) {
        res += char('0' + carry % 10);
        carry /= 10;
    }

    for (long long i = (long long)res.size() - 1; i >= 0; i--)
        cout << res[i];
    cout << "\n";
    return 0;
}