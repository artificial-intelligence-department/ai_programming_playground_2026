/*
    Задача: Снігурочка
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
int main() {
    string word;
    int score = 0;
    while (cin >> word)
    {
        int length = word.length();
        bool last = false;
        if (word[length - 1] == '.')
        {
            last = true;
            length--;
        }
        for (int i = 0; i < length; i++) 
        {
            if (word[i] >= 'A' && word[i] <= 'Z')
            {
                word[i] = word[i] - 'A' +'a';
            }
        }
        bool isPalindrome = true;
        for (int i = 0; i < length / 2; i++)
        {
            if (word[i] != word[length - 1 - i])
            {
                isPalindrome = false;
            }
        }
        if (isPalindrome)
        {
            score++;
        }
        if (last)
        {
            break;
        }
    }
    cout << score << endl;
    return 0;
}