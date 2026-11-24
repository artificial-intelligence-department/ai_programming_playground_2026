/*  
Задача: Class Practice Task. 
Завдання: Редактор текстового зображення.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;


// Динамічний масив слів.
char **splitWords(const char *text, int &count) {
char copy[256];
strcpy(copy, text);

count = 0;
char *part = strtok(copy, " .");
while (part != 0) {
    count++;
    part = strtok(0, " .");}

char **words = new char*[count];
strcpy(copy, text);
part = strtok(copy, " .");
for (int i = 0; i < count; i++) {
    words[i] = new char[strlen(part) + 1];
    strcpy(words[i], part);
    part = strtok(0, " .");}
    return words;
}

void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = 0;
    count = 0;
}

// Обхід тексту вказівником.
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    const char *p = text;
    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) letters++;
        if (isdigit((unsigned char)*p)) digits++;
        if (*p == ' ') spaces++;
        p++;
    }
}

void showStats(const char text[], int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("\nТекст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", len);
    printf("Слів:\t\t%d\n", count);
    printf("Літер:\t\t%d (%.1f%%)\n", letters, letters * 100.0 / len);
    printf("Цифр:\t\t%d (%.1f%%)\n", digits, digits * 100.0 / len);
    printf("Пробілів:\t%d (%.1f%%)\n", spaces, spaces * 100.0 / len);
}

void showTable(char **words, int count) {
    printf("\n+----+---------------------------------+-------+\n");
    printf("| N  | Слово                           | Довж. |\n");
    printf("+----+---------------------------------+-------+\n");

    int longest = 0;
    int shortest = 0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-31s | %5d |\n", i + 1, words[i], len);
        sum += len;
        if (len > (int)strlen(words[longest])) longest = i;
        if (len < (int)strlen(words[shortest])) shortest = i;
    }
    printf("+----+---------------------------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // Сортуємо лише копію масиву вказівників, не початковий words.
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) sorted[i] = words[i];

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
    for (int i = 0; i < count; i++) printf(" %s", sorted[i]);
    printf("\n");

    int bestIndex = 0;
    int bestCount = 0;
    for (int i = 0; i < count; i++) {
        int same = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sorted[i], sorted[j]) == 0) same++;
        }
        if (same > bestCount) {
            bestCount = same;
            bestIndex = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);
    delete[] sorted;
}

void replaceWord(char text[], char **&words, int &count) {
    char from[256], to[256];
    printf("Замінити слово: ");
    if (scanf("%255s", from) != 1) return;
    printf("На слово: ");
    if (scanf("%255s", to) != 1) return;
    int ch = getchar();
    while (ch != '\n' && ch != -1) ch = getchar();

    int correct = 1;
    if (strlen(from) > 31 || strlen(to) > 31) correct = 0;
    for (int i = 0; from[i] != '\0'; i++) {
        if (!((from[i] >= 'A' && from[i] <= 'Z') || (from[i] >= 'a' && from[i] <= 'z') || (from[i] >= '0' && from[i] <= '9'))) correct = 0;
    }
    for (int i = 0; to[i] != '\0'; i++) {
        if (!((to[i] >= 'A' && to[i] <= 'Z') || (to[i] >= 'a' && to[i] <= 'z') || (to[i] >= '0' && to[i] <= '9'))) correct = 0;
    }
    if (correct == 0) {
        printf("Помилка: слова повинні містити 1-31 латинських літер або цифр.\n");
        return;
    }

    string before = text;
    string result = before;
    int replacements = 0;
    int start = 0;

    while (start < (int)result.length()) {
        int pos = (int)result.find(from, start);
        if (pos == -1) break;

        int leftOk = 0;
        int rightOk = 0;
        if (pos == 0 || result[pos - 1] == ' ') leftOk = 1;
        if (pos + strlen(from) == result.length() ||
            result[pos + strlen(from)] == ' ' ||
            result[pos + strlen(from)] == '.') rightOk = 1;

        if (leftOk && rightOk) {
            result.replace(pos, strlen(from), to);
            replacements++;
            start = pos + strlen(to);
            if (result.length() > 255) {
                printf("Помилка: після заміни текст перевищив би 255 символів.\n");
                return;
            }
        } else {
            start = pos + 1;
        }
    }

    strcpy(text, result.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)result.length());
}

void compareWords() {
    char a[256], b[256];
    printf("Перше слово: ");
    if (scanf("%255s", a) != 1) return;
    printf("Друге слово: ");
    if (scanf("%255s", b) != 1) return;
    int ch = getchar();
    while (ch != '\n' && ch != -1) ch = getchar();

    int correct = 1;
    if (strlen(a) > 31 || strlen(b) > 31) correct = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (!((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= '0' && a[i] <= '9'))) correct = 0;
    }
    for (int i = 0; b[i] != '\0'; i++) {
        if (!((b[i] >= 'A' && b[i] <= 'Z') || (b[i] >= 'a' && b[i] <= 'z') || (b[i] >= '0' && b[i] <= '9'))) correct = 0;
    }
    if (correct == 0) {
        printf("Помилка: слова повинні містити 1-31 латинських літер або цифр.\n");
        return;
    }

    int cmp = strcmp(a, b);
    if (cmp < 0) printf("strcmp: -1 -> перше слово менше\n");
    if (cmp == 0) printf("strcmp: 0 -> слова однакові\n");
    if (cmp > 0) printf("strcmp: 1 -> перше слово більше\n");

    string first = a;
    string second = b;
    if (first == second) printf("Рівні (==): так\n");
    else printf("Рівні (==): ні\n");

    int same = 1;
    for (int i = 0; i < (int)first.length() || i < (int)second.length(); i++) {
        if (i >= (int)first.length() || i >= (int)second.length()) {
            same = 0;
            break;
        }
        if (tolower((unsigned char)first[i]) != tolower((unsigned char)second[i])) same = 0;
    }
    if (same) printf("Рівні без урахування регістру: так\n");
    else printf("Рівні без урахування регістру: ні\n");

    string joined = first + " & " + second;
    printf("Довжини: %d і %d\n", (int)first.length(), (int)second.length());
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

void showCharacter(const char text[]) {
    char c;
    printf("Введіть символ: ");
    if (scanf("%c", &c) != 1) return;
    int ch = getchar();
    while (ch != '\n' && ch != -1) {
        ch = getchar();
    }

    unsigned int code = (unsigned char)c;
    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--) printf("%u", (code >> bit) & 1);
    printf(")\n");

    if (c >= 'A' && c <= 'Z') {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower((unsigned char)c));
    } else if (c >= 'a' && c <= 'z') {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper((unsigned char)c));
    } else if (isdigit((unsigned char)c)) {
        printf("Тип: цифра\n");
    } else if (isspace((unsigned char)c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }
    printf("Наступний символ: '%c'\n", (unsigned char)(code + 1));

    int occurrences = 0;
    int firstPosition = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            occurrences++;
            if (firstPosition == 0) firstPosition = i + 1;
        }
    }
    if (occurrences == 0) printf("Символ у тексті не зустрічається.\n");
    else printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPosition);
}

void newSentence(char text[], char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence = "";
    string word;
    int readWords = 0;
    int finished = 0;
    int tooLong = 0;

    while (cin >> word) {
        readWords++;
        int extraSpace = 0;
        if (sentence.length() > 0) extraSpace = 1;
        if (sentence.length() + word.length() + extraSpace > 255) tooLong = 1;
        if (!tooLong) {
            if (extraSpace == 1) sentence = sentence + " ";
            sentence = sentence + word;
        }
        if (word[word.length() - 1] == '.') {
            finished = 1;
            break;
        }
    }

    int correct = 1;
    if (sentence.length() < 2 || sentence.length() > 255) correct = 0;
    if (sentence.length() >= 2) {
        if (sentence[sentence.length() - 1] != '.') correct = 0;
        if (sentence[sentence.length() - 2] == ' ') correct = 0;
    }
    int lettersOrDigits = 0;
    for (int i = 0; i < (int)sentence.length(); i++) {
        char c = sentence[i];
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) lettersOrDigits++;
        else if (c == '.' && i == (int)sentence.length() - 1) { }
        else if (c != ' ') correct = 0;
    }
    if (lettersOrDigits == 0) correct = 0;
    if (!finished || tooLong || correct == 0) {
        printf("Помилка: некоректне речення або довжина понад 255 символів.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)sentence.length());
}

int main() {
    char text[256];
    char input[258];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(input, sizeof(input), stdin) == 0) return 0;

    int len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    int correct = 1;
    if (len < 2 || len > 255) correct = 0;
    if (len >= 2) {
        if (input[len - 1] != '.') correct = 0;
        if (input[len - 2] == ' ') correct = 0;
    }
    int lettersOrDigits = 0;
    for (int i = 0; i < len; i++) {
        char c = input[i];
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) lettersOrDigits++;
        else if (c == '.' && i == len - 1) { }
        else if (c != ' ') correct = 0;
    }
    if (lettersOrDigits == 0) correct = 0;
    if (correct == 0) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою (до 255 символів).\n");
        return 0;
    }
    strcpy(text, input);

    int count = 0;
    char **words = splitWords(text, count);
    char choiceText[32];
    int running = 1;

    while (running) {
        printf("\n1 - Показати текст і статистику\n");
        printf("2 - Таблиця слів\n");
        printf("3 - Замінити слово\n");
        printf("4 - Порівняти два слова\n");
        printf("5 - Інформація про символ\n");
        printf("6 - Ввести нове речення\n");
        printf("0 - Вийти\n");

        if (scanf("%31s", choiceText) != 1) break;
        int ch = std::getchar();
        while (ch != '\n' && ch != -1) {
            ch = std::getchar();
        }

        int numeric = 1;
        for (int i = 0; choiceText[i] != '\0'; i++) {
            if (!isdigit((unsigned char)choiceText[i])) numeric = 0;
        }
        if (!numeric) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        if (strlen(choiceText) != 1 || choiceText[0] > '6') {
            printf("Помилка: пункту %s немає в меню.\n", choiceText);
            continue;
        }
        int choice = choiceText[0] - '0';
        switch (choice) {
            case 1:
                showStats(text, count);
                break;
            case 2:
                showTable(words, count);
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
            default:
                running = 0;
                break;
        }

    }

    freeWords(words, count);
    return 0;
}
