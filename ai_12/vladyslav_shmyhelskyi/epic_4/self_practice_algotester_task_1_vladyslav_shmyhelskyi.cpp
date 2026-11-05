#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int length = s.length();
    char password[length];
    if (s.length() > 10 || s.length() <= 0)
    {
        return 0;
    }
    char letters[length];
    for (int i = 0; i < s.length(); i++)

    {
        letters[i] = s[i];
    }
    password[0] = letters[0];
    int start = 1;
    int end = length - 1;
    for (int i = 1; i < length; i++)
    {
        int rest = i % 2;
        if (rest == 0)
        {
            password[i] = letters[start];
            start++;
        }
        else
        {
            password[i] = letters[end];
            end--;
        }
    }

    for (int i = 0; i < s.length(); i++)
    {
        cout << password[i];
    }
    return 0;
}
