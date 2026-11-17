#include <cstring>
#include <cstdio>

int main() {
    char s[1025];
    int count = 0;
    
    
    while (scanf("%s", s) == 1) {
        int n = strlen(s);
        bool isPalindrom = true;
        
        for (int i = 0; i < n / 2; i++) {
            char a = s[i];
            char b = s[n - 1 - i];
            
            if (a >= 'A' && a <= 'Z') {
                a += 32;  
            }
            if (b >= 'A' && b <= 'Z') {
                b += 32;
            }
            
            if (a != b) {
                isPalindrom = false;
            }
        }
        if (isPalindrom) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}