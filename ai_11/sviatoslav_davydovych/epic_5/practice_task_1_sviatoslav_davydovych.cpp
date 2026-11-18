#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

void clearBuffer(void) {
    int ch;
    // очищає буфер при зчитуванні з fgets та scanf
    while ((ch = getchar()) != '\n' && ch != EOF); // перевірка на EOF в разі аварійного закриття потоку
}

int getValidInteger(int minVal, int maxVal) {
    int value;
    while (true) {
        printf("Оберіть пункт меню: ");
        if (scanf("%d", &value) != 1) {
            clearBuffer();
        }

        if (value < minVal || value > maxVal) continue;

        break;
    }
    clearBuffer();

    return value;
}

void freeWords(char **&words, int &count) {
    if (words == nullptr) return; // ідемпотентність
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

char** splitWords(const char *text, int &count) {
    char* tempCopy = new char[strlen(text) + 1]; // +1 для \0
    strcpy(tempCopy, text);
    
    count = 0;
    char* token = strtok(tempCopy, " ."); // повертає вказівник на 1-ий токен
    while (token != nullptr) {
        count++;
        token = strtok(nullptr, " ."); // зсуває внутрішній вказівник до наступного токену
    }
    delete[] tempCopy;

    char** words = new char*[count];
    char* parseCopy = new char[strlen(text) + 1];
    strcpy(parseCopy, text);

    int index = 0;
    token = strtok(parseCopy, " .");
    while (token != nullptr) {
        words[index] = new char[strlen(token) + 1];
        strcpy(words[index], token);
        index++;
        token = strtok(nullptr, " .");
    }
    delete[] parseCopy;
    return words;
}

void inputText(char*& text, char**& words, int& wordCount, int MAX_LEN) {
    char buffer[MAX_LEN];

    while (true) {
        printf("Введіть текст (до 255 символів, крапка в кінці):\n");
        
        if (fgets(buffer, MAX_LEN, stdin) == nullptr) {
            continue;
        }

        size_t len = strlen(buffer); // strlen() повертає беззнаковий тип size_t
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; 
            len--; // фактична довжина змінюється через заміну \n на \0
        }

        if (len == 0 || buffer[len - 1] != '.') {
            printf("Помилка: текст повинен закінчуватися на крапку.\n\n");
            continue;
        }

        bool isValid = false;
        for (size_t i = 0; i < len - 1; ++i) {            
            if (isalpha(buffer[i]) || isdigit(buffer[i])) {
                isValid = true;
            } else if (buffer[i] != ' ') {
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

    text = new char[strlen(buffer) + 1];
    strcpy(text, buffer);

    words = splitWords(text, wordCount);
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    int l = 0, d = 0, s = 0;

    const char* ptr = text;
    const char* end = text + strlen(text) - 1; // до крапки
    while (ptr < end) {
        if (isalpha(*ptr)) l++;
        if (isdigit(*ptr)) d++;
        if (isspace(*ptr)) s++;
        ptr++;
    }
    letters = l;
    digits = d;
    spaces = s;
}

void printTextAndStatystic(char*& text, const int wordCount){
    printf("Текст:\t\"%s\"\n", text);
    int symbolCount = strlen(text);
    int letterCount, digitCount, spaceCount;

    countChars(text, letterCount, digitCount, spaceCount);
    float letterPart = letterCount * 100.0 / symbolCount;
    float digitPart = digitCount * 100.0 / symbolCount;
    float spacePart = spaceCount * 100.0 / symbolCount;

    printf("Символів:\t%d\n", symbolCount);
    printf("Слів:\t\t%d\n", wordCount);
    printf("Літер:\t\t%d (%.1f%%)\n", letterCount, letterPart);
    printf("Цифр:\t\t%d (%.1f%%)\n", digitCount, digitPart);
    printf("Пробілів:\t%d (%.1f%%)\n", spaceCount, spacePart);
}
// приймає компаратор
void bubbleSortWords(const char **words, int count, int (*cmp)(const char *, const char *)) {
    if (count < 2) return;

    for (int i = 0; i < count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < count - i - 1; j++) {
            if (cmp(words[j], words[j + 1]) > 0) {
                const char *temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int compareLength(const char *a, const char *b) {
    int lenA = (int)strlen(a);
    int lenB = (int)strlen(b);
    if (lenA != lenB) {
        return lenA - lenB;
    }
    return strcmp(a, b);
}

void printTable(char**& words, const int wordCount){
    printf("+----+-----------------+-------+\n");
    printf("| №  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < wordCount; i++){
        // специфікатори розміру та вирівнювання
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    const char** lengthSortedWords = new const char*[wordCount];
    for (int i = 0; i < wordCount; i++){
        lengthSortedWords[i] = words[i];
    }
    bubbleSortWords(lengthSortedWords, wordCount, compareLength);

    printf("Найдовше слово: %s (%d)\n", lengthSortedWords[wordCount - 1], (int)strlen(lengthSortedWords[wordCount - 1]));
    printf("Найкоротше слово: %s (%d)\n", lengthSortedWords[0], (int)strlen(lengthSortedWords[0]));
    delete[] lengthSortedWords;

    float average = 0;
    for (int i = 0; i < wordCount; i++){
        average += strlen(words[i]);
    }
    average /= wordCount;
    printf("Середня довжина: %.2f\n", average);

    const char** sortedWords = new const char*[wordCount];
    for (int i = 0; i < wordCount; i++){
        sortedWords[i] = words[i];
    }
    bubbleSortWords(sortedWords, wordCount, strcmp);

    printf("За абеткою: ");
    int maxCount = 1;
    int current = 1;
    const char* mostPopular = sortedWords[0];

    for (int i = 0; i < wordCount; i++){
        if (i != 0 && strcmp(sortedWords[i], sortedWords[i - 1]) == 0){
            current++;
        } else {
            current = 1;
        }
        printf("%s ", sortedWords[i]);
        if (current > maxCount) {
            maxCount = current;   
            mostPopular = sortedWords[i];
        }
    }
    printf("\n");
    printf("Найчастіше слово: %s (%d)\n", mostPopular, maxCount);
    
    delete[] sortedWords;
}

void replaceWord(char*& text, char**& words, int& wordCount, int MAX_LEN) {
    char from[32], to[32];
    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("На слово: ");
    if (scanf("%31s", to) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; to[i] != '\0'; i++) {
        if (!isalpha(to[i]) && !isdigit(to[i])) {
            printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }

    // перетворення в рядки для використання string методів
    string sText(text);
    string sFrom(from);
    string sTo(to);

    int count = 0;
    size_t pos = 0;
    // умова в while присвоює значення pos і порівнює результат
    while ((pos = sText.find(sFrom, pos)) != string::npos) {
        bool leftOk = (pos == 0 || sText[pos - 1] == ' ');
        size_t endPos = pos + sFrom.length();
        bool rightOk = (sText[endPos] == ' ' || sText[endPos] == '.');

        if (leftOk && rightOk) {
            sText.replace(pos, sFrom.length(), sTo);
            count++;
            pos += sTo.length();
        } else {
            pos += sFrom.length();
        }
    }

    if (count == 0) {
        printf("Помилка: слово '%s' не знайдено в тексті.\n", from);
        return;
    }

    if (sText.length() >= (size_t)MAX_LEN) {
        printf("Помилка: результат перевищує максимальну довжину буфера.\n");
        return;
    }

    printf("Замін виконано: %d\n", count);
    printf("Було: \"%s\"\n", text);
    printf("Стало: \"%s\"\n", sText.c_str());
    printf("Нова довжина: %zu\n", sText.length());

    delete[] text;
    text = new char[sText.length() + 1];
    strcpy(text, sText.c_str());

    freeWords(words, wordCount);
    words = splitWords(text, wordCount);
}

void compareWords() {
    char word1[32], word2[32];
    printf("Перше слово: ");
    if (scanf("%31s", word1) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Друге слово: ");
    if (scanf("%31s", word2) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    string s1(word1);
    string s2(word2);

    int cmpRes = strcmp(word1, word2);
    printf("strcmp: %d -> ", cmpRes);
    if (cmpRes < 0) {
        printf("перше слово менше\n");
    } else if (cmpRes > 0) {
        printf("перше слово більше\n");
    } else {
        printf("слова рівні\n");
    }

    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

    string lower1 = s1, lower2 = s2;
    for (size_t i = 0; i < lower1.length(); i++) lower1[i] = tolower(lower1[i]);
    for (size_t i = 0; i < lower2.length(); i++) lower2[i] = tolower(lower2[i]);

    printf("Рівні без урахування регістру: %s\n", (lower1 == lower2) ? "так" : "ні");
    // специфікатор %zu для типу size_t
    printf("Довжини: %zu %zu\n", s1.length(), s2.length()); 

    // зручна конкатенація
    string concat = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

void printCharInfo(const char *text) {
    char c;
    printf("Введіть символ: ");
    if (scanf(" %c", &c) != 1) {
        clearBuffer();
        return;
    }
    clearBuffer();

    printf("Символ: '%c'\n", c);
    
    char binStr[9];
    for (int i = 7; i >= 0; i--) {
        binStr[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    binStr[8] = '\0';
    // специфікатори для систем числення
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", (unsigned char)c, (unsigned char)c, (unsigned char)c, binStr);

    if (isupper(c)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(c));
    } else if (islower(c)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(c));
    } else if (isdigit(c)) {
        printf("Тип: цифра\n");
    } else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", c + 1);

    int occurrences = 0;
    int firstPos = -1;
    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (text[i] == c) {
            occurrences++;
            if (firstPos == -1) {
                firstPos = i + 1;
            }
        }
    }

    if (occurrences > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
    } else {
        printf("У тексті не зустрічається\n");
    }
}

void inputNewSentence(char*& text, char**& words, int& wordCount, int MAX_LEN) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence = "";
    string token;
    int readWords = 0;

    while (cin >> token) { // cin ігнорує пробільні символи
        if (!sentence.empty()) {
            sentence += " ";
        }
        sentence += token;
        readWords++;

        if (!token.empty() && token.back() == '.') {
            break;
        }
    }
    clearBuffer();

    if (sentence.length() >= (size_t)MAX_LEN) {
        printf("Помилка: речення перевищує %d символів. Текст не змінено.\n", MAX_LEN - 1);
        return;
    }

    if (sentence.empty() || sentence.back() != '.') {
        printf("Помилка: речення повинно закінчуватися на крапку. Текст не змінено.\n");
        return;
    }

    bool isValid = false;
    for (size_t i = 0; i < sentence.length() - 1; ++i) {
        if (isalpha(sentence[i]) || isdigit(sentence[i])) {
            isValid = true;
        } else if (sentence[i] != ' ') {
            isValid = false;
            break;
        }
    }

    if (!isValid) {
        printf("Помилка: дозволені лише латинські літери, цифри та пробіли. Текст не змінено.\n");
        return;
    }

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", sentence.c_str());
    printf("Довжина: %zu\n", sentence.length());

    delete[] text;
    text = new char[sentence.length() + 1];
    strcpy(text, sentence.c_str());

    freeWords(words, wordCount);
    words = splitWords(text, wordCount);
}

int main(){
    const int MAX_LEN = 256;

    char* text = nullptr;
    char** words = nullptr;
    int wordCount = 0;
    
    inputText(text, words, wordCount, MAX_LEN);

    int action;
    bool loop = true;
    do {
        printf("\n========================================\n"
                "1. Показати текст і статистику\n"
                "2. Таблиця слів\n"
                "3. Замінити слово\n"
                "4. Порівняти два слова\n"
                "5. Інформація про символ\n"
                "6. Ввести нове речення\n"
                "0. Вийти\n"
                "========================================\n");

        action = getValidInteger(0, 6);
        
        switch (action) {
        case 0:
            loop = false;
            break;
        case 1:
            printTextAndStatystic(text, wordCount);
            break;
        case 2:
            printTable(words, wordCount);
            break;
        case 3:
            replaceWord(text, words, wordCount, MAX_LEN);
            break;
        case 4:
            compareWords();
            break;
        case 5:
            printCharInfo(text);
            break;
        case 6:
            inputNewSentence(text, words, wordCount, MAX_LEN);
            break;
        }
    } while(loop);

    freeWords(words, wordCount);
    delete[] text;

    return 0;
}