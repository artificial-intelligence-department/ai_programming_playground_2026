#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

const int MAX_WORDS = 128;


bool endsWithDot(const char *text) {
    int len = strlen(text);
    return len > 0 && text[len - 1] == '.';
}

bool validateChars(const char *text) {
    int len = strlen(text);
    for (int i = 0; i + 1 < len; i++) {
        char c = text[i];
        if (!isalnum(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool validateWords(const char *text) {
    int len = strlen(text);
    for (int i = 0; i + 1 < len; i++) {
        if (isalnum((unsigned char)text[i])) {
            return true;
        }
    }
    return false;
}

bool validateText(const char *text) {
    return endsWithDot(text) && validateChars(text) && validateWords(text);
}

char **splitWords(const char *text, int &count) {
    count = 0;
    char *temp = new char[strlen(text) + 1];
    strcpy(temp, text);

    for (char *t = strtok(temp, " ."); t != NULL; t = strtok(NULL, " .")) {
        count++;
    }

    char **words = new char*[count];

    strcpy(temp, text);
    int i = 0;
    for (char *t = strtok(temp, " ."); t != NULL; t = strtok(NULL, " .")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }

    delete[] temp;
    return words;
}

void freeWords(char **&words, int &count) {
    if (words != nullptr) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}


void showMenu() {
    printf("\n========================================\n");
    printf("МЕНЮ\n");
    printf("========================================\n");
    printf("Пункт  Операція\n");
    printf("%-7d%s\n", 1, "Показати текст і статистику");
    printf("%-7d%s\n", 2, "Таблиця слів");
    printf("%-7d%s\n", 3, "Замінити слово");
    printf("%-7d%s\n", 4, "Порівняти два слова");
    printf("%-7d%s\n", 5, "Інформація про символ");
    printf("%-7d%s\n", 6, "Ввести нове речення");
    printf("%-7d%s\n", 0, "Вийти");
    printf("========================================\n");
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        unsigned char c = *p;
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else if (c == ' ') {
            spaces++;
        }
    }
}

void showStatistics(const char *text, int count) {
    int symbols = (int)strlen(text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    double lettersPercent = (double)letters / symbols * 100.0;
    double digitsPercent = (double)digits / symbols * 100.0;
    double spacesPercent = (double)spaces / symbols * 100.0;

    printf("Текст:\t\t\"%s\"\n", text);
    printf("Символів:\t%5d\n", symbols);
    printf("Слів:\t\t%5d\n", count);
    printf("Літер:\t\t%5d (%5.1f%%)\n", letters, lettersPercent);
    printf("Цифр:\t\t%5d (%5.1f%%)\n", digits, digitsPercent);
    printf("Пробілів:\t%5d (%5.1f%%)\n", spaces, spacesPercent);
}

void sortWords(char **words, int count, char **sorted) {
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    for (int i = 1; i < count; i++) {
        char *key = sorted[i];
        int j = i - 1;
        while (j >= 0 && strcmp(sorted[j], key) > 0) {
            sorted[j + 1] = sorted[j];
            j--;
        }
        sorted[j + 1] = key;
    }
}

void findShortestLongest(char **words, int count, const char *&shortestWord, const char *&longestWord) {
    shortestWord = words[0];
    longestWord = words[0];
    for (int i = 1; i < count; i++) {
        size_t len = strlen(words[i]);
        if (len < strlen(shortestWord)) {
            shortestWord = words[i];
        }
        if (len > strlen(longestWord)) {
            longestWord = words[i];
        }
    }
}

void findMostFrequentWord(char **sorted, int count, const char *&word, int &counter) {
    word = sorted[0];
    counter = 0;
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) {
            j++;
        }
        if (j - i > counter) {         
            counter = j - i;
            word = sorted[i];
        }
        i = j;
    }
}

void wordsTable(char **words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    const char *longestWord, *shortestWord, *mostFrequentWord;
    findShortestLongest(words, count, shortestWord, longestWord);

    char *sorted[MAX_WORDS];
    sortWords(words, count, sorted);

    int frequencyCounter;
    findMostFrequentWord(sorted, count, mostFrequentWord, frequencyCounter);

    double lenSum = 0;
    for (int i = 0; i < count; i++) {
        lenSum += strlen(words[i]);
    }
    double average = lenSum / count;

    printf("Найдовше слово: %s (%d)\n", longestWord, (int)strlen(longestWord));
    printf("Найкоротше слово: %s (%d)\n", shortestWord, (int)strlen(shortestWord));
    printf("Середня довжина: %.2f\n", average);
    printf("За абеткою: ");
    for (int i = 0; i < count; i++) {
        printf("%s ", sorted[i]);
    }
    printf("\nНайчастіше слово: %s (%d)\n", mostFrequentWord, frequencyCounter);
}


bool validateWord(const string &word) {
    if (word.empty() || word.length() > 31) {
        return false;
    }
    for (unsigned char c : word) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

int replaceWords(string &s, const string &from, const string &to) {
    int replaced = 0;
    size_t pos = 0;

    while ((pos = s.find(from, pos)) != string::npos) {
        size_t end = pos + from.length();
        bool leftOk = (pos == 0) || !isalnum((unsigned char)s[pos - 1]);
        bool rightOk = (end == s.length()) || !isalnum((unsigned char)s[end]);

        if (leftOk && rightOk) {
            s.replace(pos, from.length(), to);
            pos += to.length();        
            replaced++;
        } else {
            pos++;
        }
    }
    return replaced;
}

void replaceWord(char *text, char **&words, int &count, const string &from, const string &to) {
    if (!validateWord(from) || !validateWord(to)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    string result = text;              
    int replaced = replaceWords(result, from, to);

    if (replaced == 0) {
        printf("Такого слова в тексті немає, текст не змінено.\n");
        return;
    }
    if (result.length() > 255) {
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %d\n", (int)result.length());

    strcpy(text, result.c_str());       
    freeWords(words, count);
    words = splitWords(text, count);
}

bool readWord(const char *prompt, string &output) {
    char buf[64];
    printf("%s", prompt);

    if (fgets(buf, sizeof(buf), stdin) == nullptr) {
        return false;
    }

    if (strchr(buf, '\n') == nullptr) {                 
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);   
    }

    buf[strcspn(buf, "\r\n")] = '\0';
    output = buf;
    return true;
}

bool compareWordsNoRegister(const string &a, const string &b){
    if(a.length() != b.length()){
        return false;
    }
    for(size_t i = 0; i < a.length(); i++){
        if(tolower(a[i]) != tolower(b[i])){
            return false;
        }
    }
    return true;
}

void compareWords(const string &a, const string &b){
    if(!validateWord(a) || !validateWord(b)){
        printf("Помилка: слово має складатися лиш з латинських літер і цифр (до 31 символу)!\n");
        return;
    }

    int comparisonResult = strcmp(a.c_str(), b.c_str());
    comparisonResult < 0 ? comparisonResult = -1 : comparisonResult > 0 ? comparisonResult = 1 : comparisonResult = 0; 
    const char *answer = (comparisonResult < 0) ? "перше слово менше" : (comparisonResult > 0) ? "перше слово більше" : "слова однакові";
    printf("strcmp: %d -> %s\n", comparisonResult, answer);
    printf("Рівні (==): %s\n", (a == b) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", compareWordsNoRegister(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)a.length(), (int)b.length());

    string joinedStrings = a + " & " + b;
    printf("Конкатенація: \"%s\" (%d)\n", joinedStrings.c_str(), (int)joinedStrings.length());
}

void charInformation(const char a, char *text){
    printf("Символ: \'%c\'\n", a);  
    printf("Код: %d (hex %#x, oct %#o, bin ", a, a, a);
    for(int i = 7; i >= 0; i--){
        printf("%d", (a >> i) & 1);
    }
    printf(")\n");

    if (isupper(a)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", a + 32);
        printf("Наступний символ: '%c'\n", a + 1);
    } 
    else if (islower(a)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", a - 32);
        printf("Наступний символ: '%c'\n", a + 1);
    } 
    else if (isdigit(a)) {
        printf("Тип: цифра\n");
    } 
    else if (isspace(a)) {
        printf("Тип: пробільний символ\n");
    } 
    else {
        printf("Тип: інший символ\n");
    }

    int countAppearances = 0;
    char *firstPos = nullptr;

    firstPos = strchr(text, a);
    if(firstPos == NULL){
        printf("Символу '%c' у тексті немає\n", a);
        return;
    }

    char *p = firstPos;
    for(; p != NULL; p = strchr(p + 1, a)){
        countAppearances++;
    }

    printf("Входжень у тексті: %d, перше на позиції: %d\n", countAppearances, int(firstPos - text) + 1);
}

void getNewSentence(char *text, char **&words, int &count){
    printf("Введіть речення (крапка для завершення): ");
    string newSentence, word;
    while(cin >> word){
        if(!newSentence.empty()){
            newSentence += ' ';
        }
            newSentence += word;
        if(word.back() == '.'){
            break;
        }
    }
    cin.ignore(1000, '\n');
    if(newSentence.length() > 255){
        printf("Помилка: текст довший за 255 символів, текст не змінено\n");
        return;
    }
    if(!validateText(newSentence.c_str())){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватись крапкою\n");
        return;
    }

    strcpy(text, newSentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст\t\"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));

}

int main() {
    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка: введення перервано\n");
        return 1;
    }

    if (strchr(text, '\n') == nullptr) {               
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {                  
            printf("Помилка: текст довший за 255 символів\n");
            return 1;
        }
    }
    text[strcspn(text, "\r\n")] = '\0';

    if (!validateText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int userInput = -1;

    while (userInput != 0) {
        showMenu();
        printf("Ваш вибір: ");

        int ch;
        if (scanf("%d", &userInput) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            if (ch == EOF) break;                            
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);        

        if (userInput < 0 || userInput > 6) {
            printf("Помилка: пункту %d немає в меню.\n", userInput);
            continue;
        }
 
        switch (userInput) {
            case 1: {
                showStatistics(text, count);
                break;
            }
            case 2: {
                wordsTable(words, count);
                break;
            }
            case 3: {
                string from, to;
                if (readWord("Замінити слово: ", from) && readWord("На слово: ", to)) {
                    replaceWord(text, words, count, from, to);
                }
                break;
            }
            case 4: {
                string a;
                string b;
                if(readWord("Перше слово: ", a) && readWord("Друге слово: ", b)){
                    compareWords(a, b);
                }
                break;
            }
            case 5: {
                string c;
                if(readWord("Введіть символ: ", c)){
                    if(c.length() != 1){
                        printf("Помилка: потрібно ввести рівно один символ\n");
                    }
                    else{
                        charInformation(c[0], text);
                    }
                }
                break;
            }
            case 6: {
                getNewSentence(text, words, count);
                break;
            }
            default:
                break;
        }
    }

    freeWords(words, count);
    printf("Завершення програми...\n");
    return 0;
}