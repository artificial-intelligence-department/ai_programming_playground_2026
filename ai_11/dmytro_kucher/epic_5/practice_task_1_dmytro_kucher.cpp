/*
Епік 5. Практичне завдання: Редактор текстового повідомлення
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

char **splitWords(const char *text, int &count) {

    char copy[256];
    strcpy(copy, text);

    count = 0;
    char* partition = strtok(copy, " .");

    while (partition != NULL) {
        count++;
        partition = strtok(NULL, " .");
    }

    char** words = new char*[count];

    int i = 0;
    int j = 0;

    while (text[i] != '\0' && text[i] != '.') {

        if (text[i] == ' ') {
            i++;
            continue;
        }

        int start = i;

        while (text[i] != ' ' && text[i] != '.' && text[i] != '\0') {
            i++;
        }

        int len = i-start;

        words[j] = new char[len+1];

        strncpy(words[j], text+start, len);
        words[j][len] = '\0';

        j++;
    }

    return words;
}

void freeWords (char** &words, int &count) {

    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }

    delete[] words;

    words = nullptr;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {

    while (*text != '\0') {

        unsigned char c = (unsigned char)*text;

        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (isspace(c)) spaces++;

        text++;
    }
}

void showTextAndStatistic (const char* text, char** words, int count) {

    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces);

    int symbols = strlen(text);

    double letters2 = ((double)letters/symbols * 100.0);
    double digits2 = ((double)digits/symbols * 100.0);
    double spaces2 = ((double)spaces/symbols * 100.0);

    printf("\nТекст:    \"%s\"\n", text);
    printf("Символів: \t%d\n", symbols);
    printf("Слів:     \t%d\n", count);
    printf("Літер:    \t%d (%.1f%%)\n", letters, letters2);
    printf("Цифр:     \t%d (%.1f%%)\n", digits, digits2);
    printf("Пробілів: \t%d (%.1f%%)\n", spaces, spaces2);

}

void sortWords (char** sortedWords, int count) {

    for (int i = 0; i<count-1; i++) {

        int minIndex = i;
        for (int j = i+1; j<count; j++) {
            if (strcmp(sortedWords[j], sortedWords[minIndex]) < 0) minIndex = j;
        }

        char* t = sortedWords[i];
        sortedWords[i] = sortedWords[minIndex];
        sortedWords[minIndex] = t;
    }
}

void findMostFrequent (char** words, int count) {

    int maxCount = 1;
    int currentCount = 1;
    int maxIndex = 0;

    for (int i = 1; i<count; i++) {

        if (strcmp(words[i], words[i-1]) == 0) currentCount++;

        else currentCount = 1;

        if (currentCount > maxCount) {
            maxCount = currentCount;
            maxIndex = i;
        }
    }

    printf("\nНайчастіше слово: %s (%d)\n", words[maxIndex], maxCount);
}

void wordsMatrix (char** words, int count) {

    printf("\n+----+-----------------+-------+\n| N  | Слово           | Довж. |\n+----+-----------------+-------+\n");

    char** sortedWords = new char*[count];
    
    int maxIndex = 0;
    int minIndex = 0;
    double average = 0;
    for (int i = 0; i<count; i++) {

        printf("| %2d | %-15s | %5zu |\n", i+1, words[i], strlen(words[i]));

        if (strlen(words[i]) > strlen(words[maxIndex])) maxIndex = i;
        if (strlen(words[i]) < strlen(words[minIndex])) minIndex = i;

        average += strlen(words[i]);

        sortedWords[i] = words[i];
    }

    printf("+----+-----------------+-------+\n");

    sortWords(sortedWords, count);

    printf("Найдовше слово: %s (%zu)\n", words[maxIndex], strlen(words[maxIndex]));
    printf("Найкоротше слово: %s (%zu)\n", words[minIndex], strlen(words[minIndex]));
    printf("Середня довжина: %.2f\n", average/count);
    printf("За абеткою:");

    for (int i = 0; i<count; i++) {
        printf(" %s", sortedWords[i]);
    }

    findMostFrequent(sortedWords, count);

    delete[] sortedWords;
}

bool validation1 (char* str, char** words, int count) {

    for (int i = 0; i<count; i++) {
        if (strcmp(words[i], str) == 0) {
            return true;
        }
    }

    printf("Помилка! Такого слова немає в тексті!\n");
    return false;
}

bool validation2 (char* str) {

    int len = strlen(str); 

    if (len == 0) {
        printf("Помилка! Введіть одне слово!\n");
        return false;
    }


    for (int i = 0; i<len; i++) {

        bool isLetter = (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z');
        bool isNumber = (str[i] >= '0' && str[i] <= '9');

        if (!isNumber && !isLetter) {
            printf("Помилка! Недопустимий символ!\n");
            return false;
        }
    }

    return true;
}

bool changeWord (const char* from, const char* to, char**& words, int& count, char* text) {

    string result = text;
    string oldWord = from;
    string newWord = to;

    int replacements = 0;
    size_t pos = 0;

    while ((pos = result.find(oldWord, pos)) != string::npos) {

        bool left = (pos == 0 || result[pos-1] == ' ');
        bool right = (pos + oldWord.length() == result.length() || result[pos+oldWord.length()] == ' ' || result[pos+oldWord.length()] == '.');

        if (left && right) {

            if (result.length() - oldWord.length() + newWord.length() > 255) {
                printf("Помилка! Текст перевищує 255 символів!\n");
                return false;
            }

            result.replace(pos, oldWord.length(), newWord);
            replacements++;

            pos += newWord.length();
        }

        else pos += oldWord.length();
    }

    printf("\nЗамін виконано: %d\n", replacements);
    printf("Було: %s\n", text);
    printf("Стало: %s\n", result.c_str());
    printf("Нова довжина: %zu\n", result.length());

    strcpy(text, result.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    return true;
}

void compareWords (const char* a, const char* b) {

    int result = strcmp(a, b);
    if (result > 0) result = 1;
    else if (result < 0) result = -1;

    string a1 = a;
    string b1 = b;

    printf("\nПерше слово: %s\n", a);
    printf("Друге слово: %s\n", b);
    printf("strcmp: %d -> ", result);
    printf("%s\n", result > 0 ? "перше слово більше" : result < 0 ? "перше слово менше" : "слова однакові");
    printf("Рівні (==): %s\n", a1 == b1 ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", strcasecmp(a, b) == 0 ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", strlen(a), strlen(b));

    string con = a1 + " & " + b1;
    int sizeC = con.size();

    printf("Конкатенація: \"%s\" (%d)\n", con.c_str(), sizeC);

}

void countSymbol (char c, const char* text, int& count) {

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) count++;
    }
}

void symbolInformation (char c, const char* text) {

    string c_bin = "";
    for (int i = 7; i>=0; i--) {
        c_bin += (char)(((c >> i)& 1) + '0');
    }

    printf("\nСимвол: '%c'\n", c);
    printf("Код: %d (hex %#X, oct %#o, bin %s)\n", (int)c, (unsigned int)c, (unsigned int)c, c_bin.c_str());

    string c_type = "";
    
    if (isupper(c)) c_type = "велика літера";
    else if (islower(c)) c_type = "мала літера";
    else if (isdigit(c)) c_type = "цифра";
    else if (isspace(c)) c_type = "пробільний символ";
    else c_type = "інший символ";

    printf("Тип: %s\n", c_type.c_str());

    char else_c = c;
    if (c_type == "велика літера") else_c = c + 32;
    else if (c_type == "мала літера") else_c = c - 32;

    if (else_c != c) printf("Інший регістр: '%c'\n", else_c);

    printf("Наступний символ: '%c'\n", c+1);

    int count = 0;

    string copy = text;
    size_t first = copy.find(c);

    countSymbol(c, text, count);

    printf("Кількість входжень: %d\n", count);
    if (first != string::npos) printf("Перше входження: %zu\n", first+1);
    else printf("Символ у тексті відсутній\n");

}

int main () {

    char text[256];
    printf("\nВведіть текст (до 255 символів, крапка в кінці): ");
    
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Помилка введення!\n");
        return 1;
    }

    char *n = strchr(text, '\n');
    if (n) *n = '\0';

    int len = strlen(text); 

    if (len == 0) {
        printf("Помилка! Введіть хоча б одне слово!\n");
        return 1;
    }

    else if (text[len-1] != '.') {
        printf("Помилка! Текст повинен закінчуватись крапкою!\n");
        return 1;
    }

    bool hasWord = false;
    int i = 0;

    while (i < len-1) {

        bool isLetter = (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z');
        bool isNumber = (text[i] >= '0' && text[i] <= '9');
        bool isSpace = (text[i] == ' ');

        if (!isNumber && !isLetter && !isSpace) {
            printf("Помилка! Недопустимий символ!\n");
            return 1;
        }

        if (isLetter || isNumber) hasWord = true;

        i++;
    }

    if (!hasWord) {
        printf("Помилка! Введіть хоча б одне слово!\n");
        return 1;
    }

    int count = 0;
    char** words = splitWords(text, count);

    bool menuIsAlive = true;
    char choice = ' ';

    do {
        printf("\n============== Меню ==============\n1     Показати текст і статистику\n2     Таблиця слів\n3     Замінити слово\n4     Порівняти два слова\n5     Інформація про символ\n6     Ввести нове речення\n0     Вийти");
        printf("\nВведіть операцію: ");

        scanf(" %c", &choice);

        if (choice < '0' || choice > '6') {
            printf("Помилка! Введіть 1, 2, 3, 4, 5, 6 або 0\n");
            freeWords(words, count);
            return 1;
        }

        else if (choice == '0') menuIsAlive = false;

        else if (choice == '1') showTextAndStatistic(text, words, count);

        else if (choice == '2') wordsMatrix(words, count);

        else if (choice == '3') {

            char from[32];
            printf("\nВведіть слово, яке заміняємо: ");
            if (scanf("%31s", from) != 1) {
                printf("Помилка введення!\n");
                continue;
            }

            if (!validation1(from, words, count)) continue;

            char to[32];
            printf("Введіть нове слово: ");
            if (scanf("%31s", to) != 1) {
                printf("Помилка введення!\n");
                continue;
            }

            if (!validation2(to)) continue;
            
            if(!changeWord(from, to, words, count, text)) continue;

        }

        else if (choice == '4') {

            char a[32];
            printf("\nВведіть перше слово для порівняння: ");

            if (scanf("%31s", a) != 1) {
                printf("Помилка введення!\n");
                continue;
            }

            if (!validation2(a)) continue;

            char b[32];
            printf("Введіть друге слово для порівняння: ");

            if (scanf("%31s", b) != 1) {
                printf("Помилка введення!\n");
                continue;
            }

            if (!validation2(b)) continue;
            
            compareWords(a, b);

        }

        else if (choice == '5') {

            char c;
            printf("\nВведіть символ для аналізу: ");
            if (scanf(" %c", &c)!=1) {
                printf("Помилка введення!\n");
                break;
            }

            symbolInformation(c, text);

        }

        else if (choice == '6') {

            string sentence = "";
            string word = "";
            
            int newCount = 0;
            bool valid = true;
            bool finished = false;

            printf("\nВведіть нове речення: ");

            while (cin >> word) {

                bool last = (word.back() == '.');

                if (last) word.pop_back();
                if (word.empty()) valid = false;

                for (int i = 0; i < (int)word.length(); i++) {

                    bool isLetter = (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z');

                    bool isDigit = (word[i] >= '0' && word[i] <= '9');

                    if (!isLetter && !isDigit) valid = false;
                }
                
                if (valid) {
                    if (!sentence.empty()) sentence += " ";
                    sentence += word;
                }

                newCount++;

                if (last) {
                    finished = true;
                    break;
                }

                if (sentence.length() + 1 > 255) valid = false;
    
            }

            if (!finished || !valid || newCount == 0) {
                printf("Помилка! Некоректне речення!\n");
                continue;
            }

            sentence += ".";

            if (sentence.length() > 255) {
                printf("Помилка! Речення перевищує 255 символів!\n");
                continue;
            }

            char newtext[256];
            strcpy(newtext, sentence.c_str());

            int newWordsCount = 0;
            char** newWords = splitWords(newtext, newWordsCount);

            freeWords(words, count);

            strcpy(text, newtext);
            words = newWords;
            count = newWordsCount;

            printf("Прочитано слів: %d\n", newCount);
            printf("Новий текст: \"%s\"\n", text);
            printf("Довжина: %zu\n", strlen(text));

        }

    } while (menuIsAlive);

    printf("\nКінець програми\n");

    freeWords(words, count);

    return 0;
}