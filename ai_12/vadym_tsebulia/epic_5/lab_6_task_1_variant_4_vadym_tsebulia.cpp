/*
Лабораторна робота №6, Завдання №1, Варіант №4.
Цебуля Вадим
ШІ-12
*/

#include <cstdio>
#include <cstring>

const int MAX_TEXT = 256;
const int MAX_WORDS = 128;   

void removeNewline(char *s){
        int len = strlen(s);
        if (len > 0 && s[len - 1] == '\n') s[--len] = '\0';
}

// Перевірка: текст не порожній, закінчується крапкою, є хоча б одне слово
bool validText(const char *s){
        int len = strlen(s);
        if (len == 0) return false;
        if (s[len - 1] != '.') return false;

        for (int i = 0; i < len - 1; i++){
                if (s[i] != ' ' && s[i] != '.') return true;   
        }
        return false;
}

// Ріже copy через strtok, складає адреси слів у words, повертає кількість
int splitWords(char *copy, char *words[]){
        int n = 0;
        char *token = strtok(copy, " .");
        while (token != nullptr && n < MAX_WORDS){
                words[n] = token;   
                n++;
                token = strtok(nullptr, " .");
        }
        return n;
}

// Порівнює кожне слово з words[0] через strcmp, друкує збіги, повертає їх кількість
int printSameAsFirst(char *words[], int n){
        int count = 0;
        for (int i = 0; i < n; i++){
                if (strcmp(words[i], words[0]) == 0){
                        count++;
                        printf("%3d. %-15s (слово №%d)\n", count, words[i], i + 1);
                }
        }
        return count;
}

int main(){
        char text[MAX_TEXT];

        printf("Введіть рядок (до %d символів, крапка в кінці):\n", MAX_TEXT - 1);
        if (fgets(text, MAX_TEXT, stdin) == nullptr){
                printf("Помилка: рядок не введено.\n");
                return 1;
        }

        if (strchr(text, '\n') == nullptr && !feof(stdin)){
                int ch = getchar();
                if (ch != '\n' && ch != EOF){
                        printf("Помилка: рядок довший за %d символів.\n", MAX_TEXT - 1);
                        return 1;
                }
        }
        removeNewline(text);

        if (!validText(text)){
                printf("Помилка: рядок має містити хоча б одне слово і закінчуватися крапкою.\n");
                return 1;
        }

        char copy[MAX_TEXT];
        strcpy(copy, text);   
        char *words[MAX_WORDS];
        int n = splitWords(copy, words);

        printf("Рядок: \"%s\"\n", text);
        printf("Слів у рядку: %d\n", n);
        printf("Перше слово: \"%s\"\n", words[0]);
        printf("Слова, що збігаються з першим:\n");

        int k = printSameAsFirst(words, n);

        printf("Разом збігів: %d\n", k);
        return 0;
}
