#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    long long sum = 0;
    long long a;

    for (int i = 0; i < n; i++)
    {
        cin >> a;

        if (a > 0)
        {
            sum = sum + a - 1;
        }
    }

    cout << sum << "\n";

    return 0;
}