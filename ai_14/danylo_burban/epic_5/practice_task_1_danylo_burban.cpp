#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <string>

using namespace std;
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextStatistic(char *text, int wordCount);
void wordsTable(char **words, int count);
void swapWord(char *text,string origin, string paste);
void wordCompare(const char *first,const char *second);
void charCrypt(char c, const char *text);
void setNewSentence(char *text, const char *rawInput);
void buildWords(const char *text, char **&words, int &count);
void freeWords(char **&words, int &count);
bool isValidWord(const string &w);
void replaceWord(char *text, char **&words, int &wordCount);
void compareWords();
void charInfo(const char *text);
void newSentence(char *text, char **&words, int &wordCount);

static bool isWordChar(char ch) {
    return isalnum(static_cast<unsigned char>(ch)) != 0;
}

size_t findWholeWord(const string &s, const string &w, size_t pos) {
    while ((pos = s.find(w, pos)) != string::npos) {
        bool leftOk  = (pos == 0) || !isWordChar(s[pos - 1]);
        size_t end   = pos + w.length();
        bool rightOk = (end >= s.length()) || !isWordChar(s[end]);
        if (leftOk && rightOk) {
            return pos;
        }
        pos++;
    }
    return string::npos;
}

bool readFirstWord(string &out) {
    string line;
    if (!getline(cin, line)) {
        return false;
    }
    size_t start = line.find_first_not_of(" \t\r");
    if (start == string::npos) {
        out = "";
        return true;
    }
    size_t end = line.find_first_of(" \t\r", start);
    out = line.substr(start, end == string::npos ? string::npos : end - start);
    return true;
}

int main() {
    char text[256] = "";
    char **words = nullptr;
    int wordCount = 0;
    while (true) {
        printf("Введіть текст (до 255 символів, крапка в кінці):\n");
        char input[1024];
        if (fgets(input, sizeof(input), stdin) == nullptr) {
            return 0;
        }
        if (strchr(input, '\n') == nullptr) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }
        int rawLen = strlen(input);
        while (rawLen > 0 && (input[rawLen - 1] == '\n' || input[rawLen - 1] == '\r')) {
            input[--rawLen] = '\0';
        }

        if (rawLen == 0 || rawLen > 255) {
            printf("Помилка: текст має складатися з латинських літер, цифр\n"
                   "і пробілів та завершуватися крапкою.\n");
            continue;
        }

        bool isValid = (input[rawLen - 1] == '.');
        bool hasAlnum = false;

        for (int i = 0; i < rawLen - 1 && isValid; i++) {
            unsigned char uc = static_cast<unsigned char>(input[i]);
            if (isalpha(uc) || isdigit(uc)) {
                hasAlnum = true;
            } else if (uc != ' ') {
                isValid = false;
            }
        }

        if (!isValid || !hasAlnum) {
            printf("Помилка: текст має складатися з латинських літер, цифр\nі пробілів та завершуватися крапкою.\n");
            continue;
        }

        strcpy(text, input);
        break;
    }

    buildWords(text, words, wordCount);

    while (true) {
        printf("\nМеню:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");

        int choice = -1;
        while (true) {
            printf("Ваш вибір: ");
            char choiceBuf[128];
            if (fgets(choiceBuf, sizeof(choiceBuf), stdin) == nullptr) {
                freeWords(words, wordCount);
                return 0;
            }

            char *endPtr = nullptr;

            char *startPtr = choiceBuf;
            while (*startPtr == ' ' || *startPtr == '\t') {
                startPtr++;
            }

            if (*startPtr == '\n' || *startPtr == '\0') {
                printf("Помилка: введіть номер пункту меню.\n");
                continue;
            }

            long val = strtol(startPtr, &endPtr, 10);
            while (*endPtr == ' ' || *endPtr == '\t' || *endPtr == '\n' || *endPtr == '\r') {
                endPtr++;
            }

            if (*endPtr != '\0') {
                printf("Помилка: введіть номер пункту меню.\n");
                continue;
            }

            if (val < 0 || val > 6) {
                printf("Помилка: пункту %ld немає в меню.\n", val);
                continue;
            }

            choice = static_cast<int>(val);
            break;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: showTextStatistic(text, wordCount); break;
            case 2: wordsTable(words, wordCount); break;
            case 3: replaceWord(text, words, wordCount); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: newSentence(text, words, wordCount); break;
        }
    }

    freeWords(words, wordCount);
    return 0;
}

void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void buildWords(const char *text, char **&words, int &count) {
    freeWords(words, count);
    char *copy = new char[strlen(text) + 1];
    strcpy(copy, text);
    words = new char *[strlen(text) / 2 + 1];
    char *token = strtok(copy, " ");
    while (token != nullptr) {
        if (strlen(token) > 0 && token[strlen(token) - 1] == '.') {
            token[strlen(token) - 1] = '\0';
        }
        if (strlen(token) > 0) {
            words[count] = new char[strlen(token) + 1];
            strcpy(words[count], token);
            count++;
        }
        token = strtok(nullptr, " ");
    }
    delete[] copy;
}

