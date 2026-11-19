/*
Назва: Редактор текстового повідомлення
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

void clearBuffer() {
    while (getchar() != '\n');
}

bool isValidText(const char* text) {
    size_t len = strlen(text);
    if (len == 0 || text[len - 1] != '.') return false;

    bool hasWord = false;
    for (size_t i = 0; i < len - 1; i++) {
        unsigned char c = text[i];
        if (isalnum(c)) {
            hasWord = true;
        } else if (!isspace(c)) {
            return false;
        }
    }
    return hasWord;
}

char **splitWords(const char *text, int &count){
    count = 0;
    char temp1[256];
    strcpy(temp1, text);

    char *token = strtok(temp1, " .");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " .");
    }

    if (count == 0) return NULL;

    char **words = new char*[count];
    char temp2[256];
    strcpy(temp2, text);
    token = strtok(temp2, " .");
    int i = 0;
    while (token != NULL) {
        size_t len = strlen(token);
        words[i] = new char[len + 1];
        strcpy(words[i], token);
        i++;
        token = strtok(NULL, " .");
    }

    return words;
}

void freeWords(char **&words, int &count) {
    if (words == NULL) return;

    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;

    words = NULL;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha(*p)) {
            letters++;
        } else if (isdigit(*p)) {
            digits++;
        } else if (isspace(*p)) {
            spaces++;
        }
    }
    
}


void showTextStats(const char *text, int count) {
    int letters = 0, digits = 0, spaces = 0;
    
    countChars(text, letters, digits, spaces);

    int size = strlen(text);
    
    double letterPercentage = (double)letters / size * 100.0;
    double digitPercentage  = (double)digits / size * 100.0;
    double spacePercentage  = (double)spaces / size * 100.0;

    printf("\nТекст:\t\"%s\"\n", text);
    printf("Символів:\t%5d\n", size);
    printf("Слів:\t\t%5d\n", count);
    printf("Літер:\t\t%5d (%5.1f%%)\n", letters, letterPercentage);
    printf("Цифр:\t\t%5d (%5.1f%%)\n", digits, digitPercentage);
    printf("Пробілів:\t%5d (%5.1f%%)\n", spaces, spacePercentage);
}

void wordList(char** words, int count){
    printf("+----+-----------------+-------+\n");
    printf("| %-2s | %-20s | %-9s |\n", "N", "Слово", "Довж.");
    printf("+----+-----------------+-------+\n");

    int totalLetters = 0;
    char* longest = words[0];
    char* shortest = words[0];

    for (int i = 0; i < count; i++) {
        size_t len = strlen(words[i]);
        totalLetters += (int)len;

        printf("| %2d | %-15s | %5zu |\n", i + 1, words[i], len);

        if (len > strlen(longest)) {
            longest = words[i];
        }
        if (len < strlen(shortest)) {
            shortest = words[i];
        }
    }
    printf("+----+-----------------+-------+\n");

    double avgLen = (double)totalLetters / count;
    printf("Найдовше слово: %s (%zu)\n", longest, strlen(longest));
    printf("Найкоротше слово: %s (%zu)\n", shortest, strlen(shortest));
    printf("Середня довжина: %.2f\n", avgLen);
    char** sortedWords = new char*[count];
    for (int i = 0; i < count; i++) {
        sortedWords[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sortedWords[j], sortedWords[j + 1]) > 0) {
                char* temp = sortedWords[j];
                sortedWords[j] = sortedWords[j + 1];
                sortedWords[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sortedWords[i]);
    }
    printf("\n");

    // --- 4. Пошук найчастішого слова ---
    char* mostFreq = sortedWords[0];
    int maxFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < count; i++) {
        if (strcmp(sortedWords[i], sortedWords[i - 1]) == 0) {
            currentFreq++;
        } else {
            currentFreq = 1;
        }

        if (currentFreq > maxFreq) {
            maxFreq = currentFreq;
            mostFreq = sortedWords[i];
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFreq, maxFreq);

    // Очищення тимчасового масиву вказівників
    delete[] sortedWords;

}

bool isValidWord(const char* word) {
    size_t len = strlen(word);
    if (len == 0 || len > 31) return false;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = word[i];
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

void replaceWord(char *text, char **&words, int &count) {
    char from[64], to[64];

    while (true) {
        printf("\nЗамінити слово: ");
        scanf("%63s", from);
        clearBuffer();

        if (isValidWord(from)) break;
        printf("Помилка! Введіть слово лише з літер або цифр, до 31 символа.\n");
    }

    while (true) {
        printf("На слово: ");
        scanf("%63s", to);
        clearBuffer();

        if (isValidWord(to)) break;
        printf("Помилка! Введіть слово лише з літер або цифр, до 31 символа.\n");
    }

    string strText = text;
    string strFrom = from;
    string strTo = to;

    int replaced = 0;
    size_t pos = 0;

    while ((pos = strText.find(strFrom, pos)) != string::npos) {
        bool left = (pos == 0 || strText[pos - 1] == ' ');
        size_t endPos = pos + strFrom.length();
        bool right = (endPos < strText.length() && (strText[endPos] == ' ' || strText[endPos] == '.'));

        if (left && right) {
            strText.replace(pos, strFrom.length(), strTo);
            pos += strTo.length();
            replaced++;
        } else {
            pos ++;
        }
    }

    if (strText.length() > 255) {
        printf("Помилка: після заміни довжина тексту перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);

    if (replaced > 0) {
        printf("Було:  \"%s\"\n", text);
        strcpy(text, strText.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
        printf("Стало: \"%s\"\n", text);
        printf("Нова довжина: %zu\n", strlen(text));
    } else {
        printf("Слово \"%s\" не знайдено у тексті.\n", from);
    }
}

void compareTwoWords() {
    char buf1[64], buf2[64];

    while (true) {
        printf("\nПерше слово: ");
        scanf("%63s", buf1);
        clearBuffer();

        if (isValidWord(buf1)) break;
        printf("Помилка! Введіть слово лише з літер або цифр, до 31 символа.\n");
    }

    while (true) {
        printf("Друге слово: ");
        scanf("%63s", buf2);
        clearBuffer();

        if (isValidWord(buf2)) break;
        printf("Помилка! Введіть слово лише з літер або цифр, до 31 символа.\n");
    }

    string word1 = buf1;
    string word2 = buf2;

    // 1. Порівняння через strcmp 
    int cmp = strcmp(buf1, buf2);
    if (cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }
    string answer = "";
    if(word1 == word2){
        answer = "так";
    }
    else{
        answer ="ні";
    }
    
    printf("Рівні (==): %s\n", answer.c_str());

    // Порівняння без урахування регістру
    bool ignoreReg = (word1.length() == word2.length());
    if (ignoreReg) {
        for (size_t i = 0; i < word1.length(); ++i) {
            if (tolower(word1[i]) != tolower(word2[i])) {
                ignoreReg = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: ");
    if (ignoreReg) {
        printf("так\n");
    } else {
        printf("ні\n");
    }
    
    printf("Довжини: %zu і %zu\n", word1.length(), word2.length());

    // Конкатенація 
    string concat = word1 + " & " + word2;
    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

void analyzeChar(const char *text) {
    char c;
    while (true) {
        printf("\nВведіть символ: ");
        if (scanf("%c", &c) != 1) {
            printf("Помилка вводу символу.\n");
            return;
        }
        if (c == '\n') {
            printf("Помилка: введіть один символ.\n");
            continue;
        }
        int next = getchar();
        if (next != '\n') {
            clearBuffer();
            printf("Помилка: потрібно ввести лише один символ.\n");
            continue;
        }
        break; 
    }

    unsigned char uc = (unsigned char)c;

    // 1. Символ та його коди в 4 системах числення
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", uc, uc, uc);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (uc >> i) & 1);
    }
    printf(")\n");

    // 2. Тип символу та інший регістр (лише для літер)
    if (isupper(uc)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)tolower(uc));
    } else if (islower(uc)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(uc));
    } else if (isdigit(uc)) {
        printf("Тип: цифра\n");
    } else if (isspace(uc)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    // 3. Наступний символ за кодом
    unsigned char next_uc = (unsigned char)(uc + 1);
    if (isprint(next_uc)) {
        printf("Наступний символ: '%c'\n", (char)next_uc);
    } else {
        printf("Наступний символ: недрукований (код %d)\n", next_uc);
    }

    // 4. Пошук першого входження через strchr
    const char *first = strchr(text, c);
    if (first == nullptr) {
        printf("У тексті не зустрічається.\n");
    } else {
        int pos = (int)(first - text) + 1;
        int coun = 0;
        for (const char *p = text; *p != '\0'; p++) {
            if (*p == c) {
                coun++;
            }
        }
        printf("Входжень у тексті: %d, перше на позиції %d\n", coun, pos);
    }
}

void writeNewSentence(char *text, char **&words, int &count) {
    printf("\nВведіть речення (крапка після останнього слова):\n");

    string word;
    string newSentence = "";

    while (cin >> word) {
        if (!newSentence.empty()) {
            newSentence += " ";
        }
        newSentence += word;

        if (word.back() == '.') {
            break;
        }
    }
    clearBuffer();

    if (newSentence.length() > 255 || !isValidText(newSentence.c_str())) {
        printf("Помилка: речення має містити до 255 символів, складатися з латинських літер, цифр і пробілів та завершуватися крапкою після слова.\n");
        return; // Поточний текст і масив words залишаються без змін
    }

    // Оновлюємо текст 
    strcpy(text, newSentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main() {
    char text[256];
    
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!fgets(text, sizeof(text), stdin)){
        clearBuffer();
        return 0;
    }
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    int count = 0;
    char** words = splitWords(text, count);
    int choice;

    do {
        printf("\n--------- МЕНЮ ---------\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        while(!(scanf("%d", &choice))){
            printf("\nПомилка: введіть номер пункту меню.\n");
            printf("Ваш вибір: ");
            clearBuffer();
            continue;
        }

        clearBuffer();
        switch (choice) {
            case 1:
                showTextStats(text, count);
                break;

            case 2:
                wordList(words, count);
                break;

            case 3: {
                replaceWord(text, words, count);
                break;
            }

            case 4: {
                compareTwoWords();
                break;
            }

            case 5: {
                analyzeChar(text);
                break;
            }

            case 6: {
                writeNewSentence(text, words, count);
                break;
            }

            case 0:
                printf("Вихід з програми.\n");
                break;

            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    } while (choice != 0);
    freeWords(words, count);

    return 0;
}
