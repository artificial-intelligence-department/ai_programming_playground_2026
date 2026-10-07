#include <iostream>
using namespace std;
int main()
{
    long long h[4];
    for (int i = 0; i < 4; i++)
    {
        cin >> h[i];
        if (h[i] < 0 || h[i] > 1000000000000)
        {
            return 0;
        }
    }
    long long d[4];
    for (int i = 0; i < 4; i++)
    {
        cin >> d[i];
        if (d[i] < 0 || d[i] > 1000000000000)
        {
            return 0;
        }
    }

    long long maxh = h[0];
    long long minh = h[0];
    for (int i = 0; i < 4; i++)
    {
        if (h[i] < d[i])
        {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    bool isStand = true;

    for (int i = 0; i < 4; i++)
    {

        h[i] = h[i] - d[i];
        maxh = h[0];
        minh = h[0];

        for (int j = 0; j < 4; j++)
        {
            if (h[j] > maxh)
            {
                maxh = h[j];
            }

            if (h[j] < minh)
            {
                minh = h[j];
            }
            if (maxh >= 2 * minh)
            {
                isStand = false;
            }
        }
    }

    bool allEqual = false;
    if ((h[0] == h[1]) && (h[1] == h[2]) && (h[2] == h[3]))
    {
        allEqual = true;
    }
    bool notZero = (h[0] != 0) == true;

    if (isStand && allEqual && notZero == true)
    {

        cout << "YES" << endl;
    }
    else
    {

        cout << "NO" << endl;
    }
}
