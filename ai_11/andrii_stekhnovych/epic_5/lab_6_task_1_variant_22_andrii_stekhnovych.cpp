// Lab 6 variant 22

#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX_LEN=256;

int wordsStartingWithA(char str[]) {
    int count=0;
    char *token;
    token = strtok(str, " \t.,\n");

    while (token != NULL) {
        if (token[0]=='a' or token[0]=='A') {
            count++;
        }
        else if (strncmp(token, "а", 2)==0 or strncmp(token, "А", 2)==0) {
            count++;
        }
        token = strtok (NULL, " \t.,\n");
    }
    return count;
}

int main(){
    printf("%s", "Введіть рядок: ");
    char str[MAX_LEN];
    if (fgets(str, sizeof(str), stdin) != nullptr) {
        size_t length = strlen(str);
        if(length>0 and str[length-1] == '\n') {
            str[length-1] = '\0';
        }
            
        printf("Кількість слів, що починаються на букву А/а: %i\n", wordsStartingWithA(str));  
    }
    
    return 0;

}