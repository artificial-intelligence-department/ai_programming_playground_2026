/*
 * Lab 1v1
 * Автор: Illia Strazhets
 * Група: AI-13
 */
#include <iostream>
using namespace std;

int main()
{
    long long H, M;
    long long h1, m1, h2, m2, h3, m3;

    if (!(cin >> H >> M >> h1 >> m1 >> h2 >> m2 >> h3 >> m3))
        return 0;

    // 1. Перевірка: заклинання не повинно забирати і HP, і ману одночасно
    if ((h1 > 0 && m1 > 0) || (h2 > 0 && m2 > 0) || (h3 > 0 && m3 > 0))
    {
        cout << "NO";
        return 0;
    }

    // 2. Обчислення загальної кількості HP та мани, які будуть витрачені на заклинання
    long long total_h = h1 + h2 + h3;
    long long total_m = m1 + m2 + m3;

    // 3. Перевірка: в кінці і HP, і мани має бути суворо більше 0
    if ((H - total_h > 0) && (M - total_m > 0))
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    return 0;
}