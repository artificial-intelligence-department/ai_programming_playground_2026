#include <iostream>
int main()
{
    long long h, m;
    using namespace std;
    cin >> h;
    cin >> m;
    if ((h <= 0 || h > 1000000000000) || (m <= 0 || m > 1000000000000))
    {
        cout << "NO";
        return 0;
    }
    long long h1, m1;
    long long h2, m2;
    long long h3, m3;
    cin >> h1;
    cin >> m1;
    cin >> h2;
    cin >> m2;
    cin >> h3;
    cin >> m3;

    if ((h1 > 0 && m1 > 0) || (h2 > 0 && m2 > 0) || (h3 > 0 && m3 > 0))
    {
        cout << "NO";
        return 0;
    }
    h = h - h1 - h2 - h3;
    m = m - m1 - m2 - m3;
    if ((h <= 0) || (m <= 0))
    {
        cout << "NO";
    }
    else
    {
        cout << "YES";
    }
}
