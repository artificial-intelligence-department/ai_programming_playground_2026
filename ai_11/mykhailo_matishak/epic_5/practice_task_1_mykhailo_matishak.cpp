/*Епік 5. Задача: Редактор текстових повідомлень
Автор: Матішак Михайло
Група: ШІ-11*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

void prompt(const char *text){
    printf("%s", text);
    fflush(stdout);
}

bool isValidWord(const char *word){
    int len = strlen(word);
    if(len < 1 || len > 31){
        return false;
    }
    for(int i = 0; i < len; i++){
        if(!isalnum((unsigned char)word[i])){
            return false;
        }
    }
    return true;
}

bool isValidText(const char *text){
    int len = strlen(text);
    if(len < 2 || text[len - 1] != '.'){
        return false;
    }
    if(!isalnum((unsigned char)text[0]) || !isalnum((unsigned char)text[len - 2])){
        return false;
    }
    for(int i = 0; i < len - 1; i++){
        if(!isalnum((unsigned char)text[i]) && text[i] != ' '){
            return false;
        }
    }
    return true;
}

bool isNumber(const char *s){
    int len = strlen(s);
    if(len < 1 || len > 5){
        return false;
    }
    for(int i = 0; i < len; i++){
        if(!isdigit((unsigned char)s[i])){
            return false;
        }
    }
    return true;
}

int toNumber(const char *s){
    int num = 0;
    for(int i = 0; s[i] != '\0'; i++){
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

bool equalIgnoreCase(const char *a, const char *b){
    if(strlen(a) != strlen(b)){
        return false;
    }
    for(int i = 0; a[i] != '\0'; i++){
        if(tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])){
            return false;
        }
    }
    return true;
}

char **splitWords(const char *text, int &count){
    char buf[256];
    strcpy(buf, text);
    int len = strlen(buf);
    buf[len - 1] = '\0';

    char copy[256];
    strcpy(copy, buf);
    count = 0;
    char *token = strtok(copy, " ");
    while(token != nullptr){
        count++;
        token = strtok(nullptr, " ");
    }
    char **words = new char*[count];
    strcpy(copy, buf);
    token = strtok(copy, " ");
    for(int i = 0; i < count; i++){
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(nullptr, " ");
    }
    return words;
}

void freeWords(char **&words, int &count){
    for(int i = 0; i < count; i++){
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
    const char *p = text;
    while(*p != '\0'){
        if(isalpha((unsigned char)*p)){
            letters++;
        }
        else if(isdigit((unsigned char)*p)){
            digits++;
        }
        else if(*p == ' '){
            spaces++;
        }
        p++;
    }
}

void showStats(const char *text, int count){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:    %d\n", len);
    printf("Слів:        %d\n", count);
    printf("Літер:       %d (%5.1f%%)\n", letters, letters * 100.0 / len);
    printf("Цифр:        %d (%5.1f%%)\n", digits, digits * 100.0 / len);
    printf("Пробілів:    %d (%5.1f%%)\n", spaces, spaces * 100.0 / len);
}
void showTable(char **words, int count){
    int longest = 0;
    int shortest = 0;
    int total = 0;

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for(int i = 0; i < count; i++){
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        total = total + len;
        if(len > (int)strlen(words[longest])){
            longest = i;
        }
        if(len < (int)strlen(words[shortest])){
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");

    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (float)total / count);

    char **sorted = new char*[count];
    for(int i = 0; i < count; i++){
        sorted[i] = words[i];
    }
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            if(strcmp(sorted[j], sorted[j + 1]) > 0){
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    printf("За абеткою:");
    for(int i = 0; i < count; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");
    int bestCount = 0;
    int bestIndex = 0;
    for(int i = 0; i < count; i++){
        int same = 0;
        for(int j = 0; j < count; j++){
            if(strcmp(sorted[i], sorted[j]) == 0){
                same++;
            }
        }
        if(same > bestCount){
            bestCount = same;
            bestIndex = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);

    delete[] sorted;
}

void replaceWord(char *text, char **&words, int &count){
    char from[256];
    char to[256];

    prompt("Замінити слово: ");
    scanf("%255s", from);
    prompt("На слово: ");
    scanf("%255s", to);

    if(!isValidWord(from)){
        printf("Помилка: слово для заміни має складатися з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    if(!isValidWord(to)){
        printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
        return;
    }
    string fromStr = from;
    string toStr = to;
    string result = text;
    int replaced = 0;
    size_t pos = result.find(fromStr);
    while(pos != string::npos){
        size_t after = pos + fromStr.length();
        bool leftOk = (pos == 0) || !isalnum((unsigned char)result[pos - 1]);
        bool rightOk = (after >= result.length()) || !isalnum((unsigned char)result[after]);
        if(leftOk && rightOk){
            result.replace(pos, fromStr.length(), toStr);
            replaced++;
            pos = result.find(fromStr, pos + toStr.length());
        }
        else{
            pos = result.find(fromStr, pos + 1);
        }
    }
    if(replaced == 0){
        printf("Слово не знайдено. Текст не змінено.\n");
        return;
    }
    if(result.length() > 255){
        printf("Помилка: після заміни текст перевищив би 255 символів. Текст не змінено.\n");
        return;
    }
    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, result.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));

    freeWords(words, count);
    words = splitWords(text, count);
}
void compareWords(){
    char a[256];
    char b[256];

    prompt("Перше слово: ");
    scanf("%255s", a);
    prompt("Друге слово: ");
    scanf("%255s", b);

    if(!isValidWord(a) || !isValidWord(b)){
        printf("Помилка: слова мають складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    int res = strcmp(a, b);
    if(res < 0){
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if(res == 0){
        printf("strcmp: 0 -> слова однакові\n");
    }
    else{
        printf("strcmp: 1 -> перше слово більше\n");
    }
    string sa = a;
    string sb = b;
    printf("Рівні (==): %s\n", (sa == sb) ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", equalIgnoreCase(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());

    string concat = sa + " & " + sb;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}

void charInfo(const char *text){
    char token[256];
    char c;
    int code;

    prompt("Введіть символ: ");
    scanf("%255s", token);
    if(strlen(token) != 1){
        printf("Помилка: введіть рівно один символ.\n");
        return;
    }
    c = token[0];
    code = (unsigned char)c;
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", code, code, code);
    for(int i = 7; i >= 0; i--){
        printf("%d", (code >> i) & 1);
    }
    printf(")\n");
    printf("Тип: ");
    if(isupper((unsigned char)c)){
        printf("велика літера\n");
    }
    else if(islower((unsigned char)c)){
        printf("мала літера\n");
    }
    else if(isdigit((unsigned char)c)){
        printf("цифра\n");
    }
    else if(isspace((unsigned char)c)){
        printf("пробільний символ\n");
    }
    else{
        printf("інший символ\n");
    }

    if(isalpha((unsigned char)c)){
        if(isupper((unsigned char)c)){
            printf("Інший регістр: '%c'\n", tolower((unsigned char)c));
        }
        else{
            printf("Інший регістр: '%c'\n", toupper((unsigned char)c));
        }
    }
    printf("Наступний символ: '%c'\n", c + 1);

    const char *first = strchr(text, c);
    if(first == nullptr){
        printf("Символ '%c' у тексті відсутній.\n", c);
        return;
    }
    int occurrences = 0;
    const char *p = first;
    while(p != nullptr){
        occurrences++;
        p = strchr(p + 1, c);
    }
    printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
}

void newSentence(char *text, char **&words, int &count){
    string word;
    string sentence = "";
    int wordCount = 0;
    bool finished = false;

    printf("Введіть речення (крапка після останнього слова):\n");
    while(!finished && cin >> word){
        if(word[word.length() - 1] == '.'){
            finished = true;
            word = word.substr(0, word.length() - 1);
        }
        if(word.length() > 0){
            if(wordCount > 0){
                sentence = sentence + " ";
            }
            sentence = sentence + word;
            wordCount++;
        }
    }
    if(!finished){
        cin.clear();
        printf("Помилка: речення має завершуватися крапкою. Текст не змінено.\n");
        return;
    }
    sentence = sentence + ".";
    if(sentence.length() > 255){
        printf("Помилка: речення довше 255 символів. Текст не змінено.\n");
        return;
    }
    if(!isValidText(sentence.c_str())){
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою. Текст не змінено.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void printMenu(){
    printf("===Меню===\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    prompt("Ваш вибір: ");
}

int main(){
    char text[256];
    char token[256];
    char **words = nullptr;
    int count = 0;
    int choice = -1;
    bool tooLong = false;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    text[0] = '\0';
    fgets(text, 256, stdin);

    int len = strlen(text);
    if(len > 0 && text[len - 1] == '\n'){
        text[len - 1] = '\0';
    }
    else{
        int c = getchar();
        while(c != '\n' && c != EOF){
            tooLong = true;
            c = getchar();
        }
    }
    if(tooLong){
        printf("Помилка: текст довший за 255 символів.\n");
        return 0;
    }
    if(!isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр\n");
        printf("і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    words = splitWords(text, count);
    do{
        printMenu();
        if(scanf("%255s", token) != 1){
            choice = 0;
        }
        else if(isNumber(token)){
            choice = toNumber(token);
        }
        else{
            choice = -1;
        }

        switch(choice){
            case 0:
                printf("Роботу програми завершено.\n");
                break;
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
            case -1:
                printf("Помилка: введіть номер пункту меню.\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    }
    while(choice != 0);

    freeWords(words, count);
    return 0;
}