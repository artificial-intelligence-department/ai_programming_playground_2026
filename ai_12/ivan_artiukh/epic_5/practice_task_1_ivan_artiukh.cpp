/* Epic 5 - Редактор текстового повідомлення
   Артюх Іван
   ШІ-12 */
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

void freeWords(char **&words, int &count) {
    if (words != nullptr) {
        for (int i = 0; i < count; ++i) {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

bool read(char text[256]) {
    char *end = nullptr;
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, 256, stdin) == NULL) {
        return false;
    }
    end = text;
    while (*end != '\0' && *end != '\n' && *end != '\r') {
         end++;
    }
    if (*end == '\0') {
        int c = getchar();
        if (c != '\n' && c != EOF) {
            printf("Помилка: текст перевищує 255 символів.\n");
            return false;
        }
    }
    *end = '\0';

    int len = end - text;
    if (len == 0 || len > 255 || *(end - 1) != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return false;
    }
    bool areThereWords = false;
    for (char *p = text; p < end - 1; p++) {
        if (*p == ' ') {
            continue;
        }

        bool isLetter = (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z');
        bool isDigit  = (*p >= '0' && *p <= '9');

        if (isDigit || isLetter) {
            areThereWords = true;
        }
        else {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return false;
        }
    }

    if (!areThereWords) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return false;
    }

    return true;
}

char **splitWords(const char *text, int &count){
    char buf[256];
    strcpy(buf, text);
    char *dot = strchr(buf, '.');
    if (dot != nullptr) {
        *dot = '\0';
    }

    char *tokens[128];
    for (char *w = strtok(buf, " "); w != NULL; w = strtok(NULL, " ")) {
        tokens[count++] = w;
    }
    if (count == 0) {
        return nullptr;
    }

    char **words = new char*[count];
    for (int i = 0; i < count; ++i) {
        words[i] = new char[strlen(tokens[i]) + 1];
        strcpy(words[i], tokens[i]);
    }

    return words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = digits = spaces = 0;
    for(const char *p = text; *p != '\0'; p++){
        if( isalpha((unsigned char)*p) ){
            letters++;
        }
        if( isdigit((unsigned char)*p) ){
            digits ++;
        }
        if(*p == ' '){
            spaces++;
        }

    }
}

void stats( char text[256], int wordCount){
    const char *p = text;
    while (*p != '\0') {
        p++;
    }
    int len = p - text;

    int letters = 0;
    int digits = 0;
    int spaces = 0;
    countChars(text, letters, digits, spaces);

    double lettersPrcnt = letters * 100.0 / len;
    double digitsPrcnt = digits * 100.0 / len;
    double spacesPrcnt = spaces * 100.0 / len;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", len);
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d (%5.1f%%)\n", letters, lettersPrcnt);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, digitsPrcnt);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, spacesPrcnt);
}

void wordsStats(char**&words, int &wordCount){
    if (wordCount == 0 || words == nullptr) {
            printf("Слів немає.\n");
            return;
        }
        printf("+----+-----------------+-------+\n");
        printf("| N  | Слово           | Довж. |\n");
        printf("+----+-----------------+-------+\n");

        int totalLength = 0;
        const char *longestWord = words[0];
        int maxLen = strlen(words[0]);

        const char *shortestWord = words[0];
        int minLen = strlen(words[0]);

        for (int i = 0; i < wordCount; ++i) {
            int len = strlen(words[i]);
            totalLength += len;
    
            printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);

            if (len > maxLen) {
                maxLen = len;
                longestWord = words[i];
            }
            if (len < minLen) {
                minLen = len;
                shortestWord = words[i];
            }
        }
        printf("+----+-----------------+-------+\n");
        double avgLen = static_cast<double>(totalLength) / wordCount;
        printf("Найдовше слово: %s (%d)\n", longestWord, maxLen);
        printf("Найкоротше слово: %s (%d)\n", shortestWord, minLen);
        printf("Середня довжина: %.2f\n", avgLen);


        const char **sortedWords = new const char*[wordCount];
        for (int i = 0; i < wordCount; ++i) {
            sortedWords[i] = words[i];
        }

        for (int i = 0; i < wordCount - 1; ++i) {
            for (int j = 0; j < wordCount - i - 1; ++j) {
                if (strcmp(sortedWords[j], sortedWords[j + 1]) > 0) {
                    const char *temp = sortedWords[j];
                    sortedWords[j] = sortedWords[j + 1];
                    sortedWords[j + 1] = temp;
                }
            }
        }

        printf("За абеткою:");
        for (int i = 0; i < wordCount; ++i) {
            printf(" %s", sortedWords[i]);
        }
        printf("\n");

    
        const char *mostFreqWord = sortedWords[0];
        int maxFreq = 1;

        int currentFreq = 1;
        for (int i = 1; i < wordCount; ++i) {
            if (strcmp(sortedWords[i], sortedWords[i - 1]) == 0) {
                currentFreq++;
            } else {
                if (currentFreq > maxFreq) {
                    maxFreq = currentFreq;
                    mostFreqWord = sortedWords[i - 1];
                }
                currentFreq = 1;
            }
        }
        if (currentFreq > maxFreq) {
            maxFreq = currentFreq;
            mostFreqWord = sortedWords[wordCount - 1];
        }

        printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);

        delete[] sortedWords;

}

