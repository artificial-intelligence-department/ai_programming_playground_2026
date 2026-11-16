/* 
    Class Practice task: Редактор текстового повідомлення
    Соломія Королюк 
    ШІ-13
*/

#include <cstdio> //засоби C вводу і виводу
#include <cstring> //функції C рядків
#include <cctype> //перевірки й перетворення символів
#include <string>
#include <iostream>

using namespace std;

// ---------- Константи ----------
const int MAX_LEN  = 255;   // максимальна довжина тексту
const int MAX_BUF  = 256;   // розмір буфера (255 символів + '\0')
const int MAX_WORD = 31;    // максимальна довжина слова для заміни / порівняння

// ---------- Прототипи функцій ----------
void flushLine();
bool isValidText(const char *text);
bool isValidWord(const char *word);
bool readText(char *text);
bool readWord(const char *prompt, char *buf);

char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void sortWords(char **arr, int count);
bool equalIgnoreCase(const char *a, const char *b);
void printDashes(int n);

void showTextStats(const char *text, int wordCount);
void showWordTable(char **words, int count);
void replaceWord(char *text, char **&words, int &count);
void compareWords();
void showCharInfo(const char *text);
void enterNewSentence(char *text, char **&words, int &count);

int main() {
    char text[MAX_BUF];

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");

    if (!readText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n"
               "і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    // Розбиваємо текст на слова (динамічний масив рядків)
    int wordCount = 0;
    char **words = splitWords(text, wordCount);

    int choice;

    do {
        printf("\n===== МЕНЮ =====\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        int res = scanf("%d", &choice);

        if (res == EOF) {          // кінець вводу — виходимо, щоб не зациклитись
            choice = 0;
            break;
        }

        // Перевірка на нечисловий ввід
        if (res != 1) {
            flushLine();           // очищаємо буфер від некоректних символів
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;           // щоб цикл не завершився випадково
            continue;
        }
        flushLine();               // прибираємо зайве в кінці рядка

        switch (choice) {
            case 1:
                showTextStats(text, wordCount);
                break;
            case 2:
                showWordTable(words, wordCount);
                break;
            case 3:
                replaceWord(text, words, wordCount);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharInfo(text);
                break;
            case 6:
                enterNewSentence(text, words, wordCount);
                break;
            case 0:
                printf("Ви здійснили вихід.\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
        }

    } while (choice != 0);

    freeWords(words, wordCount);   // звільняємо памʼять перед виходом

    return 0;
}


// ---------- Допоміжні функції вводу та перевірки ----------

// Відкидає залишок поточного рядка у вхідному потоці
void flushLine() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // просто читаємо до кінця рядка
    }
}

// Перевіряє текст: літери, цифри, пробіли, хоча б одне слово, крапка в кінці
bool isValidText(const char *text) {
    int len = (int)strlen(text);

    if (len == 0 || len > MAX_LEN || text[len - 1] != '.') {
        return false;
    }

    int alnumCount = 0;

    // обходимо все, крім завершальної крапки
    for (const char *p = text; p < text + len - 1; p++) {
        unsigned char ch = (unsigned char)*p; // функціям cctype не можна передавати довільний від’ємний char

        if (isalnum(ch)) {
            alnumCount++;
        } else if (ch != ' ') {
            return false;
        }
    }

    return alnumCount > 0;   // має бути хоча б одне слово
}

// Перевіряє слово: непорожнє, до 31 символу, лише латинські літери й цифри
bool isValidWord(const char *word) {
    int len = (int)strlen(word);

    if (len == 0 || len > MAX_WORD) {
        return false;
    }

    for (const char *p = word; *p; p++) { //*p у for те саме, що *p != '\0'
        if (!isalnum((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

// Зчитує текст рядком цілком через fgets, перевіряє його коректність
bool readText(char *text) {
    if (fgets(text, MAX_BUF, stdin) == nullptr) {
        return false;
    }

    char *nl = strchr(text, '\n'); // повертає адресу переносу або nullptr

    if (nl != nullptr) {
        *nl = '\0';
    } else {
        // символу '\n' немає: або рядок задовгий, або це кінець вводу
        bool extra = false;
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            extra = true;
        }
        if (extra) {
            return false;      // ввід не вмістився в буфер
        }
    }

    // прибираємо '\r' (на випадок Windows)
    int len = (int)strlen(text);
    if (len > 0 && text[len - 1] == '\r') {
        text[len - 1] = '\0';
    }

    return isValidText(text);
}

// Зчитує одне слово (з контролем розміру буфера)
bool readWord(const char *prompt, char *buf) { //prompt - готовий текст підказки, а buf - адреса масиву для відповіді
    printf("%s", prompt);

    if (scanf("%63s", buf) != 1) { // читаємо одне слово (макс. 63 символи + '\0' для захисту від переповнення буфера)
        return false;
    }
    return true;
}


// ---------- Робота з памʼяттю та словами ----------

// Розбиває текст на слова, повертає динамічний масив рядків
char **splitWords(const char *text, int &count) {
    char buf[MAX_BUF];
    char tmp[MAX_BUF];

    strcpy(buf, text);

    char *dot = strchr(buf, '.');  // шукаємо адресу крапки
    if (dot != nullptr) {
        *dot = '\0'; // замінюємо крапку на кінець рядка
    }

    // Ми заздалегідь не знаємо скільки слів у реченні, тому потрібно проходити по рядку двічі
    // перший прохід: рахуємо слова (strtok змінює рядок, тому копія)
    strcpy(tmp, buf);
    count = 0;
    for (char *t = strtok(tmp, " "); t != nullptr; t = strtok(nullptr, " ")) {
        count++;
    }

    char **words = new char*[count];

    // другий прохід: копіюємо кожне слово окремо
    strcpy(tmp, buf);
    int i = 0;
    for (char *t = strtok(tmp, " "); t != nullptr; t = strtok(nullptr, " ")) {
        words[i] = new char[strlen(t) + 1]; // виділяємо пам'ять рівно під довжину слова + '\0'
        strcpy(words[i], t); // копіюємо саме слово в цю пам'ять
        i++;
    }

    return words;
}

// Звільняє памʼять: спочатку кожне слово, потім масив вказівників
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];
        words[i] = nullptr;
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

// Рахує літери, цифри й пробіли, обходячи текст вказівником
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++) {
        unsigned char ch = (unsigned char)*p;

        if (isalpha(ch)) letters++;
        else if (isdigit(ch)) digits++;
        else if (ch == ' ') spaces++;
    }
}

// Сортування вставками (порівняння як у strcmp). Змінюється лише масив вказівників arr
void sortWords(char **arr, int count) {
    for (int i = 1; i < count; i++) {
        char *key = arr[i];
        int j = i - 1;

        // Поки не дійшли до початку масиву (j >= 0) 
        // І поточне слово arr[j] за алфавітом стоїть пізніше, ніж key (> 0):
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Порівняння рядків без урахування регістру
bool equalIgnoreCase(const char *a, const char *b) {
    while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
        a++;
        b++;
    }
    return *a == *b;
}

// Друкує n символів '-'
void printDashes(int n) {
    for (int i = 0; i < n; i++) {
        putchar('-');
    }
}


// ---------- Пункти меню ----------

// Пункт 1: показати текст і статистику
void showTextStats(const char *text, int wordCount) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    int len = (int)strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", len);
    printf("Слів:\t\t%d\n", wordCount);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр:\t\t%d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, 100.0 * spaces / len);
}

// Пункт 2: таблиця слів + статистика + сортування
void showWordTable(char **words, int count) {
    // ширина стовпців залежить від найдовшого слова та кількості слів
    int w = 5;                       // мінімум — довжина заголовка "Слово"
    int nw = (count > 99) ? 3 : 2;

    int longest = 0, shortest = 0;   // індекси найдовшого й найкоротшого
    int totalLen = 0;

    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        totalLen += len;
        if (len > w) w = len;
        if (len > (int)strlen(words[longest]))   longest = i;    // строго більше - перше
        if (len < (int)strlen(words[shortest]))  shortest = i;   // строго менше - перше
    }

    // верхня межа та заголовок
    printf("+"); printDashes(nw + 2); printf("+"); printDashes(w + 2); printf("+-------+\n");
    printf("| %*s | Слово", nw, "N");
    printf("%*s | Довж. |\n", w - 5, "");
    printf("+"); printDashes(nw + 2); printf("+"); printDashes(w + 2); printf("+-------+\n");

    // рядки таблиці: слово ліворуч, числа праворуч
    for (int i = 0; i < count; i++) {
        printf("| %*d | %-*s | %5d |\n", nw, i + 1, w, words[i], (int)strlen(words[i]));
    }

    printf("+"); printDashes(nw + 2); printf("+"); printDashes(w + 2); printf("+-------+\n");

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)totalLen / count);

    // сортуємо копію масиву вказівників, щоб не змінювати порядок words
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    sortWords(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // найчастіше слово: в упорядкованому масиві однакові слова йдуть підряд
    int bestIdx = 0, bestCount = 0;
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) {
            j++;
        }
        if (j - i > bestCount) {     // строго більше - перше за абеткою
            bestCount = j - i;
            bestIdx = i;
        }
        i = j;
    }

    printf("Найчастіше слово: %s (%d)\n", sorted[bestIdx], bestCount);

    delete[] sorted;                 // самі слова не видаляємо — вони належать words
    sorted = nullptr;
}

