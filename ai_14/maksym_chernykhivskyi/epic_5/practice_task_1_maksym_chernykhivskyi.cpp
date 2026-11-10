/*Epic 5 - Редактор текстового повідомлення
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

const int MAX_TEXT = 255;
const int MIN_TEXT = 2;
const int MAX_WORD = 31;
const int MAX_WORD_INPUT = 64;

// Викидає залишок поточного рядка
void flushLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
}

// Перевіряє чи введений символ - латинська літера
bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Перевіряє чи введений символ - цифра
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
// Перевіряє чи текст валідний: від 2 до 255 символів, крапка в кінці, є лише латинські літери, цифри і пробіли, хоча б одне слово
bool isTextValid(const char *s) {
    size_t len = strlen(s);

    if (len < (size_t)MIN_TEXT || len > (size_t)MAX_TEXT) {
        return false;
    }
    if (s[len - 1] != '.') {
        return false;
    }

    bool has_word = false;
    for (size_t i = 0; i + 1 < len; i++) {
        char c = s[i];  
        if (isLatinLetter(c) || isDigit(c)) {
            has_word = true;
        } else if (c != ' ') {
            return false;
        }
    }
    return has_word;
}

// Перевіряє чи слово валідне: 1..31 символ, тільки латинські букви або цифри
bool isWordValid(const char *w) {
    size_t len = strlen(w);
    if (len == 0 || len > (size_t)MAX_WORD) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (!isLatinLetter(w[i]) && !isDigit(w[i])) {
            return false;
        }
    }
    return true;
}

// Зчитує рядок в буфер з розміром MAX_TEXT + 1, повертає: 1 - ок, 0 - рядок задовгий, -1 - кінець вводу
int readText(char *buf) {
    if (!fgets(buf, MAX_TEXT + 1, stdin)) {
        return -1;
    }
    char *nl = strchr(buf, '\n');
    if (nl) {
        *nl = '\0'; 
    } else if (strlen(buf) == (size_t)MAX_TEXT) {
        int c = getchar();
        if (c != '\n' && c != EOF) {
            flushLine();
            return 0;
        }
    }
    size_t len = strlen(buf);
    while (len > 0 && buf[len - 1] == '\r') {
        buf[--len] = '\0';
    }
    return 1;
}

// Зчитує одне слово, повертає: 1 - коректний ввід, 0 - некоректний, -1 - кінець вводу
int readWord(const char *prompt, char *out) {
    char tmp[MAX_WORD_INPUT];
    printf("%s", prompt); // "%s" - рядок
    if (scanf("%63s", tmp) != 1) {
        return -1;
    }
    bool extra = false;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace(c)) {
            extra = true;
        }
    }
    if (extra || !isWordValid(tmp)) {
        printf("Помилка. Слово має містити 1-31 символ: лише латинські літери й цифри.\n");
        return 0;
    }
    strcpy(out, tmp);
    return 1;
}

// Зчитує номер пункту меню, повертає: 1 - число, 0 - не число, -1 - кінець вводу
int readMenuChoice(int &choice) {
    printf("Ваш вибір: ");
    int r = scanf("%d", &choice);
    printf("\n");
    if (r == EOF) {
        return -1;
    }
    if (r != 1) {
        flushLine();
        return 0;
    }
    bool extra = false;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace(c)) {
            extra = true;
        }
    }
    return extra ? 0 : 1;
}

// Рахує літери, цифри й пробіли
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;

    // Закінчується коли доходить до "\0"
    for (const char *p = text; *p; ++p) {
        if (isLatinLetter(*p)) {
            letters++;
        } else if (isdigit((unsigned char)*p)) {
            digits++;
        } else if (*p == ' ') {
            spaces++;
        }
    } 
}

// Розбиває текст на слова 
char **splitWords(const char *text, int &count) {
    char buf[MAX_TEXT + 1];
    size_t len = strlen(text);  
    strcpy(buf, text);

    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }

    count = 0;
    for (char *t = strtok(buf, " "); t; t = strtok(NULL, " ")) {
        count++;
    }
    char **words = new char *[count > 0 ? count : 1];

    strcpy(buf, text);
    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }
    int i = 0;
    for (char *t = strtok(buf, " "); t && i < count; t = strtok(NULL, " ")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i], t);
        i++;
    }
    return words;
}

// Очищає пам'ять
void freeWords(char **&words, int &count) {
    if (words) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
    }
    words = NULL;
    count = 0;
}

// 1 - Показати текст і статистику
void showStats(const char *text, int count){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = (int)strlen(text);
    double d = len > 0 ? len : 1;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", len);
    printf("Слів:%10d\n", count);
    printf("Літер:%9d (%5.1f%%)\n", letters, 100 * letters / d);
    printf("Цифр:%10d (%5.1f%%)\n", digits, 100 * digits / d);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, 100 * spaces / d);
}

void printRepeat(char c, int n){
    for (int i = 0; i < n; i++){
        putchar(c);
    }
}

void printBorder(int w){
    printf("+----+");
    printRepeat('-', w + 2);
    printf("+-------+\n");
}

void sortPointers(char **a, int n){
    for (int i = 1; i < n; i++){
        char *key = a[i];
        int j = i - 1;
        while (j >= 0 && strcmp(a[j], key) > 0){ // a[j] > key
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// 2 - Таблиця слів
void showTable(char **words, int count){
    if (count == 0){
        printf("Слів немає.\n");
        return;
    }
    int w = 15; // Ширина колонки з словом
    for ( int i = 0; i < count; i++){
        int l = (int)strlen(words[i]);
        if (l > w){
            w = l;
        }
    }

    printBorder(w);
    
    printf("| N  | Слово");
    printRepeat(' ', w - 4);
    printf("| Довж. |\n");
    printBorder(w);
    
    for (int i = 0; i < count; i++){
        printf("| %2d | %-*s | %5d |\n", i + 1, w, words[i], (int)strlen(words[i]));
    }
    printBorder(w);
    
    // Найдовше, найкоротше слово, сума
    int longest = 0, shortest = 0;
    long sum = 0;
    for (int i = 0; i < count; i++){
        int l = (int)strlen(words[i]);
        sum += l;

        if (l > (int)strlen(words[longest])) {
            longest = i;
        }
        if (l < (int)strlen(words[shortest])) {
            shortest = i;
        }
    }
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));

    printf("Середня довжина: %.2f\n", (double)sum / count);

    // За алфавітом
    char **sorted = new char *[count];
    for (int i = 0; i < count; i++){
        sorted[i] = words[i];
    }
    sortPointers(sorted, count);

    printf("За абеткою:");
    for (int i = 0; i < count; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // Найчастіше слово
    int mostWordAmount = 0;
    const char *mostUsedWord = sorted[0];
    int i = 0;
    while (i < count){
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0){
            j++;
        }
        if (j - i > mostWordAmount){
            mostWordAmount = j - i;
            mostUsedWord = sorted[i];
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", mostUsedWord, mostWordAmount);
    delete[] sorted;
}

// 3 - Заміна слова
void replaceWord(char *text, char **&words, int &count){
    char from[MAX_WORD_INPUT], to[MAX_WORD_INPUT];
    if (readWord("Замінити слово: ", from) != 1){
        return;
    }
    if (readWord("На слово: ", to) != 1){
        return;
    }
    string s = text;
    string f = from;
    string t = to;
    int replaced = 0;
    size_t pos = 0;
    while ((pos = s.find(f, pos)) != string::npos){
        size_t end = pos + f.length();
        
        // Перевірки справа і зліва від слова
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (end >= s.length() || s[end] == ' ' || s[end] == '.');

        if (leftOk && rightOk){
            s.replace(pos, f.length(), t);
            pos += t.length();
            replaced++;
        } else {
            pos++;
        }
    }    
    if (s.length() > (size_t)MAX_TEXT){
        printf("Помилка: після заміни слів текст перевищив би %d символів. Текст не змінено.\n", MAX_TEXT);
        return;
    }
    printf("Замін виконано: %d\n", replaced);
    if (replaced == 0){
        printf("Слова \"%s\" у тексті немає, текст не змінено.\n", from);
        return;
    }
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", s.c_str());
    printf("Нова довжина: %d\n", (int)s.length());

    strcpy(text, s.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

// 4 - Перевіряє чи рядки однакові ігноруючи регістр
bool equalIgnoreCase(const string &a, const string &b){
    if (a.length() != b.length()){
        return false;
    }
    for (size_t i = 0; i < a.length(); i++){
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])){
            return false;
        }
    }
    return true;
}

// 4 - Порівнює два слова
void compareWords(){
    char a[MAX_WORD_INPUT], b[MAX_WORD_INPUT];
    if (readWord("Перше слово: ", a) != 1){
        return;
    }
    if (readWord("Друге слово: ", b) != 1){
        return;
    }

    int r = strcmp(a, b);
    r = (r < 0) ? -1 : (r > 0) ? 1 : 0;

    printf("strcmp: %d -> ", r);
    if (r < 0){
        printf("перше слово менше\n");
    } else if (r > 0) {
        printf("перше слово більше\n");
    } else {
        printf("слова рівні\n");
    }

    string sa = a;
    string sb = b;

    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");

    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(sa, sb) ? "так" : "ні");

    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());

    string concat = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}

// 5 - Інформація про символ
void charInfo(const char *text){
    char line[16];
    printf("Введіть символ: ");
    if (!fgets(line, sizeof(line), stdin)){
        return;
    }    
    char *nl = strchr(line, '\n');
    if (nl){
        *nl = '\0';
    } else {
        flushLine();
    }
    size_t len = strlen(line);
    while (len > 0 && line[len - 1] == '\r'){
        line[--len] = '\0';
    }
    if(len != 1){
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }
    unsigned char uc = (unsigned char)line[0];
    if (uc > 127){
        printf("Помилка: підтримуються лише символи ASCII.\n");
        return;
    }
    char c = (char)uc;
    if(isprint(uc)){
        printf("Символ: '%c'\n", c);
    } else {
        printf("Символ: (недрукований)\n");
    }

    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", uc, uc, uc);
    for (int i = 7; i >= 0; i--){
        putchar(((uc >> i) & 1) ? '1' : '0');
    }
    printf(")\n");

    printf("Тип: ");
    if (isupper(uc)){
        printf("велика літера\n");
    } else if (islower(uc)){
        printf("мала літера\n");
    } else if (isDigit(uc)){
        printf("цифра\n");
    } else if (isspace(uc)){
        printf("пробіл\n");
    } else {
        printf("інший символ\n");
    }

    if (isalpha(uc)){
        char other = islower(uc) ?  (char)(uc - 'a' + 'A') : (char)(uc - 'A' + 'a');
        printf("Інший регістр: '%c'\n", other);
    }
    unsigned char next = (unsigned char)(uc + 1);
    if (isprint(next)){
        printf("Наступний символ: '%c'\n", next);
    } else {
        printf("Наступний символ: (недрукований)\n");
    }

    int count_ch = 0;
    const char *first = strchr(text, c);
    for (const char *p = first; p; p = strchr(p + 1, c)){
        count_ch++;
    }
    if (count_ch == 0){
        printf("У тексті цей символ не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count_ch, (int)(first - text) + 1);
    }
}

void newSentence(char *text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");
    string w;
    string result;
    int n = 0;
    bool finished = false;
    
    while(cin >> w){
        if (w[w.length()-1] == '.'){
            finished = true;

            if (w.length() == 1){
                result += ".";
            } else {
                if (n > 0) {
                    result += " ";
                }
                result += w;
                n++;
            }
            break;
        }
        if (n > 0){
            result += " ";
        }
        result += w;
        n++;
    }
    cin.ignore(10000, '\n');

    if (!finished){
        cin.clear();
        printf("Помилка: речення не завершено крапкою. Поточний текст не змінено.\n");
        return;
    }
    if (result.length() > (size_t)MAX_TEXT || !isTextValid(result.c_str())){
        printf("Помилка: речення має складатись з латинських літер, цифр і пробілів, завершуватися крапкою та містити до %d символів.\nПоточний текст не змінено.\n", MAX_TEXT);
        return;
    }

    printf("Прочитано слів: %d\n", n);
    printf("Новий текст: \"%s\"\n", result.c_str());
    printf("Довжина: %d\n", (int)result.length());

    strcpy(text, result.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
}

void printMenu(){
    printf("\nМеню:\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
}

int main() {
    char text[MAX_TEXT + 1];
    printf("Введіть текст (до %d символів, крапка в кінці):\n", MAX_TEXT);

    int rc = readText(text);
    if (rc == -1){
        printf("Помилка: порожній ввід.\n");
        return 1;
    }
    if (rc == 0 || !isTextValid(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватись крапкою.\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);

    int choice = -1;
    bool run = true;
    while (run){
        printMenu();
        int r = readMenuChoice(choice);
        if (r == -1) {
            break;
        } else if (r == 0){
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        
        switch (choice){
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
                charInfo(text);
                break;
            case 6:
                newSentence(text, words, count);
                break;
            case 0:
                run = false;
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);            
        }
    }

    freeWords(words, count);
    return 0;
}