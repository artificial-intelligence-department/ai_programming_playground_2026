#include <stdio.h>

void shortest_word(char s[]){
    int i, len = 0, min = -1;

    for (i = 0; ; i++){
        if (s[i] != ' ' && s[i] != '.' && s[i] != '\n' && s[i] != '\0'){
            len++;
        }else{
            if (len > 0 && (min == -1 || len < min))
                min = len;
            len = 0;

            if (s[i] == '.' || s[i] == '\n' || s[i] == '\0')
                break;
        }
    }
    if (min == -1)
        printf("Слів у тексті немає.\n");
    else
        printf("Довжина найкоротшого слова: %d\n", min);
}

int main(void){
    char s[256];
    printf("Введіть текст (закінчується крапкою): ");
    fgets(s, sizeof(s), stdin);
    shortest_word(s);
    return 0;
}
