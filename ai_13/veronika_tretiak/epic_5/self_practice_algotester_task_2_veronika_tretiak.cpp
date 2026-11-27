/*
Задача: Снігурочка
*/
#include <cstdio>
int main(){
    char word[1025];
    int len = 0;
    int answer = 0;
    int c;
    while((c = getchar()) != EOF){
        if(c == ' ' || c == '\n' || c == '\r'){
            if(len > 0){
                bool ok = true;
                for(int i = 0; i < len / 2; i++){
                    if(word[i] != word[len - 1 - i]){
                        ok = false;
                        break;
                    }
                }
                if(ok){
                    answer++;
                }
                len = 0;

            }
        }
        else{
            if(c >= 'A' &&  c <= 'Z'){
                c = c - 'A' + 'a';
            }
            word[len] = (char)c;
            len++;
        }
    }
    if(len > 0){
        bool ok = true;
        for(int i = 0; i < len / 2;i++){
            if(word[i] != word[len - 1 - i]){
                ok = false;
                break;
            }
        }
        if(ok){
            answer++;
        }
    }
    printf("%d\n", answer);
    return 0;
}