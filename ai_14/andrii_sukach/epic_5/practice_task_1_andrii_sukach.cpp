/*
Задача: Редактор текстового повідомлення
Виконав: Сукач Андрій (ШІ-14)
*/
#include <string>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;

bool validText(const char *text);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextStats(const char *text, int &count);
void printMenu();
void wordList(char **words, int count);
void replaceWord(char *text, char **&words, int &wordCount);
bool isValidWord(const char *w);
void compareWords();
void symbolInfo(const char *text);
void newSentence(char *text,char **&words, int &wordCount);

int main(){
    char text[256];


    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    

    if (fgets(text, sizeof(text), stdin) != nullptr) {
    // Шукаємо символ нового рядка
    char *p = strchr(text, '\n');
    if (p != nullptr) {
        *p = '\0'; // Замінюємо \n на \0

    }
}


if (!validText(text)){
     printf("Ваш текст є неприпустимим; текст вважається припустимим, якщо він містить принаймні одне слово, складається лише з латинських літер, цифр і пробілів, а також закінчується крапкою.\n");
        return 1;
}



int wordCount = 0;
char **words = splitWords(text, wordCount);


int choice = -1;
do {
    printMenu();

    printf("Ваш вибір: ");
    if (scanf("%d", &choice) != 1) {// Очищаємо буфер від некоректних символі
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Помилка: введіть номер пункту меню.\n"); //
        continue;
    }

    // Очищаємо буфер від символу '\n'
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    switch (choice) {
        case 1:
          showTextStats(text, wordCount);
            break;
        case 2:
          wordList(words, wordCount);
            break;
        case 3:
           replaceWord(text, words, wordCount);
            break;
        case 4:
           compareWords();
            break;
        case 5:
            symbolInfo(text);
            break;
        case 6:
        newSentence(text, words, wordCount);
            break;
        case 0:
            break;
        default:
            printf("Помилка: пункту %d немає в меню.\n", choice); 
            break;
    }
} while (choice != 0);
printf("Вихід з програми....\n");
freeWords(words, wordCount);
return 0;

}

bool validText(const char *text){
    int len = strlen(text);
    bool hasWord = false;
    if (len == 0 || text[len - 1] != '.') return false;

    for (int i = 0; i < len - 1; i++){
      unsigned char ch = (unsigned char)text[i];
        if (!isalpha(ch) && !isdigit(ch) && ch != ' ') return false;
        if (isalpha((unsigned char)ch) || isdigit((unsigned char)ch)) hasWord = true;
    }

if (!hasWord) return false;
    return true;
}

char **splitWords(const char *text, int &count) {
    count = 0;
    char temp[256];
    strcpy(temp, text);

    // рахуємо кількість слів
    char *token = strtok(temp, " .");
    while (token != nullptr) {//ділить на слова
        count++;
        token = strtok(nullptr, " .");
    }

    //  Виділяємо масив вказівників під слова
    char **words = new char*[count];

    //  Знову копіюємо оригінал і записуємо кожне слово в динамічну пам'ять
    strcpy(temp, text);
    token = strtok(temp, " .");
    int i = 0;
    while (token != nullptr) {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        i++;
        token = strtok(nullptr, " .");
    }

    return words;
}

 void freeWords(char **&words, int &count){
    if (words == nullptr) return;
for (int i = 0; i < count; i++) {
    delete[] words[i];
}
     delete[] words;
    words = nullptr;
    count = 0;

 }

 void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;


    const char *ptr = text;
    while (*ptr != '\0') {
    if (isalpha((unsigned char)*ptr)) letters++;
    else if (isdigit((unsigned char)*ptr)) digits++;
    else if (*ptr == ' ') spaces++; 
    
    ptr++; // Зсуваємо вказівник на наступний символ у пам'яті
}

 }

void showTextStats(const char *text, int &count){
    int totalChars = strlen(text);

    int letters = 0; int digits = 0; int spaces = 0;
    countChars(text, letters, digits, spaces);

    double pLetters = (double)letters / totalChars * 100.0;
    double pDigits = (double)digits / totalChars * 100.0;
    double pSpaces = (double)spaces / totalChars * 100.0;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %5d\n", totalChars);
    printf("Слів:     %5d\n", count);
    printf("Літер:    %5d (%5.1f%%)\n", letters, pLetters);
    printf("Цифр:     %5d (%5.1f%%)\n", digits, pDigits);
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, pSpaces);
    
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

