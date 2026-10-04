// Глова Данило ШІ-14
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cout << "Введіть початкове значення n: ";
    cin >> n;
    cout << "Введіть початкове значення m: ";
    cin >> m;

    // 1) n+++m (n++) + m
    int res1 = n++ + m;
    cout << "1) Результат n+++m : " << res1 << endl;
    cout << "   Значення змінних після 1-ї дії: n = " << n << ", m = " << m << endl;

    // 2) m-- > n  (m--) > n
    bool res2 = m-- > n;
    cout << "2) Результат m-- > n : " << res2  << endl;
    cout << "   Значення змінних після 2-ї дії: n = " << n << ", m = " << m << endl;

    // 3) n-- > m (n--) > m
    bool res3 = n-- > m;
    cout << "3) Результат n-- > m : " << res3  << endl;
    cout << "   Значення змінних після 3-ї дії: n = " << n << ", m = " << m << endl;

    return 0;
}