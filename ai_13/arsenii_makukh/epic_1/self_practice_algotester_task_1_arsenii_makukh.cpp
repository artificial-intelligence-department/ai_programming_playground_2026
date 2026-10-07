/*
Назва: Lab 1v1
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long h, h1, h2, h3, m, m1, m2, m3;
    const long max_number = pow(10, 12);

    cout << "Введіть кількість хітпойнтів: ";
    cin >> h;

    cout << "Введіть кількість мани: ";
    cin >> m;

    cout << "Введіть кількість хітпойнтів у першому заклятті: ";
    cin >> h1;

    cout << "Введіть кількість мани у першому заклятті: ";
    cin >> m1;

    cout << "Введіть кількість хітпойнтів у другому заклятті: ";
    cin >> h2;

    cout << "Введіть кількість мани у другому заклятті: ";
    cin >> m2;

    cout << "Введіть кількість хітпойнтів у третьому заклятті: ";
    cin >> h3;

    cout << "Введіть кількість мани у третьому заклятті: ";
    cin >> m3;

    if ( h < 1 || h > max_number || m < 1 || m > max_number ||
        h1 < 0 || m1 < 0 || h1 > max_number || m2 > max_number || 
        h2 < 0 || m2 < 0 || h2 > max_number || m2 > max_number ||
        h3 < 0 || m3 < 0 || h3 > max_number || m3 > max_number ||
        m1 != 0 && h1 != 0 || m2 != 0 && h2 != 0 || m3 != 0 && h3 != 0 )
    {
        cout << "NO" << endl;
        return 0;
    }

    else if ( (h1 + h2 + h3) < h && (m1 + m2 + m3) < m )
    {
        cout << "YES" << endl;
        return 0;
    }

    else 
    {
        cout << "NO" << endl;
        return 0;
    }

    return 0;
}
