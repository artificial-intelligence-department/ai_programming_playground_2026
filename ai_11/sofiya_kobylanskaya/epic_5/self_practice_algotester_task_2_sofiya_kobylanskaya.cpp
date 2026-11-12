// Снігурочка

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string word;
    int count = 0;

    while (cin >> word)
    {
        bool palindrome = true;
        int len = word.length();
        for (int i = 0; i < len / 2; i++)
        {
            char left = tolower(word[i]);
            char right = tolower(word[len - 1 - i]);

            if (left != right)
            {
                palindrome = false;
                break;
            }
        }
        if (palindrome)
        {
            count++;
        }
    }
    cout << count << endl;

    return 0;
}