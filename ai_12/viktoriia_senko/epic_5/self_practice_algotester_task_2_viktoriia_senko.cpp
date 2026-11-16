//Задача №0835 "Снігурочка"
#include <cstdio>
#include <cctype>

int isPalindrome(char *word, int length) {
    int left=0;
    int right=length - 1;
    while (left<right) {
        if (tolower(word[left]) != tolower(word[right])) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

int main() {
    char poem[1050];
    int palindrome_count=0;

    while (fgets(poem, sizeof(poem), stdin) != NULL) {
        char word[1050];
        int length=0;

        for (int i=0; poem[i] != '\0'; i++) {
            char letter=poem[i];
            
            if (isalpha(letter)) {
                word[length++]=letter;
            } else {
                if (length>0) {
                    if (isPalindrome(word, length)) {
                        palindrome_count++;
                    }
                    length=0; 
                }
            }
        }
        
        if (length>0) {
            if (isPalindrome(word, length)) {
                palindrome_count++;
            }
        }
    }

    printf("%d\n", palindrome_count);
    return 0;
}