/*
Назва задачі: Редактор текстового повідомлення
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

void clearLine() {
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
    }
}

bool readLine(char *text, int capacity) {
    if (fgets(text, capacity, stdin) == nullptr) {
        return false;
    }

    char *newline = strchr(text, '\n');
    if (newline != nullptr) {
        *newline = '\0';
    } else {
        char next;
        if (scanf("%c", &next) == 1 && next != '\n') {
            clearLine();
            return false;
        }
    }
    return true;
}

bool validLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool validWord(char *word) {
    int length = strlen(word);
    if (length == 0 || length > 31) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (!validLetter(word[i]) && !isdigit((unsigned char)word[i])) {
            return false;
        }
    }
    return true;
}

bool validText(const char *text) {
    int length = strlen(text);
    if (length == 0 || length > 255 || text[length - 1] != '.') {
        return false;
    }

    if (length < 2 || text[length - 2] == ' ') {
    return false;
    }

    bool hasWord = false;
    for (int i = 0; i < length - 1; i++) {
        if (validLetter(text[i]) || isdigit((unsigned char)text[i])) {
            hasWord = true;
        } else if (text[i] != ' ') {
            return false;
        }
    }
    return hasWord;
}

char **splitWords(const char *text, int &count) {
    char copy[256];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';

    count = 0;
    char *word = strtok(copy, " ");
    while (word != nullptr) {
        count++;
        word = strtok(nullptr, " ");
    }

    char **words = new char*[count];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';
    word = strtok(copy, " ");
    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        word = strtok(nullptr, " ");
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

void updateText(char *text, string &newText, char **&words, int &count) {
    freeWords(words, count);
    int length = newText.length();
    for (int i = 0; i < length; i++) {
        text[i] = newText[i];
    }
    text[length] = '\0';
    words = splitWords(text, count);
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            letters++;
        } else if (isdigit((unsigned char)*p)) {
            digits++;
        } else if (*p == ' ') {
            spaces++;
        }
    }
}

void showText(char *text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\nСлів:     %5d\n", length, count);
    printf("Літер:    %5d (%5.1f%%)\n", letters, letters * 100.0 / length);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, digits * 100.0 / length);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, spaces * 100.0 / length);
}

void tableBorder(int width) {
    printf("+----+");
    for (int i = 0; i < width + 2; i++) {
        printf("-");
    }
    printf("+-------+\n");
}

void showWords(char **words, int count) {
    int longest = 0;
    int shortest = 0;
    int totalLength = 0;
    int width = 15;
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        if (length > width) {
            width = length;
        }
        if (length > (int)strlen(words[longest])) {
            longest = i;
        }
        if (length < (int)strlen(words[shortest])) {
            shortest = i;
        }
        totalLength += length;
    }

    tableBorder(width);
    printf("| N  | Слово%*s | Довж. |\n", width - 5, "");
    tableBorder(width);
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-*s | %5d |\n", i + 1, width, words[i], (int)strlen(words[i]));
    }
    tableBorder(width);
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)totalLength / count);

    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    int best = 0;
    int bestCount = 1;
    int repeats = 1;
    for (int i = 1; i < count; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {
            repeats++;
        } else {
            repeats = 1;
        }
        if (repeats > bestCount) {
            best = i;
            bestCount = repeats;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);
    delete[] sorted;
}

bool readWord(char *word) {
    if (!readLine(word, 32) || !validWord(word)) {
        printf("Помилка: введіть одне слово з латинських літер і цифр, до 31 символу.\n");
        return false;
    }
    return true;
}

void replaceWord(char *text, char **&words, int &count) {
    char from[32], to[32];
    printf("Замінити слово: ");
    if (!readWord(from)) {
        return;
    }

    printf("На слово: ");
    if (!readWord(to)) {
        return;
    }

    string before = text;
    string after = text;
    string oldWord = from;
    string newWord = to;
    int replacements = 0;
    int position = 0;

    while (after.find(oldWord, position) != string::npos) {
        position = after.find(oldWord, position);
        int end = position + oldWord.length();
        bool leftBoundary = (position == 0 || after[position - 1] == ' ');
        bool rightBoundary = (after[end] == ' ' || after[end] == '.');
        if (leftBoundary && rightBoundary) {
            after.replace(position, oldWord.length(), newWord);
            replacements++;
            position += newWord.length();
        } else {
            position += oldWord.length();
        }
    }

    if (after.length() > 255) {
        printf("Помилка: після заміни текст перевищує 255 символів.\n");
        return;
    }
    updateText(text, after, words, count);
    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\nСтало: \"%s\"\n", before.c_str(), text);
    printf("Нова довжина: %d\n", (int)after.length());
}

void compareWords() {
    char a[32], b[32];
    printf("Перше слово: ");
    if (!readWord(a)) {
        return;
    }

    printf("Друге слово: ");
    if (!readWord(b)) {
        return;
    }

    int result = strcmp(a, b);
    if (result < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (result > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string first = a;
    string second = b;
    printf("Рівні (==): %s\n", first == second ? "так" : "ні");
    for (int i = 0; i < (int)first.length(); i++) {
        first[i] = tolower((unsigned char)first[i]);
    }
    for (int i = 0; i < (int)second.length(); i++) {
        second[i] = tolower((unsigned char)second[i]);
    }
    printf("Рівні без урахування регістру: %s\n", first == second ? "так" : "ні");
    string joined = string(a) + " & " + string(b);
    printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

void showCharacter(char *text) {
    char input[3];
    printf("Введіть символ: ");
    if (!readLine(input, 3) || strlen(input) != 1) {
        printf("Помилка: введіть один символ.\n");
        return;
    }
    unsigned char c = input[0];
    unsigned int code = c;
    printf("Символ: '%c'\nКод: %u (hex 0x%x, oct 0%o, bin ", c, code, code, code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%u", (code >> bit) & 1u);
    }
    printf(")\n");

    if (isupper(c)) {
        printf("Тип: велика літера\nІнший регістр: '%c'\n", tolower(c));
    } else if (islower(c)) {
        printf("Тип: мала літера\nІнший регістр: '%c'\n", toupper(c));
    } else if (isdigit(c)) {
        printf("Тип: цифра\n");
    } else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }
    printf("Наступний символ: '%c'\n", (int)(code + 1));

    int occurrences = 0;
    for (char *p = text; *p != '\0'; p++) {
        if (*p == c) {
            occurrences++;
        }
    }
    char *first = strchr(text, c);
    if (first == nullptr) {
        printf("Символ у тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
    }
}

void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence;
    string word;
    int readCount = 0;
    bool finished = false;
    bool tooLong = false;

    while (cin >> word) {
        readCount++;
        if (!tooLong) {
            if (readCount > 1) {
                sentence += " ";
            }
            if (sentence.length() + word.length() > 255) {
                tooLong = true;
            } else {
                sentence += word;
            }
        }
        if (word[word.length() - 1] == '.') {
            finished = true;
            break;
        }
    }
    
    clearLine();
    if (!finished || tooLong || !validText(sentence.c_str())) {
        printf("Помилка: некоректне речення або довжина перевищує 255 символів.\n");
        return;
    }
    updateText(text, sentence, words, count);
    printf("Прочитано слів: %d\nНовий текст: \"%s\"\nДовжина: %d\n", readCount, text, (int)sentence.length());
}

void showMenu() {
    printf("\nВведіть пункт меню:\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\nВаш вибір: ");
}

bool readChoice(int &choice) {
    
    int result = scanf("%3d", &choice);
    if (result == EOF) {
        choice = 0;
        return true;
    }
    if (result != 1) {
        clearLine();
        return false;
    }

    char remainder[256];
    if (!readLine(remainder, 256)) {
        return false;
    }
    for (char *p = remainder; *p != '\0'; p++) {
        if (!isspace((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

int main() {
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!readLine(text, 256) || !validText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);
    int choice = 0;
    do {
        mainMenu:
        showMenu();
        if (!readChoice(choice)) {
            printf("Помилка: введіть номер пункту меню.\n");
            goto mainMenu;
        }
        switch (choice) {
            case 1:
                showText(text, count);
                break;
            case 2:
                showWords(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharacter(text);
                break;
            case 6:
                newSentence(text, words, count);
                break;
            case 0:
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                goto mainMenu;
        }
    } while (choice != 0);

    freeWords(words, count);
    return 0;
}
