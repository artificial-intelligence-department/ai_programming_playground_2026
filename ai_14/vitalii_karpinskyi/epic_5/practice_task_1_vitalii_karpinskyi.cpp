#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

// Розбиває текст на слова у динамічному масиві
char **splitWords(const char *text, int &count) {
    char copy[256];
    strcpy(copy, text);
    size_t length = strlen(text);
    
    copy[length - 1] = '\0';
    char *word = strtok(copy, " ");

    // Рахуємо кількість слів перед виділенням пам'яті
    count = 0;
    while (word != nullptr) {
        word = strtok(nullptr, " ");
        count++;
    }
    strcpy(copy, text);
    char **words = new char*[count];

    // Копіюємо кожне слово в окремий динамічний буфер
    copy[length - 1] = '\0';
    word = strtok(copy, " ");

    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        word = strtok(nullptr, " ");
    }
    return words;
}
// Звільняє виділену пам'ять
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
        words[i] = nullptr;
    }

    delete[] words;
    words = nullptr;
    count = 0;
}
// Рахує літери, цифри та пробіли у тексті
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    const char *check = text;

    while (*check != '\0') {
        if (isalpha(*check)) letters++;
        if (isdigit(*check)) digits++;
        if (isspace(*check)) spaces++;
        ++check;
    }
}
// Перевіряє чи є символ латинською літерою або цифрою
bool isLegit(char i) {
    bool isUp = i >= 'A' && i <= 'Z';
    bool isLow = i >= 'a' && i <= 'z';
    bool isNum = i >= '0' && i <= '9';
    return isUp || isLow || isNum;
}
// Очищає буфер вводу
bool extraInput() {
    bool extra = false;
    for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar()) {
        if (ch != ' ' && ch != '\t') {
            extra = true;
        }
    }
    return extra;
}
// Пункт 1: виводить початковий текст і статистику
void choice_1 (const char *text, int count) {
    int letters;
    int digits;
    int spaces;

    countChars(text, letters, digits, spaces);
    size_t length = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: \t%3zu\n", length);
    printf("Слів: \t\t%3d\n", count);
    printf("Літер:\t\t%3d (%5.1f%%)\n", letters, 100.0 * letters / length);
    printf("Цифр: \t\t%3d (%5.1f%%)\n", digits, 100.0 * digits / length);
    printf("Пробілів: \t%3d (%5.1f%%)\n", spaces, 100.0 * spaces / length);
}
// Пункт 2: таблиця слів, найбільше / найменше слово, вивід тексту за абеткою
void choice_2(char **words, int count) {
    int min = strlen(words[0]);
    int max = strlen(words[0]);
    double sum = 0;
    int indexMin = 0;
    int indexMax = 0;

    printf("+-----+------------------------+-------+\n");
    printf("| N   | Слово                  | Довж. |\n");
    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        if (length < min) min = length, indexMin = i;
        if (length > max) max = length, indexMax = i;

        printf("| %3d | %-22s | %5d |\n", i + 1, words[i], length);    
        sum += length;
    }
    printf("+-----+------------------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[indexMax], max);
    printf("Найкоротше слово: %s (%d)\n", words[indexMin], min);
    printf("Середня довжина: %.2f\n", sum / count);

    // Сортування копії масиву вказівників щоб не змінювати порядок оригіналу
    char *sorted[130];
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
        printf(" ");
        printf("%s", sorted[i]);
    }
    printf("\n");

    // Шукаємо найчастіше слово у відсортованому списку
    max = 1;
    indexMax = 0;
    int wordMax = 1;
    for (int j = 1; j < count; j++) {
        if (strcmp(sorted[j], sorted[j - 1]) == 0) max++;
        else max = 1;
        if (wordMax < max) wordMax = max, indexMax = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[indexMax], wordMax);
}
// Пункт 3: заміна слова з урахуванням регістру
void choice_3(char *text, char **&words, int &count) {
    char from[32];
    char to[32];

    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) {
        printf("Помилка: некоректний ввід\n");
        return;
    }
    if (extraInput()) {
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return;
    }
    
    printf("На слово: ");
    if (scanf("%31s", to) != 1) {
        printf("Помилка: некоректний ввід\n");
        return;
    }
    if (extraInput()) {
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return;
    }

    for (int i = 0; from[i] != '\0'; i++) {
        if (!isLegit(from[i])) {
            printf("Помилка: слово має складатися з латинських літер і цифр\n");
            return;
        }
    }
    for (int i = 0; to[i] != '\0'; i++) {
        if (!isLegit(to[i])) {
            printf("Помилка: слово має складатися з латинських літер і цифр\n");
            return;
        }
    }
    // Виконуємо заміну слів (перевіряємо межі зліва і справа)
    string textCopy = text;
    size_t fromLength = strlen(from);
    size_t toLength = strlen(to);
    size_t pos = textCopy.find(from);
    int replacements = 0;

    while (pos != string::npos) {
        size_t after = pos + fromLength;
        bool left = pos == 0 || textCopy[pos - 1] == ' ';
        bool right = after < textCopy.size() && (textCopy[after] == ' ' || textCopy[after] == '.');

        if (left && right) {
            textCopy.replace(pos, fromLength, to);
            ++replacements;
            pos = textCopy.find(from, pos + toLength);
        } else {
            pos = textCopy.find(from, pos + 1);
        }
    }
    if (textCopy.size() > 255) {
        printf("Помилка: текст перевищує кількість знаків\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:   \"%s\"\n", text);

    // Оновлюємо основний рядок і перестворюємо динамічний масив слів
    strcpy(text, textCopy.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Стало:   \"%s\"\n", text);
    printf("Нова довжина: %zu\n", strlen(text));
}

