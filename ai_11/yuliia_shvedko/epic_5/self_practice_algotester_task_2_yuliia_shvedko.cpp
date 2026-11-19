#include <iostream>
using namespace std;

int main()
{
    string words;
    int c = 0;
    while(cin >> words)
    {
        int i = 0;
        bool q = true;
        while(i < words.length() - 1)
        {
            if(tolower(words[i]) != tolower(words[words.length() - 1 - i]))
            {
                q = false;
                break;
            }
            i++;
        }
        if(q)
        c++;
    }
    cout << c << endl;
    return 0;
}