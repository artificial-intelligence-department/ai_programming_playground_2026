#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

void wordLength(char *text, const int n)
{
    size_t maxlen = 0;
    size_t minlen = n;
    char *token;
    char *max;
    char *min;
    token = strtok(text, " ");
    while (token != nullptr){
        if (maxlen < strlen(token)){
            maxlen = strlen(token);
            max = token;
        }
        if (minlen > strlen(token)){
            minlen = strlen(token);
            min = token;
        }
        token = strtok(nullptr, " ");
    }

    printf("Найдовше слово: %s (%zu)\n", max, maxlen);
    printf("Найкоротше слово: %s (%zu)\n", min, minlen);
}

int main()
{
    printf("Уведіть речення:\n");
    const int n = 257;
    char text[n] = {'\0'};
    fgets(text, n, stdin);
    if (strlen(text) > 0 && text[strlen(text)-1] == '\n'){
        text[strlen(text)-1] = '\0';
    } else {
        printf("Речення надто довге!\n");
        return -1;
    } 

    wordLength(text, n);
    return 0;
}