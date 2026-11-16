// 0835

#include <iostream>
#include <string>

using namespace std;

string toLower(string s)
{
    for (int i = 0; i < (int)s.size(); ++i) s[i] = tolower(s[i]);
    return s;
}

bool isPallindrome(string s)
{
    int i = 0;
    int j = (int)s.size() - 1;
    while (i < j)
    {
        if (s[i++] != s[j--]) return false;
    }

    return true;
}

int main()
{
    string word;
    int result = 0;
    while (cin >> word) result += (int)isPallindrome(toLower(word));
    cout << result;
}
