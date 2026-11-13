#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <cstdio>
using namespace std;

char **splitWords(const char *text, int &count);
void ShowTextAndStats(const char *text);
void WordsTable(char **words, int WordsCount);
void ReplaceWord(char *text, char **&words, int &WordsCount);
void CompareWords();
void SymbolInfo(char *text);
void EnterNewValue(char *text, char **&words, int &WordsCount);
void freeWords(char **&words, int &count);

int main()
{
    char text[256] = "";
    char latin[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, sizeof(text), stdin);
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }
    if (text[0] == '\0' || text[len - 1] != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    bool has_word = false;
    for (int i = 0; i < len - 1; i++) {
        if (strchr(latin, text[i]) || isdigit(text[i])) {
            has_word = true;
        } else if (text[i] == ' ') {
            continue;
        } else {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return 1;
        }
    }
    if (!has_word) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int wordsCount = 0;
    char **words = splitWords(text, wordsCount);

    int choice = -1;
    do {
        printf("Виберіть дію:\n1. Показати текст і статистику\n2. Таблиця слів\n3. Замінити слово\n4. Порівняти два слова\n5. Інформація про символ\n6. Ввести нове речення\n0. Вийти\nВаш вибір: ");
        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }
        switch (choice)
        {
        case 1:
            ShowTextAndStats(text);
            break;
        case 2:
            WordsTable(words, wordsCount);
            break;
        case 3:
            ReplaceWord(text, words, wordsCount);
            break;
        case 4:
            CompareWords();
            break;
        case 5:
            SymbolInfo(text);
            break;
        case 6:
            EnterNewValue(text, words, wordsCount);
            break;
        case 0:
            break;
        default:
            printf("Помилка: пункту %d немає в меню.\n", choice);
            break;
        }
    } while (choice != 0);

    freeWords(words, wordsCount);
    return 0;
}
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
        words[i] = nullptr;
    }
    delete[] words;
    words = nullptr;
}

char **splitWords(const char *text, int &count) {
    char copy[256];
    strcpy(copy, text);
    int len = strlen(copy);
    if (len > 0 && copy[len - 1] == '.') {
        copy[len - 1] = '\0';
    }
    char copy2[256];
    strcpy(copy2, copy);

    char *token = strtok(copy, " ");
    count = 0;
    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }
    char **words = new char*[count];
    token = strtok(copy2, " ");
    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(NULL, " ");
    }
    return words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *ptr = text; *ptr != '\0'; ptr++) {
        if (isalpha(*ptr)) {
            letters++;
        } else if (isdigit(*ptr)) {
            digits++;
        } else if (*ptr == ' ') {
            spaces++;
        }
    }
}

void ShowTextAndStats(const char *text) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int wordsCount = 0;
    char **words = splitWords(text, wordsCount);
    int savedWords = wordsCount;
    freeWords(words, wordsCount);

    int charsCount = strlen(text);
    float digit_percentage = (float)(digits * 100) / charsCount;
    float letter_percentage = (float)(letters * 100) / charsCount;
    float spaces_percentage = (float)(spaces * 100) / charsCount;
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", charsCount);
    printf("Слів:\t\t%d\n", savedWords);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, letter_percentage);
    printf("Цифр:\t\t%d (%5.1f%%)\n", digits, digit_percentage);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, spaces_percentage);
}