void wordList(char **words, int count) {
    //  Виводимо шапку таблиці
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    char *longestWord = words[0];
    char *shortestWord = words[0];
    int totalLength = 0;

    //  Таблиця слів, пошук найдовшого/найкоротшого та підрахунок суми довжин
    for (int i = 0; i < count; i++) {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);

        if (len > (int)strlen(longestWord)) {
            longestWord = words[i];
        }
        if (len < (int)strlen(shortestWord)) {
            shortestWord = words[i];
        }
        totalLength += len;
    }

    double avvLength = (double)totalLength / count;

    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", longestWord, (int)strlen(longestWord));
    printf("Найкоротше слово: %s (%d)\n", shortestWord, (int)strlen(shortestWord));
    printf("Середня довжина: %.2f\n", avvLength);

    //  Сортування за абеткою БЕЗ зміни порядку в масиві words
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];//перезапис
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) { //сортуваняя
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

    //  Пошук найчастішого слова
    char *mostFrequent = sorted[0];
    int maxFreq = 1;
    int currentFreq = 1;

    for (int i = 1; i < count; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0) {//посимвольна перевірка
            currentFreq++;
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
                mostFrequent = sorted[i];
            }
        } else {
            currentFreq = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxFreq);

    //  Звільняємо тимчасовий масив вказівників
    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &wordCount){
    char from[32], to[32];

    printf("Замінити слово: ");
    scanf("%31s", from);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Очищаємо буфер після scanf

    printf("Замінити на: ");
    scanf("%31s", to);
    while ((c = getchar()) != '\n' && c != EOF) {} 

   if (!isValidWord(from) || !isValidWord(to)) {
    printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
    return;
}

    string str = text;
    string fromStr = from;
    string toStr = to;

    int replace = 0;

    
// Захист на випадок, якщо замінюємо слово саме на себе 
    if (fromStr != toStr) {
        size_t pos = str.find(fromStr, 0);
        while (pos != string::npos) {
            // Перевіряємо, чи це ЦІЛЕ слово
            bool leftOk = (pos == 0 || str[pos - 1] == ' ');
            bool rightOk = (str[pos + fromStr.length()] == ' ' || str[pos + fromStr.length()] == '.');

            if (leftOk && rightOk) {
                str.replace(pos, fromStr.length(), toStr);
                replace++;
                pos += toStr.length();   // Зсуваємося за щойно вставлене слово
            } else {
                pos += fromStr.length(); // Не ціле слово — просто йдемо далі
            }

            pos = str.find(fromStr, pos); // Шукаємо наступне входження
        }
    }

    if (str.length() > 255) {
    printf("Помилка: після заміни текст перевищує 255 символів.\n");
    return;
}

    printf("Замін виконано: %d\n", replace);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", str.c_str());
    printf("Нова довжина: %d\n", (int)str.length());

strcpy(text, str.c_str());
freeWords(words, wordCount);
words = splitWords(text, wordCount);

}


bool isValidWord(const char *w) {
    int len = strlen(w);
    if (len == 0) return false;

    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)w[i];
        if (!isalpha(ch) && !isdigit(ch)) {
            return false;
        }
    }
    return true;
}

void compareWords(){
    char a[32], b[32];
    printf("Перше слово: ");
    scanf("%31s", a);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} //очистка
    printf("Друге слово: ");
    scanf("%31s", b);
    while ((c = getchar()) != '\n' && c != EOF) {} //очистка

    if (!isValidWord(a) || !isValidWord(b)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        return;
    }
    
    int lenA = strlen(a);
    int lenB = strlen(b);

    char lowA[32], lowB[32];
    //копія з маленькими буквами
    for (int i = 0; i <= lenA; i++) lowA[i] = tolower((unsigned char)a[i]);
    for (int i = 0; i <= lenB; i++) lowB[i] = tolower((unsigned char)b[i]);

    int cmp = strcmp(a, b);
    if (cmp == 0){
        printf("0 -> слова рівні\n");
    } else if (cmp > 0){
        printf("1 -> перше слово більше\n");
    }else if (cmp < 0){
        printf("-1 -> перше слово менше\n");
    }

    string sA = a, sB = b;
    if(sA == sB){
        printf("Рівні: так\n");
    } else printf("Рівні: ні\n");

    if(string(lowA) == string(lowB)){
        printf("Рівні без урахування регістру: Так\n");
    } else printf("Рівні без урахування регістру:НІ \n");


    string concat = sA + " & " + sB;
    printf("Довжини: %d і %d\n", lenA, lenB);
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}

void symbolInfo(const char *text){
printf("Введіть символ: ");
    int ch = getchar();
    if (ch == EOF) return;

    // Якщо без символу — беремо '\n',
    // інакше очищаємо залишок буфера до кінця рядка
    if (ch != '\n') {
        int tmp;
        while ((tmp = getchar()) != '\n' && tmp != EOF) {}
    }

    char c = (char)ch;// переведення типів щоб від'ємних не було
    unsigned char uc = (unsigned char)c;

    //  Виводимо сам символ та його коди у 4 системах числення
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", uc, uc, uc);
    for (int bit = 7; bit >= 0; bit--) {
        printf("%d", (uc >> bit) & 1);//зсуваємо число праворуч на bit позицій
    }
    printf(")\n");

    // Визначаємо тип символу та інший регістр (для літер)
    if (isupper(uc)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", (char)(uc + ('a' - 'A')));
    } else if (islower(uc)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)(uc - ('a' - 'A')));
    } else if (isdigit(uc)) {
        printf("Тип: цифра\n");
    } else if (isspace(uc)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    //  Наступний за кодом символ
    printf("Наступний символ: '%c'\n", (char)(uc + 1));

    //  Підрахунок входжень у тексті та позиція першого (нумерація з 1)
    int count = 0;
    int firstPos = -1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) {
            count++;
            if (firstPos == -1) {
                firstPos = i + 1;
            }
        }
    }

    if (count > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    } else {
        printf("Символ у тексті не зустрічається.\n");
    }
}


void newSentence(char *text,char **&words, int &wordCount){

string newText;
string word;
int readWords = 0;

printf("Введіть речення (крапка після останнього слова):\n");
while (cin >> word){

    if (!newText.empty()) {//пробіл перед словом (для подальшого підрахунку слів)
    newText += " ";
    }
    newText += word;
   if (word != ".") {
    readWords++;
}

    if(word[word.length() - 1] == '.'){
        break;
    }
}

int c;
while ((c = getchar()) != '\n' && c != EOF) {}

if(newText.length() > 255 || !validText(newText.c_str())){
    printf("Помилка: речення некоректне або перевищує 255 символів.\n");
    return;
}

printf("Прочитано слів: %d\n", readWords);
printf("Новий текст: \"%s\"\n", newText.c_str());
printf("Довжина: %d\n", (int)newText.length());

strcpy(text, newText.c_str());
freeWords(words, wordCount);
words = splitWords(text, wordCount);

}