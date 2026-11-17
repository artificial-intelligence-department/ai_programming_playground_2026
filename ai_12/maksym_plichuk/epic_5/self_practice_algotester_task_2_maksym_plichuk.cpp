#include <iostream>
#include <string>

using namespace std;

int main() {

    long n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    long s4 = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i]=='4') {
            s4++;
        }
    }
    long s7 = n - s4;

    long t4 = 0;
    for (int i = 0; i < t.length(); i++)
    {
        if (t[i]=='4') {
            t4++;
        }
    }
    long t7 = m - t4;

    long total = (n + 1) * (m + 1) - 1;
    long duplicates = s4 * t4 + s7 * t7;

    cout << total - duplicates << endl;

    return 0;
}
