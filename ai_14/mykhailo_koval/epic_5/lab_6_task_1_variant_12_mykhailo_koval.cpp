#include <stdio.h>
#include <string.h>

int main(){
    char s[256];
    fgets(s, 256, stdin);
    s[strcspn(s, "\n")] = '\0';
    int len = strlen(s);

    for(int i = 0; i < len; i++){
        if(s[i] == ' ' || s[i] == '.'){
            continue;
        }

        int j = i;
        while(j < len && s[j] != ' ' && s[j] != '.'){
            j++;
        }
     
        for(int x = i; x < j - 1; x++){
            for(int y = i; y < j - 1 - (x - i); y++){
                if(s[y] > s[y + 1]){
                    char temp = s[y];
                    s[y] = s[y + 1];
                    s[y + 1] = temp;
                }
            }
        }
        i = j;
    }

    printf("%s", s);

    return 0;
}