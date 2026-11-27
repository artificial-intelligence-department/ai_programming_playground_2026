
/*
Епік 5. Практичне завдання: Редактор текстового повідомлення
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

// Оголошення прототипів функцій
bool isValidText(const char* text);
bool isValidWord(const char* word);
char** splitWords(const char* text, int& count);
void freeWords(char**& words, int& count);
void menu();

void showTextStatistics(const char* text, int wordCount);
void countChars(const char* text, int& letters, int& digits, int& spaces);
void showWordsTable(char** words, int count);
void showSortedWords(char** sorted, int count);
void showMostFrequentWord(char** sorted, int count);

void replaceWord(char* text, char**& words, int& count,
                 const char* oldWord, const char* newWord);
void compareWords(const char* word1, const char* word2);
void showCharacterInfo(const char* text);
void enterNewSentence(char* text, char**& words, int& count);
char** sortWords(char** words, int& count);

int main() {
    char text[256];

    // Введення початкового тексту через fgets
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");

    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Помилка введення тексту.\n");
        return 1;
    }

    size_t length = strlen(text);

    // Видаляємо кінцевий символ '\n', якщо він є, або фіксуємо переповнення буфера
    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    } else if (!feof(stdin)) {
        // Очищуємо потік вводу, якщо введений рядок перевищив 255 символів
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        printf("Помилка: текст перевищує 255 символів.\n");
        return 1;
    }

    // Перевірка відповідності тексту вимогам (крапка в кінці, лише літери, цифри й пробіли)
    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    // Розбиваємо текст на слова та зберігаємо їх у динамічному масиві
    int count = 0;
    char** words = splitWords(text, count);

    if (words == NULL || count == 0) {
        printf("Помилка виділення пам'яті або порожній текст.\n");
        freeWords(words, count);
        return 1;
    }

    int action = -1;

    // Головний цикл інтерактивного меню
    do {
        menu();
        printf("Ваш вибір: ");

        // Зчитування пункту меню з перевіркою на нечисловий ввід
        if (scanf("%d", &action) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            printf("Помилка: введіть номер пункту меню.\n\n");
            action = -1;
            continue;
        }

        // Перевірка відсутності сторонніх символів після введеного числа
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (!isspace((unsigned char)ch)) {
                action = -1;
            }
        }

        if (action == -1) {
            printf("Помилка: введіть лише ціле число.\n\n");
            continue;
        }

        // Виклик функції відповідно до вибраного пункту
        switch (action) {
        case 1:
            // Пункт 1: Текст та його статистика
            showTextStatistics(text, count);
            break;

        case 2: {
            // Пункт 2: Таблиця слів, сортування та найчастіше слово
            char** sorted = sortWords(words, count);

            showWordsTable(words, count);
            showSortedWords(sorted, count);
            showMostFrequentWord(sorted, count);

            // Звільняємо тимчасовий відсортований масив слів
            int sortedCount = count;
            freeWords(sorted, sortedCount);
            break;
        }

        case 3: {
            // Пункт 3: Заміна цілого слова в тексті
            char oldWord[32];
            char newWord[32];

            printf("Замінити слово: ");
            if (scanf("%31s", oldWord) != 1) {
                printf("Помилка введення.\n");
                break;
            }

            printf("На слово: ");
            if (scanf("%31s", newWord) != 1) {
                printf("Помилка введення.\n");
                break;
            }

            // Очищення потоку після зчитування слів
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            // Перевірка допустимості символів у шуканому слові
            if (!isValidWord(oldWord)) {
                printf("Помилка: слово для заміни має містити лише латинські літери та цифри.\n");
                break;
            }

            replaceWord(text, words, count, oldWord, newWord);
            break;
        }

        case 4: {
            // Пункт 4: Порівняння двох слів
            char word1[32];
            char word2[32];

            printf("Перше слово: ");
            if (scanf("%31s", word1) != 1) {
                printf("Помилка введення.\n");
                break;
            }

            printf("Друге слово: ");
            if (scanf("%31s", word2) != 1) {
                printf("Помилка введення.\n");
                break;
            }

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            // Перевірка слів на допустимість символів
            if (!isValidWord(word1) || !isValidWord(word2)) {
                printf("Помилка: слова мають містити лише латинські літери та цифри.\n");
                break;
            }

            compareWords(word1, word2);
            break;
        }

        case 5:
            // Пункт 5: Детальна інформація про символ
            showCharacterInfo(text);
            break;

        case 6:
            // Пункт 6: Введення нового речення по словах
            enterNewSentence(text, words, count);
            break;

        case 0:
            printf("Вихід з програми.\n");
            break;

        default:
            printf("Помилка: пункту %d немає в меню.\n", action);
            break;
        }

        printf("\n");

    } while (action != 0);

    // Звільнення всієї виділеної динамічної пам'яті перед виходом
    freeWords(words, count);
    return 0;
}

// Перевірка тексту: завершується крапкою, містить лише латиницю, цифри та пробіли
bool isValidText(const char* text) {
    int length = (int)strlen(text);

    // Текст повинен містити хоча б 2 символи, останній символ — крапка, перед нею немає пробілу
    if (length < 2 || text[length - 1] != '.' || text[length - 2] == ' ') {
        return false;
    }

    bool hasWord = false;

    // Перевіряємо всі символи до завершальної крапки
    for (int i = 0; i < length - 1; ++i) {
        char ch = text[i];

        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9')) {
            hasWord = true; // Знайдено хоча б один символ слова
        } else if (ch != ' ') {
            return false;   // Будь-який інший символ є недопустимим
        }
    }

    return hasWord;
}

// Перевірка одного слова: непорожнє, містить лише латинські літери та цифри
bool isValidWord(const char* word) {
    if (word[0] == '\0') {
        return false;
    }

    for (int i = 0; word[i] != '\0'; ++i) {
        if (!((word[i] >= 'a' && word[i] <= 'z') ||
              (word[i] >= 'A' && word[i] <= 'Z') ||
              (word[i] >= '0' && word[i] <= '9'))) {
            return false;
        }
    }

    return true;
}

// Розділення тексту на слова та збереження у динамічний масив char**
char** splitWords(const char* text, int& count) {
    count = 0;

    char temporary[256];
    strcpy(temporary, text);

    // Перший прохід: підраховуємо загальну кількість слів
    char* token = strtok(temporary, " ");
    while (token != NULL) {
        if (strcmp(token, ".") != 0) {
            ++count;
        }
        token = strtok(NULL, " ");
    }

    if (count == 0) {
        return NULL;
    }

    // Виділяємо масив покажчиків під знайдену кількість слів
    char** words = new char*[count];

    // Другий прохід: копіюємо кожне слово у виділену для нього пам'ять
    strcpy(temporary, text);
    token = strtok(temporary, " ");

    int index = 0;

    while (token != NULL) {
        int tokenLength = (int)strlen(token);

        // Якщо слово завершується крапкою — відкидаємо її
        if (token[tokenLength - 1] == '.') {
            token[tokenLength - 1] = '\0';
        }

        if (token[0] != '\0') {
            words[index] = new char[strlen(token) + 1];
            strcpy(words[index], token);
            ++index;
        }

        token = strtok(NULL, " ");
    }

    count = index;
    return words;
}

// Виведення пунктів головного меню програми
void menu() {
    printf("========== МЕНЮ ==========\n");
    printf("%-3d %s\n", 1, "Показати текст і статистику");
    printf("%-3d %s\n", 2, "Таблиця слів");
    printf("%-3d %s\n", 3, "Замінити слово");
    printf("%-3d %s\n", 4, "Порівняти два слова");
    printf("%-3d %s\n", 5, "Інформація про символ");
    printf("%-3d %s\n", 6, "Ввести нове речення");
    printf("%-3d %s\n", 0, "Вийти");
    printf("==========================\n");
}

// Підрахунок літер, цифр і пробілів шляхом обходу рядка вказівником
void countChars(const char* text, int& letters, int& digits, int& spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    const char* pointer = text;

    while (*pointer != '\0') {
        if (isalpha((unsigned char)*pointer)) {
            ++letters;
        } else if (isdigit((unsigned char)*pointer)) {
            ++digits;
        } else if (*pointer == ' ') {
            ++spaces;
        }

        ++pointer; // Перехід до наступного символу за адресою
    }
}

// Виведення загальної статистики тексту та відсоткових часток символів
void showTextStatistics(const char* text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    int chars = (int)strlen(text);

    // Обчислення відсоткових часток від загальної кількості символів
    double lettersPercent = letters * 100.0 / chars;
    double digitsPercent = digits * 100.0 / chars;
    double spacesPercent = spaces * 100.0 / chars;

    printf("\nТекст:\t\t\"%s\"\n", text);
    printf("Символів:\t%d\n", chars);
    printf("Слів:\t\t%d\n", wordCount);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, lettersPercent);
    printf("Цифр:\t\t%d (%5.1f%%)\n", digits, digitsPercent);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, spacesPercent);
}

// Виведення таблиці слів, пошук найдовшого, найкоротшого та середньої довжини
void showWordsTable(char** words, int count) {
    int longest = 0;
    int shortest = 0;
    int totalLength = 0;

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    for (int i = 0; i < count; ++i) {
        int length = (int)strlen(words[i]);

        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], length);

        totalLength += length;

        // Пошук індексу першого найдовшого слова
        if (length > (int)strlen(words[longest])) {
            longest = i;
        }

        // Пошук індексу першого найкоротшого слова
        if (length < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }

    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n",
           words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n",
           words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)totalLength / count);
}

// Сортування копії масиву слів методом вставок (Insertion Sort) за strcmp
char** sortWords(char** words, int& count) {
    char** sorted = new char*[count];

    // Створюємо копію кожного слова, щоб не змінювати оригінальний масив
    for (int i = 0; i < count; ++i) {
        sorted[i] = new char[strlen(words[i]) + 1];
        strcpy(sorted[i], words[i]);
    }

    // Алгоритм сортування вставками
    for (int i = 1; i < count; ++i) {
        char* key = sorted[i];
        int j = i - 1;

        while (j >= 0 && strcmp(sorted[j], key) > 0) {
            sorted[j + 1] = sorted[j];
            --j;
        }

        sorted[j + 1] = key;
    }

    return sorted;
}

// Виведення слів за абеткою в один рядок
void showSortedWords(char** sorted, int count) {
    printf("За абеткою: ");

    for (int i = 0; i < count; ++i) {
        printf("%s", sorted[i]);

        if (i < count - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

// Пошук найчастішого слова серед відсортованого масиву
void showMostFrequentWord(char** sorted, int count) {
    char* mostFrequent = sorted[0];
    int maxCount = 0;
    int i = 0;

    // Рахуємо серії однакових підряд слів
    while (i < count) {
        int currentCount = 0;
        int j = i;

        while (j < count && strcmp(sorted[i], sorted[j]) == 0) {
            ++currentCount;
            ++j;
        }

        // Оновлюємо найчастіше слово
        if (currentCount > maxCount) {
            maxCount = currentCount;
            mostFrequent = sorted[i];
        }

        i = j;
    }

    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxCount);
}

// Заміна цілого слова в тексті за допомогою методів класу std::string
void replaceWord(char* text, char**& words, int& count, const char* oldWord, const char* newWord) {
    if (!isValidWord(newWord)) {
        printf("Помилка: нове слово має містити лише латинські літери та цифри.\n");
        return;
    }

    string oldText = text;
    string result = oldText;

    int replacements = 0;
    size_t position = 0;

    // Пошук входжень слова oldWord
    while ((position = result.find(oldWord, position)) != string::npos) {
        size_t end = position + strlen(oldWord);

        // Перевіряємо, чи знайдений фрагмент є окремим словом (межі зліва і справа)
        bool leftBoundary = (position == 0 || result[position - 1] == ' ');
        bool rightBoundary = (end == result.length() || result[end] == ' ' || result[end] == '.');

        if (leftBoundary && rightBoundary) {
            result.replace(position, strlen(oldWord), newWord);
            position += strlen(newWord);
            ++replacements;
        } else {
            position += strlen(oldWord);
        }
    }

    // Перевірка обмеження на максимальну довжину 255 символів
    if (result.length() > 255) {
        printf("Помилка: результат перевищує 255 символів. Текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);

    // Оновлюємо вихідний рядок та динамічний масив слів
    strcpy(text, result.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)result.length());
}

// Порівняння двох слів за різними критеріями (strcmp, ==, регістронезалежно, конкатенація)
void compareWords(const char* word1, const char* word2) {
    int result = strcmp(word1, word2);

    string first = word1;
    string second = word2;

    string lowerFirst = first;
    string lowerSecond = second;

    // Приведення до нижнього регістру для порівняння без урахування регістру
    for (size_t i = 0; i < lowerFirst.length(); ++i) {
        lowerFirst[i] = (char)tolower((unsigned char)lowerFirst[i]);
    }

    for (size_t i = 0; i < lowerSecond.length(); ++i) {
        lowerSecond[i] = (char)tolower((unsigned char)lowerSecond[i]);
    }

    // Конкатенація рядків оператором +
    string combined = first + " & " + second;

    printf("Перше слово: %s\n", word1);
    printf("Друге слово: %s\n", word2);

    // Результат стандартної функції strcmp
    printf("strcmp: ");
    if (result < 0) {
        printf("-1 -> перше слово менше\n");
    } else if (result > 0) {
        printf("1 -> перше слово більше\n");
    } else {
        printf("0 -> слова однакові\n");
    }

    printf("Рівні (==): %s\n", first == second ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n",
           lowerFirst == lowerSecond ? "так" : "ні");

    printf("Довжини: %d і %d\n",
           (int)first.length(), (int)second.length());

    printf("Конкатенація: \"%s\" (%d)\n",
           combined.c_str(), (int)combined.length());
}

// Виведення повної інформації про символ (коди в різних СЧ, тип, інверсія регістру, пошук)
void showCharacterInfo(const char* text) {
    char symbol;

    printf("Введіть символ: ");
    if (scanf("%c", &symbol) != 1) {
        printf("Помилка введення символу.\n");
        return;
    }

    // Очищення залишку потоку вводу
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    unsigned char code = (unsigned char)symbol;

    // Виведення кодів символу в десятковій, шістнадцятковій та вісімковій системах
    printf("Символ: '%c'\n", symbol);
    printf("Код: %u (hex 0x%02x, oct 0%o, bin ", (unsigned int)code, (unsigned int)code, (unsigned int)code);

    // Отримання двійкового представлення через побітовий зсув кожного біта (від 7 до 0)
    for (int bit = 7; bit >= 0; --bit) {
        printf("%d", (code >> bit) & 1);
    }
    printf(")\n");

    // Визначення категорії символу функціями з cctype
    if (isupper(code)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)tolower(code));
    } else if (islower(code)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(code));
    } else if (isdigit(code)) {
        printf("Тип: цифра\n");
    } else if (isspace(code)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    // Наступний символ за таблицею ASCII
    if (code < 127) {
        printf("Наступний символ: '%c'\n", (char)(code + 1));
    } else {
        printf("Наступний символ: код %u\n", (unsigned int)code + 1);
    }

    int occurrences = 0;
    int firstPosition = -1;

    // Пошук першого входження символу у тексті функцією strchr
    const char* found = strchr(text, symbol);

    if (found == NULL) {
        printf("Символ у тексті не зустрічається.\n");
    } else {
        // Позиція з 1-індексацією
        firstPosition = (int)(found - text) + 1;

        // Підрахунок усіх входжень символу
        for (int i = 0; text[i] != '\0'; ++i) {
            if (text[i] == symbol) {
                ++occurrences;
            }
        }

        printf("Входжень у тексті: %d, перше на позиції %d\n",
               occurrences, firstPosition);
    }
}

// Введення нового речення по словах через cin >> до слова з крапкою
void enterNewSentence(char* text, char**& words, int& count) {
    string sentence;
    string word;
    int readWords = 0;
    bool finished = false;

    printf("Введіть речення (крапка після останнього слова):\n");

    // Зчитуємо окремі слова оператором cin >>
    while (!finished && cin >> word) {
        ++readWords;

        if (!sentence.empty()) {
            sentence += " ";
        }

        sentence += word;

        // Речення завершується, якщо в кінці слова є крапка
        if (!word.empty() && word[word.length() - 1] == '.') {
            finished = true;
        }

        // Контроль довжини нового тексту (до 255 символів)
        if (sentence.length() > 255) {
            while (!finished && cin >> word) {
                if (!word.empty() && word[word.length() - 1] == '.') {
                    finished = true;
                }
            }

            printf("Помилка: текст перевищує 255 символів. Старий текст залишився без змін.\n");
            return;
        }
    }

    if (!finished) {
        printf("Помилка введення. Старий текст залишився без змін.\n");
        return;
    }

    // Перевірка валідності щойно введеного тексту
    if (!isValidText(sentence.c_str())) {
        printf("Помилка: речення має містити лише латинські літери, цифри та пробіли й завершуватися крапкою.\n");
        return;
    }

    // Оновлення основного рядка та перестворення динамічного масиву слів
    strcpy(text, sentence.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

// Повне звільнення динамічної пам'яті масиву слів
void freeWords(char**& words, int& count) {
    if (words != NULL) {
        // Звільняємо кожне окреме слово
        for (int i = 0; i < count; ++i) {
            delete[] words[i];
        }

        // Звільняємо масив вказівників
        delete[] words;
    }

    words = NULL;
    count = 0;
}
