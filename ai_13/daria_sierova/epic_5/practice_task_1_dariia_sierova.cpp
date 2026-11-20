#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int maxtext = 256; // 255 + \0
const int maxword = 32;  // 31 + \0

//валідність слова
bool isValidWord(const char *w) {
    if (w == nullptr || w[0] == '\0') return false;
    for (int i = 0; w[i] != '\0'; i++) {
        unsigned char c = (unsigned char)w[i]; //щоб не було відємних
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return false;
        }
    }
    return true;
}

//звільнення пам'яті
void freeWords(char **&words, int &count) { //& щоб занулити адресу
    if (words != nullptr) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
            words[i] = nullptr;
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

//розбиття тексту
char **splitWords(const char *text, int &count) {
    char copy1[maxtext];
    strcpy(copy1, text);
    int strLen = strlen(copy1);
    if (strLen > 0 && copy1[strLen - 1] == '.') {
        copy1[strLen - 1] = '\0';
    }
    char copy2[maxtext];
    strcpy(copy2, copy1);

    char *part = strtok(copy1, " "); // кількість слів
    count = 0;
    while (part != NULL) {
        count++;
        part = strtok(NULL, " ");
    }

    char **wordList = new char*[count];
    part = strtok(copy2, " "); 
    for (int i = 0; i < count; i++) {
        wordList[i] = new char[strlen(part) + 1];
        strcpy(wordList[i], part);
        part = strtok(NULL, " ");
    }
    return wordList;
}

//кількість літер цифр і пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    const char *p = text;
    while (*p != '\0') {
        unsigned char c = (unsigned char)(*p);
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else if (*p == ' ') {
            spaces++;
        }
        p++;
    }
}

// 1 показати текст і статистику
void showStatistics(const char *text, int totalwords) {
    int totalChars = strlen(text);
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);

    double let = letters * 100.0 / totalChars;
    double dig = digits * 100.0 / totalChars;
    double spc = spaces * 100.0 / totalChars;

    printf("Текст: \"%s\"\n", text);
    printf("Символів: %d\n", totalChars);
    printf("Слів: %d\n", totalwords);
    printf("Літер: %d (%.1f%%)\n", letters, let);
    printf("Цифр: %d (%.1f%%)\n", digits, dig);
    printf("Пробілів: %d (%.1f%%)\n", spaces, spc);
}

// 2. Таблиця слів
void showWordTable(char **words, int count) {
    if (count <= 0) return;

    printf("------------------------------------------------\n");
    printf("| %-2s | %-31s | %5s |\n", "№", "Слово", "Довж.");
    printf("------------------------------------------------\n");

    int longesti = 0;
    int shortesti = 0;
    int sumLen = 0;

    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        sumLen += len;
        if (len > strlen(words[longesti])) {
            longesti = i;
        }
        if (len < strlen(words[shortesti])) {
            shortesti = i;
        }
        printf("| %2d | %-31s | %5d |\n", i + 1, words[i], len);
    }
    printf("------------------------------------------------\n");

    double avgLen = (double) sumLen / count;
    printf("Найдовше слово: %s (%zu)\n", words[longesti], strlen(words[longesti]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortesti], strlen(words[shortesti]));
    printf("Середня довжина: %.2f\n", avgLen);

    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    // найчастішe словo
    char *mostFreqWord = sorted[0];
    int maxFreq = 1; 
    int currFreq = 1;

    for (int i = 1; i < count; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {
            currFreq++;
            if (currFreq > maxFreq) {
                maxFreq = currFreq;
                mostFreqWord = sorted[i];
            }
        } else {
            currFreq = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);
    delete[] sorted;
}

