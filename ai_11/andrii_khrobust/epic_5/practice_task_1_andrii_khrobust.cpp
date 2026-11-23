#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdio>
using namespace std;

bool isValidText(char* text) {
        if (strlen(text) == 0 || text[strlen(text) - 1] != '.') 
        return false;
        bool hasWord = false;

    for (int i = 0; i < strlen(text) - 1; i++) {
        char c = text[i];

        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9')) {
            hasWord = true;
        }
        else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}

char **splitWords(const char *text, int &count) {
    char temp[256];
    strcpy(temp, text);
    temp[strlen(temp) - 1] = '\0';
    count = 0;
    char *word = strtok(temp, " ");
    while (word != NULL) {
        count++;
        word = strtok(NULL, " ");
    }
    char **words = new char*[count];
    strcpy(temp, text);
    temp[strlen(temp) - 1] = '\0';
    word = strtok(temp, " ");
    for (int i = 0; i < count; i++) {
    words[i] = new char[strlen(word) + 1];
    strcpy(words[i], word);
    word = strtok(NULL, " ");
    }
    return words;
}

void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letters++;
        }
        else if (isdigit(text[i])) {
            digits++;
        }
        else if (text[i] == ' ') {
            spaces++;
        }
    }
}

void showStats(const char *text, int count) {
    int letters, digits, spaces;
    int length = strlen(text);
    countChars(text, letters, digits, spaces);
    printf("Текст: \"%s\"\n", text);
    printf("Символів: %d\n", length);
    printf("Слів:   %d\n", count);
    printf("Літер:   %2d (%5.1f%%)\n", letters, letters* 100.0 / length );
    printf("Цифр:     %d (%5.1f%%)\n", digits, digits * 100.0 / length );
    printf("Пробілів: %d (%5.1f%%)\n", spaces, spaces * 100.0 / length );
}

void wordsTable(char **words, int count) {
    printf("%-5s %-20s %8s\n", "№", "Слово", "Довжина");
    int longest = 0;
    int shortest = 0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("%-5d %-20s %8d\n", i + 1, words[i], len);
        if (len > strlen(words[longest])) {
            longest = i;
        }
        if (len < strlen(words[shortest])) {
            shortest = i;
        }
        sum += len;
    }
    printf("\nНайдовше слово: %s (%d)\n",
           words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n",
           words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина слова: %.2f\n", (double)sum / count);
    char **sortedWords = new char*[count];
    for (int i = 0; i < count; i++) {
        sortedWords[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(sortedWords[j], sortedWords[minIndex]) < 0) {
                minIndex = j;
            }
        }
        char *temp = sortedWords[i];
        sortedWords[i] = sortedWords[minIndex];
        sortedWords[minIndex] = temp;
    }
    printf("за абеткою:");
    for (int i = 0; i < count; i++) {
        printf("%s ", sortedWords[i]);
    }
    int maxFrequency = 0;
    char *mostFrequent = sortedWords[0];
    for (int i = 0; i < count; i++) {
        int frequency = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sortedWords[i], sortedWords[j]) == 0) {
                frequency++;
            }
        }
        if (frequency > maxFrequency) {
            maxFrequency = frequency;
            mostFrequent = sortedWords[i];
        }
    }
    printf("\nНайчастіше слово: %s (%d)\n",
           mostFrequent, maxFrequency);
    delete[] sortedWords;
}

