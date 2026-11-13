#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(void) {
    char s[256];

    puts("Input text: ");
    if (fgets(s, 256, stdin) == NULL) {
        puts("Input error");
        return 1;
    }

    s[strcspn(s, "\n")] = '\0';

    int cur = 0;
    int max = 0;

    for (int i = 0; s[i] != '\0' && s[i] != '.'; i++) {
        if (s[i] != ' ') {
            cur++;
        } else {
            if (cur > max) max = cur;
            cur = 0;
        }
    }

    if (cur > max) max = cur;

    printf("Output: %d \n", max);

    return 0;
}