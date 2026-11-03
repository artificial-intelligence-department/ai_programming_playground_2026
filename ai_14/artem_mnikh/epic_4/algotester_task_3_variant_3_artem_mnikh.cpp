#include <iostream>
#include <string>

using namespace std;

int main()
{
    string m;
    cin >> m;
    int n = m.size();

    string result = "";
    int counter = 0;
    char temp = m[0];

    for (int i = 0; i <= n; ++i)
    {
        char x = m[i];
        if (i == n)
        {
            if (m[n - 1] == temp)
            {
                result += temp;
                if (counter != 1) result += to_string(counter);
            }
            else
            {
                result += m[n - 1];
            }

            break;
        }
        if (x == temp)
        {
            counter++;
        }
        else
        {
            result += temp;
            if (counter != 1)
            {
                result += to_string(counter);
                counter = 1;
            }
        }
        temp = x;
    }
    cout << result;
}
