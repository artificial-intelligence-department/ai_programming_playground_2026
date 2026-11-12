/*
Задача:  Редактор текстового повідомлення
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

const int TEXT_SIZE = 256;
const int WORD_SIZE = TEXT_SIZE;

bool finishLine();
bool readLine(char text[], int size);
bool isValidText(const char* text);
bool readWord(char word[]);
char** splitWords(const char* text, int& count);
void freeWords(char**& words, int& count);
void countChars(const char* text, int& letters, int& digits, int& spaces);
void showStatistics(const char* text, int count);
void showWords(char** words, int count);
void replaceWord(char text[]);
void compareWords();
void showCharacter(const char* text);
void readSentence(char text[]);

int main() {
    char text[TEXT_SIZE];
    int count = 0;
    int choice = -1;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!readLine(text, TEXT_SIZE) || !isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    char** words = splitWords(text, count);

    do {
        printf("\nОберіть пункт:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\nВаш вибір: ");

        int result = scanf("%9d", &choice);
        if (result < 0) {
            break;
        }
        bool extra = finishLine();
        if (result != 1 || extra) {
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        }
        if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            choice = -1;
            continue;
        }

        printf("\n");
        switch (choice) {
            case 1:
                showStatistics(text, count);
                break;
            case 2:
                showWords(words, count);
                break;
            case 3:
                replaceWord(text);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharacter(text);
                break;
            case 6:
                readSentence(text);
                break;
            case 0:
                break;
        }

        if (choice == 3 || choice == 6) {
            freeWords(words, count);
            words = splitWords(text, count);
        }
    } while (choice != 0);

    freeWords(words, count);
    return 0;
}

bool finishLine() {
    bool extra = false;
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == '\n') {
            break;
        }
        if (c != ' ' && c != '\t' && c != '\r') {
            extra = true;
        }
    }
    return extra;
}

bool readLine(char text[], int size) {
    if (fgets(text, size, stdin) == nullptr) {
        return false;
    }
    char* enter = strchr(text, '\n');
    if (enter != nullptr) {
        *enter = '\0';
        return true;
    }

    char c;
    if (scanf("%c", &c) != 1 || c == '\n') {
        return true;
    }
    finishLine();
    return false;
}

bool isValidText(const char* text) {
    int length = strlen(text);
    if (length < 2 || length > 255) {
        return false;
    }
    if (text[length - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    for (int i = 0; i < length - 1; i++) {
        unsigned char c = text[i];
        bool isLetter = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        if (isLetter || isdigit(c)) {
            hasWord = true;
        }
        else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}

bool readWord(char word[]) {
    if (!readLine(word, WORD_SIZE) || strlen(word) == 0) {
        printf("Помилка: введіть одне слово від 1 до 255 символів.\n");
        return false;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        unsigned char c = word[i];
        bool isLetter = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        if (!isLetter && !isdigit(c)) {
            printf("Помилка: у слові дозволені лише латинські літери та цифри.\n");
            return false;
        }
    }
    return true;
}

char** splitWords(const char* text, int& count) {
    count = 0;
    for (int i = 0; text[i] != '.'; i++) {
        if (text[i] != ' ' && (i == 0 || text[i - 1] == ' ')) {
            count++;
        }
    }

    char buffer[TEXT_SIZE];
    strcpy(buffer, text);
    buffer[strlen(buffer) - 1] = '\0';
    char** words = new char*[count];
    char* word = strtok(buffer, " ");
    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        word = strtok(nullptr, " ");
    }
    return words;
}

void freeWords(char**& words, int& count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char* p = text; *p != '\0'; p++) {
        unsigned char c = *p;
        if (isalpha(c)) {
            letters++;
        }
        else if (isdigit(c)) {
            digits++;
        }
        else if (c == ' ') {
            spaces++;
        }
    }
}

void showStatistics(const char* text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", length);
    printf("Слів:     %5d\n", count);
    printf("Літер:    %5d (%5.1f%%)\n", letters, 100.0 * letters / length);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, 100.0 * digits / length);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, 100.0 * spaces / length);
}

void showWords(char** words, int count) {
    int minIndex = 0, maxIndex = 0;
    int sum = 0;
    int width = 15;
    int numberWidth = 2;
    for (int n = count; n >= 100; n /= 10) {
        numberWidth++;
    }
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        sum += length;
        if (length > width) {
            width = length;
        }
        if (strlen(words[i]) < strlen(words[minIndex])) {
            minIndex = i;
        }
        if (strlen(words[i]) > strlen(words[maxIndex])) {
            maxIndex = i;
        }
    }

    string border = "+" + string(numberWidth + 2, '-') + "+"
                  + string(width + 2, '-') + "+-------+";
    printf("%s\n", border.c_str());
    printf("| %-*s | Слово%*s | Довж. |\n", numberWidth, "N", width - 5, "");
    printf("%s\n", border.c_str());
    for (int i = 0; i < count; i++) {
        printf("| %*d | %-*s | %5zu |\n", numberWidth, i + 1, width, words[i], strlen(words[i]));
    }
    printf("%s\n", border.c_str());
    printf("Найдовше слово: %s (%zu)\n", words[maxIndex], strlen(words[maxIndex]));
    printf("Найкоротше слово: %s (%zu)\n", words[minIndex], strlen(words[minIndex]));
    printf("Середня довжина: %.2f\n", 1.0 * sum / count);

    char** sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(sorted[j], sorted[i]) < 0) {
                char* temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    int bestIndex = 0, bestCount = 0;
    for (int i = 0; i < count; i++) {
        int currentCount = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sorted[i], sorted[j]) == 0) {
                currentCount++;
            }
        }
        if (currentCount > bestCount) {
            bestCount = currentCount;
            bestIndex = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);
    delete[] sorted;
}

void replaceWord(char text[]) {
    char oldWord[WORD_SIZE], newWord[WORD_SIZE];
    printf("Замінити слово: ");
    if (!readWord(oldWord)) {
        return;
    }
    printf("На слово: ");
    if (!readWord(newWord)) {
        return;
    }

    string result = text;
    string from = oldWord, to = newWord;
    size_t pos = result.find(from);
    int replacements = 0;
    while (pos != string::npos) {
        size_t end = pos + from.length();
        bool left = pos == 0 || result[pos - 1] == ' ';
        bool right = result[end] == ' ' || result[end] == '.';
        if (left && right) {
            result.replace(pos, from.length(), to);
            replacements++;
            pos += to.length();
        }
        else {
            pos++;
        }
        pos = result.find(from, pos);
    }

    if (result.length() > 255) {
        printf("Помилка: після заміни текст перевищить 255 символів.\n");
        return;
    }
    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %zu\n", result.length());
    strcpy(text, result.c_str());
}

void compareWords() {
    char first[WORD_SIZE], second[WORD_SIZE];
    printf("Перше слово: ");
    if (!readWord(first)) {
        return;
    }
    printf("Друге слово: ");
    if (!readWord(second)) {
        return;
    }

    int result = strcmp(first, second);
    if (result < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (result > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string a = first, b = second;
    if (a == b) {
        printf("Рівні (==): так\n");
    }
    else {
        printf("Рівні (==): ні\n");
    }

    string lowerA = a, lowerB = b;
    int lengthA = a.length(), lengthB = b.length();
    for (int i = 0; i < lengthA; i++) {
        unsigned char c = a[i];
        lowerA[i] = tolower(c);
    }
    for (int i = 0; i < lengthB; i++) {
        unsigned char c = b[i];
        lowerB[i] = tolower(c);
    }
    if (lowerA == lowerB) {
        printf("Рівні без урахування регістру: так\n");
    }
    else {
        printf("Рівні без урахування регістру: ні\n");
    }
    string joined = a + " & " + b;
    printf("Довжини: %d і %d\n", lengthA, lengthB);
    printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}

void showCharacter(const char* text) {
    char input[3];
    printf("Введіть один символ (можна пробіл): ");
    if (!readLine(input, 3) || strlen(input) != 1) {
        printf("Помилка: введіть один однобайтовий символ.\n");
        return;
    }
    unsigned char c = input[0];
    unsigned int code = c;
    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%u", (code >> bit) & 1u);
    }
    printf(")\n");

    if (isupper(c)) {
        printf("Тип: велика літера\nІнший регістр: '%c'\n", tolower(c));
    }
    else if (islower(c)) {
        printf("Тип: мала літера\nІнший регістр: '%c'\n", toupper(c));
    }
    else if (isdigit(c)) {
        printf("Тип: цифра\n");
    }
    else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: інший символ\n");
    }
    if (code < 255) {
        int next = code + 1;
        printf("Наступний символ: '%c'\n", next);
    }
    else {
        printf("Наступного коду в межах одного байта немає.\n");
    }

    int count = 0, first = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char current = text[i];
        if (current == c) {
            count++;
            if (first == -1) {
                first = i + 1;
            }
        }
    }
    if (count == 0) {
        printf("Символ у тексті не зустрічається.\n");
    }
    else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, first);
    }
}

void readSentence(char text[]) {
    string sentence, word;
    int count = 0;
    bool finished = false;
    printf("Введіть речення (крапка після останнього слова):\n");
    while (cin >> word) {
        count++;
        if (sentence.length() <= 255) {
            if (count > 1) {
                sentence += ' ';
            }
            sentence += word;
        }
        if (word[word.length() - 1] == '.') {
            finished = true;
            break;
        }
    }
    if (finished) {
        finishLine();
    }
    if (!finished || !isValidText(sentence.c_str())) {
        printf("Помилка: некоректне речення або перевищено 255 символів.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}
