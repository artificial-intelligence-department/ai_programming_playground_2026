/*Epic 2 - Завдання 2 лабораторної 1 варіант 6
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main() {

    int m, n; 
    m = 10, n = 10;
    int res1 = m - ++n;  // Спочатку виконується ++n, n стає 11, m - n = -1
    cout << "1) m - ++n = " << res1 << endl;

    m = 10; n = 10;
    bool res2 = (++m > --n);  // m стає 11, n стає 9, 11 > 9, true, 1
    cout << "2) ++m > --n = " << res2 << endl;

    m = 10; n = 10;
    bool res3 = (--n < ++m);  // n стає 9, m стає 11, 9 < 11, true, 1
    cout << "3) --n < ++m = " << res3 << endl;

    return 0;
}
