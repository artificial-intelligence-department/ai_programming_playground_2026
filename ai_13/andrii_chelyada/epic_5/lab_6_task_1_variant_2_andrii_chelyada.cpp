// lab 6 task 1 variant 2 Челяда Андрій, ШІ-13

#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

bool hasVowel(const char *word);

int main(){
    char text[256];
    int len;
    printf("Введіть текст (крапка в кінці): ");
    fgets(text, sizeof(text), stdin);
    text[ strcspn(text, "\n")] = '\0';
    len = strlen(text);
        if(len > 0 && text[len - 1] == '.'){
        text[len - 1] = '\0';
        }
    
    printf("Слова без голосних:\n");
    int count = 0;
    char *t;
    t = strtok(text, " ");
    while(t != NULL){
        if(!hasVowel(t)){
            printf("%s\n", t);
            count++;
        }
    t = strtok(NULL, " ");
    }

    if(count == 0){
        printf("Таких слів немає\n");
    }


    return 0;
}

bool hasVowel(const char *word){
    for(int i = 0; word[i] != '\0'; i++){
        char c;
        c = tolower(word[i]);
        if (strchr("aeiou", c) != NULL) {
            return true;
        }
    }
    return false;
}