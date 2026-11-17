/*
    Задача: Practice task
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <string>
using namespace std;

char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextAndStatistics(char text[256], int length);
void showWordTable(char **words, int count);
void changeWord (char text[256], char **&words, int &count);
void compareWords();
void symbolInfo(char text[256]);
void newSentence(char text[256], char **&words, int &count);

int main() {
    char text[256];
    bool correct = true;
    bool has_word = false;

    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    if((fgets(text, 256, stdin)) == NULL) {
        printf("Помилка: некоректний текст.\n");
        return 0;
    }
    int length = strlen(text);
    // Якщо fgets зчитав перехід на новий рядок, прибираємо його.
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
        length--;
    }
    // Речення має бути непорожнім і завершуватися крапкою.
    if (length == 0 || text[length - 1] != '.') {
        correct = false;
    }
    // Перевіряємо всі символи перед кінцевою крапкою.
    for (int i = 0; i < length - 1; i++) {
        char c = text[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            has_word = true;
        } else if (c != ' ') {
            correct = false;
        }
    }
    // Відхиляємо текст із забороненими символами або без слів.
    if (!(correct) || !(has_word)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. ");
        return 0;
    }
    int count = 0; // Кількість слів. splitWords запише сюди фактичне значення.
    char **words = splitWords(text, count);  // Динамічний масив вказівників на окремі C-рядки (слова).
    int choice;
    do {
        printf("Пункт\tОперація\n");
        printf("1\tПоказати текст і статистику\n");
        printf("2\tТаблиця слів\n");
        printf("3\tЗамінити слово\n");
        printf("4\tПорівняти два слова\n");
        printf("5\tІнформація про символ\n");
        printf("6\tВвести нове речення\n");
        printf("0\tВийти\n");
        printf("Ваш вибір: ");
        // Якщо введено не ціле число, очищаємо некоректний ввід.
        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n') {}
            printf("Помилка: введіть номер пункту меню.\n");
            printf("Ваш вибір: ");
        }
        // Перевіряємо, чи існує такий номер пункту меню.
        while (choice < 0 || choice > 6) {
            while (getchar() != '\n') {}
            printf("Помилка: пункту %d немає в меню.\n", choice);
            printf("Ваш вибір: ");

            while(scanf("%d", &choice) != 1) {
                while (getchar() != '\n') {}
                printf("Помилка: введіть номер пункту меню.\n");
                printf("Ваш вибір: ");
            }
        }
        switch(choice) {
            case 1: showTextAndStatistics(text, strlen(text)); break;
            case 2: showWordTable(words, count); break;
            case 3: changeWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: symbolInfo(text); break;
            case 6: newSentence(text, words, count); break;
            case 0: freeWords(words, count); break;
        }
    } while (choice != 0);
    return 0;
} 
// Розбиваємо речення на слова й повертаємо динамічний масив рядків.
char **splitWords(const char *text, int &count) {
    char copy[256]; // Працюємо з копією, бо strtok змінює переданий масив.
    strcpy(copy, text);
    count = 0;
    // Знаходимо перше слово; пробіл і крапка є роздільниками.
    char *word = strtok(copy, ". ");
    // Для підрахунку кількості слів
    while (word != NULL) {  // Продовжуємо, доки strtok повертає чергове слово.
        count++;
        word = strtok(NULL, ". ");
    }

    // Виділяємо масив із count вказівників char*.
    char **words = new char*[count];
    // Відновлюємо копію, оскільки перший прохід strtok її змінив.
    strcpy(copy, text);
    int i = 0;
    word = strtok(copy, ". ");  // Починаємо другий прохід для копіювання слів.
    // Продовжуємо, доки strtok повертає чергове слово.
    while (word != NULL) {
        words[i] = new char[strlen(word) + 1];  // Для слова виділяємо рівно стільки байтів, скільки потрібно, включно з \0.
        strcpy(words[i], word); // Копіюємо символи слова у власну виділену пам’ять.
        i++;
        word = strtok(NULL, ". ");
    }
    // Повертаємо адресу динамічного масиву слів.
    return words;
}
// Обнуляємо вказівник і лічильник
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];  // Спочатку видаляємо кожен окремий рядок.
    }
    // Потім видаляємо сам масив вказівників.
    delete[] words;
    words = NULL;  // Обнуляємо вказівник
    count = 0;  // Після звільнення масив більше не містить слів.
}
// Рахуємо літери, цифри й пробіли
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    const char *p = text;  // p вказує на поточний символ; const забороняє змінювати текст.
    // Ідемо вказівником до кінця рядка або до крапки.
    for (; *p != '\0' && *p != '.'; p++) {
        char c = *p;
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letters++;
        }
    }
    printf("Літер:       %d (%7.1f%%)\n", letters, (letters * 100.0) / strlen(text));

    p = text;
    for (; *p != '\0' && *p != '.'; p++) {
        char c = *p;
        if (c >= '0' && c <= '9') {
            digits++;
        }
    }
    printf("Цифр:        %d (%7.1f%%)\n", digits, (digits * 100.0) / strlen(text));
    
    p = text;
    for (; *p != '\0' && *p != '.'; p++) {
        char c = *p;
        if (c == ' ') {
            spaces++;
        }
    }
    printf("Пробілів:    %d (%7.1f%%)\n", spaces, (spaces * 100.0) / strlen(text));
}
// Показуємо текст, кількість символів, слів і статистику символів.
void showTextAndStatistics(char text[256], int length) {
    printf("\n");
    printf("Текст:    \"%s\"\n", text);
    printf("Символів:    %zu\n", strlen(text));
    int words = 0;
    // Перевіряємо всі символи перед кінцевою крапкою.
    for (int i = 0; i < length - 1; i++) {
        if (text[i] != ' ' && (i == 0 || text [i - 1] == ' ')) {
            words++;
        }
    }
    printf("Слів:        %d\n", words);
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    // Заповнюємо три лічильники та друкуємо відсотки.
    countChars(text, letters, digits, spaces);
    printf("\n");
}
// Виводимо таблицю та характеристики слів.
void showWordTable(char **words, int count) {
    printf("\n");
    // Сума довжин усіх слів потрібна для середнього.
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += strlen(words[i]);
    }

    printf("+----+--------------------+-------+\n");
    printf("|  N | Слово              | Довж. |\n");
    printf("+----+--------------------+-------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-18s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+--------------------+-------+\n");

    // Пошук найдовшого і найкоротшого слова
    int longest = 0;
    int shortest = 0;
    for (int i = 0; i < count; i++){
        if (strlen(words[i]) > strlen(words[longest])) {
            longest = i;
        }
        if (strlen(words[i]) < strlen(words[shortest])) {
            shortest = i;
        }
    }

    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // Статична копія для сортування без зміни основного масиву words.
    char sorted[256][256];
    for (int i = 0; i < count; i++) {
        strcpy(sorted[i], words[i]);
    }
    // Сортування вибором: для кожної позиції шукаємо найменше слово.
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < count; j++) {
            // strcmp < 0 означає, що лівий рядок стоїть раніше
            if (strcmp(sorted[j], sorted[minIndex]) < 0) {
                minIndex = j;
            }
        }

        char temporary[256];
        strcpy(temporary, sorted[i]);
        strcpy(sorted[i], sorted[minIndex]);
        strcpy(sorted[minIndex], temporary);
    }

    printf("За абеткою: ");
    for (int i = 0; i < count; i++) {
        printf("%s ", sorted[i]);
    }
    printf("\n");

    int maxCount = 0;  // Найбільша знайдена частота повторень.
    int maxIndex = 0;  // Індекс слова з найбільшою частотою
    for (int i = 0; i < count; i++) {
        // Рахуємо, скільки разів поточне слово зустрічається у списку.
        int frequency = 0;
        for (int j = 0; j < count; j++) {
            // Нуль означає повну рівність двох C-рядків.
            if (strcmp(sorted[i], sorted[j]) == 0) {
                frequency++;
            }
        }
        if (frequency > maxCount) {
                maxCount = frequency;
                maxIndex = i;
            }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[maxIndex], maxCount);
    printf("\n");
}
// Замінюємо всі окремі входження слова й оновлюємо динамічний масив.
void changeWord (char text[256], char **&words, int &count) {
    char oldInput[256], newInput[256]; // Буфери для слова, яке шукаємо, і нового слова.

    printf("Замінити слово: ");
    scanf("%31s", oldInput);

    printf("На слово: ");
    scanf("%31s", newInput);

    // Перетворюємо C-рядок на string для пошуку та заміни.
    string oldWord = oldInput;
    string newWord = newInput;

    // Перевіряємо, що нове слово містить лише дозволені символи.
    bool correct = true;
    for(int i = 0; i < newWord.length(); i++) {
        char c = newWord[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) {
            correct = false;
            break;
        }
    }
    if (!(correct)) {
        printf("Помилка.");
        return;
    }
    
    string original = text; // Зберігаємо початкове речення для показу було
    string result = original;  // Працюємо з копією
    int replaced = 0;
    size_t pos = 0;
    // find повертає позицію збігу; npos означає, що збігів більше немає.
    while ((pos = result.find(oldWord, pos)) != string::npos) {
        // Ліворуч від збігу має бути початок рядка або не літера/цифра.
        bool left = (pos == 0 || !((result[pos - 1] >= 'A' && result[pos - 1] <= 'Z') || (result[pos - 1] >= 'a' && result[pos - 1] <= 'z') || (result[pos - 1] >= '0' && result[pos - 1] <= '9')));
        // Позиція одразу після знайденого слова.
        size_t end = pos + oldWord.length();
        // Праворуч має бути кінець рядка або не літера/цифра.
        bool right = (end == result.length() || !((result[end] >= 'A' && result[end] <= 'Z') || (result[end] >= 'a' && result[end] <= 'z') || (result[end] >= '0' && result[end] <= '9')));
        // Замінюємо тільки ціле слово, а не частину довшого слова.
        if (left && right) {
            // Видаляємо знайдене слово і вставляємо нове.
            result.replace(pos, oldWord.length(), newWord);
            replaced++;
            pos += newWord.length(); // Продовжуємо після вставленого слова, не обробляючи його повторно.
        } else {
            pos += oldWord.length();  // Якщо збіг був частиною слова, пропускаємо його
        }
    }
    if (result.length() > 255) {
        printf("Помилка: текст перевищує 255 символів.\n");
        return;
    }
    strcpy(text, result.c_str());  // Копіюємо готовий string назад у C-рядок text.
    freeWords(words, count);  // Старі слова вже не відповідають зміненому реченню: звільняємо їх
    words = splitWords(text, count);  // Створюємо новий масив слів і оновлюємо count

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", original.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", result.length());
}
// Порівнюємо два введені слова різними способами.
void compareWords() {
    char first[256], second[256];
    printf("Перше слово: ");
    scanf("%31s", first);

    printf("Друге слово: ");
    scanf("%31s", second);

    // strcmp повертає від’ємне, нуль або додатне число.
    int comparison = strcmp(first, second);
    if (comparison < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (comparison > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    // Перетворюємо слова на string.
    string word1 = first;
    string word2 = second;
    if (word1 == word2) {
        printf("Рівні (==): так\n");
    } else {
        printf("Рівні (==): ні\n");
    }

    // Робимо копії для порівняння без урахування регістру.
    string lower1 = word1;
    string lower2 = word2;

    for (int i = 0; i < lower1.length(); i++) {
        if (lower1[i] >= 'A' && lower1[i] <= 'Z') {
            lower1[i] += 32;
        }
    }

    for (int i = 0; i < lower2.length(); i++) {
        if (lower2[i] >= 'A' && lower2[i] <= 'Z') {
            lower2[i] += 32;
        }
    }

    if (lower1 == lower2) {
        printf("Рівні без урахування регістру: так\n");
    } else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %zu і %zu\n", word1.length(), word2.length());
    string combined = word1 + " & " + word2;
    printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), combined.length());
}
// Виводимо код і тип символу, шукаємо його в поточному тексті.
void symbolInfo(char text[256]) {
    char c;

    printf("Введіть символ: ");
    scanf(" %c", &c); // Пробіл у форматі пропускає попередні пробільні символи.
    unsigned char code = (unsigned char)c; // Отримуємо невід’ємний байтовий код символу.
    printf("Символ: '%c'\n", c);

    printf("Код: %d (hex 0x%02X, oct 0%o, bin ",
           (int)code, (unsigned int)code, (unsigned int)code);

    // Друкуємо 8 бітів від старшого до молодшого.
    for (int i = 7; i >= 0; i--) {
        printf("%d", (code >> i) & 1);  // Зсуваємо потрібний біт праворуч і залишаємо лише його
    }
    printf(")\n");

    if (c >= 'A' && c <= 'Z') {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", c + 32);
    } else if (c >= 'a' && c <= 'z') {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", c - 32);
    } else if (c >= '0' && c <= '9') {
        printf("Тип: цифра\n");
    } else if (isspace(code)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    if (code < 255) {
        printf("Наступний символ: '%c'\n", code + 1);
    } else {
        printf("Наступного символу немає\n");
    }

    // Пошук символу в тексті
    int count = 0;  // Кількість слів; splitWords запише сюди фактичне значення.
    int first = -1;  // -1 означає, що символ ще не знайдено.

    // Знаходимо перше входження символу
    char *p = strchr(text, c);

    if (p != NULL) {
        first = p - text + 1;
    }

    // Рахуємо всі входження символу
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            count++;
        }
    }

    if (count > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n",
               count, first);
    } else {
        printf("Символ у тексті відсутній\n");
    }
}
// Читаємо нове речення по словах до крапки й оновлюємо масив.
void newSentence(char text[256], char **&words, int &count) {
    string word;  // Чергове слово, яке зчитує cin
    string result = "";  // Тут поступово збираємо нове речення
    int wordsRead = 0;  // Кількість прочитаних слів

    printf("Введіть речення (крапка після останнього слова):\n");

    while (cin >> word) { 
        // Перед кожним словом, крім першого, додаємо один пробіл.
        if (wordsRead > 0) {
            result += " ";
        }

        result += word;
        wordsRead++;

        // Зупиняємо введення, коли останній символ слова крапка
        if (word[word.length() - 1] == '.') {
            break;
        }
    }

    // Перевірка довжини
    if (result.length() > 255) {
        printf("Помилка: текст перевищує 255 символів.\n");
        return;
    }

    // Перевірка завершення речення
    if (wordsRead == 0 || result[result.length() - 1] != '.') {
        printf("Помилка: речення має закінчуватися крапкою.\n");
        return;
    }

    // Перевірка нового речення
    for (int i = 0; i < result.length() - 1; i++) {
        char c = result[i];

        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ')) {
            printf("Помилка: недопустимі символи.\n");
            return;
        }
    }
    // Заміна поточного тексту
    strcpy(text, result.c_str());  // Копіюємо готовий string назад у C-рядок text
    freeWords(words, count);  // Старі слова вже не відповідають зміненому реченню: звільняємо їх.
    words = splitWords(text, count);  // Cтворює новий динамічний масив слів із поточного речення

    cout << "Прочитано слів: " << wordsRead << endl;
    cout << "Новий текст: \"" << text << "\"" << endl;
    cout << "Довжина: " << result.length() << endl;
}