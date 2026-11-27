/*Плахтина Дмитро
Ші-11
Редактор текстового повідомлення */
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
//Перевірка вводу
bool isValidText(char text[]) {
if (strlen(text) == 0) {
    printf("Помилка! Рядок не може бути порожнім! \n");
    return false;
}
if (text[strlen(text) - 1] != '.') {
    printf("Помилка! В кінці має стояти крапка! \n");
     return false;
}
bool hasWord = false;
for (int i = 0; i < strlen(text) - 1; i ++) {
    if (isalpha((unsigned char)text[i]) || isdigit((unsigned char)text[i])) {
        hasWord = true;
    } else if (text[i] == ' ') {
        continue;
    } else {
        printf("Помилка! Введіть текст правильно! \n");
        return false;
    }
}
if(!hasWord) {
    printf("Помилка! Введіть текст правильно! \n");
}
return hasWord;
}
//Показ меню
void showMenu() {
printf("\n========== МЕНЮ ==========\n");
printf("1. Показати текст і статистику\n");
printf("2. Таблиця слів\n");
printf("3. Замінити слово\n");
printf("4. Порівняти два слова\n");
printf("5. Інформація про символ\n");
printf("6. Ввести нове речення\n");
printf("0. Вийти\n");
printf("==========================\n");
printf("Ваш вибір: ");
}

//Розбиття тексту на слова
char **splitWords(const char *text, int &count) {
char textCopy[256];
strcpy(textCopy, text);
char *w = strtok(textCopy, " .");
count = 0;
while (w != NULL) {
    w = strtok(NULL, " .");
    count ++;
}
char **words = new char*[count];
strcpy(textCopy, text);
w = strtok(textCopy, " .");
int i = 0;
while (w != NULL) {
    words[i] = new char[strlen(w) + 1];
    strcpy(words[i], w);
    i ++;
    w = strtok(NULL, " .");
}
return words;
}

//Пункт 1
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0, digits = 0, spaces =0;
    const char *p = text;
    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            letters++;
        }
        if (isdigit((unsigned char)*p)) {
            digits++;
        }
        if (*p == ' ') {
            spaces++;
        }
        p++;
    }
}