// Пункт 3: заміна слова (через std::string)
void replaceWord(char *text, char **&words, int &count) {
    char fromBuf[64], toBuf[64];

    if (!readWord("Замінити слово: ", fromBuf) || !readWord("На слово: ", toBuf)) {
        flushLine();
        printf("Помилка: слова не введено.\n");
        return;
    }
    flushLine();

    if (!isValidWord(fromBuf) || !isValidWord(toBuf)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до %d символів).\n",
               MAX_WORD);
        return;
    }

    string s(text);
    string from(fromBuf);
    string to(toBuf);

    int replaced = 0;
    size_t pos = 0;

    while ((pos = s.find(from, pos)) != string::npos) {
        size_t end = pos + from.length();

        // це ціле слово, якщо до нього початок або пробіл, а після — пробіл, крапка чи кінець
        bool leftOk  = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (end >= s.length() || s[end] == ' ' || s[end] == '.');

        if (leftOk && rightOk) {
            s.replace(pos, from.length(), to);
            pos += to.length();      // пропускаємо вставлене слово
            replaced++;
        } else {
            pos++;
        }
    }

    if (replaced == 0) {
        printf("Замін виконано: 0\n");
        printf("Слово \"%s\" у тексті не знайдено, текст не змінено.\n", fromBuf);
        return;
    }

    if (s.length() > (size_t)MAX_LEN) {
        printf("Помилка: після заміни текст перевищує %d символів. Текст не змінено.\n", MAX_LEN);
        return;
    }

    string before(text);
    strcpy(text, s.c_str());

    // оновлюємо масив слів
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

