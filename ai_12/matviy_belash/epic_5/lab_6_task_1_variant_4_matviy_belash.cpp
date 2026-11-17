#include <cstdio>
#include <cstring>


void word(char s[], char* &f_word, int &n){

    f_word = strtok(s, " .\n");
    if(f_word == NULL) return;
    char* help_x = strtok(NULL, " .\n");
    while(help_x != NULL){
        if(strcmp(help_x, f_word) == 0)
        n++;
        help_x = strtok(NULL, " .\n");
    }

}

int main(){

    char string[256];
    fgets(string, 256, stdin);

    int n_word = 1;
    char* firs_word;
    word(string, firs_word, n_word);

    for(int i = 1; i <= n_word; i++){
        printf("%s ", firs_word);
    }

    return 0;
}