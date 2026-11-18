#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

void sortDigitsInText(char* text, const int* numPos, int count) {
    if (count < 2) return;
    
    for (int i = 0; i < count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < count - 1 - i; j++) {
            if (text[numPos[j]] < text[numPos[j + 1]]) {
                char temp = text[numPos[j]];
                text[numPos[j]] = text[numPos[j + 1]];
                text[numPos[j + 1]] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    const int MAX_LEN = 1000;
    char* buffer = new char[MAX_LEN + 1];

    size_t len = 0;
    while (true) {
        if (fgets(buffer, MAX_LEN, stdin) == nullptr) continue;
        len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        bool isValid = true;
        for (size_t i = 0; i < len; ++i) {
            if (!(isalpha(buffer[i]) || isdigit(buffer[i]) || buffer[i] == ' ')) {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            printf("Помилка: дозволені лише латинські літери, цифри та пробіли.\n\n");
            continue;
        }
        break;
    }

    char* text = new char[len + 1];
    strcpy(text, buffer);
    delete[] buffer; 

    int countNum = 0;
    for (size_t c = 0; c < len; c++) {
        if (isdigit(text[c])) countNum++;
    }


    int* numPos = new int[countNum];

    int index = 0;
    for (size_t c = 0; c < len; c++) {
        if (isdigit(text[c])) {
            numPos[index++] = c;
        }
    }

    sortDigitsInText(text, numPos, countNum);

    delete[] numPos;

    printf("Результат: %s\n", text);

    delete[] text;
    return 0;
}