// Пункт 4: порівняння двох слів
void compareWords() {
    char a[64], b[64];

    if (!readWord("Перше слово: ", a) || !readWord("Друге слово: ", b)) {
        flushLine();
        printf("Помилка: слова не введено.\n");
        return;
    }
    flushLine();

    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до %d символів).\n",
               MAX_WORD);
        return;
    }

    // strcmp може повертати довільні числа, тому зводимо до -1, 0, 1
    int r = strcmp(a, b);
    int sign = (r > 0) - (r < 0);

    printf("strcmp: %d -> ", sign);
    if (sign < 0)       printf("перше слово менше\n");
    else if (sign > 0)  printf("перше слово більше\n");
    else                printf("слова рівні\n");

    string sa(a), sb(b);

    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));

    string joined = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// Пункт 5: інформація про символ
void showCharInfo(const char *text) {
    char c;

    printf("Введіть символ: ");

    if (scanf("%c", &c) != 1 || c == '\n') {
        printf("Помилка: символ не введено.\n");
        return;
    }
    flushLine();

    unsigned char uc = (unsigned char)c;

    // Перевіряємо, чи має символ видимий вигляд (літера, цифра, знак, пробіл)
    if (isprint(uc)) printf("Символ: '%c'\n", c);
    else             printf("Символ: (недрукований)\n"); // наприклад, Enter (\n), Tab (\t) чи Esc

    // Виводимо код у десятковій (%d), шістнадцятковій (%x) та вісімковій (%o) системах
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", uc, uc, uc);

    // двійковий код — побітові операції
    for (int bit = 7; bit >= 0; bit--) {

        // (uc >> bit) — зсуваємо потрібний біт на крайню праву позицію
        // & 1         — відкидаємо всі інші біти, залишаючи лише 0 або 1
        // '0' + ...   — перетворюємо число 0 чи 1 на символ '0' чи '1' для друку

        putchar('0' + ((uc >> bit) & 1)); // Якщо біт дорівнює 0: '0' + 0 = 48 (символ '0') інакше '0' + 1 = 49 (символ '1')
    }
    printf(")\n");

    printf("Тип: ");
    if (isupper(uc))        printf("велика літера\n");
    else if (islower(uc))   printf("мала літера\n");
    else if (isdigit(uc))   printf("цифра\n");
    else if (isspace(uc))   printf("пробільний символ\n");
    else                    printf("інший символ\n");

    if (isalpha(uc)) {
        // Якщо літера мала — переводимо у велику, і навпаки
        int other = islower(uc) ? toupper(uc) : tolower(uc);
        printf("Інший регістр: '%c'\n", other);

        unsigned char next = (unsigned char)(uc + 1);   // наступний за кодом
        if (isprint(next)) printf("Наступний символ: '%c'\n", next);
        else               printf("Наступний символ: (недрукований, код %d)\n", next);
    }

    // кількість входжень і позиція першого
    int occurrences = 0;
    int firstPos = 0;

    //strchr шукає перше входження, а strchr(p + 1, c) — наступне після знайденого
    for (const char *p = strchr(text, c); p != nullptr; p = strchr(p + 1, c)) { 
        if (occurrences == 0) {
            // (p - text) — кількість символів від початку рядка до знахідки (індекс з 0)
            firstPos = (int)(p - text) + 1;   // нумерація з одиниці
        }
        occurrences++;
    }

    if (occurrences == 0) {
        printf("У тексті цей символ не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
    }
}

// Пункт 6: нове речення 
void enterNewSentence(char *text, char **&words, int &count) {
    string sentence;
    string w;
    int n = 0;
    bool finished = false;   // чи зустріли слово з крапкою
    bool tooLong = false;    // чи перевищили 255 символів

    printf("Введіть речення (крапка після останнього слова):\n");

    while (!finished && cin >> w) {
        n++;

        if (!tooLong) {                  // далі читаємо, але вже не накопичуємо
            if (n > 1) sentence += " ";
            sentence += w;
            if (sentence.length() > (size_t)MAX_LEN) {
                tooLong = true;
            }
        }

        if (w[w.length() - 1] == '.') {
            finished = true;
        }
    }

    if (finished) {
        cin.ignore(10000, '\n');         // відкидаємо залишок рядка після крапки
    } else {
        cin.clear();
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }

    if (tooLong || !isValidText(sentence.c_str())) {
        printf("Помилка: речення має складатися з латинських літер, цифр\n"
               "і пробілів, завершуватися крапкою та містити не більше %d символів.\n", MAX_LEN);
        return;
    }

    strcpy(text, sentence.c_str()); 

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", n);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}
