#include <cstdio>
#include <cstring>

int main(){

    char text[255];
    int maxlen = 0;
    if (fgets(text,255,stdin)){

        char delimiters[] = " .,\n\t";
        char *token = strtok(text, delimiters);

        while (token != NULL)
        {
            int current_len = (int)strlen(token);
            if (current_len > maxlen) {
                maxlen = current_len;
            }
            token = strtok(NULL, delimiters);
        }
    }
    printf("Longest word length is %d\n", maxlen);
    return 0;
}