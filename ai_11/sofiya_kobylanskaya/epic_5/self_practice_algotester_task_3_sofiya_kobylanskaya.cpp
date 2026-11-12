// Буквозабирання

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++)
    {
        string s, t;
        cin >> s >> t;
        int n = s.length();
        int m = t.length();
        int moves = n - m;
        int middle = moves / 2;
        bool win = false;

        if (moves % 2 == 1)
        {
            if (s.substr(middle, m) == t && s.substr(middle + 1, m) == t)
            {
                win = true;
            }
        }
        else
        {
            if (s.substr(middle, m) == t)
            {
                win = true;
            }
            else if (middle > 0)
            {
                if (s.substr(middle - 1, m) == t && s.substr(middle + 1, m) == t)
                {
                    win = true;
                }
            }
        }
        if (win)
        {
            cout << "Sergei" << endl;
        }
        else
        {
            cout << "Larry" << endl;
        }
    }

    return 0;
}