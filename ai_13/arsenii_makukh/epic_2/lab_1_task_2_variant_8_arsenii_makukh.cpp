/*
    Назва: Lab 1 Task 2 Variant 8
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>

using namespace std;

/*
    1) n++-m
    2) m-- >n
    3) n-- >m
*/

int main() {
    int n, m;
    cin >> n >> m;

    int a_1 = (n++-m);
    cout << "1) n++-m = " << a_1 << ", n=" << n << ", m=" << m << endl;

    bool a_2 = (m-- > n);
    cout << "2) m-- >n = " << a_2 << ", m=" << m << ", n=" << n << endl;

    bool a_3 = (n-- > m);
    cout << "3) n-- >m = " << a_3 << ", n=" << n << ", m=" << m << endl;

    return 0;
}