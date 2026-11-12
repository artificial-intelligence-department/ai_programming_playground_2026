
/*
    Редактор текстового повідомлення
    Рубаха Олексій
    ШІ-13
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

// Перевіряє, чи складається текст лише з латинських літер,
// цифр і пробілів та чи містить хоча б один символ слова.
bool correctText(const char *text, int len) {
    bool has_word_char = false;

    // Перебираємо всі символи, крім останнього — крапки.
    for (int i = 0; i < len - 1; i++) {
        char c = text[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            has_word_char = true;
        }else if (c >= '0' && c <= '9') {
            has_word_char = true;
        }else if (c == ' ') {
            continue;
        }else {
            printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
            return false;
        }
    }

    // Не дозволяємо вводити текст, який містить лише пробіли.
    if (!has_word_char) {
        printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
        return false;
    }

    return true;
}

// Розбиває текст на окремі слова.
// Повертає масив вказівників на рядки, а count передає кількість слів.
char **splitWords(const char *text, int &count) {
    count = 0;

    // Виділяємо пам'ять для масиву, який зберігатиме слова.
    char **words = new char*[128];

    // Створюємо копію тексту, оскільки strtok змінює рядок.
    char *buf = strdup(text);

    // Прибираємо крапку з кінця копії.
    int len = strlen(buf);
    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }

    // Розділяємо текст на слова за пробілами.
    char *t = strtok(buf, " ");

    while (t != NULL) {
        // Виділяємо пам'ять для поточного слова.
        words[count] = new char[strlen(t) + 1];

        // Копіюємо слово в окремий елемент масиву.
        strcpy(words[count], t);
        count++;

        // Отримуємо наступне слово.
        t = strtok(NULL, " ");
    }

    // Звільняємо пам'ять тимчасової копії тексту.
    free(buf);

    return words;
}

// Звільняє пам'ять, виділену для масиву слів.
void freeWords(char **&words, int &count) {
    if (!words) return;

    // Видаляємо кожен окремий рядок зі словом.
    for (int i = 0; i < count; i++) {
        delete [] words[i];
    }

    // Видаляємо сам масив вказівників.
    delete [] words;

    words = nullptr;
    count = 0;
}

// Підраховує кількість літер, цифр і пробілів у тексті.
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    // Перебираємо текст за допомогою вказівника.
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) letters++;
        if (isdigit((unsigned char)*p)) digits++;
        if (isspace((unsigned char)*p)) spaces++;
    }
}

// Виводить текст і статистику щодо його символів.
void showStats(const char *text, int wordCount) {
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    // Отримуємо кількість кожного типу символів.
    countChars(text, letters, digits, spaces);

    printf("%-15s \"%s\"\n", "Текст:", text);

    // Додаємо 1, оскільки крапка в кінці теж є символом.
    float symb = letters + digits + spaces + 1;

    printf("Символів:      %5d\n", (int)symb);
    printf("Слів:          %5d\n", wordCount);
    printf("Літер:         %5d  (%5.1f%%)\n", letters, (double)letters / symb * 100);
    printf("Цифр:          %5d  (%5.1f%%)\n", digits, (double)digits / symb * 100);
    printf("Пробілів:      %5d  (%5.1f%%)\n", spaces, (double)spaces / symb * 100);
}

// Сортує слова за абеткою методом бульбашкового сортування.
void sortWords(char **arr, int count) {
    if (count == 0) return;

    // Створюємо додатковий масив вказівників,
    // щоб не змінювати порядок слів у початковому масиві.
    char **sorted_words = new char*[count];

    for (int i = 0; i < count; i++) {
        sorted_words[i] = arr[i];
    }

    // Бульбашкове сортування.
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            // Якщо поточне слово більше за наступне, міняємо їх місцями.
            if (strcmp(sorted_words[j], sorted_words[j + 1]) > 0) {
                char *temp = sorted_words[j];
                sorted_words[j] = sorted_words[j + 1];
                sorted_words[j + 1] = temp;
            }
        }
    }

    // Виводимо відсортовані слова.
    for (int i = 0; i < count; i++) {
        printf("%s ", sorted_words[i]);
    }
    printf("\n");

    // Звільняємо додатковий масив вказівників.
    delete[] sorted_words;
}

// Знаходить найдовше та найкоротше слово,
// а також обчислює середню довжину слів.
void sortWordsBySize(char **arr, int count) {
    if (count == 0) return;

    // Спочатку вважаємо перше слово найдовшим і найкоротшим.
    char *max = arr[0];
    char *min = arr[0];

    float averageValue = 0;

    // Перебираємо всі слова та порівнюємо їхню довжину.
    for (int j = 0; j < count; j++) {
        averageValue += strlen(arr[j]);

        if (strlen(arr[j]) > strlen(max)) {
            max = arr[j];
        }

        if (strlen(arr[j]) < strlen(min)) {
            min = arr[j];
        }
    }

    // Виводимо результати пошуку.
    printf("Найдовше слово: %s  (%d)\n", max, (int)strlen(max));
    printf("Найкоротше слово: %s  (%d)\n", min, (int)strlen(min));

    // Обчислюємо середню довжину слова.
    printf("Середня довжина: %.2f\n", averageValue / count);
}

// Виводить таблицю слів, їхню довжину,
// статистику та найчастіше слово.
void showWordTable(char **words, int count) {
    // Заголовок таблиці.
    printf("| %-3s | %-15s      | %-6s  |\n", "N", "Слово", "Довж.");

    // Виводимо кожне слово з номером і довжиною.
    for (int i = 0; i < count; i++) {
        printf("| %-3d | %-15s | %6d |\n", i + 1, words[i], (int)strlen(words[i]));
    }

    // Виводимо інформацію про довжину слів.
    sortWordsBySize(words, count);

    // Виводимо слова в алфавітному порядку.
    printf("За абеткою: ");
    sortWords(words, count);

    // Масив count_w зберігає кількість входжень кожного слова.
    int count_w[count] = {0};

    // Для кожного слова порівнюємо його з усіма іншими словами.
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                count_w[i]++;
            }
        }
    }

    int max_count = 0;
    string most_frequent = "";

    // Знаходимо слово з найбільшою кількістю входжень.
    for (int i = 0; i < count; i++) {
        if (count_w[i] > max_count) {
            max_count = count_w[i];
            most_frequent = words[i];
        }
    }

    // Виводимо найчастіше слово та кількість його входжень.
    printf("Найчастіше слово: %s ( %d )\n", most_frequent.c_str(), max_count);
}

// Перевіряє, чи складається рядок лише з латинських літер.
bool isLatinWord(const string &word) {
    if (word.empty()) return false;

    for (char c : word) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return false;
        }
    }

    return true;
}

// Перевіряє, чи складається рядок лише з цифр.
bool isNumber(const string &word) {
    if (word.empty()) return false;

    for (char c : word) {
        if (!(c >= '0' && c <= '9')) {
            return false;
        }
    }

    return true;
}

// Замінює задане слово в тексті на інше слово.
// Після заміни оновлює початковий текст.
void replaceWord(char *text, char **&words, int &count) {
    string from, to;

    // Отримуємо слово для заміни та нове слово.
    printf("Замінити слово: ");
    cin >> from;

    printf("На слово: ");
    cin >> to;

    // Перевіряємо, чи відповідає нове слово типу початкового.
    if (isLatinWord(from) && !isLatinWord(to)) {
        printf("Не можна замінити слово на цифру чи кирилицю.\n");
        return;
    }else if (isNumber(from) && !isNumber(to)) {
        printf("Не можна замінити цифру на слово чи кирилицю.\n");
        return;
    }else if (!isLatinWord(from) && !isNumber(from)) {
        printf("Помилка: слово має складатися лише з латинських літер або цифр.\n");
        return;
    }

    int count_ch = 0;

    // Перебираємо всі слова та шукаємо збіги.
    for (int i = 0; i < count; i++) {
        if (words[i] == from) {
            count_ch++;

            // Видаляємо старий рядок і виділяємо пам'ять для нового.
            delete[] words[i];
            words[i] = new char[to.length() + 1];

            // Копіюємо нове слово в масив.
            strcpy(words[i], to.c_str());
        }
    }

    printf("Виконано замін: %d\n", count_ch);
    printf("Було: \"%s\"\n", text);

    // Очищаємо початковий текст перед повторним формуванням.
    text[0] = '\0';

    // Об'єднуємо всі слова в один рядок через пробіли.
    for (int i = 0; i < count; i++) {
        strcat(text, words[i]);

        // Після останнього слова додаємо крапку.
        if (i == count - 1) {
            strcat(text, ".");
        }else {
            strcat(text, " ");
        }
    }

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

// Порівнює два слова, перевіряє їхню рівність,
// довжину та виконує конкатенацію.
void compareWords() {
    // Виділяємо пам'ять для двох слів.
    char *w1 = new char[50];
    char *w2 = new char[50];

    // Зчитуємо перше слово.
    printf("Перше слово: ");
    fgets(w1, 50, stdin);
    w1[strcspn(w1, "\n")] = '\0';

    // Зчитуємо друге слово.
    printf("Друге слово: ");
    fgets(w2, 50, stdin);
    w2[strcspn(w2, "\n")] = '\0';

    // strcmp повертає від'ємне число, нуль або додатне число.
    if (strcmp(w1, w2) < 0) {
        printf("strcmp: -1 -> перше слово менше \n");
    }else if (strcmp(w1, w2) > 0) {
        printf("strcmp: 1 -> перше слово більше \n");
    }else {
        printf("strcmp: 0 -> слова однакові \n");
    }

    // Перевіряємо рівність слів з урахуванням регістру.
    printf("Рівні (==):  ");
    if (strcmp(w1, w2) == 0) {
        printf("так\n");
    }else {
        printf("ні\n");
    }

    // Перевіряємо рівність слів без урахування регістру.
    printf("Рівні без урахування регістру:  ");

    if (strlen(w1) == strlen(w2)) {
        int a = 0;

        // Переводимо символи в один регістр і порівнюємо їх.
        for (int i = 0; w1[i] != '\0'; i++) {
            if (tolower((unsigned char)w1[i]) != tolower((unsigned char)w2[i])) {
                a++;
            }
        }

        if (a == 0) {
            printf("так\n");
        }else {
            printf("ні\n");
        }
    }else {
        printf("ні\n");
    }

    // Виводимо довжини обох слів.
    printf("Довжини:  %d  i  %d \n", (int)strlen(w1), (int)strlen(w2));

    // Розраховуємо необхідний розмір пам'яті для об'єднаного рядка.
    // Додаємо 3 символи для " & " та 1 для завершального '\0'.
    int newLen = strlen(w1) + 3 + strlen(w2) + 1;
    char *concat = new char[newLen];

    // Об'єднуємо два слова через рядок " & ".
    strcpy(concat, w1);
    strcat(concat, " & ");
    strcat(concat, w2);

    printf("Конкатенація: \"%s\"(%d)\n", concat, (int)strlen(concat));

    // Звільняємо пам'ять усіх трьох динамічних рядків.
    delete[] w1;
    w1 = nullptr;

    delete[] w2;
    w2 = nullptr;

    delete[] concat;
}

// Виводить інформацію про введений символ:
// його код, тип, символ іншого регістру та кількість входжень у текст.
void charInfo(const char *text) {
    unsigned char one_symbol;

    // Зчитуємо один символ.
    printf("Введіть символ: ");
    scanf(" %c", &one_symbol);

    printf("Символ: '%c' \n", one_symbol);

    // Виводимо код символу в різних системах числення.
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", one_symbol, one_symbol, one_symbol);

    // Формуємо двійкове представлення символу.
    for (int i = 7; i >= 0; i--) {
        printf("%d", (one_symbol >> i) & 1);
    }
    printf(")\n");

    // Лічильники для визначення типу символу.
    int upper = 0;
    int lower = 0;
    int space = 0;
    int number = 0;

    char type = one_symbol;

    printf("Тип: ");

    // Визначаємо тип введеного символу.
    if (islower(one_symbol)) {
        printf("мала літера \n");
        lower++;
    }else if (isupper(one_symbol)) {
        printf("велика літера \n");
        upper++;
    }else if (isdigit(one_symbol)) {
        printf("цифра \n");
        number++;
    }else if (isspace(one_symbol)) {
        printf("пробіл \n");
        space++;
    }else {
        printf("інший символ\n");
    }

    // Для літер показуємо відповідник в іншому регістрі
    // та наступний символ за кодом.
    if (space == 0 && number == 0) {
        printf("Інший регістр: ");

        if (upper != 0) {
            printf("'%c'\n", type + 32);
        }else if (lower != 0) {
            printf("'%c'\n", type - 32);
        }

        char next = one_symbol;
        printf("Наступний символ:  '%c'\n", next + 1);
    }

    // Підраховуємо кількість входжень символу в текст.
    int count = 0;

    for (const char *p = text; *p != '\0'; p++) {
        if (*p == one_symbol) {
            count++;
        }
    }

    if (count == 0) {
        printf(" Входжень у тексті: у тексті не трапляється\n");
    }else {
        // strchr знаходить адресу першого входження символу.
        const char *posPtr = strchr(text, one_symbol);

        // Визначаємо позицію символу, починаючи нумерацію з одиниці.
        int pos = posPtr - text + 1;

        printf("Входжень у тексті: %d, перше на позиції %d \n", count, pos);
    }
}

// Дозволяє користувачу ввести нове речення.
// Старий текст і масив слів замінюються новими даними.
void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова): \n");

    int new_count = 0;
    string sentence = "";

    char word[32];

    // Зчитуємо слова по одному, доки слово не закінчиться крапкою.
    while (cin >> word) {
        new_count++;

        int len = strlen(word);

        // Додаємо чергове слово до нового речення.
        sentence += word;

        // Якщо останній символ слова — крапка, введення завершено.
        if (word[len - 1] == '.') break;

        // Між словами додаємо пробіл.
        if (new_count > 0) {
            sentence += " ";
        }
    }

    int len = sentence.length();

    // Перевіряємо довжину та наявність крапки в кінці.
    if (len == 0 || sentence[len - 1] != '.' || len > 255) {
        printf("Помилка: некоректне речення або перевищено 255 символів. \n");
        return;
    }

    // Перевіряємо допустимість символів нового речення.
    if (!correctText(sentence.c_str(), len)) {
        return;
    }

    // Звільняємо пам'ять старого масиву слів.
    freeWords(words, count);

    count = new_count;

    // Копіюємо нове речення в основний символьний масив.
    strcpy(text, sentence.c_str());

    // Повторно розбиваємо текст на слова.
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);

    printf("Довжина: \n");
    printf("...\n");

    // Оновлюємо статистику для нового речення.
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces);
    showStats(text, count);

    printf("Нова довжина: %d\n", (int)strlen(text));
}

// Головна функція програми.
int main() {
    // Основний текст зберігається в масиві на 256 символів.
    char text[256];

    // Масив вказівників на слова спочатку порожній.
    char **words = NULL;

    int wordCount = 0;

    // Отримуємо початковий текст від користувача.
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");

    if (!fgets(text, sizeof(text), stdin)) return 0;

    int len = strlen(text);

    // Видаляємо символ переходу на новий рядок, якщо він є.
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    // Перевіряємо, чи завершується текст крапкою.
    if (len == 0 || text[len - 1] != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
        return 1;
    }

    // Перевіряємо допустимість усіх символів тексту.
    if (!correctText(text, len)) {
        return 1;
    }

    // Розбиваємо початковий текст на окремі слова.
    words = splitWords(text, wordCount);

    int choice = 1;

    // Цикл меню працює, доки користувач не вибере пункт 0.
    do {
        printf("\nМеню: \n");
        printf(" 1 - Показати текст та статистику \n");
        printf(" 2 - Таблиця слів \n");
        printf(" 3 - Замінити слово \n");
        printf(" 4 - Порівняти два слова \n");
        printf(" 5 - Інформація про символ \n");
        printf(" 6 - Ввести нове речення \n");
        printf(" 0 - Вийти \n");
        printf(" > ");

        // Зчитуємо номер пункту меню.
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Некоректний ввід. \n");
            continue;
        }

        // Очищаємо залишок рядка після введення числа.
        while (getchar() != '\n');

        printf("\n");

        // Виконуємо дію відповідно до вибраного пункту меню.
        switch (choice) {
            case 1:
                // Виведення тексту та статистики.
                showStats(text, wordCount);
                printf("\n");
                break;

            case 2:
                // Виведення таблиці слів та інформації про них.
                showWordTable(words, wordCount);
                printf("\n");
                break;

            case 3:
                // Заміна заданого слова в тексті.
                replaceWord(text, words, wordCount);
                printf("\n");
                break;

            case 4:
                // Порівняння двох введених слів.
                compareWords();
                printf("\n");
                break;

            case 5:
                // Отримання інформації про введений символ.
                charInfo(text);
                printf("\n");
                break;

            case 6:
                // Введення нового речення замість поточного.
                newSentence(text, words, wordCount);
                printf("\n");
                break;

            case 0:
                // Завершення роботи програми.
                choice = 0;
                printf("\n");
                break;

            default:
                // Обробка неіснуючого пункту меню.
                printf("Некоректний пункт меню.\n");
                break;
        }
    } while (choice != 0);

    // Перед завершенням програми звільняємо пам'ять масиву слів.
    freeWords(words, wordCount);

    return 0;
}