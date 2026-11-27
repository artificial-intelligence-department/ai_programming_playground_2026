#include <iostream>
#include <cstring>

using namespace std;

int main(){
    char text[256];
    fgets(text, sizeof(text), stdin);
    int len = strlen(text);

    char *check = strchr(text, '\n');

    if(check != NULL){
        *check = '\0';
        len--;
    }
    else{
        printf("Помилка: текст задовгий.");
        return 1;
    }

    printf("Початковй текст: %s\n", text);

    for(int i = 0; i < len-1; i++){
        int j = 1;
        if(isdigit(text[i])){
            while(isdigit(text[i+j])){
                if(i+j == len-1){
                    j = 0;
                    break;
                }
                else{
                    j+=1;
                }
            }
            char tmp = text[i];
            text[i] = text[i+j];
            text[i+j] = tmp;
        }

    }

    printf("Новий текст: %s\n", text);

    return 0;
}
