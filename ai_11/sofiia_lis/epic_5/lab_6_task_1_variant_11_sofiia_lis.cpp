/* 
Епік 5. lab_6_task_1_variant_11
Авторка: Софія Ліс
Група: ші-11
*/

#include <string.h>
#include <stdio.h>

const int MAX_SIZE = 256;

void swapLetters(char * str, int start, int end) {
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char str[MAX_SIZE];
    fgets(str, MAX_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';

    int i = 0;
    while(str[i] != '\0' && str[i] != '.') {
        while(str[i] == ' ') {
            i++;
        }
        if (str[i] == '\0' || str[i] == '.')
            break;
        int start = i;
        while (str[i] != ' ' && str[i] != '.' && str[i] != '\0') {
            i++;
        }
        int end = i - 1;
        swapLetters(str, start, end);       
    }
    printf("%s\n", str);
    return 0;
}