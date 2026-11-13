// Щасливі рядки

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n, m;
    string s, t;
    cin >> n >> m;
    cin >> s >> t;

    long long sFour = 0;
    long long sSeven = 0;
    long long tFour = 0;
    long long tSeven = 0;
    int len;
    if (n > m)
    {
        len = n;
    }
    else
    {
        len = m;
    }
    for (int i = 0; i < len; i++)
    {
        if (i < n)
        {
            if (s[i] == '4')
            {
                sFour++;
            }
            else
            {
                sSeven++;
            }
        }

        if (i < m)
        {
            if (t[i] == '4')
            {
                tFour++;
            }
            else
            {
                tSeven++;
            }
        }
    }
    long long result = (long long)(n + 1) * (m + 1) - 1;
    result = result - sFour * tFour - sSeven * tSeven;
    cout << result << endl;
    return 0;
}