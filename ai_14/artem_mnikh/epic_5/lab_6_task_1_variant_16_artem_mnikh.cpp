#include <ctype.h>
#include <stdio.h>
#include <string.h>

void replacePunctuation(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.' || s[i] == ',' || s[i] == '?' || s[i] == '!' || s[i] == '\"' || s[i] == '\'')
        {
            s[i] = ' ';
        }
    }
}

int isValidText(const char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isalpha(s[i]) && !isdigit(s[i]) && s[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

void findUniqueWords(const char s[])
{
    char copy[256];
    strcpy(copy, s);

    char words[128][256];
    int word_count = 0;

    char* token = strtok(copy, " ");
    while (token != NULL)
    {
        strcpy(words[word_count], token);
        word_count++;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < word_count - 1; i++)
    {
        for (int j = 0; j < word_count - 1 - i; j++)
        {
            if (strcmp(words[j], words[j + 1]) > 0)
            {
                char temp[256];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }

    printf("Слова, які зустрічаються по одному разу:\n");
    for (int i = 0; i < word_count; i++)
    {
        int same_as_prev = (i > 0) && (strcmp(words[i], words[i - 1]) == 0);
        int same_as_next = (i < word_count - 1) && (strcmp(words[i], words[i + 1]) == 0);

        if (!same_as_prev && !same_as_next)
        {
            printf("%s\n", words[i]);
        }
    }
}

int main()
{
    char s[256];
    printf("Введіть речення (латинськими літерами):\n");
    fgets(s, sizeof(s), stdin);

    s[strcspn(s, "\n")] = '\0';

    int len = (int)strlen(s);
    if (len == 0)
    {
        printf("Речення не може бути порожнім.\n");
        return 1;
    }

    replacePunctuation(s);

    if (!isValidText(s))
    {
        printf(
            "Введіть речення, що містить лише англійські літери, цифри, пробіли та базові розділові знаки (. , ? ! \" "
            "').\n");
        return 1;
    }

    findUniqueWords(s);

    return 0;
}