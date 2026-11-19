// Снігурочка 0835

#include <cstdio>

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

bool isPalindrome(const char word[]) {
    int length = 0;
    while (word[length] != '\0') {
        length++;
    }
    //перевіряємо чи є паліндромом
    for (int i = 0; i < length / 2; i++) {
        if (toLower(word[i]) != toLower(word[length - 1 - i])) {
            return false;
        }
    }

    return true;
}

int main() {
    char word[1025];
    int answer = 0;
    //скануємо та запускаємо по функціях
    while (scanf("%1024s", word) == 1) {
        if (isPalindrome(word)) {
            answer++;
        }
    }

    printf("%d\n", answer);
    return 0;
}