#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

int readLine(char* buffer, int size) {
    int length = 0;
    bool valid = true;
    char c;
    int scanned;
    //читаємо доки scanned до ки !="\n"
    while ((scanned = scanf("%c", &c)) == 1 && c != '\n') {
        if (length == size - 1 || c == '\0') {
            //якщо length = 0 то ввід не валідний
            valid = false;
        } else {
            //записуємо символ і збільшуємо length
            buffer[length++] = c;
        }
    }
    buffer[length] = '\0';
    //фінальні перевірки на ввід
    if (!valid) {
        return 0;
    }
    if (scanned == EOF && length == 0) {
        return EOF;
    }
    return 1;
}

bool readInitialText(char* text, int size) {
    //заповнюємо кожен байт 1 щоб побачити де \0
    memset(text, 1, size);
    //перевіряємо чи вдалося зчитати рядок
    if (fgets(text, size, stdin) == nullptr) {
        return false;
    }

    int length = size - 1;
    while (text[length] != '\0') {
        length--;
    }
    //перевірка чи довжина text без \0. Якщо != то \0 був у середині тексту
    if (strlen(text) != static_cast<size_t>(length)) {
        return false;
    }

    char* newline = strchr(text, '\n');
    //якщо enter не вмістився у ввід, ми зчитуємо ще один байт 
    if (newline != nullptr) {
        *newline = '\0';
        return true;
    }

    char c;
    //ретурнимо що ввід закінчився
    return scanf("%c", &c) == EOF || c == '\n';
}

bool isValidText(const char* text) {
    size_t length = strlen(text);
    //basic check
    if (length == 0 || length > 255 || text[length - 1] != '.') {
        return false;
    }

    bool hasWord = false;
    for (size_t i = 0; i < length - 1; i++) {
        char c = text[i];
        if (c == ' ') {
            continue;
        }
        //будь який інший символ крім нижче наведених дасть false
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9')) {
            hasWord = true;
        } else {
            return false;
        }
    }
    return hasWord;
}

char** splitWords(const char* text, int& count) {
    char copy[256];
    strcpy(copy, text);
    //робимо щоб наступні функції читали copy до крапки
    *strchr(copy, '.') = '\0';

    const char* tokens[128];
    count = 0;
    //tokens зберігає адреси, 1 strtok - ділить за пробілами, 2 - продовжує з місця на якому закінчив
    for (char* word = strtok(copy, " "); word != nullptr;
         word = strtok(nullptr, " ")) {
        tokens[count++] = word;
    }
    //записуємо кожне слово у words щоб мати доступ надалі
    char** words = new char*[count];
    for (int i = 0; i < count; i++) {
        words[i] = new char[strlen(tokens[i]) + 1];
        strcpy(words[i], tokens[i]);
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
    //рахуємо значення
    for (const char* p = text; *p != '\0'; ++p) {
        unsigned char c = static_cast<unsigned char>(*p);
        if (isalpha(c)) {
            ++letters;
        } else if (isdigit(c)) {
            ++digits;
        } else if (*p == ' ') {
            ++spaces;
        }
    }
}
void menu() {
    printf("Пункт| Операція\n");
    printf("1    | Показати текст і статистику\n");
    printf("2    | Таблиця слів\n");
    printf("3    | Замінити слово\n");
    printf("4    | Порівняти два слова\n");
    printf("5    | Інформація про символ\n");
    printf("6    | Ввести нове речення\n");
    printf("0    | Вийти\n");
}

void textCout(const char* text, int count) {
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);

    size_t length = strlen(text);
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5zu\n", length);
    printf("Слів:     %5d\n", count);
    printf("Літер:    %5d (%5.1f%%)\n", letters, length ? letters * 100.0 / length : 0.0);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, length ? digits * 100.0 / length : 0.0);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, length ? spaces * 100.0 / length : 0.0);
}

