/*Дзідзьо і його пісня
ШІ-14
Кравець Аліна*/
#include <cstdio>
#include <cstring>

int main()
{
    char s[101] = {'\0'};
    int result = 1;

    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < strlen(s) - 1; i++)
    {
        if (s[i] != s[i+1]) result++;
    }

    printf("%d\n", result);

    return 0;
}
