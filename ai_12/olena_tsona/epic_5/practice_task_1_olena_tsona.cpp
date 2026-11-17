#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

void clearInput();
bool isValidText(const char *text);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextAndStatistic(const char *text, int wordCount);
void wordsTable(char **words, int wordCount);
void replaceWord(char **&words, char *text, int &wordCount);
void compareWords();
void symbolInfo(const char *text);
void newSentence(char *text, char **&words, int &wordCount);

int main() {

    char text[256];
    int choice;
    char **words = nullptr;
    int wordCount = 0;

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    char *readText = fgets(text, sizeof(text), stdin);
    if (readText == nullptr) {
        printf("Помилка: текст не введено.\n");
        return 1;
    }

    size_t len = strcspn(text, "\n");
    bool hadNewline = (text[len] == '\n');                    
    text[len] = '\0';                                         

    if (!hadNewline) {
        int next = getchar();
        if (next != '\n' && next != EOF) {                    
            printf("Помилка: текст довший за 255 символів.\n");
            return 1;
        }
    }
    
    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 1;
    }
    
    words = splitWords(text, wordCount);



    choice = -1;
    do {
        printf("Меню\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n\n");
        printf("Ваш вибір: ");

        int read = (scanf("%d", &choice));
        clearInput();
        if ( read == EOF) {              
            choice = 0;
            
            
        }

        if(!read) {
            printf("Помилка: введіть номер пункту меню.\n" );
            choice = -1;
            continue;

        }
        



        switch (choice) {
            case 1: 
                showTextAndStatistic(text, wordCount);
                break;
            case 2:
                wordsTable(words, wordCount);
                break;
            case 3:
                replaceWord(words, text, wordCount);
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
                printf("Вихід...\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);



        }



    }while(choice != 0);

    freeWords(words, wordCount);

    return 0;



}

void clearInput() {
    int ch = getchar();
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

bool isValidText(const char *text) {
    size_t len = strlen(text);
    if (len == 0 || text[len - 1] != '.') return false;      // 1

    bool hasWord = false;
    for (const char *p = text; p < text + len - 1; p++) {
        unsigned char c = *p;
        if (isalpha(c) || isdigit(c)) {                                    
            hasWord = true;
        } else if (c != ' ') {                               
            return false;
        }
    }
    return hasWord;                                              
}
bool isValidWord(const char *word) {
    size_t len = strlen(word);
    if (len == 0 || len > 31) {
        
        return false;
    }
    for (const char *p = word; *p != '\0'; p++) {
        unsigned char c = *p;
        if (!(isalpha(c) || isdigit(c))) {
            
            return false;
        }
    }
    return true;

}
bool readWord(const char *prompt, char *word, int size) {
    printf("%s", prompt);
    if (fgets(word, size, stdin) == nullptr) return false;
    bool hadNewline = (strchr(word, '\n') != nullptr);
    word[strcspn(word, "\n")] = '\0';
    if (!hadNewline) clearInput();               
    return hadNewline && isValidWord(word);
}
char **splitWords(const char *text, int &count) {
    count = 0;

    char *copy = new char[strlen(text) + 1];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';                  

    char **words = new char*[127];

    char *token = strtok(copy, " ");               
    while (token != nullptr && count < 127) {
        words[count] = new char[strlen(token) + 1];              
        strcpy(words[count], token);
        count++;
        token = strtok(NULL, " ");                  
    }

    delete[] copy;
    return words;
}
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i];                               
    }
    delete[] words;                                   
    words = nullptr;
    count = 0;
}
void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;                     
    for (const char *p = text; *p != '\0'; p++) {         
        unsigned char c = *p;                           
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {                                
            digits++;
        } else if (isspace(c)) {                                
            spaces++;
        }
    }
}
void showTextAndStatistic(const char *text, int wordCount){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);                              

    printf("Текст: \t\"%s\"\n", text);
    printf("Символів: %5zu\n", strlen(text)); 
    printf("Слів:     %5d\n", wordCount);
    printf("Літер:    %5d (%5.1f%%)\n", letters, double(letters)*100/double(strlen(text))); 
    printf("Цифр:     %5d (%5.1f%%)\n", digits, double(digits)*100/double(strlen(text))); 
    printf("Пробілів: %5d (%5.1f%%)\n\n", spaces, double(spaces)*100/double(strlen(text)));
    
}
void printTableLine(int numWidth, int wordWidth) {
    printf("+");
    for (int i = 0; i < numWidth + 2; i++) printf("-");
    printf("+");
    for (int i = 0; i < wordWidth + 2; i++) printf("-");
    printf("+-------+\n");
}

