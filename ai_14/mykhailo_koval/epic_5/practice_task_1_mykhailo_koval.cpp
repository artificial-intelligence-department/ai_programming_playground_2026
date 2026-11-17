#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

char **splitWords(const char *text, int &count){
    char temp[256];
    strcpy(temp, text);

    int len = strlen(temp);
    if (len > 0 && temp[len - 1] == '.') {
        temp[len - 1] = '\0';
    }

    char tempCount[256];
    strcpy(tempCount, temp);
    count = 0;
    char *x = strtok(tempCount, " ");
    while (x != nullptr) {
        count++;
        x = strtok(nullptr, " ");
    }

    if (count == 0){
        return nullptr;
    }

    char **words = new char *[count];
    int idx = 0;
    x = strtok(temp, " ");
    while (x != nullptr) {
        words[idx] = new char[strlen(x) + 1];
        strcpy(words[idx], x);
        idx++;
        x = strtok(nullptr, " ");
    }
    return words;
}

void freeWords(char **&words, int &count){
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void sortPointers(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int isValidText(const char *t){
    int len = strlen(t);
    if (len < 2 || t[len - 1] != '.') {
        return 0;
    }
    int hasWord = 0;
    for (int i = 0; i < len - 1; i++) {
        unsigned char c = t[i];
        bool isLatin = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        if (isLatin || isdigit(c)) {
            hasWord = 1;
        } else if (c != ' ') {
            return 0;
        }
    }
    return hasWord;
}

int isValidWord(const char *w){
    if (*w == '\0') {
        return 0;
    }
    for (const char *p = w; *p != '\0'; p++) {
        unsigned char c = *p;
        bool isLatin = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        if (!isLatin && !isdigit(c)) {
            return 0;
        }
    }
    return 1;
}

void clearLine(){
    int x;
    while ((x = getchar()) != '\n' && x != EOF);
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;
    while ((*text) != '\0') {
        char x = (*text);
        if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')) {
            letters++;
        } else if (isdigit((unsigned char)x)) {
            digits++;
        } else if (x == ' ') {
            spaces++;
        }
        text++;
    }
}

void stats(const char *text, int wordCount){
    int totalChars = strlen(text);
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    countChars(text, letters, digits, spaces);

    double pLetters = (totalChars > 0) ? (100.0 * letters / totalChars) : 0.0;
    double pDigits  = (totalChars > 0) ? (100.0 * digits / totalChars) : 0.0;
    double pSpaces  = (totalChars > 0) ? (100.0 * spaces / totalChars) : 0.0;

    printf("Текст:\t\"%s\"\n", text);
    printf("%-12s %d\n", "Символів:", totalChars);
    printf("%-12s %d\n", "Слів:", wordCount);
    printf("%-12s %d (%5.1f%%)\n", "Літер:", letters, pLetters);
    printf("%-12s %d (%5.1f%%)\n", "Цифр:", digits, pDigits);
    printf("%-12s %d (%5.1f%%)\n", "Пробілів:", spaces, pSpaces);
}

void optionWordTable(char **words, int count) {
    if (count == 0 || words == nullptr) return;

    printf("+----+-----------------+-------+\n");
    printf("| %-2s | %-15s | %-5s |\n", "N", "Слово", "Довж.");
    printf("+----+-----------------+-------+\n");

    int maxIdx = 0;
    int minIdx = 0;
    int maxLen = strlen(words[0]);
    int minLen = maxLen;
    int totalLen = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        totalLen += len;
        if (len > maxLen) {
            maxLen = len;
            maxIdx = i;
        }
        if (len < minLen) {
            minLen = len;
            minIdx = i;
        }
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
    }
    printf("+----+-----------------+-------+\n");

    double avgLen = (double)totalLen / count;
    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", avgLen);

    char **sorted = new char *[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    sortPointers(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    char *mostFreqWord = sorted[0];
    int maxFreq = 1;
    int curFreq = 1;

    for (int i = 1; i < count; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {
            curFreq++;
            if (curFreq > maxFreq) {
                maxFreq = curFreq;
                mostFreqWord = sorted[i];
            }
        } else {
            curFreq = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);
    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count){
    char from[33], to[33];

    printf("Замінити слово: ");
    if (scanf("%32s", from) != 1) {
        clearLine();
        return;
    }
    clearLine();
    printf("На слово: ");
    if (scanf("%32s", to) != 1) {
        clearLine();
        return;
    }
    clearLine();

    if (!isValidWord(from) || !isValidWord(to)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    std::string before(text);
    std::string body(text);
    body.erase(body.length() - 1);

    std::string f(from);
    std::string t(to);
    int fLen = f.length();
    int tLen = t.length();
    int replaced = 0;
    size_t pos = 0;

    while ((pos = body.find(f, pos)) != std::string::npos) {
        bool leftOk = (pos == 0 || body[pos - 1] == ' ');
        bool rightOk = (pos + fLen == body.length() || body[pos + fLen] == ' ');
        if (leftOk && rightOk) {
            body.replace(pos, fLen, t);
            pos += tLen;
            replaced++;
        } else {
            pos++;
        }
    }

    std::string result = body + ".";
    int newLen = result.length();
    if (newLen > 255) {
        printf("Помилка: результат перевищує 255 символів.\n");
        return;
    }

    strcpy(text, result.c_str());
    if (replaced > 0) {
        freeWords(words, count);
        words = splitWords(text, count);
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", newLen);
}

int equalIgnoreCase(const char *a, const char *b){
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

void compareWords(){
    char a[33], b[33];

    printf("Перше слово: ");
    if (scanf("%32s", a) != 1) {
        clearLine();
        return;
    }
    clearLine();

    printf("Друге слово: ");
    if (scanf("%32s", b) != 1) {
        clearLine();
        return;
    }
    clearLine();

    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    int r = strcmp(a, b);
    int sign = 0;
    const char *expl = "слова рівні";
    if (r < 0) {
        sign = -1;
        expl = "перше слово менше";
    } else if (r > 0) {
        sign = 1;
        expl = "перше слово більше";
    }
    printf("strcmp: %d -> %s\n", sign, expl);

    std::string sa(a);
    std::string sb(b);
    printf("Рівні (==): %s\n", sa == sb ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(a, b) ? "так" : "ні");

    int la = sa.length();
    int lb = sb.length();
    printf("Довжини: %d і %d\n", la, lb);

    std::string cat = sa + " & " + sb;
    int lc = cat.length();
    printf("Конкатенація: \"%s\" (%d)\n", cat.c_str(), lc);
}

void charInfo(const char *text){
    char ch;

    printf("Введіть символ: ");
    if (scanf("%c", &ch) != 1 || ch == '\n') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    clearLine();
    unsigned char uc = ch;

    printf("Символ: '%c'\n", ch);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", uc, uc, uc);
    for (int b = 7; b >= 0; b--) {
        putchar('0' + ((uc >> b) & 1));
    }
    printf(")\n");

    const char *type;
    if (isupper(uc)) {
        type = "велика літера";
    } else if (islower(uc)) {
        type = "мала літера";
    } else if (isdigit(uc)) {
        type = "цифра";
    } else if (isspace(uc)) {
        type = "пробільний символ";
    } else {
        type = "інший символ";
    }
    printf("Тип: %s\n", type);

    if (isalpha(uc)) {
        int other = isupper(uc) ? tolower(uc) : toupper(uc);
        printf("Інший регістр: '%c'\n", other);
    }

    unsigned char next = uc + 1;
    if (isprint(next)) {
        printf("Наступний символ: '%c'\n", next);
    } else {
        printf("Наступний символ: недрукований (код %d)\n", next);
    }

    int occ = 0;
    int first = 0;
    const char *found = strchr(text, ch);
    while (found != nullptr) {
        if (occ == 0) {
            first = (int)(found - text) + 1;
        }
        occ++;
        found = strchr(found + 1, ch);
    }
    if (occ == 0) {
        printf("У тексті цей символ не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occ, first);
    }
}

void newSentence(char *text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");

    std::string sentence;
    std::string w;
    int read = 0;
    bool finished = false;

    while (std::cin >> w) {
        if (read > 0) {
            sentence += " ";
        }
        sentence += w;
        read++;
        if (w[w.length() - 1] == '.') {
            finished = true;
            break;
        }
    }

    clearLine();

    if (!finished) {
        std::cin.clear();
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }

    int sLen = sentence.length();
    if (sLen > 255 || !isValidText(sentence.c_str())) {
        printf("Помилка: речення має складатися з латинських літер, цифр\n");
        printf("і пробілів, завершуватися крапкою та містити не більше 255 символів.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", read);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", sLen);
}

int main(){
    char text[256];
    printf("Введіть текст (обмеження: 255 символів, крапка в кінці): ");
    if (!fgets(text, sizeof(text), stdin)) {
        printf("Помилка вводу\n");
        return 1;
    }
    if (!strchr(text, '\n') && strlen(text) == 255) {
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            printf("Помилка: текст довший за 255 символів.\n");
            return 1;
        }
    }
    text[strcspn(text, "\r\n")] = '\0';

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int wordCount = 0;
    char **words = splitWords(text, wordCount);

    int option = -1;
    do {
        printf("\n=========Меню=========\n");
        printf("1  Показати текст і статистику\n");
        printf("2  Таблиця слів\n");
        printf("3  Замінити слово\n");
        printf("4  Порівняти два слова\n");
        printf("5  Інформація про символ\n");
        printf("6  Ввести нове речення\n");
        printf("0  Вийти\n");
        printf("Ваш вибір: ");

        int r = scanf("%d", &option);
        if (r == EOF) {
            break;
        }
        if (r == 0) {
            printf("Помилка: введіть номер пункту меню.\n");
            clearLine();
            option = -1;
            continue;
        }

        int nextCh = getchar();
        if (nextCh != '\n' && nextCh != EOF) {
            printf("Помилка: введіть номер пункту меню.\n");
            clearLine();
            option = -1;
            continue;
        }

        switch (option) {
            case 1: stats(text, wordCount); break;
            case 2: optionWordTable(words, wordCount); break;
            case 3: replaceWord(text, words, wordCount); break;
            case 4: compareWords(); break;
            case 5: charInfo(text); break;
            case 6: newSentence(text, words, wordCount); break;
            case 0: break;
            default: printf("Помилка: пункту %d немає в меню.\n", option);
        }
    } while (option != 0);

    freeWords(words, wordCount);
    return 0;
}