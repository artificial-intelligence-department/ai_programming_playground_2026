#include <iostream>
using namespace std;

// Painting: кількість змін кольору на паркані довжиною n
// Blue-шар: межі в точках k*b, yellow-шар: межі в точках k*y.
// Колір змінюється в точці x (1 <= x <= n-1), якщо змінився стан хоча б одного шару.
// Кількість таких точок: floor(m/b) + floor(m/y) - floor(m/L), де m = n-1, L = НСК(b, y).

long long gcdLL(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    long long n, b, y;
    cin >> n >> b >> y;

    long long m = n - 1;                 // межі можуть бути лише між клітинками
    long long g = gcdLL(b, y);           // найбільший спільний дільник
    long long L = (b / g) * y;           // найменше спільне кратне (НСК)

    long long answer = m / b + m / y - m / L;
    cout << answer << endl;
    return 0;
}
