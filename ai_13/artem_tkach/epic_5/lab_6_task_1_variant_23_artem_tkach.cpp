// Лабораторна робота № 6, варіант 23.
// Знайти довжину найкоротшого слова у рядку, слова відокремлені пробілами.

#include <cstdio>
#include <cstring>

int main() {
    char text[258];
    if (std::fgets(text, sizeof(text), stdin) == nullptr) return 0;

    int length = static_cast<int>(std::strlen(text));
    if (length > 0 && text[length - 1] == '\n') {
        text[--length] = '\0';
    }

    int shortest = length;
    int currentLength = 0;

    for (int i = 0; i < length; ++i) {
        if (text[i] == ' ' || text[i] == '.') {
            if (currentLength > 0 && currentLength < shortest) {
                shortest = currentLength;
            }
            currentLength = 0;
        } else {
            ++currentLength;
        }
    }
    if (currentLength > 0 && currentLength < shortest) {
        shortest = currentLength;
    }

    std::printf("%d\n", shortest);
    return 0;
}
