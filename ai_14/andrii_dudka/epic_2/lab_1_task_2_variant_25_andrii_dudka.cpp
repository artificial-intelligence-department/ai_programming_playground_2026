#include <iostream>
using namespace std;

int main() {
    cout << boolalpha;

    int a, b; // Початкові значення
    cout << "Введіть m і n від -10000 до 10000: \n";
    if (!(cin >> a >> b)) return 1;
    if (a < -10000 || a > 10000 || b < -10000 || b > 10000) return 1;

    // 1. Префіксні операції
    int m = a, n = b;
    int r1 = --m - ++n;
    cout << "1) " << r1 << "; m = " << m << "; n = " << n << '\n';

    // 2. Виправлений вираз
    // m*n < n++: невизначена поведінка
    m = a;
    n = b;
    bool r2 = m * n < n;
    n++;
    cout << "2) Виправлений варіант: " << r2
         << "; m = " << m << "; n = " << n << '\n';

    // 3. Постфіксні операції
    m = a;
    n = b;
    bool r3 = n-- > m++;
    cout << "3) " << r3 << "; m = " << m << "; n = " << n << '\n';

    return 0;
}
