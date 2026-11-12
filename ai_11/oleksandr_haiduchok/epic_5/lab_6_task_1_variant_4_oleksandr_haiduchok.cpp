#include <cstdio>
#include <string.h>
int Slov(char str[]){
    char *first = strtok(str, " .\n");
    if(first == NULL){
        return 0;
    }
    char *letter = strtok(NULL, " .\n");
    while (letter != NULL) {
    if(strcmp(first, letter) == 0){
        printf("%s\n", letter);
    }
    letter = strtok(NULL, " .\n");
    }
    return 0;
}
int main(){
    char arr[256];
    printf("Заповніть рядок: ");
    fgets(arr, sizeof(arr), stdin);
    Slov(arr);
    return 0;
}