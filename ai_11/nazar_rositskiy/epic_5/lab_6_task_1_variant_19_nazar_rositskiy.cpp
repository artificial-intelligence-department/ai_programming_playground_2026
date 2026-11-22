#include <cstdio>
#include <cstring>
#include <cctype>

bool isIdentificator(char *word){
    
    //перевірка 1ї букви на цифру
    if (!isalpha(word[0]) && word[0] != '_') {
        return 0;
    }
    
    //Перевірка слова символи
    for (int i = 1; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int main(){

    char s[256];
    printf("Введіть рядок: ");

        //Ввід слів
        fgets(s, sizeof(s), stdin);
        //Видалення н
        s[strcspn(s, "\n")] = '\0';

        //Визначення довжини
        int len = strlen(s);

        //Видалення крапки в кінці
        if (len > 0 && s[len - 1] == '.') {
            s[len - 1] = '\0';
        }

        //Розділення рядка на слово і перевірка
        char *word = strtok(s, " ");
        bool isFirst = true;
        while(word != NULL){
            if(isIdentificator(word)){
                if(!isFirst){
                    printf(" ");
                }
                isFirst = false;
                printf("%s", word);
            }
            word = strtok(NULL, " ");
        }
        printf(".");
    
}