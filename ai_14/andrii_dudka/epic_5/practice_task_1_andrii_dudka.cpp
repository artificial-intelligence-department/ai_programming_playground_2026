#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int MaxText = 255;
const int WordBuffer = 33;

bool validText(const char* text) {
    const size_t length = strlen(text);
    if (length < 2 || length > MaxText || text[length - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    for (size_t i = 0; i + 1 < length; ++i) {
        if (isalnum(static_cast<unsigned char>(text[i]))) {
            hasWord = true;
        } else if (text[i] != ' ') {
            return false;
        }
    }
    return hasWord;
}

void printTextError() {
    printf("Помилка: введіть хоча б одне слово та крапку в кінці. "
           "Дозволені латинські літери, цифри й пробіли. Ліміт 255 символів.\n");
}

char** splitWords(const char* text, int& count) {
    char copy[MaxText + 1];
    strcpy(copy, text);

    char** words = new char*[strlen(text)];
    count = 0;
    for (char* word = strtok(copy, " ."); word != nullptr; word = strtok(nullptr, " .")) {
        words[count] = new char[strlen(word) + 1];
        strcpy(words[count], word);
        ++count;
    }
    return words;
}

void freeWords(char**& words, int& count) {
    for (int i = 0; i < count; ++i) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void updateText(char* text, char**& words, int& count, const string& newText) {
    freeWords(words, count);
    strcpy(text, newText.c_str());
    words = splitWords(text, count);
}

void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = digits = spaces = 0;
    for (const char* p = text; *p != '\0'; ++p) {
        const unsigned char c = static_cast<unsigned char>(*p);
        if (isalpha(c)) {
            ++letters;
        } else if (isdigit(c)) {
            ++digits;
        } else if (c == ' ') {
            ++spaces;
        }
    }
}

void showStatistics(const char* text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    const int length = static_cast<int>(strlen(text));

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", length);
    printf("Слів:    %6d\n", wordCount);
    printf("Літер:   %6d (%5.1f%%)\n", letters, 100.0 * letters / length);
    printf("Цифр:    %6d (%5.1f%%)\n", digits, 100.0 * digits / length);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, 100.0 * spaces / length);
}

void showWords(char** words, int count) {
    int longest = 0;
    int shortest = 0;
    int totalLength = 0;
    for (int i = 0; i < count; ++i) {
        const size_t length = strlen(words[i]);
        totalLength += static_cast<int>(length);
        if (length > strlen(words[longest])) {
            longest = i;
        }
        if (length < strlen(words[shortest])) {
            shortest = i;
        }
    }

    const int longestLength = static_cast<int>(strlen(words[longest]));
    const int wordWidth = longestLength > 15 ? longestLength : 15;
    printf("  N | Слово%*s | Довж.\n", wordWidth - 5, "");
    for (int i = 0; i < count; ++i) {
        printf("%3d | %-*s | %5zu\n", i + 1, wordWidth, words[i], strlen(words[i]));
    }

    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", static_cast<double>(totalLength) / count);

    const char* sorted[(MaxText + 1) / 2];
    for (int i = 0; i < count; ++i) {
        sorted[i] = words[i];
    }
    for (int i = 1; i < count; ++i) {
        const char* word = sorted[i];
        int j = i;
        while (j > 0 && strcmp(sorted[j - 1], word) > 0) {
            sorted[j] = sorted[j - 1];
            --j;
        }
        sorted[j] = word;
    }

    printf("За абеткою:");
    for (int i = 0; i < count; ++i) {
        printf(" %s", sorted[i]);
    }
    putchar('\n');

    int mostFrequent = 0;
    int maxFrequency = 0;
    for (int first = 0; first < count;) {
        int end = first + 1;
        while (end < count && strcmp(sorted[first], sorted[end]) == 0) {
            ++end;
        }
        if (end - first > maxFrequency) {
            mostFrequent = first;
            maxFrequency = end - first;
        }
        first = end;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[mostFrequent], maxFrequency);
}

bool readWord(char* word) {
    if (scanf("%32s", word) != 1 || word[0] == '\0') {
        return false;
    }
    if (strlen(word) == WordBuffer - 1) {
        int c;
        do {
            c = getchar();
        } while (c != EOF && !isspace(c));
        return false;
    }
    for (int i = 0; word[i] != '\0'; ++i) {
        if (!isalnum(static_cast<unsigned char>(word[i]))) {
            return false;
        }
    }
    return true;
}

bool readPair(char* first, char* second, const char* firstPrompt, const char* secondPrompt) {
    printf("%s", firstPrompt);
    const bool firstValid = readWord(first);
    printf("%s", secondPrompt);
    const bool secondValid = readWord(second);
    if (!firstValid || !secondValid) {
        printf("Помилка: кожне слово має містити від 1 до 31 латинської літери або цифри.\n");
        return false;
    }
    return true;
}

void replaceWord(char* text, char**& words, int& count) {
    char fromInput[WordBuffer], toInput[WordBuffer];
    if (!readPair(fromInput, toInput, "Замінити слово: ", "На слово: ")) {
        return;
    }

    const string from = fromInput;
    const string to = toInput;
    string result = text;
    int replacements = 0;
    size_t position = 0;
    while ((position = result.find(from, position)) != string::npos) {
        const size_t end = position + from.length();
        const bool startsWord = position == 0 || result[position - 1] == ' ';
        const bool endsWord = result[end] == ' ' || result[end] == '.';
        if (startsWord && endsWord) {
            result.replace(position, from.length(), to);
            ++replacements;
            position += to.length();
        } else {
            ++position;
        }
    }

    if (result.length() > MaxText) {
        printf("Помилка: після заміни текст перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %zu\n", result.length());
    if (replacements > 0) {
        updateText(text, words, count, result);
    }
}

string lowerCase(string word) {
    for (char& c : word) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return word;
}

void compareWords() {
    char first[WordBuffer], second[WordBuffer];
    if (!readPair(first, second, "Перше слово: ", "Друге слово: ")) {
        return;
    }

    const int comparison = strcmp(first, second);
    if (comparison < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (comparison > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    const string a = first;
    const string b = second;
    const string joined = a + " & " + b;
    printf("Рівні (==): %s\n", a == b ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", lowerCase(a) == lowerCase(b) ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", a.length(), b.length());
    printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}

bool finishLine() {
    bool onlySpace = true;
    int c = getchar();
    while (c != '\n' && c != EOF) {
        if (!isspace(c)) {
            onlySpace = false;
        }
        c = getchar();
    }
    return onlySpace;
}

void printSymbol(unsigned char symbol) {
    if (isprint(symbol)) {
        printf("'%c'", symbol);
    } else {
        printf("'\\x%02x'", static_cast<unsigned int>(symbol));
    }
}

void showCharacter(const char* text) {
    printf("Введіть символ: ");
    char symbol;
    if (scanf("%c", &symbol) != 1) {
        return;
    }
    if (symbol != '\n' && !finishLine()) {
        printf("Помилка: введіть один символ.\n");
        return;
    }

    const unsigned int code = static_cast<unsigned char>(symbol);
    printf("Символ: ");
    printSymbol(static_cast<unsigned char>(code));
    printf("\nКод: %u (hex 0x%02x, oct %#o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; --bit) {
        printf("%u", (code >> bit) & 1U);
    }
    printf(")\n");

    const char* type = "інший символ";
    if (isupper(code)) {
        type = "велика літера";
    } else if (islower(code)) {
        type = "мала літера";
    } else if (isdigit(code)) {
        type = "цифра";
    } else if (isspace(code)) {
        type = "пробільний символ";
    }
    printf("Тип: %s\n", type);

    if (isalpha(code)) {
        const int otherCase = isupper(code) ? tolower(code) : toupper(code);
        printf("Інший регістр: ");
        printSymbol(static_cast<unsigned char>(otherCase));
        putchar('\n');
    }
    printf("Наступний символ: ");
    printSymbol(static_cast<unsigned char>(code + 1));
    putchar('\n');

    int occurrences = 0;
    for (const char* p = text; *p != '\0'; ++p) {
        if (*p == symbol) {
            ++occurrences;
        }
    }
    if (occurrences == 0) {
        printf("Цей символ у тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %td\n",
               occurrences, strchr(text, symbol) - text + 1);
    }
}

void readSentence(char* text, char**& words, int& count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence;
    string word;

    while (cin >> word) {
        if (sentence.length() <= MaxText) {
            if (!sentence.empty()) {
                sentence += ' ';
            }
            sentence += word;
        }
        if (word.back() == '.') {
            break;
        }
    }

    if (sentence.length() > MaxText) {
        printf("Помилка: речення перевищує 255 символів.\n");
        return;
    }
    if (!validText(sentence.c_str())) {
        printTextError();
        return;
    }

    updateText(text, words, count, sentence);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}

void showMenu() {
    printf("\n1. Показати текст і статистику\n"
           "2. Таблиця слів\n"
           "3. Замінити слово\n"
           "4. Порівняти два слова\n"
           "5. Інформація про символ\n"
           "6. Ввести нове речення\n"
           "0. Вийти\n"
           "Ваш вибір: ");
}

int main() {
    char line[MaxText + 3];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(line, sizeof(line), stdin) == nullptr) {
        printTextError();
        return 0;
    }
    char* newline = strchr(line, '\n');
    if (newline != nullptr) {
        *newline = '\0';
    }
    const size_t length = strlen(line);
    if (length > 0 && line[length - 1] == '\r') {
        line[length - 1] = '\0';
    }
    if (!validText(line)) {
        printTextError();
        return 0;
    }

    char text[MaxText + 1];
    strcpy(text, line);
    int count;
    char** words = splitWords(text, count);
    while (true) {
        showMenu();
        int choice;
        const int status = scanf("%4d", &choice);
        if (status == EOF) {
            break;
        }
        const bool validLine = finishLine();
        if (status != 1 || !validLine) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                showStatistics(text, count);
                break;
            case 2:
                showWords(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharacter(text);
                break;
            case 6:
                readSentence(text, words, count);
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    }
    freeWords(words, count);
}