bool isValidWord(const string &w) {
    if (w.empty() || w.length() > 255) {
        return false;
    }
    for (char ch : w) {
        if (!isalnum(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

void replaceWord(char *text, char **&words, int &wordCount) {
    string origin, paste;
    printf("Введіть слово для заміни: ");
    if (!readFirstWord(origin)) return;
    printf("Введіть нове слово: ");
    if (!readFirstWord(paste)) return;

    if (!isValidWord(origin) || !isValidWord(paste)) {
        printf("Помилка: слова мають містити лише латинські літери або цифри (до 255 символів).\n");
        return;
    }

    string temp(text);
    size_t pos = 0;
    int matches = 0;
    while ((pos = findWholeWord(temp, origin, pos)) != string::npos) {
        matches++;
        pos += origin.length();
    }
    long newLen = static_cast<long>(strlen(text)) +
                  static_cast<long>(matches) * (static_cast<long>(paste.length()) - static_cast<long>(origin.length()));

    if (newLen > 255) {
        printf("Помилка: після заміни довжина тексту перевищить 255 символів.\n");
    } else {
        swapWord(text, origin, paste);
        buildWords(text, words, wordCount);
    }
}

void compareWords() {
    string w1, w2;
    printf("Введіть перше слово: ");
    if (!readFirstWord(w1)) return;
    printf("Введіть друге слово: ");
    if (!readFirstWord(w2)) return;

    if (!isValidWord(w1) || !isValidWord(w2)) {
        printf("Помилка: слова мають містити лише латинські літери або цифри (до 255 символів).\n");
        return;
    }
    wordCompare(w1.c_str(), w2.c_str());
}

void charInfo(const char *text) {
    printf("Введіть символ: ");
    char c;

    if (scanf("%c", &c) != 1 || c == '\n') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    if (c == '\0' || static_cast<unsigned char>(c) > 127) {
        printf("Помилка: допускаються лише ASCII-символи.\n");
        return;
    }
    charCrypt(c, text);
}

void newSentence(char *text, char **&words, int &wordCount) {
    printf("Введіть речення (крапка після останнього слова):\n");
    char rawInput[2048] = "";
    char word[256];
    bool hasDot = false;
    bool tooBig = false;

    while (!hasDot && cin >> setw((int)sizeof(word)) >> word) {
        if (strlen(rawInput) + strlen(word) + 2 < sizeof(rawInput)) {
            strcat(rawInput, word);
            strcat(rawInput, " ");
        } else {
            tooBig = true;
        }

        if (word[strlen(word) - 1] == '.') {
            hasDot = true;
        }
    }
    if (hasDot) {
        cin.ignore(10000, '\n');
    }

    char checkCopy[2048];
    strcpy(checkCopy, rawInput);
    char normalized[2048] = "";
    int wordCount2 = 0;
    bool validSentence = !tooBig;

    char *tok = strtok(checkCopy, " \t\n\r");
    while (tok != nullptr) {
        if (wordCount2 > 0) {
            strcat(normalized, " ");
        }
        strcat(normalized, tok);
        wordCount2++;

        int tlen = strlen(tok);
        if (tlen > 0 && tok[tlen - 1] == '.') {
            break;
        }
        tok = strtok(nullptr, " \t\n\r");
    }

    int normLen = strlen(normalized);
    if (!hasDot || normLen <= 1 || normLen > 255 || normalized[normLen - 1] != '.') {
        validSentence = false;
    } else {
        for (int i = 0; i < normLen - 1; i++) {
            unsigned char uc = static_cast<unsigned char>(normalized[i]);
            if (!isalpha(uc) && !isdigit(uc) && uc != ' ') {
                validSentence = false;
                break;
            }
        }
    }

    if (!validSentence) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n"
               "і пробілів та завершуватися крапкою (до 255 символів).\n");
    } else {
        setNewSentence(text, rawInput);
        buildWords(text, words, wordCount);
    }
}

void setNewSentence(char *text, const char *rawInput) {
    char *copy = new char[strlen(rawInput) + 1];
    strcpy(copy, rawInput);

    char newText[256] = "";
    int wordsRead = 0;

    char *token = strtok(copy, " \t\n\r");
    while (token != nullptr) {
        if (wordsRead > 0) {
            strcat(newText, " ");
        }
        strcat(newText, token);
        wordsRead++;

        if (token[strlen(token) - 1] == '.') {
            break;
        }
        token = strtok(nullptr, " \t\n\r");
    }

    delete[] copy;

    strcpy(text, newText);

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}
void charCrypt(char c, const char *text) {
    unsigned char uc = static_cast<unsigned char>(c);

    char bin[9];
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = ((uc >> i) & 1) ? '1' : '0';
    }
    bin[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n",
           uc, uc, uc, bin);

    if (isupper(uc)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(uc));
    } else if (islower(uc)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(uc));
    } else if (isdigit(uc)) {
        printf("Тип: цифра\n");
    } else if (isspace(uc)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", static_cast<char>(uc + 1));

    int count = 0;
    int firstPos = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            if (count == 0) {
                firstPos = i + 1;
            }
            count++;
        }
    }

    if (count > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    } else {
        printf("Входжень у тексті: символ відсутній\n");
    }
}