void replaceWord(char *text, char **&words, int &count) {
    char oldWord[32], newWord[32];
    printf("Замінити слово: ");
    if (scanf("%31s", oldWord) != 1) {
        printf("Помилка введення.\n");
        return;
    }
    printf("На слово: ");
    if (scanf("%31s", newWord) != 1) {
        printf("Помилка введення.\n");
        return;
    }
    bool valid = true;
    for (int i = 0; oldWord[i] != '\0'; i++) {
        if (!((oldWord[i] >= 'A' && oldWord[i] <= 'Z') ||
              (oldWord[i] >= 'a' && oldWord[i] <= 'z') ||
              (oldWord[i] >= '0' && oldWord[i] <= '9'))) {
            valid = false;
        }
    }
    for (int i = 0; newWord[i] != '\0'; i++) {
        if (!((newWord[i] >= 'A' && newWord[i] <= 'Z') ||
              (newWord[i] >= 'a' && newWord[i] <= 'z') ||
              (newWord[i] >= '0' && newWord[i] <= '9'))) {
            valid = false;
        }
    }
    if (!valid) {
        printf("Помилка: використовуйте лише латинські літери та цифри.\n");
        return;
    }
    string result = text;
    string before = result;
    int replacements = 0;
    size_t pos = 0;
    while ((pos = result.find(oldWord, pos)) != string::npos) {
        bool left = (pos == 0 || result[pos - 1] == ' ');
        bool right = (pos + strlen(oldWord) == result.length() - 1 ||
                      result[pos + strlen(oldWord)] == ' ');
        if (left && right) {
            result.replace(pos, strlen(oldWord), newWord);
            pos += strlen(newWord);
            replacements++;
        }
        else {
            pos += strlen(oldWord);
        }
    }
    if (result.length() > 255) {
        printf("Помилка: текст перевищує 255 символів.\n");
        return;
    }
    if (replacements > 0) {
        strcpy(text, result.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
    }
    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

void compareTwoWords() {
    char a[32], b[32];
    printf("Перше слово: ");
    if (scanf("%31s", a) != 1) {
        printf("Помилка введення.\n");
        return;
    }
    printf("Друге слово: ");
    if (scanf("%31s", b) != 1) {
        printf("Помилка введення.\n");
        return;
    }
    string str1 = a;
    string str2 = b;
    int result = strcmp(a, b);
    if (result < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (result > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else {
        printf("strcmp: 0 -> слова однакові\n");
    }
    if (str1 == str2) {
        printf("Рівні (==): так\n");
    }
    else {
        printf("Рівні (==): ні\n");
    }
    bool equal = true;
    if (str1.length() != str2.length()) {
        equal = false;
    }
    else {
        for (int i = 0; i < str1.length(); i++) {
            if (tolower(str1[i]) != tolower(str2[i])) {
                equal = false;
                break;
            }
        }
    }
    if (equal) {
        printf("Рівні без урахування регістру: так\n");
    }
    else {
        printf("Рівні без урахування регістру: ні\n");
    }
    string combined = str1 + " & " + str2;
    printf("Довжини: %d і %d\n",
           (int)str1.length(), (int)str2.length());
    printf("Конкатенація: \"%s\" (%d)\n",
           combined.c_str(), (int)combined.length());
}

void charInfo(const char *text) {
    char c;
    printf("Введіть символ: ");
    if (scanf(" %c", &c) != 1) {
        printf("Помилка введення.\n");
        return;
    }
    unsigned char code = (unsigned char)c;
    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex 0x%02x, oct 0%o, bin ",code, code, code);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (code >> i) & 1);
    }
    printf(")\n");
    if (isupper(code)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(code));
    }
    else if (islower(code)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(code));
    }
    else if (isdigit(code)) {
        printf("Тип: цифра\n");
    }
    else if (isspace(code)) {
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: інший символ\n");
    }
    if (isalpha(code)) {
        printf("Наступний символ: '%c'\n", code + 1);
    }
    int count = 0;
    int firstPosition = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            count++;
            if (firstPosition == -1) {
                firstPosition = i + 1;
            }
        }
    }
    if (count > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n",
               count, firstPosition);
    }
    else {
        printf("У тексті не зустрічається\n");
    }
}

void enterNewSentence(char *text, char **&words, int &count) {
    string newText = "";
    string word;
    int wordCount = 0;
    bool finished = false;
    printf("Введіть речення (крапка після останнього слова):\n");
    while (!finished && cin >> word) {
        if (wordCount > 0) {
            newText += " ";
        }
        newText += word;
        wordCount++;
        if (word[word.length() - 1] == '.') {
            finished = true;
        }
    }
    if (!finished) {
        printf("Помилка: речення не завершене крапкою.\n");
        return;
    }
    if (newText.length() > 255) {
        printf("Помилка: текст перевищує 255 символів.\n");
        return;
    }
    char temp[256];
    strcpy(temp, newText.c_str());
    if (!isValidText(temp)) {
        printf("Помилка: некоректне речення.\n");
        return;
    }
    strcpy(text, newText.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

int main() {
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Помилка зчитування тексту.\n");
        return 1;
    }
    char *n = strchr(text, '\n');
    if (n) {
        *n = '\0';
    }
    if (!isValidText(text)) {
        printf("Помилка: текст має складатися із латинських літер, цифр і пробілів та завершуватись крапкою.\n");
        return 1;
    }
    int count = 0;
    char **splittedWords = splitWords(text, count);

    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Статистика тексту\n");
        printf("2. Таблиця слів\n");
        printf("3. Заміна слова\n");
        printf("4. Порівняння двох слів\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");
        if (scanf("%d", &choice) != 1) {
            printf("Зробіть свій вибір!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                showStats(text, count);
                break;
            case 2:
                wordsTable(splittedWords, count);
                break;
            case 3:
                replaceWord(text, splittedWords, count);
                break;
            case 4:
                compareTwoWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                enterNewSentence(text, splittedWords, count);
                break;
            case 0:
                break;
            default:
                printf("Неправильний пункт меню!\n");
        }

    } while (choice != 0);
    freeWords(splittedWords, count);
    return 0;
}