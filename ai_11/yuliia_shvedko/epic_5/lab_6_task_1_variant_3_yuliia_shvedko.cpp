#include <cstdio>
#include <cstring>
#include <string>

int main()
{
    char text[256];
    printf("Введіть речення: \n");
    fgets(text, sizeof(text), stdin);
    for(size_t i = 0; i < strlen(text) - 2; i++)
    {
        if(!isspace(text[i]) && !isdigit(text[i]) && !isalpha(text[i])){
            printf("Текст має складатися лише з латинських літер, пробілів та цифр!\n");
            return 0;
        }
    }
    if(text[strlen(text) - 2] != '.')
    {
        printf("Речення має закінчуватись крапкою!\n");
        return 0;
    }
    printf("Слова, що містять одну цифру:\n");
    char *word = strtok(text, " .");
    while(word != nullptr)
    {
        int c = 0;
        for(size_t i = 0; i < strlen(word); i++){
            if(isdigit(word[i]))
            c++;
        }
        if(c == 1)
        printf("%s\n", word);
        word = strtok(nullptr, " .");
    }
    return 0;
}