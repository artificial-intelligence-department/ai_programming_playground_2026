#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

bool validation(char text[]) {
    bool valid = true;
    if (strlen(text) < 2) return 0;
    if (text[strlen(text) - 1] != '.') valid = false;
    bool symbol = false;
    int size = strlen(text) - 1;
    for (int i = 0; i < size; i++) {
        if (isalnum((unsigned char)text[i])) symbol = true;
        else if (text[i] == ' ') continue;
        else { valid = false; break; }
    }
    if (symbol == false) valid = false;
    return valid;
}

char** splitWords(const char text[], int &count) {
    char temp[256];
    strcpy(temp, text);
    temp[strlen(text) - 1] = '\0';
    count = 0;
    char* word = strtok(temp, " ");
    while (word != NULL) {
        count++;
        word = strtok(NULL, " ");
    }
    char** p = new char*[count];

    strcpy(temp, text);
    temp[strlen(text) - 1] = '\0';
    word = strtok(temp, " ");
    count = 0;
    while (word != NULL) {
        p[count] = new char[strlen(word) + 1];
        strcpy(p[count], word);
        count++;
        word = strtok(NULL, " ");
    }
    return p;
}

void freeWords(char** &p, int &count) {
    if (p == NULL) {
        count = 0;
        return;
    }
    for (int i = 0; i < count; i++) {
        delete[] p[i];
    }
    delete[] p;
    p = nullptr;
    count = 0;
    return;
}

void printMenu() {
    printf("\nМеню:\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha((unsigned char)*(text + i))) letters++;
        if (isdigit((unsigned char)*(text + i))) digits++;
        if (*(text + i) == ' ') spaces++;
    }
    return;
}

void showStats(const char *text, int count) {
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);
    int total = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", total);
    printf("Слів:%10d\n", count);
    printf("Літер:%9d (%5.1f%%)\n", letters, (letters * 100.0) / total);
    printf("Цифр:%10d (%5.1f%%)\n", digits, (digits * 100.0) / total);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, (spaces * 100.0) / total);
}

void qs(char** a, int l, int r) {
    int i = l, j = r;
    char* p = a[(l + r) / 2];
    while (i <= j) {
        while (strcmp(a[i], p) < 0) i++;
        while (strcmp(a[j], p) > 0) j--;
        if (i <= j) {
            char* t = a[i];
            a[i++] = a[j];
            a[j--] = t;
        }
    }
    if (l < j) qs(a, l, j);
    if (i < r) qs(a, i, r);
}

void showWordTable(char** words, int count) {
    printf("\nТаблиця слів:\n");
    printf("#    Слово           Довжина\n");
    printf("----------------------------\n");

    int totalLen = 0;
    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("%-4d %-15s %d\n", i + 1, words[i], len);

        totalLen += len;
        if (len < strlen(words[minIdx])) {
            minIdx = i;
        }
        if (len > strlen(words[maxIdx])) {
            maxIdx = i;
        }
    }

    int bestWordIdx = 0;
    int maxFreq = 0;
    for (int i = 0; i < count; i++) {
        int freq = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                freq++;
            }
        }
        if (freq > maxFreq) {
            maxFreq = freq;
            bestWordIdx = i;
        }
    }

    double avgLen = (double)totalLen / count;

    printf("\nНайдовше слово:    \"%s\" (%d симв.)\n", words[maxIdx], (int)strlen(words[maxIdx]));
    printf("Найкоротше слово:  \"%s\" (%d симв.)\n", words[minIdx], (int)strlen(words[minIdx]));
    printf("Середня довжина:   %.2f симв.\n", avgLen);
    printf("Найчастіше слово:  \"%s\" (%d раз.)\n", words[bestWordIdx], maxFreq);

    char** sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    qs(sorted, 0, count - 1);

    printf("\nСлова за абеткою:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, sorted[i]);
    }

    delete[] sorted;
}

bool readLine(const char* prompt, char* buf, int size) {
    printf("%s", prompt);
    if (!fgets(buf, size, stdin)) return false;
    int n = strcspn(buf, "\n");
    if (buf[n] == '\n') { buf[n] = '\0'; return true; }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return false;
}

bool readWord(const char* prompt, char* w, int size) {
    if (!readLine(prompt, w, size) || !w[0]) return false;
    for (int i = 0; w[i]; i++)
        if (!isalnum((unsigned char)w[i])) return false;
    return true;
}

