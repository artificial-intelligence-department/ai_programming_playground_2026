#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        long long a;
        cin >> a;

        sum += a - 1;
    }

    cout << sum;
    return 0;
}