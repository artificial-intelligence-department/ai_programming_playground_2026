#include <iostream>
using namespace std;

int main() {
    int n = 0;
    int m = 0;

    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть m: ";
    cin >> m;

    // n++ використовує поточне значення n, а потім збільшує його на 1.
    int res1 = n++ + m;
    cout << "1) n++ + m = " << res1 << endl;
    cout << "n = " << n << ", m = " << m << endl;

    // Порівнюємо поточне m з n, після цього зменшуємо m на 1.
    bool res2 = m-- > n;
    cout << "2) m-- > n = " << res2 << endl;
    cout << "n = " << n << ", m = " << m << endl;

    // Порівнюємо поточне n з m, після цього зменшуємо n на 1.
    bool res3 = n-- > m;
    cout << "3) n-- > m = " << res3 << endl;
    cout << "n = " << n << ", m = " << m << endl;

    return 0;
}
