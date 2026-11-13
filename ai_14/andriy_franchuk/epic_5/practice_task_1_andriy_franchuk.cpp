#include <iostream>
#include <stdio.h>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;

const int Max_size = 255;

int input(char s[]);
bool validText(char s[]);
bool valid(char s[]);
bool latin(char c);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void option1(char *text, int count);
void option2(char **words, int count);
void option3(char *text, char **&words, int &count);
void option4();
void option5(char *text);
void option6(char *text, char **&words, int &count);
bool equalIgnoreCase(string w1, string w2);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void minmax(char** words, int n, int &min, int &max, char *min_word, char *max_word);
void sort(char **words, int count);
void swap(char *a, char *b);
void popular(char **words, int count);

int main(){
    int count;
    char text[Max_size+1];
    printf("%s", "Введіть текст (до 255 символів, крапка в кінці):\n");
    int rc = input(text);

    if (rc == -1){
        printf("Помилка: порожній ввід.\n");
        return 1;
    }else if(rc == 0 || !validText(text)){
        printf("Помилка: текст має скаладатися менш ніж з 255 символів(латинських літер, цифр і пробілів) та завершуватись крапкою.\n");
        return 1;
    }

    char **words = splitWords(text, count);

    int choice = -1;
    do{
        printf("\nМеню:\n1. Показати текст і статистику\n2. Таблиця слів\n3. Замінити слово\n4. Порівняти два слова\n5. Інформація про символ\n6. Ввести нове речення\n0. Вийти\n");
        if(scanf("%d", &choice) != 1){
            choice = -1;
        }
        while(getchar() !='\n');

        switch (choice)
        {
        case 0:
            break;
        case 1:
            option1(text, count);
            break;
        case 2:
            option2(words, count);
            break;
        case 3:
            option3(text, words, count);
            break;
        case 4:
            option4();
            break;
        case 5:
            option5(text);
            break;
        case 6:
            option6(text, words, count);
            break;
        default:
            printf("Помилка, введіть числове значення від 0 до 6.");
            break;
        }
    }while(choice != 0);
    freeWords(words, count);
}

int input(char t[]){
    if (!fgets(t, Max_size+1, stdin)){
        return -1;
    }
    return 1;
}

bool validText(char s[]){
    int len = strlen(s);

    if(len < 3 || s[len-1] != '\n' || s[len-2] != '.'){
        return 0;
    }

    for(int i = 0; i < len - 2; i++){
        char c = s[i];
        if(!latin(c)&&!isdigit(c)&&(c!=' ')){
            return 0;
        }
    }

    s[len - 1] = '\0';

    return 1;
}