// Пункт 4: порівняння слів через strcmp, оператором == та конкатенція
void choice_4() {
    char a[32];
    char b[32];

    printf("Перше слово: ");
    if (scanf("%31s", a) != 1) {
        printf("Помилка: некоректний ввід\n");
        return;
    }
    if (extraInput()) {
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return;
    }
    for (int i = 0; a[i] != '\0'; i++) {
        if (!isLegit(a[i])) {
            printf("Помилка: слово має складатися з латинських літер і цифр\n");
            return;
        }
    }

    printf("Друге слово: ");
    if (scanf("%31s", b) != 1) {
        printf("Помилка: некоректний ввід\n");
        return;
    }
    if (extraInput()) {
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return;
    }
    for (int i = 0; b[i] != '\0'; i++) {
        if (!isLegit(b[i])) {
            printf("Помилка: слово має складатися з латинських літер і цифр\n");
            return;
        }
    }
    // Порівнюємо лексикографічно через strcmp та оператором == для string
    int res = strcmp(a, b);
    if (res < 0) printf("strcmp: -1 -> перше слово менше\n");
    if (res == 0) printf("strcmp: 0 -> слова однакові\n");
    if (res > 0) printf("strcmp: 1 -> перше слово більше\n");

    string first = a;
    string second = b;

    printf("Рівні (==): ");
    if (first == second) printf("так\n");
    else printf("ні\n");

    // Зводимо обидва слова до нижнього регістру для порівняння без урахування регістру
    for (int i = 0; a[i] != '\0'; i++) {
        a[i] = tolower(a[i]);
    }

    for (int i = 0; b[i] != '\0'; i++) {
        b[i] = tolower(b[i]);
    }
    printf("Рівні без урахування регістру: ");
    if (strcmp(a, b) == 0) printf("так\n");
    else printf("ні\n");

    printf("Довжини: %zu і %zu\n", first.length(), second.length());

    string united = first + " & " + second;
    printf("Конкатенація: \"%s\" (%zu)\n", united.c_str(), united.length());
}

