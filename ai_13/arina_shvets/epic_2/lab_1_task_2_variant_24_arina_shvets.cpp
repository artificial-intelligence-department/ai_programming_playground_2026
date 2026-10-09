#include <iostream>

using namespace std;

int main() {
    int n, m, res;

    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть m: ";
    cin >> m;

    // запам'ятовуємо початкові значення
    int n0 = n;
    int m0 = m;

    // 1) n++ * m
    n = n0; m = m0;
    res = n++ * m;
    cout << "1) n++*m  = " << res << ", n = " << n << ", m = " << m << endl;

    // 2) n++ < m
    n = n0; m = m0;
    res = n++ < m;
    cout << "2) n++<m  = " << res << ", n = " << n << ", m = " << m << endl;

    // 3) m-- > m
    n = n0; m = m0;
    res = m-- > m;
    cout << "3) m-- >m = " << res << ", n = " << n << ", m = " << m << endl;

    return 0;
}