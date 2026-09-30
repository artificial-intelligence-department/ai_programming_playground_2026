#include <iostream>
using namespace std;

int main() {
    int m, n;
    cout << "введіть m" << endl;
    cin >> m;
    cout << "введіть n" << endl;
    cin >> n;

    // Збереження початкових значень для відновлення перед кожним виразом
    int m0 = m;
    int n0 = n;

    // Обчислення виразу з префіксним декрементом n (спочатку n зменшується на 1, потім додається до m)
    int result = m + (--n);
    cout << "результати виразу " << result << endl;
    cout << "new m=" << m << endl;
    cout << "new n=" << n << endl;

    // Відновлення початкових значень
    m = m0;
    n = n0;

    // Фраза 1: перевірка постфіксного інкременту m та префіксного інкременту n
    // Порівнюється поточне m з вже збільшеним (n + 1), після порівняння m збільшується на 1
    bool phraze1 = (m++ < ++n);
    cout << "phraze1 m=" << m << endl;
    cout << "phraze1 n=" << n << endl;

    // Відновлення початкових значень
    m = m0;
    n = n0;

    // Фраза 2: перевірка постфіксного декременту n та префіксного декременту m
    // Порівнюється поточне n з вже зменшеним (m - 1), після порівняння n зменшується на 1
    bool phraze2 = (n-- < --m);
    cout << "phraze2 m=" << m << endl;
    cout << "phraze2 n=" << n << endl;

    // Виведення результатів булевих виразів (true/false)
    cout << boolalpha << "phraze1 = " << phraze1 << endl;
    cout << boolalpha << "phraze2 = " << phraze2 << endl;

    return 0;
}