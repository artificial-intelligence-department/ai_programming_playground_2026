#include <cstdio>
#include <cstring>
#include <cctype>

int main() {
    char s[256];
    printf("Input text(тільки англ. символи): \n");
    fgets(s, 256, stdin);

    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }

    char slovo[256];
    int dov = 0;
    bool golosna = false;
    bool found = false;

    printf("Output text: \n");
    for (int i = 0; ; i++) {
        char c = s[i];

        if (c != ' ' && c != '.' && c != '\0') {
            slovo[dov] = c;
            dov++;

            char lit = tolower(c);
            if (lit == 'a' || lit == 'e' || lit == 'i' || lit == 'o' || lit == 'u' || lit == 'y') {
                golosna = true;
            }
        } 
        
        else {
            if (dov > 0 && !golosna) {
                slovo[dov] = '\0';
                printf("%s\n", slovo);
                found = true;
            }
            dov = 0;
            golosna = false;

            if (c == '\0') {
                break;
            }
        }
    }

    if (!found) {
        printf("No words\n");
    }

    return 0;
}