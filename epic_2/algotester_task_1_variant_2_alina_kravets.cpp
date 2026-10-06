#include <iostream>

using namespace std;

int main()
{
    long long h1 = 0;
    long long h2 = 0;
    long long h3 = 0;
    long long h4 = 0;
    long long d1 = 0;
    long long d2 = 0;
    long long d3 = 0;
    long long d4 = 0;
    long long hmax = 0;
    long long hmin = 0;

    cin >> h1 >> h2 >> h3 >> h4;
    cin >> d1 >> d2 >> d3 >> d4;

    if (d1 > h1 || d2 > h2 || d3 > h3 || d4 > h4)
    {
        cout << "ERROR";
        return 0;
    }
    
    hmax = h1;
    if (h2 > hmax) hmax = h2;
    if (h3 > hmax) hmax = h3;
    if (h4 > hmax) hmax = h4;

    hmin = h1;
    if (h2 < hmin) hmin = h2;
    if (h3 < hmin) hmin = h3;
    if (h4 < hmin) hmin = h4;

    h1 -= d1;
    hmax = h1;
    if (h2 > hmax) hmax = h2;
    if (h3 > hmax) hmax = h3;
    if (h4 > hmax) hmax = h4;
    hmin = h1;
    if (h2 < hmin) hmin = h2;
    if (h3 < hmin) hmin = h3;
    if (h4 < hmin) hmin = h4;
    if (hmax >= 2*hmin) 
    {
        cout << "NO";
        return 0;
    }

    h2 -= d2;
    hmax = h1;
    if (h2 > hmax) hmax = h2;
    if (h3 > hmax) hmax = h3;
    if (h4 > hmax) hmax = h4;
    hmin = h1;
    if (h2 < hmin) hmin = h2;
    if (h3 < hmin) hmin = h3;
    if (h4 < hmin) hmin = h4;
    if (hmax >= 2*hmin)
    {
        cout << "NO";
        return 0;
    }

    h3 -= d3;
    hmax = h1;
    if (h2 > hmax) hmax = h2;
    if (h3 > hmax) hmax = h3;
    if (h4 > hmax) hmax = h4;
    hmin = h1;
    if (h2 < hmin) hmin = h2;
    if (h3 < hmin) hmin = h3;
    if (h4 < hmin) hmin = h4;
    if (hmax >= 2*hmin)
    {
        cout << "NO";
        return 0;
    }
    
    h4 -= d4;
    hmax = h1;
    if (h2 > hmax) hmax = h2;
    if (h3 > hmax) hmax = h3;
    if (h4 > hmax) hmax = h4;
    hmin = h1;
    if (h2 < hmin) hmin = h2;
    if (h3 < hmin) hmin = h3;
    if (h4 < hmin) hmin = h4;
    if (hmax >= 2*hmin)
    {
        cout << "NO";
        return 0;
    }

    if (h1 == h2 && h2 == h3 && h3 == h4 && hmin > 0) cout << "YES";
    else cout << "NO";
    
    return 0;
}
