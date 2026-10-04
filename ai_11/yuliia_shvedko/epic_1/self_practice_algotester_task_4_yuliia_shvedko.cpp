/*"Білка на дереві"
Автор: Шведько Юлія
Група: ШІ-11*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float h;
    float H;
    float s;

    cin >> h >> H >> s;

    float l = sqrt(pow(h, 2) + pow(s, 2));
    float r = (H / h)*l;

    cout << r << endl;
    return 0;
}