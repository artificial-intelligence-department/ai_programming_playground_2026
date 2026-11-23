/*Задача 1806 - "ДНК реп'яховірусу"
Максімко Павло - СШІ-13*/

#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100005;
const int SYMBOLS = 26;

char t[MAX];
char s[MAX];
long long letters[SYMBOLS][MAX];

int main()
{
    scanf("%s", t);
    scanf("%s", s);
    long long t_length = strlen(t);
    long long s_length = strlen(s);
    if(t_length < s_length)
    {
        printf("0\n");
        return 0;
    }
    for (int i = 0; i < s_length; i++)
    {
        for (int j = 0; j < SYMBOLS; j++)
        {
            letters[j][i + 1] = letters[j][i];
        }
        letters[s[i] - 'a'][i + 1] += i + 1;
    }
    long long k = 0;
    for(int i = 0; i < t_length; i++)
    {
        int L = i - t_length + s_length;
        if (L < 0) L = 0;

        int R = i;
        if (R > s_length - 1) R = s_length - 1;

        if (L <= R)
        {
            int j = t[i] - 'a';
            k += letters[j][R + 1] - letters[j][L];
        }
    }

    printf("%lld", k);
    return 0;
}