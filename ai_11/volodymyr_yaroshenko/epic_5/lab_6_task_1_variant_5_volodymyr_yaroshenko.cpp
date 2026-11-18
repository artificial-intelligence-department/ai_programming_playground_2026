/*  
Лабораторна 6 завдання 1
Варіант 5
Ярошенко Володимир 
11 група 
*/
#include <string.h>
#include <ctype.h>
#include <stdio.h>
using namespace std;

int main() {
char s[256];
printf("Введіть текст: ");
fgets(s, 256, stdin);
s[strcspn(s, "\n")] = '\0';
char letters[256];
char numbers[256];
int a =0, b=0, i=0;
while (s[i] != '\0')
{
    if (isalpha(s[i]))
    {
        letters[a] = s[i];
        a++;
    }

    if (isdigit(s[i]))
    {
        numbers[b] = s[i];
        b++;
    }
    i++;
}
letters[a] = '\0';
numbers[b] = '\0';
printf("Результат: %s%s", letters, numbers);
    return 0;
}