void replaceWord(char text[], char** &words, int &count) {
    char oldW[256], newW[256];
    if (!readWord("Введіть слово для заміни: ", oldW, 256) || !readWord("Введіть нове слово: ", newW, 256)) {
        printf("Помилка: слово має складатися лише з латинських літер та цифр без пробілів.\n");
        return;
    }
    int hits = 0, newLen = 1;
    for (int i = 0; i < count; i++) {
        bool match = strcmp(words[i], oldW) == 0;
        if (match) hits++;
        newLen += strlen(match ? newW : words[i]) + (i > 0);
    }
    if (!hits) { printf("Слово \"%s\" не знайдено в тексті.\n", oldW); return; }
    if (newLen > 255) { printf("Помилка: після заміни довжина тексту перевищить 255 символів.\n"); return; }

    char buf[256] = "";
    for (int i = 0; i < count; i++) {
        if (i > 0) strcat(buf, " ");
        strcat(buf, strcmp(words[i], oldW) == 0 ? newW : words[i]);
    }
    strcat(buf, ".");
    strcpy(text, buf);
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Замінено входжень: %d\nОновлений текст: \"%s\"\n", hits, text);
}

void compareWords(char** words, int count) {
    char w1[256], w2[256];
    if (!readWord("Введіть перше слово: ", w1, 256) || !readWord("Введіть друге слово: ", w2, 256)) {
        printf("Помилка: слово має складатися лише з латинських літер та цифр без пробілів.\n");
        return;
    }
    int l1 = strlen(w1), l2 = strlen(w2), cmp = strcmp(w1, w2), f1 = 0, f2 = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], w1) == 0) f1++;
        if (strcmp(words[i], w2) == 0) f2++;
    }
    printf("\nРезультат порівняння \"%s\" та \"%s\":\n", w1, w2);
    if (cmp == 0) printf("- Слова повністю однакові.\n");
    else printf("- За абеткою слово \"%s\" стоїть %s, ніж \"%s\".\n", w1, cmp < 0 ? "раніше" : "пізніше", w2);

    if (l1 == l2) printf("- Довжина однакова: по %d симв.\n", l1);
    else if (l1 > l2) printf("- Слово \"%s\" довше (%d проти %d симв., різниця %d).\n", w1, l1, l2, l1 - l2);
    else printf("- Слово \"%s\" довше (%d проти %d симв., різниця %d).\n", w2, l2, l1, l2 - l1);
    printf("- У поточному тексті \"%s\" зустрічається %d раз., \"%s\" — %d раз.\n", w1, f1, w2, f2);
}

void charInfo(const char* text) {
    char buf[64];
    if (!readLine("Введіть один символ: ", buf, 64) || strlen(buf) != 1) {
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }
    unsigned char ch = buf[0];
    printf("\nІнформація про символ '%c':\n- Код ASCII: %d\n", ch, ch);
    if (isupper(ch)) printf("- Категорія: велика літера\n- У нижньому регістрі: '%c'\n", tolower(ch));
    else if (islower(ch)) printf("- Категорія: мала літера\n- У верхньому регістрі: '%c'\n", toupper(ch));
    else printf("- Категорія: %s\n", isdigit(ch) ? "цифра" : (ch == ' ' ? "пробіл" : (ispunct(ch) ? "розділовий знак" : "інший символ")));

    int freq = 0;
    for (int i = 0; text[i]; i++) if ((unsigned char)text[i] == ch) freq++;
    printf("- Кількість у тексті: %d\n", freq);
    if (freq > 0) {
        printf("- Позиції (індекси): ");
        for (int i = 0, first = 1; text[i]; i++)
            if ((unsigned char)text[i] == ch) { printf("%s%d", first ? "" : ", ", i); first = 0; }
        printf("\n");
    }
}

void enterNewSentence(char text[], char** &words, int &count) {
    char buf[256];
    if (!readLine("Введіть новий текст (до 255 символів, крапка в кінці):\n", buf, 256) || !validation(buf)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. Попередній текст збережено.\n");
        return;
    }
    strcpy(text, buf);
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Текст успішно оновлено.\n");
}

int main() {
    char text[256];
    bool valid = true;
    int count;
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
        return 0;
    }
    if (text[strcspn(text, "\n")] == '\n') text[strcspn(text, "\n")] = '\0';
    else valid = false;
    if (valid == true) valid = validation(text);
    if (valid == false) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
        return 0;
    }
    char** p = splitWords(text, count);

    while (true) {
        printMenu();
        printf("Ваш вибір: ");
        int choice;
        int scanned = scanf("%d", &choice);

        if (scanned == EOF) {
            break;
        }

        bool extraChars = false;
        char ch;
        while (scanf("%c", &ch) == 1 && ch != '\n') {
            extraChars = true;
        }

        if (scanned != 1 || extraChars) {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: showStats(text, count); break;
            case 2: showWordTable(p, count); break;
            case 3: replaceWord(text, p, count); break;
            case 4: compareWords(p, count); break;
            case 5: charInfo(text); break;
            case 6: enterNewSentence(text, p, count); break;
            default: printf("Помилка: пункту %d немає в меню.\n", choice); break;
        }
    }

    freeWords(p, count);
    return 0;
}