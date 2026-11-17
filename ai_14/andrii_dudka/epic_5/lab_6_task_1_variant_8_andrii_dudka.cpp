#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool only_digits(const char* word) {
    for (int i = 0; word[i] != '\0'; ++i) {
        if (!is_digit(word[i])) {
            return false;
        }
    }
    return true;
}

void print_identifier(const char* word) {
    cout << "id_";
    bool last_underscore = true;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (is_letter(word[i]) || is_digit(word[i])) {
            cout << word[i];
            last_underscore = false;
        } else if (!last_underscore) {
            cout << '_';
            last_underscore = true;
        }
    }
}

int main() {
    char s[257];
    cout << "Рядок: " << flush;
    if (fgets(s, sizeof(s), stdin) == nullptr) {
        return 0;
    }

    char* newline = strchr(s, '\n');
    if (newline != nullptr) {
        *newline = '\0';
    }

    size_t length = strlen(s);
    if (length > 0 && s[length - 1] == '\r') {
        s[--length] = '\0';
    }
    if (length == 0 || length > 255 || s[length - 1] != '.') {
        cerr << "Рядок має містити до 255 символів і завершуватися крапкою.\n";
        return 1;
    }
    s[length - 1] = '\0';

    bool printed = false;
    for (char* word = strtok(s, " "); word != nullptr; word = strtok(nullptr, " ")) {
        if (only_digits(word)) {
            continue;
        }
        if (printed) {
            cout << ' ';
        }
        print_identifier(word);
        printed = true;
    }

    cout << ".";
}
