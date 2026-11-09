#include <cstdio>
#include <cstring>

int main() {
    char c[256]; 
    printf("Введіть набір слів: ");
    fgets(c, sizeof(c), stdin);
    char word[256];
    int ii = 0;
    int countBest = 0;
    char wordBest[256];

    for (int i = 0; i <= strlen(c); i++) {
        if (c[i] == ' ' || c[i] == '.') {
            int wordLen = i - ii; 

            if (wordLen > 0) {
                strncpy(word, c + ii, wordLen);
                int count = 0;
                char *neww = strstr(c, word);

                while (neww != NULL) {
                    bool leftOk = (neww == c || *(neww - 1) == ' ');
                    bool rightOk = (*(neww + wordLen) == ' ' || *(neww + wordLen) == '\0');

                    if (leftOk && rightOk) {
                        count++;
                    }
                    neww = strstr(neww + 1, word);
                }
                    if (count > countBest) {
                    countBest = count;
                    strcpy(wordBest, word);
                }
            }

            ii = i + 1;
        }
    }
    printf("Найбільш повторюване слово: %s", wordBest);
    return 0;
}