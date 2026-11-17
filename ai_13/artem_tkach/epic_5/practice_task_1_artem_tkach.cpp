/*
 * Практична робота: Редактор текстових повідомлень
 * Ткач Артем Ігорович, ШІ-13
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

const int TEXT_CAPACITY = 256;
const int WORD_CAPACITY = 32;

bool isAsciiLetterOrDigit(unsigned char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
           (ch >= '0' && ch <= '9');
}

bool isValidWord(const char *word) {
    if (word == nullptr || word[0] == '\0' || std::strlen(word) >= WORD_CAPACITY) return false;
    for (const unsigned char *p = reinterpret_cast<const unsigned char *>(word); *p; ++p) {
        if (!isAsciiLetterOrDigit(*p)) return false;
    }
    return true;
}

bool isValidText(const char *text) {
    const std::size_t length = std::strlen(text);
    if (length < 2 || length >= TEXT_CAPACITY || text[length - 1] != '.') return false;
    if (std::strchr(text, '.') != text + length - 1) return false;

    bool hasWord = false;
    for (std::size_t i = 0; i < length; ++i) {
        const unsigned char ch = static_cast<unsigned char>(text[i]);
        if (isAsciiLetterOrDigit(ch)) hasWord = true;
        else if (ch != ' ' && ch != '.') return false;
    }
    return hasWord;
}

char **splitWords(const char *text, int &count) {
    count = 0;
    const std::size_t length = std::strlen(text);
    char buffer[TEXT_CAPACITY];
    std::strcpy(buffer, text);

    int capacity = 1;
    for (std::size_t i = 0; i < length; ++i) {
        if (buffer[i] == ' ') ++capacity;
    }
    char **words = new char *[capacity];
    for (int i = 0; i < capacity; ++i) words[i] = nullptr;

    char *token = std::strtok(buffer, " .");
    while (token != nullptr) {
        const std::size_t wordLength = std::strlen(token);
        words[count] = new char[wordLength + 1];
        std::strcpy(words[count], token);
        ++count;
        token = std::strtok(nullptr, " .");
    }
    return words;
}

void freeWords(char **&words, int &count) {
    if (words != nullptr) {
        for (int i = 0; i < count; ++i) delete[] words[i];
        delete[] words;
    }
    words = nullptr;
    count = 0;
}

bool rebuildWords(const char *text, char **&words, int &count) {
    int newCount = 0;
    char **newWords = splitWords(text, newCount);
    if (newWords == nullptr) return false;
    freeWords(words, count);
    words = newWords;
    count = newCount;
    return true;
}

bool readInitialText(char *text) {
    std::printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (std::fgets(text, TEXT_CAPACITY, stdin) == nullptr) return false;

    std::size_t length = std::strlen(text);
    if (length > 0 && text[length - 1] == '\n') {
        text[--length] = '\0';
    } else if (!std::feof(stdin)) {
        int ch = std::getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = std::getchar()) != '\n' && ch != EOF) {}
            std::printf("Помилка: текст задовгий.\n");
            return false;
        }
    }

    if (!isValidText(text)) {
        std::printf("Помилка: текст має містити слова лише з латинських літер і цифр,\n"
                    "розділені пробілами, та завершуватися крапкою.\n");
        return false;
    }
    return true;
}

void showMenu() {
    std::printf("\nМеню:\n"
                "1 - Показати текст і статистику\n"
                "2 - Таблиця слів\n"
                "3 - Замінити слово\n"
                "4 - Порівняти два слова\n"
                "5 - Інформація про символ\n"
                "6 - Ввести нове речення\n"
                "0 - Вийти\n");
}

int readChoice() {
    int choice;
    std::printf("Ваш вибір: ");
    if (std::scanf("%d", &choice) != 1) {
        int ch;
        while ((ch = std::getchar()) != '\n' && ch != EOF) {}
        std::printf("Помилка: введіть номер пункту меню.\n");
        return -1;
    }
    int ch;
    while ((ch = std::getchar()) != '\n' && ch != EOF) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            while ((ch = std::getchar()) != '\n' && ch != EOF) {}
            std::printf("Помилка: введіть лише один номер пункту.\n");
            return -1;
        }
    }
    return choice;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    const unsigned char *p = reinterpret_cast<const unsigned char *>(text);
    while (*p) {
        if (std::isalpha(*p)) ++letters;
        else if (std::isdigit(*p)) ++digits;
        else if (*p == ' ') ++spaces;
        ++p;
    }
}

void showTextAndStatistics(const char *text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    const int length = static_cast<int>(std::strlen(text));
    const double denominator = length == 0 ? 1.0 : static_cast<double>(length);
    std::printf("Текст:\t\"%s\"\n", text);
    std::printf("Символів:\t%3d\n", length);
    std::printf("Слів:\t\t%3d\n", wordCount);
    std::printf("Літер:\t\t%3d (%5.1f%%)\n", letters, letters * 100.0 / denominator);
    std::printf("Цифр:\t\t%3d (%5.1f%%)\n", digits, digits * 100.0 / denominator);
    std::printf("Пробілів:\t%3d (%5.1f%%)\n", spaces, spaces * 100.0 / denominator);
}

void showWordTable(char **words, int count) {
    if (count == 0) {
        std::printf("Слів немає.\n");
        return;
    }

    int longest = 0, shortest = 0;
    double totalLength = 0.0;
    std::printf("+----+-----------------+-------+\n| N  | Слово           | Довж. |\n+----+-----------------+-------+\n");
    for (int i = 0; i < count; ++i) {
        const int length = static_cast<int>(std::strlen(words[i]));
        std::printf("|%3d | %-15s | %5d |\n", i + 1, words[i], length);
        totalLength += length;
        if (length > static_cast<int>(std::strlen(words[longest]))) longest = i;
        if (length < static_cast<int>(std::strlen(words[shortest]))) shortest = i;
    }
    std::printf("+----+-----------------+-------+\n");
    std::printf("Найдовше слово: %s (%zu)\n", words[longest], std::strlen(words[longest]));
    std::printf("Найкоротше слово: %s (%zu)\n", words[shortest], std::strlen(words[shortest]));
    std::printf("Середня довжина: %.2f\n", totalLength / count);

    char **sorted = new char *[count];
    for (int i = 0; i < count; ++i) sorted[i] = words[i];
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (std::strcmp(sorted[i], sorted[j]) > 0) {
                char *temporary = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temporary;
            }
        }
    }
    std::printf("За абеткою:");
    for (int i = 0; i < count; ++i) std::printf(" %s", sorted[i]);

    int bestCount = 0;
    const char *mostFrequent = sorted[0];
    for (int i = 0; i < count; ++i) {
        int occurrences = 0;
        for (int j = 0; j < count; ++j) {
            if (std::strcmp(sorted[i], sorted[j]) == 0) ++occurrences;
        }
        if (occurrences > bestCount) {
            bestCount = occurrences;
            mostFrequent = sorted[i];
        }
    }
    std::printf("\nНайчастіше слово: %s (%d)\n", mostFrequent, bestCount);
    delete[] sorted;
}

bool readWord(const char *prompt, char *word) {
    std::printf("%s", prompt);
    if (std::scanf("%255s", word) != 1) return false;
    int ch;
    while ((ch = std::getchar()) != '\n' && ch != EOF) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            while ((ch = std::getchar()) != '\n' && ch != EOF) {}
            return false;
        }
    }
    return true;
}

void replaceWord(char *text, char **&words, int &wordCount) {
    char from[TEXT_CAPACITY], to[TEXT_CAPACITY];
    if (!readWord("Замінити слово: ", from) || !readWord("На слово: ", to) ||
        !isValidWord(from) || !isValidWord(to)) {
        std::printf("Помилка: введіть два слова з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    const std::string source(text);
    std::string result = source;
    const std::string fromString(from), toString(to);
    std::size_t position = 0;
    int replacements = 0;
    while ((position = result.find(fromString, position)) != std::string::npos) {
        const bool leftBoundary = position == 0 || result[position - 1] == ' ';
        const std::size_t after = position + fromString.length();
        const bool rightBoundary = after == result.length() || result[after] == ' ' || result[after] == '.';
        if (leftBoundary && rightBoundary) {
            result.replace(position, fromString.length(), toString);
            ++replacements;
            position += toString.length();
        } else {
            position += fromString.length();
        }
    }

    if (result.length() >= TEXT_CAPACITY) {
        std::printf("Помилка: результат перевищує 255 символів; текст не змінено.\n");
        return;
    }

    std::printf("Замін виконано: %d\nБуло:  \"%s\"\nСтало: \"%s\"\nНова довжина: %zu\n",
                replacements, text, result.c_str(), result.length());
    std::strcpy(text, result.c_str());
    rebuildWords(text, words, wordCount);
}

void compareWords() {
    char first[TEXT_CAPACITY], second[TEXT_CAPACITY];
    if (!readWord("Перше слово: ", first) || !readWord("Друге слово: ", second) ||
        !isValidWord(first) || !isValidWord(second)) {
        std::printf("Помилка: введіть два слова з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    const std::string a(first), b(second);
    int caseInsensitiveEqual = a.length() == b.length();
    if (caseInsensitiveEqual) {
        for (std::size_t i = 0; i < a.length(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) !=
                std::tolower(static_cast<unsigned char>(b[i]))) {
                caseInsensitiveEqual = 0;
                break;
            }
        }
    }
    const std::string joined = a + " & " + b;
    const int rawComparison = std::strcmp(first, second);
    const int cmp = (rawComparison > 0) - (rawComparison < 0);
    std::printf("Перше слово: %s\nДруге слово: %s\nstrcmp: %d\n", first, second, cmp);
    std::printf("Рівні (==): %s\nРівні без урахування регістру: %s\n",
                a == b ? "так" : "ні", caseInsensitiveEqual ? "так" : "ні");
    std::printf("Довжини: %zu і %zu\nКонкатенація: \"%s\" (%zu)\n",
                a.length(), b.length(), joined.c_str(), joined.length());
}

void showCharacterInfo(char *text) {
    char value;
    std::printf("Введіть символ: ");
    if (std::scanf(" %c", &value) != 1) {
        std::printf("Помилка введення символу.\n");
        return;
    }
    int ch;
    while ((ch = std::getchar()) != '\n' && ch != EOF) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            while ((ch = std::getchar()) != '\n' && ch != EOF) {}
            std::printf("Помилка: введіть лише один символ.\n");
            return;
        }
    }

    const unsigned char code = static_cast<unsigned char>(value);
    char binary[9];
    for (int bit = 7; bit >= 0; --bit) binary[7 - bit] = ((code >> bit) & 1) ? '1' : '0';
    binary[8] = '\0';
    std::printf("Символ: '%c'\nКод: %u (hex 0x%02X, oct 0%o, bin %s)\n",
                value, static_cast<unsigned int>(code), static_cast<unsigned int>(code),
                static_cast<unsigned int>(code), binary);

    const char *type = "інший символ";
    if (std::isupper(code)) type = "велика літера";
    else if (std::islower(code)) type = "мала літера";
    else if (std::isdigit(code)) type = "цифра";
    else if (std::isspace(code)) type = "пробільний символ";
    std::printf("Тип: %s\n", type);
    if (std::isalpha(code)) {
        const char otherCase = static_cast<char>(std::islower(code) ? std::toupper(code) : std::tolower(code));
        std::printf("Інший регістр: '%c'\n", otherCase);
    }
    std::printf("Наступний символ: '%c'\n", static_cast<char>(code + 1));

    int occurrences = 0, firstPosition = -1;
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] == value) {
            if (firstPosition == -1) firstPosition = i + 1;
            ++occurrences;
        }
    }
    if (occurrences == 0) std::printf("У тексті символ не зустрічається.\n");
    else std::printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPosition);
}

bool readNewSentence(std::string &sentence, int &wordCount) {
    std::cout << "Введіть речення (крапка після останнього слова):\n";
    sentence.clear();
    wordCount = 0;
    std::string word;
    bool finished = false;
    bool valid = true;
    while (std::cin >> word) {
        const bool hasPeriod = !word.empty() && word.back() == '.';
        if (hasPeriod) word.pop_back();
        if (word.empty()) valid = false;
        for (unsigned char ch : word) {
            if (!isAsciiLetterOrDigit(ch)) valid = false;
        }
        if (word.length() >= WORD_CAPACITY) valid = false;
        const std::size_t addedLength = word.length() + (sentence.empty() ? 0 : 1) + (hasPeriod ? 1 : 0);
        if (sentence.length() + addedLength >= TEXT_CAPACITY) valid = false;
        if (valid) {
            if (!sentence.empty()) sentence += ' ';
            sentence += word;
            ++wordCount;
        }
        if (hasPeriod) {
            finished = true;
            if (valid) sentence += '.';
            break;
        }
    }
    return finished && valid && sentence.length() < TEXT_CAPACITY && isValidText(sentence.c_str());
}

void enterNewSentence(char *text, char **&words, int &wordCount) {
    std::string sentence;
    int readCount = 0;
    if (!readNewSentence(sentence, readCount)) {
        std::cout << "Помилка: речення має містити слова з латинських літер і цифр, "
                     "завершуватися крапкою та мати не більше 255 символів.\n";
        return;
    }
    std::strcpy(text, sentence.c_str());
    rebuildWords(text, words, wordCount);
    std::cout << "Прочитано слів: " << readCount << "\nНове речення: \"" << text
              << "\"\nДовжина: " << std::strlen(text) << '\n';
}

int main() {
    char text[TEXT_CAPACITY];
    if (!readInitialText(text)) return 1;

    int wordCount = 0;
    char **words = splitWords(text, wordCount);
    if (words == nullptr || wordCount == 0) {
        freeWords(words, wordCount);
        return 1;
    }

    bool running = true;
    while (running) {
        showMenu();
        const int choice = readChoice();
        switch (choice) {
            case 0: running = false; break;
            case 1: showTextAndStatistics(text, wordCount); break;
            case 2: showWordTable(words, wordCount); break;
            case 3: replaceWord(text, words, wordCount); break;
            case 4: compareWords(); break;
            case 5: showCharacterInfo(text); break;
            case 6: enterNewSentence(text, words, wordCount); break;
            case -1: break;
            default: std::printf("Помилка: пункту %d немає в меню.\n", choice); break;
        }
    }

    freeWords(words, wordCount);
    return 0;
}
