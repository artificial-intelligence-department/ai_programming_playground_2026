// "Сортування"
#include <iostream>
using namespace std;

void swapNumbers(int &a, int &b)
{
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
}
int main()
{
    int a[10000];
    int n = 0;
    int x;
    while (cin >> x)
    {
        if (n >= 10000 || x < 0 || x > 50000)
        {
            return 0;
        }
        a[n] = x;
        n++;
    }
    if (n < 1)
    {
        return 0;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            swapNumbers(a[j], a[j + 1]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}