void wordsTable(char **words, int wordCount) {
    if (words == nullptr || wordCount == 0) return;

    int longest = 0, shortest = 0, total = 0;
    for (int i = 0; i < wordCount; i++) {
        int len = (int)strlen(words[i]);
        total += len;
        if (len > (int)strlen(words[longest])) longest = i;
        if (len < (int)strlen(words[shortest])) shortest = i;
    }

    int wordWidth = 15;
    if ((int)strlen(words[longest]) > wordWidth) {
        wordWidth = (int)strlen(words[longest]);
    }
    int numWidth = (wordCount >= 100) ? 3 : 2;

    // printf рахує байти, а не літери, тому для шапки кирилицею пробіли додаєм циклом.
    printTableLine(numWidth, wordWidth);
    printf("| N");
    for (int i = 1; i < numWidth; i++) printf(" ");
    printf(" | Слово");
    for (int i = 5; i < wordWidth; i++) printf(" ");
    printf(" | Довж. |\n");
    printTableLine(numWidth, wordWidth);

    for (int i = 0; i < wordCount; i++) {
        printf("| %*d | %-*s | %5d |\n", numWidth, i + 1, wordWidth, words[i], (int)strlen(words[i]));
    }
    printTableLine(numWidth, wordWidth);

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)total / wordCount);

    
    char **sorted = new char*[wordCount];
    for (int i = 0; i < wordCount; i++) sorted[i] = words[i];

    for (int i = 0; i < wordCount - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < wordCount; j++) {
        if (strcmp(sorted[j], sorted[minIndex]) < 0) {
            minIndex = j;
        }
    }
    if (minIndex != i) {
        char *tmp = sorted[i];
        sorted[i] = sorted[minIndex];
        sorted[minIndex] = tmp;
    }
}
    

    printf("За абеткою:");
    for (int i = 0; i < wordCount; i++) printf(" %s", sorted[i]);
    printf("\n");

    const char *bestWord = sorted[0];
    int bestRun = 0;
    int i = 0;
    while (i < wordCount) {
        int j = i;
        while (j < wordCount && strcmp(sorted[i], sorted[j]) == 0) j++;
        if (j - i > bestRun) {
            bestRun = j - i;
            bestWord = sorted[i];
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n\n", bestWord, bestRun);

    delete[] sorted;        
}

void replaceWord( char **&words,  char *text, int &wordCount ) {
    char buf1[33];
    char buf2[33];
    if (!readWord("Замінити слово: ", buf1, sizeof(buf1)) || !readWord("На слово: ", buf2, sizeof(buf2))) {
        printf("Помилка: слово має складатися з 1-31 латинських літер і цифр.\n");
        return;
    }

    buf1[strcspn(buf1, "\n")] = '\0';
    buf2[strcspn(buf2, "\n")] = '\0';

    string s = text;
    string from = buf1;
    string to = buf2;
    int replaced = 0;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos) {
        size_t end = pos + from.length();
        bool startOk = (pos == 0 || s[pos - 1] == ' ');                       
        bool endOk = (end == s.length() || s[end] == ' ' || s[end] == '.');   
        if (startOk && endOk) {
            s.replace(pos, from.length(), to);                               
            pos += to.length();                                                       
            replaced++;
        } else {
            pos++;
        }
    }
    if (s.length() > 255) {
    printf("Помилка: результат довший за 255 символів. Текст не змінено.\n");
    return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, s.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));

    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

}
bool equalIgnoreCase(const string &a, const string &b) {
    if (a.length() != b.length()) return false;                                          
    for (size_t i = 0; i < a.length(); i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false; 
    }
    return true;                                                                        
}
void compareWords() {
    char buf1[33];
    char buf2[33];
    
    if (!readWord("Перше слово: ", buf1, sizeof(buf1)) || !readWord("Друге слово: ", buf2, sizeof(buf2))) {
        printf("Помилка: слово має складатися з 1-31 латинських літер і цифр.\n");
        return;
    }

    string a = buf1;                                 
    string b = buf2;

    int r = strcmp(buf1, buf2);

    int sign;
    const char *explain;
    if (r < 0) {
        sign = -1;
        explain = "перше слово менше";
    } else if (r > 0) {
        sign = 1;
        explain = "перше слово більше";
    } else {
        sign = 0;
        explain = "слова збігаються";
    }
    printf("strcmp: %d -> %s\n", sign, explain);


    bool equal = (a == b);                 
    printf("Рівні (==): ");
    if (equal) {
        printf("так\n");
    } else {
        printf("ні\n");
    }

    bool equalNoCase = equalIgnoreCase(a, b);
    printf("Рівні без урахування регістру: ");
    if (equalNoCase) {
        printf("так\n");
    } else {
        printf("ні\n");
    }

    int lenA = (int)a.length();
    int lenB = (int)b.length();
    printf("Довжини: %d і %d\n", lenA, lenB);


    string concatenation = a + " & " + b;
    printf("Конкатенація: \"%s\" (%d)\n\n", concatenation.c_str(), (int)concatenation.length());
    

}
void symbolInfo( const char *text) {
    char buffer[256];

    printf("Введіть символ: ");
    if(fgets(buffer, sizeof(buffer), stdin) == nullptr || buffer[0] == '\n')
    {
        printf("Символ не введено.\n");
        return;
    }
    if (buffer[1] != '\n' && buffer[1] != '\0')
    {
        if (strchr(buffer, '\n') == nullptr)        
        {
            char rest[256];
            while (fgets(rest, sizeof(rest), stdin) != nullptr && strchr(rest, '\n') == nullptr) {}
        }
        printf("Помилка: введіть один символ.\n");
        return;

    }
    char symbol = buffer[0];
    unsigned int code = (unsigned char)symbol;

    printf("Символ: '%c'\n", symbol);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code); 


    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (code >> i) & 1);
    }
    printf(")\n");

    if (isupper(code))      printf("Тип: велика літера\n");
    else if (islower(code)) printf("Тип: мала літера\n");
    else if (isdigit(code)) printf("Тип: цифра\n");
    else if (isspace(code)) printf("Тип: пробільний символ\n");
    else                    printf("Тип: інший символ\n");


    if (isalpha(code))
    {
        if (isupper(code)) printf("Інший регістр: '%c'\n", tolower(code));
        else               printf("Інший регістр: '%c'\n", toupper(code));

        printf("Наступний символ: '%c'\n", symbol + 1);
    }

    
    int count = 0, first = 0;   //пошук входжень
    for (const char *p = strchr(text, symbol); p != nullptr; p = strchr(p + 1, symbol)) {
        if (count == 0) {
            first = (int)(p - text) + 1;
            }     
        count++;
    }
    if (count == 0) printf("Символ у тексті не зустрічається.\n");
    else            printf("Входжень у тексті: %d, перше на позиції %d\n\n", count, first);

}
void newSentence(char *text, char **&words, int &wordCount) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string w;
    string sentence;
    int wordsRead = 0;
    bool finished = false;

    while (cin >> w) {
        wordsRead++;
        if (sentence.length() <= 255) {        
            if (!sentence.empty()) {
                sentence += " ";
            } 
            sentence += w;
        }
        if (w[w.length() - 1] == '.') {        
            finished = true;
            break;
        }
    }
    if (!finished) {
        cin.clear();                           
        printf("Помилка: введення закінчилось до крапки. Текст не змінено.\n\n");
        return;
    }
    clearInput();                               

    if (sentence.length() > 255 || !isValidText(sentence.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        printf("\n");
        return;
    }

    strcpy(text, sentence.c_str());             
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n\n", (int)strlen(text));
}
