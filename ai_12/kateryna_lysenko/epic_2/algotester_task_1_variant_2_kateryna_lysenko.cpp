
#include <iostream>
using namespace std;

// true, якщо стіл перевертається: hmax >= 2 * hmin
bool tips(long long a, long long b, long long c, long long d) {
    long long mx = a, mn = a;
    if (b > mx) mx = b;
    if (c > mx) mx = c;
    if (d > mx) mx = d;
    if (b < mn) mn = b;
    if (c < mn) mn = c;
    if (d < mn) mn = d;
    return mx >= 2 * mn;
}

int main() {
    long long h1, h2, h3, h4;
    long long d1, d2, d3, d4;
    cin >> h1 >> h2 >> h3 >> h4;
    cin >> d1 >> d2 >> d3 >> d4;

    //Відпилюємо більше, ніж є
    if (d1 > h1 || d2 > h2 || d3 > h3 || d4 > h4) {
        cout << "ERROR" << endl;
        return 0;
    }

    //Відпилюємо по черзі й перевіряємо, чи не перевернувся стіл
    h1 -= d1;
    if (tips(h1, h2, h3, h4)) { cout << "NO" << endl; return 0; }
    h2 -= d2;
    if (tips(h1, h2, h3, h4)) { cout << "NO" << endl; return 0; }
    h3 -= d3;
    if (tips(h1, h2, h3, h4)) { cout << "NO" << endl; return 0; }
    h4 -= d4;
    if (tips(h1, h2, h3, h4)) { cout << "NO" << endl; return 0; }

    //Усі ніжки рівні й не нульові
    if (h1 == h2 && h2 == h3 && h3 == h4 && h1 != 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}