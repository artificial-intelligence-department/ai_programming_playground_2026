#include <iostream>

using namespace std;

int main() {
    int n = 5;
    int m = 3;

    cout << "Початкові значення: n = " << n << ", m = " << m << endl << endl;

    // 1) n++-m
    cout << "1) n++-m: " << (n++ - m) << endl;
    cout << "Після операції: n = " << n << ", m = " << m << endl << endl;

    // Скидаємо значення назад до початкових
    n = 5;
    m = 3;

    // 2) m-- > n
    cout << "2) m-- > n: " << (m-- > n) << endl;
    cout << "Після операції: n = " << n << ", m = " << m << endl << endl;

    // Скидаємо значення назад до початкових
    n = 5;
    m = 3;

    // 3) n-- > m
    cout << "3) n-- > m: " << (n-- > m) << endl;
    cout << "Після операції: n = " << n << ", m = " << m << endl;

    return 0;
}