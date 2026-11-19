#include<stdio.h>
#include<string.h>
#include<ctype.h>

void sortLetters(char s[]){
    char letters[256];
    int letterCount = 0;
    int len = strlen(s);

    for(int i = 0; i < len; i++){
        if(isalpha((unsigned char)s[i])){
            letters[letterCount] = s[i];
            letterCount++;
        }
    }
    for(int i = 0; i < letterCount - 1; i++){
        for(int j = 0; j < letterCount - 1 - i; j++){
            if(letters[j] > letters[j + 1]){
                char t = letters[j];
                letters[j] = letters[j + 1];
                letters[j + 1] = t;
            }
        }
    }
    int index = 0;
    for(int i = 0; i < len; i++){
        if(isalpha((unsigned char)s[i])){
            s[i] = letters[index];
            index++;
        }
    }
}


int main(){
    char s[256];
    printf("Введіть рядок(не більше 255 символів, крапка вкінці): ");
    if(fgets(s, sizeof(s), stdin) == NULL){
        printf("Помилка введення\n");
        return 1;
    }

    if(strchr(s, '\n') == NULL){
        printf("Помилка: рядок перевищує 255 символів\n");
        return 1;
    }
    s[strcspn(s, "\n")] = '\0';
    int len = strlen(s);
    if(len == 0 || s[len - 1] != '.'){
        printf("Помилка: рядок має бути непорожнім і закінчуватися крапкою\n");
        return 1;
    }

    sortLetters(s);
    printf("Перетворений рядок: %s\n", s);
  
    return 0;
}
