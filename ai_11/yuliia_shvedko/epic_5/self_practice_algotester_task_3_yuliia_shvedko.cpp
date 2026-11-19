#include <iostream>
using namespace std;
int main()
{
    long long n, m;
    cin >> n >> m;
    long long s4 = 0;
    long long s7 = 0;
    long long t4 = 0;
    long long t7 = 0;
    char *s = new char[n];
    for(long long i = 0; i < n; i++)
    {
        cin >> s[i];
        if(s[i] == '4')
        s4++;
        else if(s[i] == '7')
        s7++;
    }
    char *t = new char[m];
    for(long long i = 0; i < m; i++)
    {
        cin >> t[i];
        if(t[i] == '4')
        t4++;
        else if(t[i] == '7')
        t7++;
    }
    long long r = (n + 1)*(m + 1) - 1;
    long long d = (s4 * t4) + (s7 * t7);
    r = r - d;
    cout << r << endl;
    delete[] s;
    delete[] t;
    return 0;
}