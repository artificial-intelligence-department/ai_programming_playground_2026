/*
Лабораторна робота № 6, Варіант 8
Зубак Тетяна
ШІ-12
*/
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX = 256;
const char a[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const char b[] = "0123456789";

char* st(char *word){
    int i = 0;
    while(isdigit((unsigned char)word[i])) i++;
    if(i > 0) memmove(word, word + i, strlen(word + i) + 1);
    return word;
}

char* sm(char *word){
    for(int i = 0; word[i] != '\0'; ){
        if(strchr(a, word[i]) == NULL && strchr(b, word[i]) == NULL){
            int j = i;
            while (word[j] != '\0') {
                word[j] = word[j + 1];
                j++;
            }
        } else {
            i++;
        }
    }
    return word;
}

void err(char *word, bool &start, bool &sym){
    int len = strlen(word);
    start = false;
    sym = true;
    for(int i = 0; i < len; i++){
        if(i == 0){
            if(strchr(a, word[i]) != NULL) start = true;
        }
        if(strchr(a, word[i]) == NULL && strchr(b, word[i]) == NULL) sym = false;
    }
}

char* words(char *word){
    bool start, sym;
    err(word, start, sym);
    if(start && sym) return word;
    else{
        if(sym == false) word = sm(word);
        if(start == false) word = st(word);
    }
    return word;
}

int main(){
    char s[MAX], res[MAX][MAX];
    int k = 0, len;
    bool hasWord;

    do {
        printf("Введіть рядок: ");
        fgets(s, MAX, stdin);
        len = strlen(s);
        if(len > 0 && s[len - 1] == '\n'){
            s[len - 1] = '\0';
            len--;
        }

        hasWord = false;
        for(int i = 0; i < len; i++){
            if(s[i] != ' ' && s[i] != '.'){
                hasWord = true;
                break;
            }
        }

        if(len == 0 || s[len - 1] != '.' || !hasWord){
            printf("Помилка! Рядок повинен містити хоча б одне слово і закінчуватися крапкою.\n");
        }
    } while (len == 0 || s[len - 1] != '.' || !hasWord);

    char *token = strtok(s, " .\n");
    while (token != NULL){
        char *word = words(token);
        if(strlen(word) > 0){
            strcpy(res[k++], word);
        }
        token = strtok(NULL, " .\n");
    }
    strcpy(res[k++], ".");

    printf("Рядок після перетворень:");
    for(int i = 0; i < k; i++){
        if(strcmp(res[i], ".") != 0){
            printf(" %s", res[i]);
        } else {
            printf("%s\n", res[i]);
        }
    }
    return 0;
}