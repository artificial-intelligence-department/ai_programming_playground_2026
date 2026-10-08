#include <iostream>

using namespace std;

int main() {
    int n, m;

    // Обчислення виразу: n++ - m
    n = 10;
    m = 20;
    int res1 = n++ - m;

    // Обчислення виразу: m-- > n++
    n = 10;
    m = 20;
    bool res2 = m-- > n++;

    // Обчислення виразу: n-- > --m
    n = 10;
    m = 20;
    bool res3 = n-- > --m;

    // Вивід результатів
    cout << "n++ - m = " << res1 << endl;
    cout << "m-- > n++ = " << (res2 ? "true" : "false") << endl;
    cout << "n-- > --m = " << (res3 ? "true" : "false") << endl;

    return 0;
}