/*Lab 6 V 4
Sofiia Chovhan */
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char text[256];
    char first[256];

    fgets(text, 256, stdin);

    char *word = strtok(text, " \t\n.,!?");

    if (word == NULL) {
        return 0;
    }

    strcpy(first, word);

    while (word != NULL) {
        if (strcmp(word, first) == 0) {
            printf("%s\n", word);
        }

        word = strtok(NULL, " \t\n.,!?");
    }

    return 0;
}
