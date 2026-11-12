#include <stdio.h>
#include <string.h>
#include <ctype.h>


void sortDigitsInWord(char *word, int len) {
        char digits[512];
        int count = 0;
        // 1. Зібрати всі цифри зі слова у масив digits
        for (int i = 0; i < len; i++) {
            if (isdigit((unsigned char)word[i])) {          // якщо символ є цифрою ('0'...'9')
                digits[count] = word[i];     // зберігаємо його
                count++;                     // збільшуємо лічильник знайдених цифр
            }
        }
            // 2. Відсортувати масив digits за спаданням
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (digits[i] < digits[j]) { // якщо лівий менший за правий — міняємо
                    char temp = digits[i];
                    digits[i] = digits[j];
                    digits[j] = temp;
                }
        }
    }
        
        
        // 3. Записати відсортовані цифри назад у слово
            int k = 0;
        for (int i = 0; i < len; i++) {
            if (isdigit((unsigned char)word[i])) {
                word[i] = digits[k];
                k++;
            }
        }
    }

int main() {
    char s[256];
    printf("Vvedit riadok: ");
    if (!fgets(s, sizeof(s), stdin)) return 0;

    // Прибираємо '\n' в кінці, якщо він є
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }

        int i = 0;
    while (s[i] != '\0') {
        // 1. Пропускаємо пробіли
        while (s[i] == ' ') {
            i++;
        }

        // Якщо дійшли до кінця або крапки — зупиняємося
        if (s[i] == '\0' || s[i] == '.') {
            break;
        }

        // 2. Початок слова
        int start = i;
        while (s[i] != ' ' && s[i] != '.' && s[i] != '\0') {
            i++;
        }
        int wordLen = i - start;

        // 3. Обробляємо знайдене слово
        sortDigitsInWord(&s[start], wordLen);
    }    

    printf("Rezultat: %s\n", s);
    return 0;
}