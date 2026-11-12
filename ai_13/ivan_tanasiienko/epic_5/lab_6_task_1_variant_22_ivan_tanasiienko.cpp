/*
    Lab 6, Task 1, Variant 22, Танасієнко Іван, ШІ-13
*/
#include<cstdio>

int main()
{
    char text[256];
    bool valid = true;
    bool hasWord = false;
    do
    {
        valid = true;
        hasWord = false;
        printf("Введіть рядок: ");
        fgets(text, 256, stdin);
        for(int i = 0; text[i] != 0; i++)
        {
            if(text[i] == '\n')
            {
                text[i] = '\0';
                break;
            }
        }
        for(int i = 0; text[i] != '\0'; i++)
        {
            bool validText = !((text[i] >= 'a' && text[i] <= 'z') ||
            (text[i] >= 'A' && text[i] <= 'Z'));
            if(validText && !(text[i] == ' ' || text[i] == '.' || (text[i] >= '0' && text[i] <= '9')))
            {
                valid = false;
            }
            if(!validText)
            {
                hasWord = true;
            }
            if(text[i] == '.' && text[i + 1] != '\0')
            {
                valid = false;
            }
            if(text[i + 1] == '\0' && text[i] != '.')
            {
                valid = false;
            }
        }
    }while(!valid || !hasWord);
    int words = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(i > 0)
        {
            if(text[i-1] == ' ' && (text[i] == 'a' || text[i] == 'A'))
            {
                words++;
            }
        }
        else
        {
            if(text[i] == 'a' || text[i] == 'A')
            {
                words++;
            }
        }
    }
    printf("Кількість слів, які починаються на \"a\": %d\n", words);
    return 0;
}