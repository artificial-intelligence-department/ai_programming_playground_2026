#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>

bool isIdentifier(const char* word) {
    if (word[0] == '\0') return false;

    //перший символ літера або _
    if (!isalpha(word[0]) && word[0] != '_') {
        return false;
    }

    //наступні літери цифри _
    for (int i = 1; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return false;
        }
    }

    return true;
}

int main() {
    char s[256];
    char res[256] = ""; // новий рядок для ідентифікаторів
    char word[256];     // тимчасовий буфер для одного слова

    fgets(s, sizeof(s), stdin); 

    int i = 0;
    bool firstWord = true;

    while (s[i] != '\0' && s[i] != '.' && s[i] != '\n' && s[i] != '\r') {
        // пропускаємо пробіли
        while (s[i] == ' ') {
            i++;
        }

        //дійшли до крапки/кінця рядка виходимо
        if (s[i] == '\0' || s[i] == '.' || s[i] == '\n' || s[i] == '\r') {
            break;
        }

        // виділяємо слово
        int len = 0;
        while (s[i] != ' ' && s[i] != '.' && s[i] != '\0' && s[i] != '\n' && s[i] != '\r') {
            word[len++] = s[i++];
        }
        word[len] = '\0';

        if (isIdentifier(word)) {
            if (!firstWord) {
                strcat(res, " ");
            }
            strcat(res, word);
            firstWord = false;
        }
    }

    strcat(res, ".");
    strcpy(s, res);
    std::cout << s << std::endl;

    return 0;
}