#include <cstdio>
#include <cstring>

using namespace std;

int isletter(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

int isnumber(char c) {
    return c >= '0' && c <= '9';
}

int wordtype(char *s, int len) {
    int hasDigit = 0, hasLetter = 0, hasOther = 0;
    for (int j = 0; j < len; j++) {
        if (isnumber(s[j]))
            hasDigit = 1;
        else if (isletter(s[j]))
            hasLetter = 1;
        else
            hasOther = 1;
    }
    if (hasDigit && !hasLetter && !hasOther) {
        return 0;
    }
    if (hasLetter && !hasDigit && !hasOther) {
        return 1;
    }
    else{
        return 2;
    }
}
int main() {
    char s[256];

    printf("Введіть рядок (слова розділяйте пробілами, у кінці крапка): ");
    if (fgets(s, 256, stdin) == NULL) {
        return 1;
    }
        
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '.') s[--n] = '\0';

    int count = 0, i = 0;
    int start[128], len[128];
    while (i < n) {
        while (i < n && s[i] == ' ') i++;
        if (i >= n) break;
        int b = i;
        while (i < n && s[i] != ' ') i++;
        start[count] = b;
        len[count] = i - b;
        count++;
    }

    int position = 0;
    char result[256];
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < count; k++){
            if (wordtype(s + start[k], len[k]) != j) {
                continue;
            }
            if (position > 0) {
                result[position++] = ' ';
            }
            memcpy(result + position, s + start[k], len[k]);
            position += len[k];

        }
    }
    
    result[position++] = '.';
    result[position] = '\0';

    printf("Результат: %s\n", result);
    return 0;

}