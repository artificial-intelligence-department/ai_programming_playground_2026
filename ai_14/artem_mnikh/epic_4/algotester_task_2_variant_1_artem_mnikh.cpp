#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int* el = new int[n];
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; ++i) cin >> el[i];
    int min1 = 100001, min2 = 10001, max1 = -1, max2 = -1;
    for (int i = 0; i < n; ++i)
    {
        if (min1 >= el[i])
        {
            min2 = min1;
            min1 = el[i];
        }
        else if (min2 > el[i])
        {
            min2 = el[i];
        }
        if (max1 <= el[i])
        {
            max2 = max1;
            max1 = el[i];
        }
        else if (max2 < el[i])
        {
            max2 = el[i];
        }
    }
    if (min2 - min1 > max1 - max2)
    {
        cout << max1 - min2;
    }
    else
    {
        cout << max2 - min1;
    }
    delete[] el;
    el = nullptr;
}
