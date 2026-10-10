/*
Lab 1 Task 2 Variant 6
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
using namespace std;

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Оголошення початкових змінниї
    int n, m;
    cout << "Введіть початкове значення m: ";
    cin >> m;
    cout << "Введіть початкове значення n: ";
    cin >> n;
    cout << endl;

    // 1) Вираз: m - ++n
    int res1 = m - ++n;
    cout << "Результат 1) m - ++n = " << res1 << endl;

    // 2) Вираз: ++m > --n
    bool res2 = (++m > --n);
    cout << "Результат 2) ++m > --n = " << res2 << endl;

    // 3) Вираз: --n < ++m
    bool res3 = (--n < ++m);
    cout << "Результат 3) --n < ++m = " << res3 << endl;

    return 0;
}