bool latin(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char **splitWords(const char *text, int &count){
    char buf[Max_size+1];
    strcpy(buf, text);
    char **words = new char*[Max_size+1];
    count = 0;
    char *t = strtok(buf, " ");
    while (t != NULL) {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }
    words[count-1][strlen(words[count-1]) - 1] = '\0';
    return words;
}

void option1(char *text, int count){
    printf("Текст:\t\"");
    int len = strlen(text);
    int digits = 0;
    int letters = 0;
    int spaces = 0;
    for(int i = 0; i < len; i++){
        printf("%c", text[i]);
    }
    countChars(text, letters, digits, spaces);

    printf("\"\n");
    printf("Символів:\t%d\n", len);
    printf("Слів:\t\t%d\n", count);
    printf("Літер:\t\t%d ( %.1f%%)\n", letters, (float)letters/len*100);
    printf("Цифр:\t\t%d ( %.1f%%)\n", digits, (float)digits/len*100);
    printf("Пробілів:\t%d ( %.1f%%)\n", spaces, (float)(spaces)/len*100);
}

void option2(char **words, int count){
    printf("+----+-----------------+-------+\n| N  | Слово           | Довж. |\n+----+-----------------+-------+\n");
    for(int i = 0; i < count; i++){
        printf("|%3d | %-16s| %5zu |\n", i+1, words[i], strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    int sum_len = 0;
    int min, max;
    char min_word[Max_size], max_word[Max_size];
    for(int i = 0; i < count; i++){
        sum_len += strlen(words[i]);
    }

    minmax(words, count, min, max, min_word, max_word);

    printf("Найдовше слово: %s (%d)\n", max_word, max);
    printf("Найкоротше слово: %s (%d)\n", min_word, min);
    printf("Середня довжина: %.2f\n", (float)sum_len/count);

    sort(words, count);
    popular(words, count);
}

void option3(char *text, char **&words, int &count){
    printf("Замінити слово: ");
    char word1[Max_size], word2[Max_size];
    if(input(word1) != 1 || !valid(word1)){
        printf("Неправильний ввід\n");
        return;
    }

    printf("На слово: ");
    if(input(word2) != 1 || !valid(word2)){
        printf("Неправильний ввід\n");
        return;
    }

    int len = strlen(text);
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int counter = 0;

    string t = text;
    string w1 = word1;
    string w2 = word2;

    size_t pos = t.find(w1, 0);

    while(pos != string::npos){
        if(!(pos == 0 || t[pos-1] == ' ') || !(t[pos + len1] == ' ' || t[pos + len1] == '.')){
            pos = t.find(w1, pos+1);
            continue;
        }

        len += len2 - len1;

        if(len > 255){
            printf("Помилка: після заміни слів текст перевищив би 255 символів.\n");
            return;
        }
        counter++;

        t.replace(pos, len1, w2);

        pos = t.find(w1, pos+len2);
    }
    printf("Замін виконано: %d\n", counter);
    printf("Було:  %s\n", text);
    strcpy(text, t.c_str());
    printf("Стало: %s\n", text);
    printf("Нова довжина: %d\n", len);

    freeWords(words, count);
    words = splitWords(text, count);
}

void option4(){
    printf("Перше слово: ");
    char w1[Max_size], w2[Max_size];
    if(input(w1) != 1 || !valid(w1)){
        printf("Неправильний ввід\n");
        return;
    }

    printf("Друге слово: ");
    if(input(w2) != 1 || !valid(w2)){
        printf("Неправильний ввід\n");
        return;
    }

    int cmp = strcmp(w1, w2);
    if (cmp < 0){
        cmp = -1;
    }else if (cmp > 0){
        cmp = 1;
    } 
    printf("strcmp: %d -> перше слово ", cmp);
    if(cmp == -1){
        printf("менше\n");
    }else if(cmp == 0){
        printf("рівне\n");
    }else{
        printf("більше\n");
    }

    string w1_s = w1;
    string w2_s = w2;

    bool equal = w1_s == w2_s;
    printf("Рівні (==): ");
    if(equal){
        printf("так\n");
    }else{
        printf("ні\n");
    }

    printf("Рівні без урахування регістру: ");
    if(equalIgnoreCase(w1, w2)){
        printf("так\n");
    }else{
        printf("ні\n");
    }

    printf("Довжини: %zu і %zu\n", w1_s.length(), w2_s.length());
    string result = w1_s + " & " + w2_s;
    printf("Конкатенація: \"%s\" (%zu)", result.c_str(), result.length());
}

void option5(char *text){
    char line[16];
    printf("Введіть символ: ");
    if(input(line) != 1 || strlen(line) != 2 || (unsigned char)line[0] > 127){
        printf("Неправильний ввід\n");
        return;
    }

    unsigned char c = (unsigned)line[0];
    if(isprint(c)){
        printf("Символ: '%c'\n", c);
    } else {
        printf("Символ: (недрукований)\n");
    }

    printf("Код: %d (hex 0x%02x, oct 0%o, bin ", c, c,  c);
    for (int i = 7; i >= 0; i--){
        printf("%d", (c >> i)&1);
    }
    printf(")\n");

    printf("Тип: ");
    if (isupper(c)){
        printf("велика літера\n");
    } else if (islower(c)){
        printf("мала літера\n");
    } else if (isdigit(c)){
        printf("цифра\n");
    } else if (isspace(c)){
        printf("пробіл\n");
    } else {
        printf("інший символ\n");
    }

    if (isalpha(c)){
        if(islower(c)){
            printf("Інший регістр: '%c'\n", toupper(c));
        }else{
            printf("Інший регістр: '%c'\n", tolower(c));
        }
    }
    unsigned char next = c + 1;
    if (isprint(next)){
        printf("Наступний символ: '%c'\n", next);
    } else {
        printf("Наступний символ: (недрукований)\n");
    }

    int count = 0;
    const char *first = strchr(text, c);
    for (const char *p = first; p; p = strchr(p + 1, c)){
        count++;
    }
    if (count == 0){
        printf("У тексті цей символ не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, (int)(first - text) + 1);
    }
}

void option6(char *text, char **&words, int &count){
    char word[Max_size];
    char new_text[Max_size+1];
    int len = 0;
    printf("Введіть речення (крапка після останнього слова):\n");
    cin >> word;
    int len_word = strlen(word);
    for(int i = 0; i < len_word; i++){
            char c = word[i];
            if(!latin(c)&&!isdigit(c)&&c!='.'){
                printf("Неправильний ввід\n");
                return;
            }
        }
    int counter = 0;
    while(word[len_word-1] != '.'){
        if(len + len_word > 255){
            printf("Помилка: текст має скаладатися менш ніж з 255 символів(латинських літер, цифр і пробілів) та завершуватись крапкою.\n");
            return;
        }
        for(int i = 0; i < len_word; i++){
            new_text[len+i] = word[i];
        }
        len += len_word;
        new_text[len] = ' ';
        cin >> word;
        len_word = strlen(word);
        for(int i = 0; i < len_word; i++){
            char c = word[i];
            if(!latin(c)&&!isdigit(c)&&c!='.'){
                printf("Неправильний ввід\n");
                return;
            }
        }
        len++;
        counter++;
    }
    counter++;
    len_word = strlen(word);
    for(int i = 0; i < len_word; i++){
        new_text[len+i] = word[i];
    }
    len += len_word;
    new_text[len] = '\0';
    if(len > 255){
        printf("Помилка: текст має скаладатися менш ніж з 255 символів(латинських літер, цифр і пробілів) та завершуватись крапкою.\n");
        return;
    }

    printf("Прочитано слів: %d\n", counter);
    printf("Новий текст: \"%s\"\n", new_text);
    printf("Довжина: %zu\n", strlen(new_text));

    strcpy(text, new_text);
    freeWords(words, count);
    words = splitWords(text, count);
}

void countChars(const char *t, int &letters, int &digits, int &spaces){
    while(*t != '\0'){
        if(isalpha(*t)){
            letters += 1;
        } else if(isdigit(*t)){
            digits += 1;
        } else if(*t==' '){
            spaces += 1;
        }
        t++;
    }
}

void minmax(char** words, int n, int &min, int &max, char *min_word, char *max_word){
    min = strlen(words[0]);
    max = strlen(words[0]);
    strcpy(max_word, words[0]);
    strcpy(min_word, words[0]);
    for(int i = 1; i < n; i++){
        if(strlen(words[i]) > max){
            max = strlen(words[i]);
            strcpy(max_word, words[i]);
        } else if(strlen(words[i]) < min){
            min = strlen(words[i]);
            strcpy(min_word, words[i]);
        }
    }
}

void swap(char *a, char *b) {
    char temp[Max_size];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void sort(char **words, int count){
    char **buf = new char*[count];

    for (int i = 0; i < count; i++) {
        buf[i] = new char[Max_size];
        strcpy(buf[i], words[i]);
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (strcmp(buf[j], buf[j+1]) > 0){
                swap(buf[j], buf[j+1]);
            }
        }
    }
    printf("За абеткою: ");
    for (int i = 0; i < count; i++) {
        printf("%s ", buf[i]);
    }
    printf("\n");

    int n = count;
    freeWords(buf, n);
}

void popular(char **words, int count){
    int max = 0;
    char word[Max_size];
    strcpy(word, words[0]); 
    for(int i = 0; i < count; i++){
        int counter = 0;
        for(int j = i; j < count; j++){
            if(strcmp(words[i], words[j])==0){
                counter += 1;
            }
        }
        if(counter >= max){
            if(max == counter && strcmp(word, words[i]) > 0){
                continue;
            }
            max = counter;
            strcpy(word, words[i]);
        }
    }
    printf("Найчастіше слово: %s (%d)\n", word, max);
}

bool valid(char s[]){
    int len = strlen(s);
    if(s[0] == '\n'){
        return 0;
    }

    for(int i = 0; i < len - 1; i++){
        char c = s[i];
        if(!latin(c)&&!isdigit(c)){
            return 0;
        }
    }

    s[len - 1] = '\0';

    return 1;
}

bool equalIgnoreCase(string w1, string w2){
    if (w1.length() != w2.length()){
        return 0;
    }
    for (int i = 0; i < w1.length(); i++){
        if (tolower(w1[i]) != tolower(w2[i])){
            return 0;
        }
    }
    return 1;
}

void freeWords(char **&words, int &count) {
    for(int i = 0; i < count; i++){
        delete[] words[i];
        words[i] = nullptr;
    }
    delete[] words;
    words = nullptr;
    count = 0;
}