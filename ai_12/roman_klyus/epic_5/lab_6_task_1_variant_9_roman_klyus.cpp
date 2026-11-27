#include <cstdio>
#include <cstring>

using namespace std;

bool is_palindrome(const char* word) {
    int len = strlen(word);

    for (int i {0}; i < len / 2; i++) {
        if (word[i] != word[len - i - 1]) return false;
    }
    return true;
}

bool input_text(char *s, int size) {
    while (true) {
        printf("Введіть текст: ");
        if (fgets(s, size, stdin) == nullptr) return false;

        char *nl = strchr(s, '\n');
        if (nl != nullptr) *nl = '\0';

        int len = strlen(s);
        if (len > 0 && s[len - 1] == '.') {
            s[len - 1] = '\0';
            return true;
        }
        printf("Текст не може бути порожнім і повинен закінчуватись крапкою.\n");
    }
}

int main() {
    char s[256];
    input_text(s, 256);
    
    bool found = false;

    for (char *w = strtok(s, " "); w != nullptr; w = strtok(nullptr, " ")) {
        if (is_palindrome(w)) {
            printf("%s\n", w);
            found = true;
        }
    }
    if (!found) printf("В цьому рядку паліндромів нема.\n");

}