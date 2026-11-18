/*
Lab 6
variant 9
Лисюк Андріана
ШІ-13
*/

#include <stdio.h>
#include <string.h>

int isPalindrome(char word[]){
    int len = strlen(word);
    int i;
    for (i = 0; i < len / 2; i++)
    {
        if (word[i] != word[len - 1 - i])
            return 0;
    }
    return 1;
}
int main(){
    char text[256];
    char word[256];
    int i, len = 0, found = 0;
    puts("Input text:");
    gets(text);
    puts("Palindromes:");
    for (i = 0; ; i++)
    {
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\0')
        {
            if (len > 0)
            {
                word[len] = '\0';
                if (isPalindrome(word))
                {
                    puts(word);
                    found++;
                }
                len = 0;
            }
            if (text[i] == '.' || text[i] == '\0')
                break;
        }
        else
        {
            word[len] = text[i];
            len++;
        }
    }
    if (found == 0)
        puts("No palindromes found");
    return 0;
}