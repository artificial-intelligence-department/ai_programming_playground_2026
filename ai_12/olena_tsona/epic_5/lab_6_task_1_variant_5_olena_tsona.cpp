#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#define n 256 

void transformString(char s[n], char result[n]) {
    int i;
    int isorted = 0; 
   
    for (i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            result[isorted++] = s[i];
        }
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i])) {
            result[isorted++] = s[i];
        }
    }

    
    result[isorted] = '\0';
}

int main() {
    char s1[n];
    char transformed[n];

    printf("Введіть текст (в кінці поставте крапку): \n");
    

    if (fgets(s1, n, stdin) != NULL) {
        
        size_t len = strlen(s1);
        if (len > 0 && s1[len - 1] == '\n') {
            s1[len - 1] = '\0';
        }
    }

    printf("Початковий текст: \n");
    puts(s1);
    printf("Довжина рядка: %i\n", (int)strlen(s1));

    
    transformString(s1, transformed);

    printf("Перетворений текст (спочатку букви, потім цифри):\n");
    puts(transformed);

    return 0;
}