// 1806

#include <iostream>
#include <string>

using namespace std;

long long compareDNA(const string& a, const string& b)
{
    if (a.size() < b.size()) return 0;

    long long result = 0;
    int window_len = (int)a.size() - (int)b.size() + 1;

    int count[26] = {0};
    for (int j = 0; j < window_len; ++j)
    {
        count[a[j] - 'a']++;
    }

    for (int i = 0; i < (int)b.size(); ++i)
    {
        result += 1LL * count[b[i] - 'a'] * (i + 1);

        if (i + window_len < (int)a.size())
        {
            count[a[i] - 'a']--;
            count[a[i + window_len] - 'a']++;
        }
    }

    return result;
}

int main()
{
    string t, s;
    if (cin >> t >> s)
    {
        cout << compareDNA(t, s) << "\n";
    }
    return 0;
}