// Пункт 5: виводить коди символу, тип та його позицію в тексті
void choice_5(const char *text) {
    char sym;
    printf("Введіть символ: ");
    if (scanf("%c", &sym) != 1) {
        printf("Помилка: некоректний ввід\n");
        return;
    }
    if (sym == '\n' || extraInput()) {
        printf("Помилка: введіть один символ\n");
        return;
    }
    printf("Символ: '%c'\n", sym);

    // Побітово виводимо 8-бітний двійковий код символу
    unsigned char byte = sym;
    unsigned int code = byte;
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) {
        printf("%u", (code >> i) & 1u);
    }
    printf(")\n");

    // Визначаємо категорію символу через функції <cctype>
    printf("Тип: ");
    if (isupper(byte)) {
        printf("велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(byte));
    } else if (islower(byte)) {
        printf("мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(byte));
    } else if (isdigit(byte)) {
        printf("цифра\n");
    } else if (isspace(byte)) {
        printf("пробільний символ\n");
    } else {
        printf("інший символ\n");
    }
    printf("Наступний символ: '%c'\n", byte + 1);

    // Шукаємо перше входження через strchr і рахуємо загальну кількість у тексті
    const char *found = strchr(text, sym);
    if (found == nullptr) {
        printf("Входжень у тексті: немає\n");
        return;
    }
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == sym) {
            count++;
        }
    }
    int pos = found - text + 1;
    printf("Входжень у тексті: %d, перше на позиції %d\n", count, pos);
}
// Пункт 6: зчитує нове речення по словах через cin, перевіряє коректність і оновлює текст
void choice_6(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string newText;
    string word;
    // Зчитуємо слова через cin >> об'єднюючи їх одним пробілом до слова з крапкою
    while (cin >> word) {
        if (!newText.empty()) {
            newText += " ";
        }
        newText += word;
        if (word[word.length() - 1] == '.') {
            break;
        }
    }
    bool extraIn = extraInput();
    if(extraIn) {
        printf("Помилка: зайві символи після крапки\n");
        return;
    }
    // Валідуємо речення перед перезаписом text
    size_t len = newText.length();
    bool valid = !extraIn && len >= 2 && len <= 255 && newText[len - 1] == '.' && newText[len - 2] != ' ';

    if (valid) {
        for (size_t i = 0; i < len - 1; i++) {
            if (!isLegit(newText[i]) && newText[i] != ' ') {
                valid = false;
                break;
            }
        }
    }
    if (!valid) {
        printf("Помилка: некоректне речення\n");
        return;
    }
    
    strcpy(text, newText.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main() {
    char text[256];

    // Зчитування рядка разом із пробілами
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        printf("Помилка: некорректний текст\n");
        return 0;
    }
    // Забираєм символ переносу рядка '\n' або знаходимо переповнення буфера
    char *found = strchr(text, '\n');
    if (found != nullptr) {
        *found = '\0';
    } else {
        int next = getchar();
        if (next != '\n' && next != EOF) {
            printf("Помилка: некорректний текст\n");
        return 0;
        }
    }
    // Перевіряємо мінімальну довжину та наявність крапки в кінці
    size_t length = strlen(text);
    if (length < 2 || text[length - 1] != '.' || text[length - 2] == ' ') {
        printf("Помилка: некорректний текст\n");
        return 0;
    }
    // Перевірка щоб текст містив лише дозволені символи та хоча б одне слово
    bool validWord = false;
    for (int i = 0; i < length - 1; i++) {
        bool legit = isLegit(text[i]);
        bool isSpace = text[i] == ' ';
        if (!(legit || isSpace)) {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою\n");
            return 0;
        }
        if (legit) {
            validWord = true;
        }
    }
    if (!validWord) {
        printf("Помилка: у тексті немає слів\n");
        return 0;
    }

    int choice = -1;
    int count = 0;
    char **words = splitWords(text, count);

    do {
        printf("\n==============МЕНЮ==============\n");
        printf("1\tПоказати текст і статистику\n");
        printf("2\tТаблиця слів\n");
        printf("3\tЗамінити слово\n");
        printf("4\tПорівняти два слова\n");
        printf("5\tІнформація про символ\n");
        printf("6\tВвести нове речення\n");
        printf("0\tВийти\n");

        printf("Виберіть пункт: ");

        int read = scanf("%d", &choice);

        // Відсіюємо нечислові символи, зайвий текст після числа та неіснуючі пункти
        bool inp = extraInput();
        if (read != 1 || inp) {
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        } else if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                choice_1(text, count);
                break;
            case 2:
                choice_2(words, count);
                break;
            case 3:
                choice_3(text, words, count);
                break;
            case 4:
                choice_4();
                break;
            case 5:
                choice_5(text);
                break;
            case 6:
                choice_6(text, words, count);
                break;
            case 0:
                break;
        }

    } while(choice != 0);

    freeWords(words, count);
    printf("============Завершення роботи============\n");

    return 0;
}