// 3 заміна слова
void replaceWord(char *text, char **&words, int &totalwords) {
    char from[maxword];
    char to[maxword];

    printf("Замінити слово: ");
    if (scanf("%31s", from) != 1) { //одне слово
        while (getchar() != '\n');
        printf("Помилка введення слова.\n");
        return;
    }
    while (getchar() != '\n'); // очистка залишку рядка

    printf("На слово: ");
    if (scanf("%31s", to) != 1) {
        while (getchar() != '\n');
        printf("Помилка введення слова.\n");
        return;
    }
    while (getchar() != '\n');

    if (!isValidWord(from) || !isValidWord(to)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    string strText = text;
    string fromStr = from;
    string toStr = to;

    int replacements = 0;
    size_t pos = 0; // тип який повертає файнд

    // пошук і заміна лише цілих слів
    while ((pos = strText.find(fromStr, pos)) != string::npos) {
        bool left = (pos == 0 || strText[pos - 1] == ' '); //приклеєне до іншого слова зліва
        size_t endPos = pos + fromStr.length(); //індекс символу який іде після знайденого слова
        bool right = (endPos == strText.length() || strText[endPos] == ' ' || strText[endPos] == '.');

        //якщо це дійсно окреме слово
        if (left && right) {
            if (strText.length() - fromStr.length() + toStr.length() >= maxtext) { //поточна - старе + нове
                printf("Помилка: після заміни довжина тексту перевищить 255 символів.\n");
                return;
            }
            strText.replace(pos, fromStr.length(), toStr);
            replacements++;
            pos += toStr.length(); // курсор на наступне слово
        } else {
            pos += 1;
        }
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", text);

    strcpy(text, strText.c_str()); // копіюєм відредагований текст назад у масив символів
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", strText.length());

    if (replacements > 0) {
        freeWords(words, totalwords);//видаляєм старий рядок з памяті
        words = splitWords(text, totalwords); //перезаписуєм з новим словом
    }
}

// 4 порівняти два слова
void compareWords() {
    char a[maxword];
    char b[maxword];

    printf("Перше слово: ");
    if (scanf("%31s", a ) != 1) {
        while (getchar() != '\n');
        printf("Помилка введення.\n");
        return;
    }
    while (getchar() != '\n');

    printf("Друге слово: ");
    if (scanf("%31s", b ) != 1) {
        while (getchar() != '\n');
        printf("Помилка введення.\n");
        return;
    }
    while (getchar() != '\n');

    if (!isValidWord(a) || !isValidWord(b)) {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }

    int cmp = strcmp(a, b);
    if (cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if (cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }

    string s1 = a;
    string s2 = b;

    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

    //без урахування регістру
    bool equal = (s1.length() == s2.length());
    if (equal) {
        for (size_t i = 0; i < s1.length(); i++) {
            if (tolower(s1[i]) != tolower(s2[i])) {
                equal = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: %s\n", equal ? "так" : "ні");
    printf("Довжини: %zu і %zu\n", s1.length(), s2.length());

    string concat = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

// 5 інформація про символ
void charInfo(const char *text) {
    char line[64];
    printf("Введіть символ: ");
    if (fgets(line, sizeof(line), stdin) == nullptr || line[0] == '\n' || line[0] == '\0') {
        printf("Помилка: символ не введено.\n");
        return;
    }

    char c = line[0];
    unsigned char uc = c;

    // двійковий запис
    char bin[9];
    int temp = uc;
    for (int i = 7; i >= 0; i--) {
        bin[i] = (temp % 2) + '0'; 
        temp = temp / 2;           
    }
    bin[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%02x, oct 0%o, bin %s)\n", uc, uc, uc, bin); //шістнадцятковий вісімковий двійковий

    if (isupper(uc)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)tolower(uc));
    } else if (islower(uc)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(uc));
    } else if (isdigit(uc)) {
        printf("Тип: цифра\n");
    } else if (isspace(uc)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: '%c'\n", uc + 1);

    int occur = 0;
    int firstPos = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            occur++;
            if (firstPos == -1) {
                firstPos = i + 1;
            }
        }
    }

    if (occur > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occur, firstPos);
    } else {
        printf("У тексті не зустрічається\n");
    }
}

// 6 ввести нове речення
void inputNewSentence(char *text, char **&words, int &totalwords) {
    printf("Введіть речення (крапка після останнього слова):\n");

    char newText[maxtext] = "";
    int currentLen = 0;
    int readWords = 0;
    bool valid = true;
    string token;

    while (cin >> token) {
        bool isLast = false;
        if (!token.empty() && token.back() == '.') {
            isLast = true;
            token.erase(token.length() - 1); // видаляє останній символ
        }

        // ввели крапку окремо або порожній токен
        if (token.empty()) {
            valid = false;
            if (isLast) break;
            continue;
        }
        //
        if (!isValidWord(token.c_str())) {
            valid = false;
        }

        if (valid) {
            int needed = token.length() + (readWords > 0 ? 1 : 0) + (isLast ? 1 : 0); //пробіл перед? крапка?
            if (currentLen + needed >= maxtext) {
                valid = false;
            } else {
                if (readWords > 0) {
                    strcat(newText, " "); // є слова - пробіл
                    currentLen++;
                }
                strcat(newText, token.c_str()); //дописуєм слово
                currentLen += token.length();
                readWords++;

                if (isLast) {
                    strcat(newText, ".");
                    currentLen++;
                }
            }
        }

        if (isLast) {
            break;
        }
    }

    while (getchar() != '\n');

    if (!valid || readWords == 0) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою (до 255 символів).\n");
        return;
    }

    strcpy(text, newText);
    freeWords(words, totalwords);
    words = splitWords(text, totalwords);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

int main() {
    char text[maxtext] = "";
    char alphabet[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    if (fgets(text, sizeof(text), stdin) == nullptr) {
        return 1;
    }

    int textlen = strlen(text);
    // заміна \n на \0
    if (textlen > 0 && text[textlen - 1] == '\n') {
        text[textlen - 1] = '\0';
        textlen--;
    }

    // рядок порожній або нема крапки
    if (text[0] == '\0' || text[textlen - 1] != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    // перевірка символів тексту
    bool hasword = false;
    for (int i = 0; i < textlen - 1; i++) {
        if (strchr(alphabet, text[i]) || isdigit((unsigned char)text[i])) {
            hasword = true;
        } else if (text[i] == ' ') {
            continue;
        } else {
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return 1;
        }
    }

    // якщо текст це пробіли і крапка
    if (!hasword) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }

    int totalwords = 0;
    char **words = splitWords(text, totalwords);

    int option = -1;
    do {
        printf("\nВиберіть дію:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &option) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            while (getchar() != '\n');
            option = -1;
            continue;
        }
        while (getchar() != '\n'); // очищаємо \n після числа, щоб наступні fgets/cin працювали чисто

        switch (option) {
            case 1:
                showStatistics(text, totalwords);
                break;
            case 2:
                showWordTable(words, totalwords);
                break;
            case 3:
                replaceWord(text, words, totalwords);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                inputNewSentence(text, words, totalwords);
                break;
            case 0:
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", option);
                break;
        }
    } while (option != 0);

    freeWords(words, totalwords);
    return 0;
}