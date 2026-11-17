#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
using namespace::std;
/* Редактор текстового повідомлення
   Сідлецький Тимофій ШІ-13*/

bool validText(const char *text, int length) {
    bool valid = true;
    bool hasword = false;

    if (length == 0 || text[length - 1] != '.') valid = false;

    for (int i = 0; i < length - 1; i++) {
        if (isalpha((unsigned char)text[i]) ||
            isdigit((unsigned char)text[i])) {
            hasword = true;
        }
        else if (text[i] != ' ') {
            valid = false;
        }
    }
    if (!hasword) valid = false;
    return valid;
}
bool validWord(const char *word, int length) {
    if (length == 0) return false;

    for (int i = 0; i < length; i++) {
        if (!isalpha((unsigned char)word[i]) && !isdigit((unsigned char)word[i])) return false;
    }
    return true;
}
void removeNewline(char *text) {
    int length = strlen(text);

    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    }
}
void clearLine() {
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {}
}
char **splitWords (const char *text, int &count) {
    count = 0;
    char copy[256];
    strcpy (copy, text);
    char *word = strtok(copy, " .");

    while(word != nullptr) {
        count++;
        word = strtok(nullptr, " .");
    }

    char **words = new char*[count];
    strcpy(copy, text);

    word = strtok(copy, " .");
    int i = 0;
    while (word != nullptr) {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        i++;
        word = strtok(nullptr, " .");
    }
    return words;
}
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    const char *p = text;
    while(*p != '\0') {
        if (isalpha((unsigned char)*p)) letters++;
        else if (isdigit((unsigned char)*p)) digits++;
        else if (*p == ' ') spaces++;
        p++;
    }
}
void showText (char *text, int count) {
    int letters,digits,spaces;
    int symbols = strlen(text);
    countChars(text,letters,digits,spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%4d\n", symbols);
    printf("Слів:%4d\n",count);
    printf("Літер:%4d (%.1f%%)\n", letters, letters * 100.0 / symbols);
    printf("Цифр:%4d (%.1f%%)\n", digits, digits * 100.0 / symbols);
    printf("Пробілів:%4d (%.1f%%)\n", spaces, spaces * 100.0 / symbols);
}
void textTable (char **words, int count) {
    string tableBorder = "+----+-----------------+-------+";
    int mostfrin = 0;
    int frequentCount = 1;
    int mostFrequentCount = 1;
    int longest = 0;
    int shortest = 0;
    double sum = 0;
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        if (length > (int)strlen(words[longest])) longest = i;
        if (length < (int)strlen(words[shortest])) shortest = i;
        sum += length;
    }

    char **copy = new char*[count];
    for (int i = 0; i < count; i++) {
        copy[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            
            if (strcmp(copy[j], copy[j + 1]) > 0) {
                char *temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < count - 1; i++) {
        if (strcmp(copy[i], copy[i + 1]) == 0) frequentCount++;
        else frequentCount = 1;
        if (frequentCount > mostFrequentCount) {
            mostfrin = i;
            mostFrequentCount = frequentCount;
        }
    }
    
    printf("%s\n",tableBorder.c_str());
    printf("|  N | Слово%10s | Довж. |\n", "");
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-15s | %5zu |\n", i + 1, words[i], strlen(words[i]));
    }
    printf("%s\n",tableBorder.c_str());
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", sum / count);
    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", copy[i]);
    }
    printf("\nНайчастіше слово: %s (%d)\n", copy[mostfrin], mostFrequentCount);
}
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}
void replaceWord(char *text, char **&words, int &count) {
    char oldWord[256];
    char newWord[256];
    printf("Замінити слово: ");
    fgets(oldWord, 256, stdin);
    removeNewline(oldWord);

    if (!validWord(oldWord, strlen(oldWord))) {
        printf("Некоректний текст\n");
        return;
    }
    printf("\nНа слово: ");
    fgets(newWord, 256, stdin);
    removeNewline(newWord);

    if (!validWord(newWord, strlen(newWord))) {
        printf("Некоректний текст\n");
        return;
    }
    string oldText = text;
    string newText = text;
    string oldWords = oldWord;
    string newWords = newWord;
    int subs = 0;
    int pos = 0;
    while (newText.find(oldWord, pos) != string::npos) {
        pos = newText.find(oldWord, pos);
        int endpos = pos + oldWords.length();
        bool leftBoundary = (pos == 0 || newText[pos - 1] == ' ');
        bool rigthBoundary = (newText[endpos] == ' ' || newText[endpos] == '.');
        if (leftBoundary && rigthBoundary) {
            newText.replace(pos, oldWords.length(), newWords);
            subs++;
            pos += newWords.length();
        } else pos += oldWords.length();
    }

    if (newText.length() > 255) {
        printf("Помилка: текст перевищує 255 символів\n");
        return;
    }
    freeWords(words, count);
    int length = newText.length();
    for (int i = 0; i < length; i++) {
        text[i] = newText[i];
    }
    text[length] = '\0';
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", subs);
    printf("Було: \"%s\"\n", oldText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", newText.length());
}
void compareWords () {
    char word1[255];
    char word2[255];
    printf("Перше слово: ");
    fgets(word1, 255, stdin);
    removeNewline(word1);
    if(!validWord(word1, strlen(word1))) {
        printf("Некоректний текст\n");
        return;
    }
    printf("Друге слово: ");
    fgets(word2, 255, stdin);
    removeNewline(word2);
    if(!validWord(word2, strlen(word2))) {
        printf("Некоректний текст\n");
        return;
    }
    int result = strcmp(word1,word2);
    if (result < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (result > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }
    string word1s = word1;
    string word2s = word2;
    string con = string(word1s) + " & " + string(word2s);
    printf("Рівні (==): %s\n", word1s == word2s ? "так" : "ні");
    for (int i = 0; i < (int)word1s.length(); i++) {
        word1s[i] = tolower((unsigned char)word1s[i]);
    }
    for (int i = 0; i < (int)word2s.length(); i++) {
        word2s[i] = tolower((unsigned char)word2s[i]);
    }
    printf("Рівні без урахування регістру: %s\n", word1s == word2s ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(word1), (int)strlen(word2));
    printf("Конкатенація: \"%s\" (%d)\n", con.c_str(), (int)con.length());
}
void charInfo (char *text) {
    char charAsked[3];
    int appears = 0;
    printf("Введіть символ: ");
    if (!fgets(charAsked, 3, stdin)) {
        printf("Помилка введення\n");
        return;
    }
    if (strchr(charAsked, '\n') == nullptr) {
        clearLine();
    }
    removeNewline(charAsked);
    if (strlen(charAsked) != 1) {
        printf("Помилка: введіть один символ.\n");
        return;
    }
    unsigned char c = charAsked[0];
    unsigned int code = c;
    printf("Символ: '%c'\nКод: %u (hex 0x%x, oct 0%o, bin ", c, code, code, code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%u", (code >> bit) & 1u);
    }
    printf(")\n");
    if (isupper(c)) {
        printf("Тип: велика літера\nІнший регістр: '%c'\n", tolower(c));
        printf("Наступний символ: '%c'\n", (int)(code + 1));
    } else if (islower(c)) {
        printf("Тип: мала літера\nІнший регістр: '%c'\n", toupper(c));
        printf("Наступний символ: '%c'\n", (int)(code + 1));
    } else if (isdigit(c)) {
        printf("Тип: цифра\n");
    } else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    for (char *p = text; *p != '\0'; p++) {
        if (*p == c) {
            appears++;
        }
    }
    char *first = strchr(text, c);
    if (first == nullptr) {
        printf("Символ у тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", appears, (int)(first - text) + 1);
    }
}
void newSentence (char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string newSentence;
    string word;
    int wordCount = 0;
    bool end = false;
    bool tooLong = false;
    while (cin >> word) {
        wordCount++;
        if (!tooLong) {
            if (wordCount > 1) newSentence += " ";
            if (newSentence.length() + word.length() > 255) tooLong = true;
            else newSentence += word;
        }
        if(word[word.length() - 1] == '.') {
            end = true;
            break;
        }
    }
    clearLine();
    if (!end || tooLong || !validText(newSentence.c_str(), newSentence.length())) {
        printf("Помилка: некоректне речення або довжина перевищує 255 символів.\n");
        return;
    }
    freeWords(words, count);
    int length = newSentence.length();
    for (int i = 0; i < length; i++) {
        text[i] = newSentence[i];
    }
    text[length] = '\0';
    words = splitWords(text, count);
    printf("Прочитано слів: %d\nНовий текст: \"%s\"\nДовжина: %d\n", wordCount, text, (int)newSentence.length());
}


int main () {
    char text[256];
    int len;
    int count = 0;
    int action = 0;
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    fgets(text, 256, stdin);
    removeNewline(text);
    len = strlen(text);
    if (!validText(text,len)) {
        printf("Некоректний текст\n");
        return 1;
    }
    char **words = splitWords(text, count);
    do {
        menuStart:
        printf("\nВведіть пункт меню:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\nВаш вибір: ");
        if (scanf("%d", &action) != 1) {
            clearLine();
            printf("Помилка: введіть номер пункту меню.\n");
            goto menuStart;
        } else {
            char cinRemain[256];
            if (fgets(cinRemain, 256, stdin) == nullptr) {
                printf("Помилка введення.\n");
                goto menuStart;
            }

            char *newline = strchr(cinRemain, '\n');

            if (newline != nullptr) {
                *newline = '\0';
            }
            
            for (char *p = cinRemain; *p != '\0'; p++) {
                if (!isspace((unsigned char)*p)) {
                    printf("Помилка: введіть номер пункту меню.\n");
                    goto menuStart;
                }
            }
        }

        
        switch (action) {
            case 1:
                showText(text, count);
                break;
            case 2:
                textTable(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                newSentence(text, words, count);
                break;
            case 0:
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", action);
                goto menuStart;
        }
    } while (action != 0);
    freeWords(words, count);
    return 0;
}