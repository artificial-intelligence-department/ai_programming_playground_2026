#include <stdio.h>

const int n = 256;

int main() {
    char text[n];

    fgets(text, sizeof(text), stdin);

    int start = 0;

    for (int i = 0; ; i++) {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\0') {
            bool print = 1;
            for (int j = start; j < i; j++) {
                char c = text[j];
                if(c == 'a'|| c == 'e' || c == 'u' || c == 'i' || c == 'o' || c == 'y' || c == 'A'|| c == 'E' || c == 'U' || c == 'I' || c == 'O' || c == 'Y'){
                    print = 0;
                    break;
                }
            }

            if(print){
                for(int j = start; j < i; j++) {
                    printf("%c", text[j]);
                }
                printf(" ");
            }

            if (text[i] == '\0' || text[i] == '\n') {
                text[i] = '\0';
                break;
            }

            start = i + 1;
        }

        if (text[i] == '\0') {
            break;
        }
    }

    return 0;
}