void WordsTable(char **words, int WordsCount) {
    printf("+----+-----------------+-------+\n");
    printf("| %-2s | %-20s | %10s|\n", "N", "Слово", "Довж.");
    printf("+----+-----------------+-------+\n");
    char biggestWord[256];
    char smallestWord[256];
    strcpy(biggestWord, *words);
    strcpy(smallestWord, *words);
    float averaegeLength = 0.0;
    int max_count = 0;
    for (int i = 0; i < WordsCount; i++) {
        averaegeLength += strlen(words[i]);
        printf("| %2d | %-15s | %6d |\n", i + 1, words[i], (int)strlen(words[i]));
        if (strlen(words[i]) > strlen(biggestWord)) {
            strcpy(biggestWord, words[i]);
        }
        if (strlen(words[i]) < strlen(smallestWord)) {
            strcpy(smallestWord, words[i]);
        }
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", biggestWord, (int)strlen(biggestWord));
    printf("Найкоротше слово: %s (%d)\n", smallestWord, (int)strlen(smallestWord));
    printf("Середня довжина: %.2f\n", averaegeLength / WordsCount);
    printf("За абеткою:");
    char **sortedWords = new char*[WordsCount];
    for (int i = 0; i < WordsCount; i++) {
        sortedWords[i] = words[i];
    }
    for (int i = 0; i < WordsCount; i++) {
        for (int j = 0; j < WordsCount - 1; j++) {
            if (strcmp(sortedWords[j], sortedWords[j + 1]) > 0) {
                char *temp = sortedWords[j];
                sortedWords[j] = sortedWords[j + 1];
                sortedWords[j + 1] = temp;
            }
        }
    }

    char *mostFrequentWord = *sortedWords;
    for (int i = 0; i < WordsCount; i++) {
        int count = 0;
        for (int j = 0; j < WordsCount; j++) {
            if (strcmp(sortedWords[i], sortedWords[j]) == 0) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            mostFrequentWord = sortedWords[i];
        }
        printf(" %s", sortedWords[i]);
    }
    printf("\nНайчастіше слово: %s (%d)\n", mostFrequentWord, max_count);
    delete[] sortedWords;
}
void ReplaceWord(char *text, char **&words, int &WordsCount) {
    char oldWord[32], newWord[32];
    char latin[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Замінити слово: ");
    scanf("%31s", oldWord);
    printf("На слово: ");
    scanf("%31s", newWord);
    int i = 0;
    while(newWord[i] != '\0'){
        if (!strchr(latin, newWord[i]) && !isdigit(newWord[i])) {
            printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
            return ;
        }
        i++;
    }

    string stringText = text;
    string stringOld = oldWord;
    string stringNew = newWord;
    int count = 0;
    size_t pos = 0;
    while (pos != string::npos) {
        pos=stringText.find(stringOld, pos);
        if(pos == string::npos){
            break;
        }
        bool left = (pos == 0 || stringText[pos - 1] == ' ');
        bool right = (pos + stringOld.length() == stringText.length() || stringText[pos + stringOld.length()] == ' ' || stringText[pos + stringOld.length()] == '.');
        if (left && right) {
            stringText.replace(pos, stringOld.length(), stringNew);
            count++;
            pos += stringNew.length();
        } else {
            pos += stringOld.length();
        }
    }

    if (stringText.length() > 255) {
        printf("Помилка: текст перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", count);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, stringText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));

    freeWords(words, WordsCount);
    words = splitWords(text, WordsCount);
}

void CompareWords() {
    char firstWord[32], secondWord[32];
    printf("Перше слово: ");
    scanf("%31s", firstWord);
    printf("Друге слово: ");
    scanf("%31s", secondWord);

    string s1 = firstWord;
    string s2 = secondWord;

    int cmpResult = strcmp(firstWord, secondWord);
    if (cmpResult < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (cmpResult > 0) {
        printf("strcmp: 1 -> друге слово менше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    if (s1 == s2) {
        printf("Рівні (==): так\n");
    } else {
        printf("Рівні (==): ні\n");
    }

    bool same = (s1.length() == s2.length());
    for (int i = 0; i < (int)s1.length(); i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            same = false;
        }
    }
    if (same) {
        printf("Рівні без урахування регістру: так\n");
    } else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %d і %d\n", (int)s1.length(), (int)s2.length());
    string res = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", res.c_str(), (int)res.length());
}

void SymbolInfo(char *text) {
    char symbol;
    printf("Введіть символ: ");
    scanf(" %c", &symbol);
    printf("Символ: '%c'\n", symbol);

    printf("Код: %d (hex 0x%x, oct 0%o, bin: ", int(symbol), int(symbol), int(symbol));
    unsigned char binary;
    for (int i = 7; i >= 0; i--) {
        binary = (symbol >> i) & 1;
        printf("%d", binary);
    }
    printf(")\n");
    if (islower(symbol)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(symbol));
    } else if (isupper(symbol)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(symbol));
    } else if (isdigit(symbol)) {
        printf("Тип: цифра\n");
    } else if (isspace(symbol)) {
        printf("Тип: пробіл\n");
    } else {
        printf("Тип: інший символ\n");
    }
    printf("Наступний символ: '%c'\n", symbol + 1);
    int len = strlen(text);
    int count = 0;
    char *ptr = strchr(text, symbol);
    for (int i = 0; i < len; i++) {
        if (text[i] == symbol) {
            count++;
        }
    }
    if (ptr != NULL) {
        int firstIndex = ptr - text;
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstIndex + 1);
    } else {
        printf("Символ у тексті не зустрічається\n");
    }
}

void EnterNewValue(char *text, char **&words, int &WordsCount) {
    char NewText[256] = "";
    char word[256];
    char latin[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int readWords = 0;
    int overflow = 0;
    printf("Введіть речення (крапка після останнього слова):\n");
    while (cin >> word) {
        if(strcmp(word,".")==0){
            overflow=1;
            break;
        }
        readWords++;
        int spaceNeeded = (readWords > 1) ? 1 : 0;
        if (strlen(NewText) + spaceNeeded + strlen(word) > 255) {
            overflow = 1;
        }
        if (!overflow) {
            if (readWords > 1) {
                strcat(NewText, " ");
            }
            strcat(NewText, word);
        }
        if (word[strlen(word) - 1] == '.') {
            break;
        }
    }
    cin.ignore(10000,'\n');
    int len = strlen(NewText);
    int has_word = 0;
    bool valid = true;

    if (len < 2 || NewText[len - 1] != '.' || overflow) {
        valid = false;
    } else {
        for (int i = 0; i < len - 1; i++) {
            if (strchr(latin, NewText[i]) || isdigit(NewText[i])) {
                has_word = 1;
            } else if (NewText[i] != ' ') {
                valid = false;
                break;
            }
        }
    }
    if (!valid || has_word == 0) {
        printf("Помилка: некоректне речення.\n");
        return;
    }
    freeWords(words, WordsCount);
    strcpy(text, NewText);
    words = splitWords(NewText, WordsCount);
    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(NewText));
}