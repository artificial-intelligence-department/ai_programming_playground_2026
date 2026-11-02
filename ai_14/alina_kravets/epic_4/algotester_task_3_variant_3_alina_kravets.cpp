/*Алготестер lab3v3
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

int main()
{
    const int MAX = 100001; 
    char s[MAX] = "";
    char s_letters[MAX] = "";
    int s_numbers[MAX] = {0};
    int j = 0;
    int count = 1;

    cin >> s;

    for (int i = 0; i < MAX; i++)
    {
        if (s[i] == '\0') break;

        if (s[i] == s[i+1]) count++;
        else
        {
            s_letters[j] = s[i];
            s_numbers[j] = count;
            j++;
            count = 1;
        }
    }

    for (int i = 0; i < j; i++)
    {
        if (s_numbers[i] == 1) cout << s_letters[i];
        else cout << s_letters[i] << s_numbers[i];
    }

    return 0;
}
