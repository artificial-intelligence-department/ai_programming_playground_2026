#include <stdio.h>

int main() {
    char s[256];

    printf("Введіть рядок: ");
    fgets(s, sizeof(s), stdin);

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            
            for (int j = i + 1; s[j] != '\0'; j++) {
                if (s[j] >= '0' && s[j] <= '9') {
                    
                    if (s[i] < s[j]) {
                        char temp = s[i];
                        s[i] = s[j];
                        s[j] = temp;
                    }
                }
            }
        }
    }

    printf("Результат: %s\n", s);

    return 0;
}
