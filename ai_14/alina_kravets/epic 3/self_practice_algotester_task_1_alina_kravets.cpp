/*Існує дві дороги: одна пряма, а інша...
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long n = 0;
    long long length = 0;
    long x1 = 0;
    long y1 = 0;
    long x2 = 0;
    long y2 = 0;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        length += sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
    }

    cout << length;

    return 0;
}