void changeWord(char text[256], char **&words, int &wordCount){
    char fromBuf[256];
    char toBuf[256];

    printf("Замінити слово: ");
    if (fgets(fromBuf, sizeof(fromBuf), stdin) == NULL) return;
    char *p = fromBuf;
    while (*p != '\0' && *p != '\n' && *p != '\r') p++;
    *p = '\0';

    printf("На слово: ");
    if (fgets(toBuf, sizeof(toBuf), stdin) == NULL) return;
    p = toBuf;
    while (*p != '\0' && *p != '\n' && *p != '\r') p++;
    *p = '\0';

    if (strlen(fromBuf) == 0 || strlen(toBuf) == 0 || strlen(fromBuf) > 31 || strlen(toBuf) > 31) {
        printf("Помилка: слово не може бути порожнім та бути більше 31 символу.\n");
           return;
    }

    for (int i = 0; fromBuf[i] != '\0'; i++) {
        char c = (char)(fromBuf[i]);
        bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');

        if (!isLatin && !isDigit) {
            printf("Помилка: слово, яке замінюємо, має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }

    for (int i = 0; toBuf[i] != '\0'; i++) {
        char c = (char)(toBuf[i]);
        bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');

        if (!isLatin && !isDigit) {
            printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }
    string originalText = text;
    string s = text;
    string from = fromBuf;
    string to = toBuf;

    int replacements = 0;
    size_t pos = 0;

    while ((pos = s.find(from, pos)) != string::npos) {
        bool leftBoundary = (pos == 0) || (s[pos - 1] == ' ');
        size_t endPos = pos + from.length();
        bool rightBoundary = (endPos == s.length()) || (s[endPos] == ' ') || (s[endPos] == '.');

        if (leftBoundary && rightBoundary) {
            s.replace(pos, from.length(), to);
            replacements++;
            pos += to.length();
        } else {
            pos += 1;
        }
    }

    if (s.length() > 255) {
        printf("Помилка: новий текст перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", originalText.c_str());
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %d\n", (int)(s.length()));

    strcpy(text, s.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);
}

void compareWords() {
    char one[256];
    char two[256];

    printf("Перше слово: ");
    if (fgets(one, sizeof(one), stdin) == NULL) return;
    char *p = one;
    while (*p != '\0' && *p != '\n' && *p != '\r') p++;
    *p = '\0';
    if (strlen(one) == 0 || strlen(one) > 31) {
        printf("Помилка: слово має містити від 1 до 31 символу.\n");
        return;
    }
    for (int i = 0; one[i] != '\0'; i++) {
        char c = (char)(one[i]);
        bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');

        if (!isLatin && !isDigit) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }

    printf("Друге слово: ");
    if (fgets(two, sizeof(two), stdin) == NULL) return;
    p = two;
    while (*p != '\0' && *p != '\n' && *p != '\r') p++;
    *p = '\0';
    if (strlen(two) == 0 || strlen(two) > 31) {
        printf("Помилка: слово має містити від 1 до 31 символу.\n");
        return;
    }
    for (int i = 0; two[i] != '\0'; i++) {
        char c = (char)(two[i]);
        bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');

        if (!isLatin && !isDigit) {
            printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
            return;
        }
    }
    string first = one;
    string second = two;
    int stringCmpRes = strcmp(one, two);
    if(stringCmpRes < 0){
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if(stringCmpRes == 0){
        printf("strcmp: 0 -> слова рівні\n");
    }
    else{
        printf("strcmp: 1 -> перше слово більше\n");
    
    }

    printf("Рівні (==): %s\n", (first==second)? "так" : "ні");

    bool isEqual = false;
    if (first.length() == second.length()) {
        isEqual = true;
        for (int i = 0; i < first.length(); ++i) {
            if (tolower((char)first[i]) != tolower((char)second[i])){
                isEqual = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: %s\n", isEqual ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)first.length(), (int)second.length());
    string concat = first + " & " + second;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());

}

void symbols(const char *text){
    char input[64];
    printf("Введіть символ: ");
    if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '\n' || input[1] != '\n' || !isprint((unsigned char)input[0])) {
        printf("Помилка: некоректний ввід.\n");
        return;
    }

    char sym = input[0];
    printf("Символ: '%c'\n", sym);
    char bin[9];
    for(int i = 0; i < 8; i++){
        bin[i] = ((sym >> (7 - i)) & 1) + '0';
    }
    bin[8] = '\0';
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", sym, sym, sym, bin);
    if(isupper((unsigned char)sym)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", sym + 32);
    } 
    else if(islower((unsigned char)sym)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", sym - 32);
    }
    else if(isdigit((unsigned char)sym)) printf("Тип: цифра\n");  
    else if(isspace((unsigned char)sym)) printf("Тип: пробільний символ\n");  
    else printf("Тип: інший символ\n");  
    if(sym < 126) printf("Наступний символ: '%c'\n", sym + 1);
    else printf("Це останній символ!\n");
    int nOfInclusions = 0;
    int indexOfFirst = -1;
    for(const char *p = text; *p != '\0'; p++){
        if(*p == sym){
            nOfInclusions ++;
            if(indexOfFirst == -1) indexOfFirst = p - text;
        }
    }
    if (nOfInclusions > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", nOfInclusions, indexOfFirst + 1);
    }
    else {
        printf("Символ не знайдено у тексті.\n");
    }

}

void readNewLine(char text[256], char **&words, int &wordCount){
    string newSentence = "";
    string word;
    printf("Введіть речення (крапка після останнього слова): ");
    while (std::cin >> word) {
        if (!newSentence.empty()) {
            newSentence += " ";
        }
            newSentence += word;
        if (word[word.length() - 1] == '.') {
            break;
        }
    }
    cin.ignore(10000, '\n');

    
    if (newSentence.length() > 255) {
        printf("Помилка: новий текст перевищує 255 символів.\n");
        return;
    }
    int len = newSentence.length();
    if (len == 0 || newSentence[len - 1] != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    bool areThereWords = false;
    for (size_t i = 0; i < len - 1; ++i) {
        char c = (char)(newSentence[i]);
        if (c == ' ') {
            continue;
        }

        bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');

        if (isLatin || isDigit) {
            areThereWords = true;
        }
        else {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return;
        }
    }
    if (!areThereWords) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, newSentence.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", newSentence.c_str());
    printf("Довжина: %d\n", (int)(newSentence.length()));
}

int main(){
    char text[256];
    if(!read(text)){
        printf("Сталася неочікувана проблема. Завершення програми");
        return 0;
    }

    int wordCount = 0;
    char ** words = splitWords(text, wordCount);

    char inputBuffer[256];
    int menu_option = -1;

    do{
        printf("\n--- Меню ---\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            break;
        }

        int choice;
        char extra;
        if (sscanf(inputBuffer, " %d %c", &choice, &extra) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        menu_option = choice;

        switch (menu_option)
        {
        case 1:
            stats(text, wordCount);
            break;

        case 2:
            wordsStats(words, wordCount);
            break;

        case 3:
            changeWord(text, words, wordCount);
            break;

        case 4:
            compareWords();
            break;

        case 5:
            symbols(text);
            break;

        case 6:
            readNewLine(text, words, wordCount);
            break;

        case 0:
            printf("Роботу програми завершено.\n");
            break;
        
        default:
            printf("Помилка: пункту %d немає в меню.\n", menu_option);
            break;
        }
    }while(menu_option != 0);
    freeWords(words, wordCount);
    return 0;
}