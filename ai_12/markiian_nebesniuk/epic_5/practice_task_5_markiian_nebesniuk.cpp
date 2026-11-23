/*
Редактор текстового повідомлення
Небеснюк Маркіян
ШІ-12
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

// Перевірка коректності тексту: спільна для початкового вводу та пункту 6,
// щоб гарантувати наявність хоча б одного слова, дозволені символи та фінальну крапку
bool isValidText(const char *text) {
    size_t len = strlen(text);
    if (len == 0 || text[len - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    // Перевіряємо символи до len - 1, оскільки останній символ уже підтверджено як крапку
    for (size_t i = 0; i < len - 1; i++) {
        // Приведення до unsigned char захищає функції cctype від від'ємних кодів
        unsigned char c = (unsigned char)text[i];
        if (isalpha(c) != 0 || isdigit(c) != 0) {
            hasWord = true;
        } else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}

// Перевірка окремого слова: крапка та пробіли тут заборонені,
// щоб не зламати межі слів під час заміни чи порівняння
bool isValidWord(const char *word) {
    if (word[0] == '\0') {
        return false;
    }
    for (const char *p = word; *p != '\0'; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c) == 0 && isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

// Розбиття тексту на динамічний масив слів:
// спершу рахуємо кількість слів, щоб виділити точний обсяг пам'яті в купі
char **splitWords(const char *text, int &count) {
    // Працюємо з копією, оскільки strtok змінює рядок і ставить '\0' замість роздільників
    char copy[256];
    strcpy(copy, text);
    // Відкидаємо завершальну крапку, бо за умовою вона не входить до останнього слова
    copy[strlen(copy) - 1] = '\0';

    count = 0;
    char *t = strtok(copy, " ");
    while (t != NULL) {
        count++;
        t = strtok(NULL, " ");
    }

    char **words = new char *[count];

    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';

    int k = 0;
    t = strtok(copy, " ");
    while (t != NULL) {
        // +1 байт потрібен для завершального нуль-термінатора '\0'
        words[k] = new char[strlen(t) + 1];
        strcpy(words[k], t);
        k++;
        t = strtok(NULL, " ");
    }

    return words;
}

// Звільнення динамічної пам'яті: спершу кожне окреме слово, потім масив вказівників,
// щоб уникнути витоків пам'яті при оновленні тексту та завершенні програми
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

// Підрахунок літер, цифр і пробілів обходом тексту вказівником;
// результати повертаємо через параметри-посилання
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++) {
        unsigned char c = (unsigned char)*p;
        if (isalpha(c) != 0) {
            letters++;
        } else if (isdigit(c) != 0) {
            digits++;
        } else if (isspace(c) != 0) {
            spaces++;
        }
    }
}

// Пункт 1: Вивід тексту та статистики символів
void Menu_1(const char *text, int wordCount) {
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    countChars(text, letters, digits, spaces);

    int totalChars = (int)strlen(text);

    // Крапка входить у totalChars, тому сума відсотків літер, цифр і пробілів менша за 100%
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", totalChars);
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d (%5.1f%%)\n", letters, (double)letters * 100.0 / totalChars);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, (double)digits * 100.0 / totalChars);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, (double)spaces * 100.0 / totalChars);
}

// Пункт 2: Таблиця слів, екстремуми довжин, абеткове сортування та найчастіше слово
void Menu_2(char **words, int wordCount) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int maxIdx = 0, maxLen = (int)strlen(words[0]);
    int minIdx = 0, minLen = (int)strlen(words[0]);
    int totalLen = 0;

    for (int i = 0; i < wordCount; i++) {
        int len = (int)strlen(words[i]);
        // %-15s вирівнює слово ліворуч, %2d і %5d вирівнюють числа праворуч
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);

        totalLen += len;
        // Строга нерівність зберігає перше знайдене слово при однаковій довжині
        if (len > maxLen) {
            maxLen = len;
            maxIdx = i;
        }
        if (len < minLen) {
            minLen = len;
            minIdx = i;
        }
    }

    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", (double)totalLen / wordCount);

    // Створюємо тимчасовий масив вказівників, щоб сортування не змінювало порядок у words
    char **sorted = new char *[wordCount];
    for (int i = 0; i < wordCount; i++) {
        sorted[i] = words[i];
    }

    // Сортування бульбашкою за ASCII-кодами через strcmp (цифри передують літерам)
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - 1 - i; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < wordCount; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // У відсортованому масиві однакові слова стоять поруч, що дозволяє знайти максимум за один прохід
    char *mostFreqWord = sorted[0];
    int maxFreq = 1;
    int currFreq = 1;

    for (int i = 1; i < wordCount; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {
            currFreq++;
            // Строга нерівність гарантує вибір першого за абеткою слова при рівній частоті
            if (currFreq > maxFreq) {
                maxFreq = currFreq;
                mostFreqWord = sorted[i];
            }
        } else {
            currFreq = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);

    // Звільняємо лише масив вказівників, самі рядки належать основному масиву words
    delete[] sorted;
}

// Пункт 3: Заміна цілих слів у тексті засобами std::string
void Menu_3(char *text, char **&words, int &wordCount) {
    // Розмір 32 (31 символ + '\0') відповідає формату вводу з умови
    char from[32];
    char to[32];

    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) {
        while (getchar() != '\n');
        printf("Помилка вводу слова.\n");
        return;
    }
    while (getchar() != '\n');

    printf("На слово: ");
    if (scanf("%31s", to) != 1) {
        while (getchar() != '\n');
        printf("Помилка вводу слова.\n");
        return;
    }
    while (getchar() != '\n');

    if (isValidWord(from) == false || isValidWord(to) == false) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        return;
    }

    string str = text;
    string fromStr = from;
    string toStr = to;

    int replacedCount = 0;
    size_t pos = 0;

    while ((pos = str.find(fromStr, pos)) != string::npos) {
        // Перевіряємо межі слова зліва та справа, щоб не замінити частину довшого слова (cat у cats)
        bool leftEnd = (pos == 0 || str[pos - 1] == ' ');
        size_t endPos = pos + fromStr.length();
        bool rightEnd = (str[endPos] == ' ' || str[endPos] == '.');

        if (leftEnd == true && rightEnd == true) {
            str.replace(pos, fromStr.length(), toStr);
            replacedCount++;
            // Перестрибуємо вставлене слово, щоб уникнути зациклення при заміні cat на supercat
            pos += toStr.length();
        } else {
            pos += 1;
        }
    }

    if (replacedCount == 0) {
        printf("Слово \"%s\" не знайдено.\n", from);
        return;
    }

    // Контроль переповнення буфера char text[256] перед записом результату
    if (str.length() > 255) {
        printf("Помилка: після заміни текст перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacedCount);
    printf("Було:  \"%s\"\n", text);

    // Оновлюємо основний рядок і перебудовуємо динамічний масив слів під новий вміст
    strcpy(text, str.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

// Пункт 4: Порівняння двох слів різними способами та їх конкатенація
void Menu_4() {
    char a[32];
    char b[32];

    printf("Перше слово: ");
    if (scanf("%31s", a) != 1) {
        while (getchar() != '\n');
        printf("Помилка вводу слова.\n");
        return;
    }
    while (getchar() != '\n');

    printf("Друге слово: ");
    if (scanf("%31s", b) != 1) {
        while (getchar() != '\n');
        printf("Помилка вводу слова.\n");
        return;
    }
    while (getchar() != '\n');

    if (isValidWord(a) == false || isValidWord(b) == false) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        return;
    }

    // Нормалізуємо результат strcmp до -1, 0 або 1, бо на різних ОС функція повертає різницю кодів
    int cmp = strcmp(a, b);
    if (cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    string strA = a;
    string strB = b;

    if (strA == strB) {
        printf("Рівні (==): так\n");
    } else {
        printf("Рівні (==): ні\n");
    }

    // Для регістронезалежного порівняння зводимо копії обох слів до нижнього регістру
    string lowA = strA;
    string lowB = strB;
    for (size_t i = 0; i < lowA.length(); i++) {
        lowA[i] = (char)tolower((unsigned char)lowA[i]);
    }
    for (size_t i = 0; i < lowB.length(); i++) {
        lowB[i] = (char)tolower((unsigned char)lowB[i]);
    }

    if (lowA == lowB) {
        printf("Рівні без урахування регістру: так\n");
    } else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %d і %d\n", (int)strA.length(), (int)strB.length());

    string joined = strA + " & " + strB;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// Пункт 5: Аналіз коду, типу та входжень окремого символу
void Menu_5(const char *text) {
    char c;
    printf("Введіть символ: ");
    // Пробіл перед %c пропускає залишки пробільних символів у буфері
    if (scanf(" %c", &c) != 1) {
        while (getchar() != '\n');
        printf("Помилка вводу символу.\n");
        return;
    }
    while (getchar() != '\n');

    unsigned char code = (unsigned char)c;

    printf("Символ: '%c'\n", c);

    // Виводимо код у трьох системах через специфікатори printf та 8 біт побітовим зсувом
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", (int)code, (int)code, (int)code);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (code >> bit) & 1);
    }
    printf(")\n");

    if (isupper(code) != 0) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)tolower(code));
    } else if (islower(code) != 0) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(code));
    } else if (isdigit(code) != 0) {
        printf("Тип: цифра\n");
    } else if (isspace(code) != 0) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", (char)(code + 1));

    // strchr знаходить адресу першого входження, різниця вказівників + 1 дає позицію з одиниці
    const char *firstPtr = strchr(text, c);
    if (firstPtr == NULL) {
        printf("У тексті не зустрічається\n");
    } else {
        int count = 0;
        for (const char *p = text; *p != '\0'; p++) {
            if (*p == c) {
                count++;
            }
        }
        int firstPos = (int)(firstPtr - text) + 1;
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    }
}

// Пункт 6: Введення нового речення по словах через cin >> до крапки в кінці слова
void Menu_6(char *text, char **&words, int &wordCount) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence = "";
    string word;
    int readWords = 0;
    bool tooLong = false;

    // cin >> автоматично пропускає зайві пробіли та переноси рядків між словами
    while (cin >> word) {
        if (readWords > 0) {
            sentence += " ";
        }
        sentence += word;
        readWords++;

        if (sentence.length() > 255) {
            tooLong = true;
        }

        // Ознака кінця речення — крапка в кінці чергового прочитаного слова
        if (word[word.length() - 1] == '.') {
            break;
        }
    }

    // Очищаємо залишок рядка після останнього слова, щоб не збити наступний scanf у меню
    cin.ignore(1000, '\n');

    if (readWords == 0 || tooLong == true) {
        printf("Помилка: речення занадто довге (максимум 255 символів). Текст не змінено.\n");
        return;
    }

    if (isValidText(sentence.c_str()) == false) {
        printf("Помилка: речення має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. Текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

int main() {
    // 255 символів тексту + 1 байт для '\0'
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Помилка зчитування.\n");
        return 1;
    }
    // Прибираємо символ нового рядка '\n', який зберігає fgets
    text[strcspn(text, "\n")] = '\0';

    if (isValidText(text) == false) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int wordCount = 0;
    char **words = splitWords(text, wordCount);

    int choice = -1;
    while (true) {
        printf("\n=====Меню=====\n"
               "Пункт\tОперація\n"
               "1  \tПоказати текст і статистику\n"
               "2  \tТаблиця слів\n"
               "3  \tЗамінити слово\n"
               "4  \tПорівняти два слова\n"
               "5  \tІнформація про символ\n"
               "6  \tВвести нове речення\n"
               "0  \tВийти\n"
               "Ваш вибір: ");

        int scanned = scanf("%d", &choice);
        // Перевіряємо символ одразу після числа, щоб відсіяти ввід типу "1abc"
        int nextChar = getchar();

        if (scanned != 1 || nextChar != '\n') {
            if (nextChar != '\n') {
                while (getchar() != '\n');
            }
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }

        if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            continue;
        }

        if (choice == 0) {
            break;
        }

        printf("\n");

        switch (choice) {
            case 1:
                Menu_1(text, wordCount);
                break;
            case 2:
                Menu_2(words, wordCount);
                break;
            case 3:
                Menu_3(text, words, wordCount);
                break;
            case 4:
                Menu_4();
                break;
            case 5:
                Menu_5(text);
                break;
            case 6:
                Menu_6(text, words, wordCount);
                break;
            default:
                break;
        }
    }

    // Обов'язково звільняємо динамічну пам'ять перед виходом із програми
    freeWords(words, wordCount);
    return 0;
}