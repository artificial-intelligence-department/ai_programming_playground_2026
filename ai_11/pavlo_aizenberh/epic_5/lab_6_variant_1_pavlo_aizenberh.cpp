
#include <stdio.h>
#include <string.h>

void longestShortestWords(char str[]) {
    char* token = strtok(str, " .\t\n");

    if (token == NULL) return;

    int max = strlen(token);
    int min = strlen(token);

    char* longestChar = token;
    char* shortestChar = token;

    while (token != NULL) {
        if (strlen(token) > max) {
            max = strlen(token);
            longestChar = token;
        }

        if (strlen(token) < min) {
            min = strlen(token);
            shortestChar = token;
        }

        token = strtok(NULL, " .\t\n");
    }

    printf("Найдовше слово: %s\n", longestChar);
    printf("Найкоротше слово: %s\n", shortestChar);
}

int main() {
    char str[256];

    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    longestShortestWords(str);

    return 0;
}
