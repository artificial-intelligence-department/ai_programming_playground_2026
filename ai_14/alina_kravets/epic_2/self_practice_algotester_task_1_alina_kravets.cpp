#include <iostream>

using namespace std;

int main()
{
    long long n = 0;
    long long a = 0;
    long long cookies = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a;
        a--;
        cookies += a;
    }
    cout << cookies;
    return 0;
}
