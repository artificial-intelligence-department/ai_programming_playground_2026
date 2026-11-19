/*Практична задача - редактор текстових повідомлень
Швець Аріна - ШІ-13*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

bool isLatinLetterOrDigit(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

bool isValidWord(const char *word){
    size_t length = strlen(word);
    if (length == 0 || length > 31){
        return false;
    }
    for (const char *p = word; *p != '\0'; ++p){
        if (!isLatinLetterOrDigit(*p)){
            return false;
        }
    }
    return true;
}

bool isValidText(const char *text){
    size_t length = strlen(text);
    if (length < 2 || length > 255 || text[length - 1] != '.'){
        return false;
    }
    if (!isLatinLetterOrDigit(text[length - 2])){
        return false;
    }

    bool hasWord = false;
    for (size_t i = 0; i + 1 < length; ++i){
        if (isLatinLetterOrDigit(text[i])){
            hasWord = true;
        }
        else if (text[i] != ' '){
            return false;
        }
    }
    return hasWord;
}

bool readLine(char text[], int size){
    if (fgets(text, size, stdin) == nullptr){
        return false;
    }

    char *newline = strchr(text, '\n');
    if (newline != nullptr){
        *newline = '\0';
    }
    else{
        char extra;
        if (scanf("%c", &extra) == 1 && extra != '\n'){
            while (scanf("%c", &extra) == 1 && extra != '\n'){
            }
            return false;
        }
    }

    size_t length = strlen(text);
    if (length > 0 && text[length - 1] == '\r'){
        text[length - 1] = '\0';
    }
    return true;
}

bool readInitialText(char text[256]){
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!readLine(text, 256)){
        return false;
    }
    return isValidText(text);
}

char **splitWords(const char *text, int &count){
    char temporary[256];
    strcpy(temporary, text);
    char *period = strchr(temporary, '.');
    if (period){
        *period = '\0';
    }

    count = 0;
    for (char *token = strtok(temporary, " "); token != nullptr; token = strtok(nullptr, " ")){
        ++count;
    }

    char **words = new char *[count];
    strcpy(temporary, text);
    period = strchr(temporary, '.');
    if (period){
        *period = '\0';
    }

    int index = 0;
    for (char *token = strtok(temporary, " "); token != nullptr; token = strtok(nullptr, " ")){
        words[index] = new char[strlen(token) + 1];
        strcpy(words[index], token);
        ++index;
    }
    return words;
}

void freeWords(char **&words, int &count){
    if (words != nullptr){
        for (int i = 0; i < count; ++i){
            delete[] words[i];
        }
        delete[] words;
    }
    words = nullptr;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = digits = spaces = 0;
    for (const char *p = text; *p != '\0'; ++p){
        unsigned char c = static_cast<unsigned char>(*p);
        if (isalpha(c)){
            ++letters;
        }
        else if (isdigit(c)){
            ++digits;
        }
        else if (*p == ' '){
            ++spaces;
        }
    }
}

bool discardLineAndCheckTail(){
    bool onlyWhitespace = true;
    char c;
    while (scanf("%c", &c) == 1 && c != '\n'){
        if (c != ' ' && c != '\t' && c != '\r'){
            onlyWhitespace = false;
        }
    }
    return onlyWhitespace;
}

bool readMenuChoice(int &choice){
    printf("\nВаш вибір: ");
    int result = scanf("%d", &choice);
    if (result < 0){
        return false;
    }
    bool validTail = discardLineAndCheckTail();
    if (result != 1 || !validTail){
        printf("Помилка: введіть номер пункту меню.\n");
        choice = -1;
    }
    return true;
}

bool readSingleWord(const char *prompt, char word[32]){
    printf("%s", prompt);
    if (!readLine(word, 32) || !isValidWord(word)){
        printf("Помилка: введіть одне слово з 1-31 латинських літер або цифр.\n");
        return false;
    }
    return true;
}

void showStatistics(const char *text, int count){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = static_cast<int>(strlen(text));
    printf("\nТекст:\t\"%s\"\n", text);
    printf("Символів: %6d\n", length);
    printf("Слів:     %6d\n", count);
    printf("Літер:    %6d (%5.1f%%)\n", letters, 100.0 * letters / length);
    printf("Цифр:     %6d (%5.1f%%)\n", digits, 100.0 * digits / length);
    printf("Пробілів: %6d (%5.1f%%)\n", spaces, 100.0 * spaces / length);
}

void printSeparator(int wordWidth){
    printf("+-----+");
    for (int i = 0; i < wordWidth + 2; ++i){
        printf("-");
    }
    printf("+--------+\n");
}

void showWordsTable(char **words, int count){
    if (count == 0){
        return;
    }
    int longest = 0, shortest = 0, totalLength = 0;
    for (int i = 0; i < count; ++i){
        int len = static_cast<int>(strlen(words[i]));
        totalLength += len;
        if (len > static_cast<int>(strlen(words[longest]))){
            longest = i;
        }
        if (len < static_cast<int>(strlen(words[shortest]))){
            shortest = i;
        }
    }

    int wordWidth = 16;
    for (int i = 0; i < count; ++i){
        int len = static_cast<int>(strlen(words[i]));
        if (len > wordWidth){
            wordWidth = len;
        }
    }

    printf("\nТаблиця слів:\n");
    printSeparator(wordWidth);
    printf("| %3s | %-*s | %s |\n", "N", wordWidth + 5, "Слово", "Довж. ");
    printSeparator(wordWidth);
    for (int i = 0; i < count; ++i){
        printf("| %3d | %-*s | %6zu |\n", i + 1, wordWidth, words[i], strlen(words[i]));
    }
    printSeparator(wordWidth);
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", static_cast<double>(totalLength) / count);

    char **sorted = new char *[count];
    for (int i = 0; i < count; ++i){
        sorted[i] = words[i];
    }

    for (int i = 1; i < count; ++i){
        char *current = sorted[i];
        int j = i - 1;
        while (j >= 0 && strcmp(sorted[j], current) > 0){
            sorted[j + 1] = sorted[j];
            --j;
        }
        sorted[j + 1] = current;
    }

    printf("За абеткою:");
    for (int i = 0; i < count; ++i){
        printf(" %s", sorted[i]);
    }
    printf("\n");

    char *mostFrequent = sorted[0];
    int mostCount = 0;
    for (int i = 0; i < count;){
        int j = i + 1;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0){
            ++j;
        }
        if (j - i > mostCount){
            mostCount = j - i;
            mostFrequent = sorted[i];
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", mostFrequent, mostCount);
    delete[] sorted;
}

void replaceWord(char text[256], char **&words, int &count){
    char from[32], to[32];
    if (!readSingleWord("Замінити слово: ", from)){
        return;
    }
    if (!readSingleWord("На слово: ", to)){
        return;
    }

    string before(text);
    string after = before;
    string oldWord(from), newWord(to);
    int replacements = 0;
    string::size_type position = 0;

    while ((position = after.find(oldWord, position)) != string::npos){
        string::size_type end = position + oldWord.length();
        bool wholeLeft = (position == 0 || after[position - 1] == ' ');
        bool wholeRight = (end == after.length() || after[end] == ' ' || after[end] == '.');
        if (wholeLeft && wholeRight){
            after.replace(position, oldWord.length(), newWord);
            ++replacements;
            position += newWord.length();
        } else {
            position += oldWord.length();
        }
    }

    if (after.length() > 255){
        printf("Помилка: після заміни текст перевищив би 255 символів.\n");
        return;
    }

    int newCount = 0;
    char **newWords = splitWords(after.c_str(), newCount);
    freeWords(words, count);
    strcpy(text, after.c_str());
    words = newWords;
    count = newCount;

    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", after.length());
}

void compareTwoWords(){
    char first[32], second[32];
    if (!readSingleWord("Перше слово: ", first)){
        return;
    }
    if (!readSingleWord("Друге слово: ", second)){
        return;
    }

    int comparison = strcmp(first, second);
    int sign = (comparison > 0) - (comparison < 0);
    string a(first), b(second);
    bool equalWithoutCase = (a.length() == b.length());
    if (equalWithoutCase){
        for (size_t i = 0; i < a.length(); ++i){
            if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i]))){
                equalWithoutCase = false;
                break;
            }
        }
    }

    printf("strcmp: %d -> ", sign);
    if (sign < 0){
        printf("перше слово менше\n");
    }
    else if (sign > 0){
        printf("перше слово більше\n");
    }
    else{
        printf("слова однакові\n");
    }
    printf("Рівні (==): %s\n", (a == b) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalWithoutCase ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", a.length(), b.length());
    string joined = a + " & " + b;
    printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}

void showSymbolInfo(const char *text){
    printf("Введіть символ: ");
    char symbol;
    if (scanf("%c", &symbol) != 1){
        return;
    }
    if (symbol == '\n'){
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }

    bool extra = false;
    char extraChar;
    while (scanf("%c", &extraChar) == 1 && extraChar != '\n'){
        if (extraChar != '\r'){
            extra = true;
        }
    }
    if (extra){
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }

    unsigned char code = static_cast<unsigned char>(symbol);
    printf("Символ: '%c'\n", symbol);
    printf("Код: %u (hex 0x%02x, oct 0%o, bin ", static_cast<unsigned int>(code), static_cast<unsigned int>(code), static_cast<unsigned int>(code));
    for (int bit = 7; bit >= 0; --bit){
        printf("%u", (static_cast<unsigned int>(code) >> bit) & 1u);
    }
    printf(")\n");

    if (isupper(code)){
        printf("Тип: велика літера\n");
    }
    else if (islower(code)){
        printf("Тип: мала літера\n");
    }
    else if (isdigit(code)){
        printf("Тип: цифра\n");
    }
    else if (isspace(code)){
        printf("Тип: пробільний символ\n");
    }
    else{
        printf("Тип: інший символ\n");
    }

    if (isalpha(code)){
        char other = static_cast<char>(islower(code) ? toupper(code) : tolower(code));
        printf("Інший регістр: '%c'\n", other);
    }
    unsigned int nextCode = static_cast<unsigned int>(code) + 1;
    if (nextCode <= 255 && isprint(static_cast<unsigned char>(nextCode))){
        printf("Наступний символ: '%c'\n", static_cast<char>(nextCode));
    } else {
        printf("Наступний код: %u (недрукований символ)\n", nextCode);
    }

    const char *firstOccurrence = strchr(text, symbol);
    int occurrences = 0;
    for (const char *p = text; *p != '\0'; ++p){
        if (*p == symbol){
            ++occurrences;
        }
    }
    if (firstOccurrence){
        printf("Входжень у тексті: %d, перше на позиції %td\n", occurrences, firstOccurrence - text + 1);
    } else {
        printf("Символ у тексті не зустрічається.\n");
    }
}

void enterNewSentence(char text[256], char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");
    char sentence[256] = "";
    string word;
    int readCount = 0;
    bool tooLong = false, finished = false;

    while (cin >> word){
        ++readCount;
        size_t oldLength = strlen(sentence);
        size_t required = oldLength + (readCount > 1 ? 1u : 0u) + word.length();
        if (required > 255){
            tooLong = true;
        }
        else if (!tooLong){
            if (readCount > 1){
                strcat(sentence, " ");
            }
            strcat(sentence, word.c_str());
        }
        if (!word.empty() && word[word.length() - 1] == '.'){
            finished = true;
            break;
        }
    }

    bool extraAfterPeriod = false;
    if (finished){
        char extraChar;
        while (cin.get(extraChar) && extraChar != '\n'){
            if (extraChar != ' ' && extraChar != '\t' && extraChar != '\r'){
                extraAfterPeriod = true;
            }
        }
    }

    if (!finished || tooLong || extraAfterPeriod || !isValidText(sentence)){
        printf("Помилка: речення некоректне або довше за 255 символів.\n");
        return;
    }

    int newCount = 0;
    char **newWords = splitWords(sentence, newCount);
    freeWords(words, count);
    strcpy(text, sentence);
    words = newWords;
    count = newCount;

    printf("Прочитано слів: %d\n", readCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

void printMenu(){
    printf("\n========== МЕНЮ РЕДАКТОРА ==========\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
}

int main(){
    char text[256];
    if (!readInitialText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою; максимум 255 символів.\n");
        return 0;
    }

    int count = 0;
    char **words = splitWords(text, count);

    while (true){
        printMenu();
        int choice;
        if (!readMenuChoice(choice)){
            break;
        }
        switch (choice){
            case 0:
                freeWords(words, count);
                printf("Роботу завершено.\n");
                return 0;
            case 1:
                showStatistics(text, count);
                break;
            case 2:
                showWordsTable(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareTwoWords();
                break;
            case 5:
                showSymbolInfo(text);
                break;
            case 6:
                enterNewSentence(text, words, count);
                break;
            case -1:
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    }

    freeWords(words, count);
    return 0;
}