#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

void reverseWords(char *text) {
    int i = 0;
    while (text[i] != '\0' && text[i] != '.') {
        while (text[i] == ' ') {
            i++;
        }
        if (text[i] == '.' || text[i] == '\0') {
            break;
        }
        int left = i;
        while (text[i] != ' ' && text[i] != '.' && text[i] != '\0') i++;
        int right = i - 1;
        while (right > left) {
            char temp = text[left];
            text[left] = text[right];
            text[right] = temp;
            left++;
            right--;
        }
    }

}

int main() {
    char text[256];
    printf("Введіть текст (не більше 255 символів): ");
    fgets(text, sizeof(text), stdin);
    char *over = strchr(text, '\n');

    if (over == nullptr) {
        int next = getchar();
        if (next != '\n' && next != EOF) {
            printf("Помилка: текст перевищує 255 символів\n");
            return 0;
        }
    } else {
        *over = '\0';
    }
    size_t len = strlen(text);
    if (len < 2 || text[len - 1] != '.') {
        printf("Помилка: некоректний ввід\n");
        return 0;
    }

    bool legit = false;
    for (int i = 0; i < len - 1; i++) {
        unsigned char ch = text[i];
        if (isalpha(ch) || isdigit(ch)) {
            legit = true;
        } else if (ch == ' ') {
            
        } else {
            printf("Помилка: некоректний ввід\n");
            return 0;
        }
    }
    if (!legit) {
        printf("Помилка: некоректний ввід\n");
        return 0;
    }

    reverseWords(text);
    printf("Перетворений текст: %s\n", text);
    return 0;
}