void showStats(char text[], int count) {
    printf("Текст: \t\"%s\"\n", text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int symbols = strlen(text);
    printf("Символів: \t%3d\n", symbols);
    printf("Слів: \t\t%3d\n", count);
    printf("Літер: \t\t%3d (%5.1f%%)\n", letters, 100.0 * letters / symbols);
    printf("Цифр: \t\t%3d (%5.1f%%)\n", digits, 100.0 * digits / symbols);
    printf("Пробілів: \t%3d (%5.1f%%)\n", spaces, 100.0 * spaces / symbols);
}

//Пункт 2
void showWordTable(char **words, int count) {
    // 1. Таблиця
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i ++) {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    // Найдовше і найкоротше слово
    int longest = 0, shortest = 0;
    for (int i = 1; i < count; i ++) {
        if (strlen(words[i]) > strlen(words[longest])) {
            longest = i;
        }
        if (strlen(words[i]) < strlen(words[shortest])) {
            shortest = i;
        }
    }
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));

    // Середня довжина
    int sum = 0;
    for (int i = 0; i < count; i ++) {
        sum += strlen(words[i]);
    }
    printf("Середня довжина: %.2f\n", (double)sum / count);

    // Копія масиву вказівників, сортування бульбашкою, вивід
    char **sorted = new char*[count];
    for (int i = 0; i < count; i ++) {
        sorted[i] = words[i];
    }
    for (int i = 0; i < count - 1; i ++) {
        for (int j = 0; j < count - 1 - i; j ++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i ++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    //Найчастіше слово
    int best = 0, bestCount = 1;
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0) {
            j ++;
        }
        if (j - i > bestCount) {
            bestCount = j - i;
            best = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);

    delete[] sorted;
}
//Звільнення памʼяті
void freeWords(char **&words, int &count) {
    for(int i = 0; i < count; i ++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}
//Перевірка слова
bool isValidWord(const char w[]) {
    for(int i = 0; i < strlen(w); i ++) {
        if(!isalpha((unsigned char)w[i]) && !isdigit((unsigned char)w[i])) {
            printf("Помилка! Слово має складатися лише з латинських літер і цифр\n");
            return false;
        }
    }
    return true;
}

//Пункт 3
void replaceWord(char text[], char **&words, int &count) {
    char from[32], to[32];
    printf("Замінити слово: ");
    scanf("%31s", from);
    while (getchar() != '\n') { }
    if (!isValidWord(from)) {return;}

    printf("На слово: ");
    scanf("%31s", to);
    while (getchar() != '\n') { }
    if (!isValidWord(to)) {return;}

    string s = text;
    string f = from;
    string t = to;
    int replaced = 0;
    size_t pos = s.find(f);
    while (pos != string::npos) {
        size_t end = pos + f.length();
        bool leftOk = (pos == 0 || s[pos - 1] == ' ');
        bool rightOk = (end == s.length() || s[end] == ' ' || s[end] == '.');
        if (leftOk && rightOk) {
            s.replace(pos, f.length(), t);
            replaced ++;
            pos = s.find(f, pos + t.length());
        } else {
            pos = s.find(f, pos + 1);
        }
    }

    if (s.length() > 255) {
        printf("Помилка! Після заміни текст перевищить 255 символів. Текст не змінено\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, s.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)s.length());

    freeWords(words, count);
    words = splitWords(text, count);
}
//Пункт 4
void compareWords() {
    char first[32], second[32];
    printf("Перше слово: ");
    scanf("%31s", first);
    while (getchar() != '\n') { }
    if (!isValidWord(first)) {return;}
    printf("Друге слово: ");
    scanf("%31s", second);
    while (getchar() != '\n') { }
    if (!isValidWord(second)) {return;}
    int comres = strcmp(first, second);
    if (comres < 0) {
        printf ("strcmp: -1 -> перше слово менше\n");
    } else if (comres == 0) {
        printf ("strcmp: 0 -> слова рівні\n");
    } else {
        printf ("strcmp: 1 -> перше слово більше\n");
    }
string sa = first;
string sb = second;
if (sa == sb) {
    printf("Рівні (==): так\n");
} else {
    printf("Рівні (==): ні\n");
}
string copysa = first;
string copysb = second;
for (int i = 0; i < copysa.length(); i++) {
    if(copysa[i] > 64 && copysa[i] < 91) {
        copysa[i] += 32;
    }
}
for (int i = 0; i < copysb.length(); i++) {
    if(copysb[i] > 64 && copysb[i] < 91) {
        copysb[i] += 32;
    }
}
if (copysb == copysa) {
    printf("Рівні без урахування регістру: так\n");
} else {
    printf("Рівні без урахування регістру: ні\n");
}
int lenfirst = sa.length();
int lensec = sb.length();
printf("Довжини: %d і %d\n", lenfirst, lensec);
string joined = sa + " & " + sb;
printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}
//Пункт 5
void symbolInfo(const char text[]) {
    char c;
    printf("Введіть символ: ");
    scanf("%c", &c);
    if (c != '\n') {
        while (getchar() != '\n') { }
    }
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", c, c, c);
    for(int i = 7; i >= 0; i--) {
        int bincode = (c >> i) & 1;
        printf("%d", bincode);
    }
    printf(")\n");
    if(c >= 'a' && c <= 'z') {
        printf("Тип: мала літера\n");
    } else if (c >= 'A' && c <= 'Z'){
        printf("Тип: велика літера\n");
    } else if(c >= '0' && c <= '9' ) {
        printf("Тип: цифра\n");
    } else if (isspace((unsigned char)c)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }
    if (c >= 'a' && c <= 'z') {
        printf("Інший регістр: '%c'\n", c - 32);
    } else if (c >= 'A' && c <= 'Z') {
        printf("Інший регістр: '%c'\n", c + 32);
    }
    printf("Наступний символ: '%c'\n", c + 1);
    int count = 0;
    for(int i = 0; i < strlen(text); i ++) {
        if (text[i] == c) {
            count++;
        }
    }
    const char *first = strchr(text, c);
    if (count > 0 && first != NULL) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, (int)(first - text) + 1);
    } else {
        printf("Символ у тексті не зустрічається\n");
    }
}
//Пункт 6
void newSentence(char text[], char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence;
    string word;
    int n = 0;
    while (true) {
        if (!(cin >> word)) {
            break;
        }
        if (n > 0) {
            sentence += " ";
        }
        sentence += word;
        n ++;
        if (word[word.length() - 1] == '.') {
            break;
        }
    }
    while (getchar() != '\n') { }

    if (sentence.length() > 255) {
        printf("Помилка! Речення довше за 255 символів. Текст не змінено\n");
        return;
    }
    char buf[256];
    strcpy(buf, sentence.c_str());
    if (!isValidText(buf)) {
        printf("Текст не змінено\n");
        return;
    }

    strcpy(text, buf);
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", n);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

int main() {
char text[256];
printf("Введіть текст (до 255 символів, крапка в кінці):\n");
fgets(text, 256, stdin);
char* t = strchr(text, '\n');
if (t != NULL) {
   *t = '\0'; 
} else {
    int c = getchar();
    if (c != '\n' && c != EOF) {
        printf("Помилка! Текст довший за 255 символів! \n");
        return 1;
    }
}
if (!isValidText(text)) {
    printf("Помилка: текст має складатися з латинських літер, цифр\n");
    printf("і пробілів та завершуватися крапкою.\n");
    return 1;
}
int count = 0;
char **words = splitWords(text, count);

int choice = -1;
do {
showMenu();
int result = scanf("%d", &choice);
if (result == EOF) {
    break;
}
bool extra = false;
int ch = getchar();
while (ch != '\n' && ch != EOF) {
    if (ch != ' ') {
        extra = true;
    }
    ch = getchar();
}

if (result != 1 || extra) {
    printf("Помилка: введіть номер пункту меню.\n");
    choice = -1;
    continue;
}

switch (choice) {
    case 1:
        showStats(text, count);
        break;
    case 2:
        showWordTable(words, count);
        break;
    case 3:
        replaceWord(text, words, count);
        break;
    case 4:
        compareWords();
        break;
    case 5:
        symbolInfo(text);
        break;
    case 6:
        newSentence(text, words, count);
        break;
    case 0:
        printf("До побачення!\n");
        break;
    default:
        printf("Помилка: пункту %d немає в меню.\n", choice);
        break;
}
} while (choice != 0);
freeWords(words, count);
    return 0;
}