void swapWord(char *text, string origin, string paste) {
    if (text == nullptr || origin.empty()) return;

    string str(text);
    string result;
    size_t pos = 0, last = 0;
    int count = 0;

    printf("Замінити слово: %s\n", origin.c_str());
    printf("На слово: %s\n", paste.c_str());

    while ((pos = findWholeWord(str, origin, pos)) != string::npos) {
        result += str.substr(last, pos - last);
        result += paste;
        pos += origin.length();
        last = pos;
        count++;
    }
    result += str.substr(last);

    printf("Замін виконано: %d\n", count);
    printf("Було: %s\n", text);

    strcpy(text, result.c_str());

    printf("Стало: %s\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}
void wordCompare(const char *first, const char *second) {
    printf("Перше слово: %s\nДруге слово: %s\n", first, second);
    char result[256];

    int cmp = strcmp(first, second);
    if (cmp < 0) {
        strcpy(result, "перше слово менше\n");
        cmp=-1;
    } else if (cmp > 0) {
        strcpy(result, "друге слово менше\n");
        cmp = 1;
    } else {
        strcpy(result, "слова рівні\n");
        cmp = 0;
    }
    printf("strcmp: %d -> %s", cmp, result);

    bool isEqual = string(first) == string(second);
    if (isEqual) {
        printf("Рівні (==): так\n");
    } else {
        printf("Рівні (==): ні\n");
    }

    int i = 0;
    bool isLowerEqual = true;
    while (first[i] != '\0' && second[i] != '\0') {
        char c1 = tolower(static_cast<unsigned char>(first[i]));
        char c2 = tolower(static_cast<unsigned char>(second[i]));
        if (c1 != c2) {
            isLowerEqual = false;
            break;
        }
        i++;
    }
    if (first[i] != second[i]) {
        isLowerEqual = false;
    }

    if (isLowerEqual) {
        printf("Рівні без урахування регістру (==): так\n");
    } else {
        printf("Рівні без урахування регістру (==): ні\n");
    }

    printf("Довжини: %d і %d\n", (int)strlen(first), (int)strlen(second));

    string cont = string(first) + " & " + string(second);
    printf("Конкатенація: %s (%d)\n", cont.c_str(), (int)cont.length());
}

void wordsTable(char **words, int count){
    if (count == 0) {
        printf("У тексті немає слів.\n");
        return;
    }
    int sum=0;
    int max_count = 0;
    const char *most_frequent = words[0];
    const char *longest = words[0];
    const char *shortest = words[0];

    char **sorted = new char *[count];

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++)
    {
        sorted[i] = words[i];
        sum+=strlen(words[i]);
        if(strlen(words[i])>strlen(longest)){
            longest = words[i];
        }
        if(strlen(words[i])<strlen(shortest)){
            shortest = words[i];
        }
        printf("|%3d | %-16s| %5d |\n",i+1,words[i],(int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int current_count = 0;

        for (int j = 0; j < count; j++) {
            if (strcmp(sorted[i], sorted[j]) == 0) {
                current_count++;
            }
        }

        if (current_count > max_count) {
            max_count = current_count;
            most_frequent = sorted[i];
        }
    }
    printf("Найдовше слово: %s (%d)\n",longest,(int)strlen(longest));
    printf("Найкоротше слово: %s (%d)\n",shortest,(int)strlen(shortest));
    printf("Середня довжина: %.2f\n",static_cast<float>(sum)/count);
    printf("За абеткою: ");
    for (int i = 0; i < count; i++) {
        printf("%s ", sorted[i]);
    }

    printf("\nНайчастіше слово: %s (%d)\n",most_frequent,max_count);
    delete[] sorted;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    for(const char *p = text; *p != '\0'; p++){
        unsigned char uc = static_cast<unsigned char>(*p);
        if(isalpha(uc)){
            letters++;
        }
        if(isdigit(uc)){
            digits++;
        }
        if(*p==' '){
            spaces++;
        }
    }
}

void showTextStatistic(char *text, int wordCount){
    int letters=0, digits=0, spaces=0;
    countChars(text, letters, digits, spaces);
    printf("Текст:\t\t \"%s\"\n",text);
    printf("Символів:\t %3d\n",(int)strlen(text));
    printf("Слів:\t\t %3d\n",wordCount);

    printf("Літер:\t\t %3d (%5.1f%%)\n",letters, static_cast<float>(letters)/strlen(text)*100);
    printf("Цифр:\t\t %3d (%5.1f%%)\n",digits, static_cast<float>(digits)/strlen(text)*100);
    printf("Пробілів:\t %3d (%5.1f%%)\n",spaces, static_cast<float>(spaces)/strlen(text)*100);
}
