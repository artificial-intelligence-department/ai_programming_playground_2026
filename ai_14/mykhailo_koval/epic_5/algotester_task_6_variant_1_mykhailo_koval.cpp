#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>

std::string words[100000];

int main(){
    int N, K;
    scanf("%d %d", &N, &K);

    for(int i = 0; i < N; i++){
        char s[12];
        scanf("%11s", s);
        for(int j = 0; s[j] != '\0'; j++){
            if(s[j] >= 'A' && s[j] <= 'Z'){
                s[j] = s[j] - 'A' + 'a';
            }
        }
        words[i] = s;
    }

    std::sort(words, words + N);

    bool used[26];
    memset(used, false, 26);

    int i = 0;
    while(i < N){
        int j = i;
        while(j < N && words[j] == words[i]){
            j++;
        }
        if(j - i >= K){
            for(size_t c = 0; c < words[i].size(); c++){
                used[words[i][c] - 'a'] = true;
            }
        }
        i = j;
    }

    int M = 0;
    for(int c = 0; c < 26; c++){
        if(used[c]){
            M++;
        }
    }

    if(M == 0){
        printf("Empty!\n");
    } else {
        printf("%d\n", M);
        for(int c = 25; c >= 0; c--){
            if(used[c]){
                printf("%c ", 'a' + c);
            }
        }
        printf("\n");
    }

    return 0;
}