
/*
    Щасливі паліндроми
    Рубаха Олексій
    ШІ-13
*/

#include <stdio.h>
#include <string.h>

int isPalindrom(char s[]){
    int n = strlen(s);
    if (n == 1) return 1;
    for (int i = 0; i<n/2; i++){
        if (s[i] != s[n-i-1])
            if(!((s[i] == '4' || s[i] == '7') || (s[n-i-1] == '4' || s[n-i-1] == '7')))
                return 0;
    }
    return 1;
}

int main(){
    char s[100001];
    scanf("%s", s);
    if (isPalindrom(s)) printf("YES");
    else printf("NO");

    return 0;
}