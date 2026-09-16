#include <iostream>

using namespace std;

int main()
{
    long long H, M;

    cin >> H;
    cin >> M;

    long long h1, m1;
    long long h2, m2;
    long long h3, m3;

    cin >> h1;
    cin >> m1;

    cin >> h2;
    cin >> m2;

    cin >> h3;
    cin >> m3;

    bool incorrectSpell =
        (h1 > 0 && m1 > 0) ||
        (h2 > 0 && m2 > 0) ||
        (h3 > 0 && m3 > 0);

    H = H - h1 - h2 - h3;
    M = M - m1 - m2 - m3;

    if (!incorrectSpell && H > 0 && M > 0)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }

    return 0;
}
