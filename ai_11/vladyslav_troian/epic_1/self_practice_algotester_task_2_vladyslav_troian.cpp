#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int k = 0;
    int v = 0;
    int vicK = 0;
    int vicV = 0;

    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;

        if (c == 'K')
            k++;
        else
            v++;

        if (k >= 11 && k >= v + 2)
        {
            vicK++;
            k = 0;
            v = 0;
        }
        else if (v >= 11 && v >= k + 2)
        {
            vicV++;
            k = 0;
            v = 0;
        }
    }

    cout << vicK << ":" << vicV << endl;

    if (k != 0 || v != 0)
        cout << k << ":" << v << endl;

    return 0;
}