void tablSliv(char** words, int count) {
    int longest = 0;
    int shortest = 0;
    int totalLength = 0;
    //записуємо значення для статистики
    for (int i = 0; i < count; i++) {
        int length = static_cast<int>(strlen(words[i]));
        totalLength += length;
        if (length > static_cast<int>(strlen(words[longest]))) {
            longest = i;
        }
        if (length < static_cast<int>(strlen(words[shortest]))) {
            shortest = i;
        }
    }
    //якщо менше 15 то 15
    int wordWidth = static_cast<int>(strlen(words[longest]));
    if (wordWidth < 15) {
        wordWidth = 15;
    }
    //створюємо та виводимо табличку
    int numberWidth = (count >= 100 ? 3 : 2);
    string border = "+" + string(numberWidth + 2, '-') + "+"
                  + string(wordWidth + 2, '-') + "+-------+";
    
    printf("%s\n", border.c_str());
    printf("| N%*s | Слово%*s | Довж. |\n", numberWidth - 1, "", wordWidth - 5, "");
    printf("%s\n", border.c_str());
    for (int i = 0; i < count; i++) {
        printf("| %*d | %-*s | %5zu |\n",
               numberWidth, i + 1, wordWidth, words[i], strlen(words[i]));
    }
    printf("%s\n", border.c_str());
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", static_cast<double>(totalLength) / count);

    char** sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    //бабл сортом сортуємо за абеткою
    for (int end = count - 1; end > 0; end--) {
        for (int i = 0; i < end; i++) {
            if (strcmp(sorted[i], sorted[i + 1]) > 0) {
                char* temp = sorted[i];
                sorted[i] = sorted[i + 1];
                sorted[i + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    int mostFrequent = 0;
    int maxFrequency = 0;
    for (int i = 0; i < count;) {
        int next = i + 1;
        //рахуємо чатоту слів
        while (next < count && strcmp(sorted[i], sorted[next]) == 0) {
            next++;
        }
        //запис кількості слів
        int frequency = next - i;
        if (frequency > maxFrequency) {
            maxFrequency = frequency;
            mostFrequent = i;
        }
        i = next;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[mostFrequent], maxFrequency);

    delete[] sorted;
}

bool readWord(const char* prompt, char word[33]) {
    printf("%s", prompt);

    char line[256];
    //не задов - return false
    if (readLine(line, sizeof(line)) != 1) {
        return false;
    }

    const char* whitespace = " \t\r\f\v";
    //рахуємо де закінчуються пробіли
    const char* start = line + strspn(line, whitespace);
    //скільки до наступного пробілу
    size_t length = strcspn(start, whitespace);
    const char* rest = start + length;
    //чек чи після кінцевої функції є ще щось
    if (length == 0 || length > 31 || rest[strspn(rest, whitespace)] != '\0') {
        return false;
    }
    // пеервірка на латинську літеру або цифру і хзапис у word
    for (size_t i = 0; i < length; i++) {
        char c = start[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
              || (c >= '0' && c <= '9'))) {
            return false;
        }
        word[i] = c;
    }
    word[length] = '\0';
    return true;
}

void changeWord(char* text, char**& words, int& count) {
    char from[33];
    char to[33];
    if (!readWord("Замінити слово: ", from) || !readWord("На слово: ", to)) {
        printf("Помилка: введіть одне слово з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    string result = text;
    size_t fromLength = strlen(from);
    size_t toLength = strlen(to);
    size_t pos = result.find(from);
    int replacements = 0;
    //виконуємо поки є збіги
    while (pos != string::npos) {
        size_t after = pos + fromLength;
        bool leftBoundary = pos == 0 || result[pos - 1] == ' ';
        bool rightBoundary = after < result.length()
                          && (result[after] == ' ' || result[after] == '.');

        if (leftBoundary && rightBoundary) {
            result.replace(pos, fromLength, to);
            replacements++;
            pos += toLength;
        } else {
            pos++;
        }
        pos = result.find(from, pos);
    }

    if (result.length() > 255) {
        printf("Помилка: після заміни текст перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %zu\n", result.length());

    if (replacements > 0) {
        strcpy(text, result.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
    }
}

void compareWords() {
    char a[33];
    char b[33];
    if (!readWord("Перше слово: ", a) || !readWord("Друге слово: ", b)) {
        printf("Помилка: введіть одне слово з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    int comparison = strcmp(a, b);
    if (comparison < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (comparison > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string first = a;
    string second = b;
    printf("Рівні (==): %s\n", first == second ? "так" : "ні");

    string lowerFirst = first;
    string lowerSecond = second;
    for (char& c : lowerFirst) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    for (char& c : lowerSecond) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    printf("Рівні без урахування регістру: %s\n",
           lowerFirst == lowerSecond ? "так" : "ні");

    string joined = first + " & " + second;
    printf("Довжини: %zu і %zu\n", first.length(), second.length());
    printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}

void symvolInfo(const char* text) {
    printf("Введіть символ: ");
    char line[2];
    if (readLine(line, sizeof(line)) != 1 || line[0] == '\0') {
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }

    char c = line[0];
    //числове значення c
    unsigned int code = static_cast<unsigned char>(c);
    printf("Символ: '%c'\n", c);
    //виводимо десятковий, шістнадцятковий та вісімковий коди
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) {
        printf("%u", (code >> i) & 1u);
    }
    printf(")\n");

    bool upper = isupper(code);
    bool lower = islower(code);
    const char* type = "інший символ";
    if (upper) {
        type = "велика літера";
    } else if (lower) {
        type = "мала літера";
    } else if (isdigit(code)) {
        type = "цифра";
    } else if (isspace(code)) {
        type = "пробільний символ";
    }
    printf("Тип: %s\n", type);

    if (upper || lower) {
        int otherCase = upper ? tolower(code) : toupper(code);
        printf("Інший регістр: '%c'\n", otherCase);
        printf("Наступний символ: '%c'\n", static_cast<int>(code + 1));
    }

    int occurrences = 0;
    int firstPosition = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            if (occurrences == 0) {
                firstPosition = i + 1;
            }
            occurrences++;
        }
    }

    if (occurrences == 0) {
        printf("Символ у тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPosition);
    }
}

void newSentence(char* text, char**& words, int& count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence;
    string word;
    int wordsRead = 0;
    bool tooLong = false;
    bool hasPeriod = false;
    //для cin >> word виконуємо
    while (cin >> word) {
        size_t separatorLength = sentence.empty() ? 0 : 1;
        if (sentence.length() + separatorLength + word.length() > 255) {
            tooLong = true;
        }
        //за потреби функція додає 1 пробіл
        if (!tooLong) {
            if (separatorLength != 0) {
                sentence += ' ';
            }
            sentence += word;
            wordsRead++;
        }
        //якщо символ крапка то у цьому слові щось є
        if (word.back() == '.') {
            hasPeriod = word.length() > 1;
            char c;
            // зчитує і вікдикає рештк рядка від enter
            while (cin.get(c) && c != '\n') {
            }
            break;
        }
    }

    if (tooLong) {
        printf("Помилка: речення перевищує 255 символів.\n");
        return;
    }

    if (!hasPeriod || sentence.find('\0') != string::npos
        || !isValidText(sentence.c_str())) {
        printf("Помилка: введіть слова з латинських літер і цифр "
               "та поставте крапку після останнього слова.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}
void memoryRelease(char**& words, int& count) {
    freeWords(words, count);
}

int main() {
    char text[256];
    //вводимо текст та виконуємо перевірки
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (!readInitialText(text, sizeof(text)) || !isValidText(text)) {
        printf("Помилка: введіть до 255 символів, щонайменше одне слово "
               "та крапку в кінці. Дозволено латинські літери, цифри й пробіли.\n");
        return 0;
    }

    int count = 0;
    char** words = splitWords(text, count);
    bool exit = false;
    int choice = 0;

    do {
        menu();
        printf("Ваш вибір: ");
        int scanned = scanf("%2d", &choice);
        //перевіряємо чи немає помилки читання
        if (scanned == EOF) {
            break;
        }
        //зчитуємо на зишишки в рядку scanf та перевіряємо на неправильний вивід
        //рахуємо пробільні символи та перевіряяємо чи не ввів користувач щосб зайве
        char rest[256];
        if (readLine(rest, sizeof(rest)) == 0 || scanned != 1
            || rest[strspn(rest, " \t\r\f\v")] != '\0') {
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            continue;
        }

        switch (choice) {
            case 1:
                textCout(text, count);
                break;
            case 2:
                tablSliv(words, count);
                break;
            case 3:
                changeWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                symvolInfo(text);
                break;
            case 6:
                newSentence(text, words, count);
                break;
            case 0:
                exit = true;
                printf("Вихід з програми\n");
                break;
            default:
                printf("Помилка введення");
                break;
        }
    } while (exit == false);

    memoryRelease(words, count);
    return 0;
}