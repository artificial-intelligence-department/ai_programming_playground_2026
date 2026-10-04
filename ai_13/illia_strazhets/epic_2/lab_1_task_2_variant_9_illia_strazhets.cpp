/*
 * Лабораторна робота №1
 * Задача: 2, варіант: 9
 * Автор: Illia Strazhets
 * Група: AI-13
 */

/*
Обчислити вирази:
1) ++n*++m
2) m++ < n
3) n++ > m
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // Введення значень m та n
    int m_orig, n_orig;
    cout << "Введіть значення m: ";
    cin >> m_orig;
    cout << "Введіть значення n: ";
    cin >> n_orig;

    // Обчислення 1) ++n * ++m
    int m = m_orig;
    int n = n_orig;
    int result1 = ++n * ++m;
    cout << "1) ++n * ++m = " << result1 << " (n = " << n << ", m = " << m << ")" << endl;

    // Обчислення 2) m++ < n

    // Повертаємо m та n до початкових значень
    m = m_orig;
    n = n_orig;
    bool result2 = m++ < n;
    cout << "2) m++ < n = " << boolalpha << result2 << " (m = " << m << ", n = " << n << ")" << endl;

    // Обчислення 3) n++ > m

    // Повертаємо m та n до початкових значень
    m = m_orig;
    n = n_orig;
    bool result3 = n++ > m;
    cout << "3) n++ > m = " << boolalpha << result3 << " (n = " << n << ", m = " << m << ")" << endl;
    return 0;
}