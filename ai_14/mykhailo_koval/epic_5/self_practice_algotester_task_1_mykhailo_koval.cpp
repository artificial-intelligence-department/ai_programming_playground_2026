#include <stdio.h>
#include <string.h>

char S[500005], T[500005];
int m;

bool eq(int i){
    return strncmp(S + i, T, m) == 0;
}

int main(){
    int t;
    scanf("%d", &t);

    while(t--){
        scanf("%s %s", S, T);
        int n = strlen(S);
        m = strlen(T);
        int d = n - m;
        int j = d / 2;

        bool sergei;
        if(d % 2 == 1){
            sergei = eq(j) && eq(j + 1);
        } else {
            sergei = eq(j) || (eq(j - 1) && eq(j + 1));
        }

        if(sergei){
            printf("Sergei\n");
        } else {
            printf("Larry\n");
        }
    }

    return 0;
}