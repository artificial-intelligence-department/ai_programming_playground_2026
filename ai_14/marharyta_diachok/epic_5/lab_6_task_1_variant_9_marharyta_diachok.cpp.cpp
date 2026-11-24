/*  
Задача: Lab. Варіант №9.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <stdio.h>
#include <string.h>

int isPalindrome(const char *s) {
int m = strlen(s);
for (int i = 0; i < m / 2; i++) {
    if (s[i] != s[m - i - 1]) {
        return 0;}}

    return 1;
}

int main() {
char s[256];
puts("Введіть текст:");
    
gets(s);

printf("Паліндроми:\n");
int found = 0;
char *word = strtok(s, " .");
    
while (word != NULL) {
    if (isPalindrome(word)) {
        puts(word);
        found++;}
    
word = strtok(NULL, " .");}
    
if (found == 0) puts("Паліндроми відсутні.");
    
    
    return 0;
}
