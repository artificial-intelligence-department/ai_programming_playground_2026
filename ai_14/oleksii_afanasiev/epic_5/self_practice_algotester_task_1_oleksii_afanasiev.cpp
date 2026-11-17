/*
Задача: Снігурочка (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string word)
{
    int len = word.length();

    for(int i = 0; i < len / 2; i++)
    {
        if(tolower(word[i]) != tolower(word[len - i - 1])) return false;
    }

    return true;
}

int main()
{
    string s;
    int count = 0;

    while(cin >> s)
    {
        if(isPalindrome(s)) count++;
    }

    cout << count;

    return 0;
}
