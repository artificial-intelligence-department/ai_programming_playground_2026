// "Найбільша пара"
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
int sumNumbers(int a, int b)
{
    int sum;
    sum = a + b;
    return sum;
}
int main()
{
    int n;
    if (!(cin >> n) || n < 2 || n > 1000 || n % 2 != 0)
    {
        return 0;
    }
    int a[1000];
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> a[i]) || a[i] < 1 || a[i] > 1000000000)
        {
            return 0;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            swapNumbers(a[j], a[j + 1]);
        }
    }
    int sumMax = -1;
    for (int i = 0; i < n / 2; i++)
    {
        int sumDigits = sumNumbers(a[i], a[n - 1 - i]);
        if (sumDigits > sumMax) {
            sumMax = sumDigits;
        }
    }
    cout << sumMax << endl;
    return 0;
}