#include <cstring>
#include <cstdio>
using namespace std;

/*
 * Задача: Lab 6 - Task 1 - 4
 * Щербак Орислав
 * Група ШІ-11
 */

int main(){
    char s[256];
    fgets(s, 256, stdin);
    char first[256];
    char *token = strtok(s, " .\n");
    strcpy(first, token);
    while(token != NULL){
        if(strcmp(first, token) == 0){
            printf("%s\n", token);
        }
        token = strtok(NULL, " .\n");
    }
    return 0;
}