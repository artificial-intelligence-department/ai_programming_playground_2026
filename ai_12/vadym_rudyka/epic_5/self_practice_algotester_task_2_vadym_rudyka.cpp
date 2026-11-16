#include <cstdio>
#include <cstring>
#include <cctype>

int main() {
    char word[1100];
    int count = 0;
    
    while (scanf("%1099s", word) == 1) {
        int len = strlen(word);
        bool isPalindrome = true;

        for (int i = 0, j = len - 1; i < j; i++, j--) {
            if (tolower((unsigned char)word[i]) != tolower((unsigned char)word[j])) {
                isPalindrome = false;
                break;
            }
        }

        if (isPalindrome) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}