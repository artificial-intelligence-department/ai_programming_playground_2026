/*
Редактор текстового повідомлення
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/


#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

bool correctText(const char *text, size_t len) {
    bool has_word_char = false;

    for (size_t i = 0; i < len - 1; i++) {
        char c = text[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            has_word_char = true;
        } 
        else if (c >= '0' && c <= '9') {
            has_word_char = true;
        } 
        else if (c == ' ') {
            continue;
        } 
        else {
            printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
            return false;
        }
    }

    if (!has_word_char) {
        printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
        return false;
    }

    return true;
}

char **splitWords(const char *text, int &count) {
    count = 0;
    char **words = new char*[128];
    char *buf = strdup(text);

    // Прибираємо крапку з буфера, щоб слова були чистими
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '.') {
        buf[len - 1] = '\0';
    }

    char *t = strtok(buf, " ");
    while (t != NULL) {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }

    free(buf);
    return words; 
}

void freeWords(char **&words, int &count) {
    if (!words) return;
    for (int i = 0; i < count; i++) { 
        delete [] words[i];
    }
    delete [] words;
    words = nullptr;
    count = 0; 
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = 0;
    digits = 0;
    spaces = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) letters++;
        if (isdigit((unsigned char)*p)) digits++;
        if (isspace((unsigned char)*p)) spaces++;
    }
}

void showStats(const char *text, int wordCount) {
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces); 

    printf("%-15s \"%s\"\n", "Текст:", text);
    float symb = letters + digits + spaces + 1; // +1 — це крапка в кінці

    printf("Символів:      %5d\n", (int)symb);
    printf("Слів:          %5d\n", wordCount);
    printf("Літер:         %5d  (%5.1f%%)\n", letters, (double)letters / symb * 100);
    printf("Цифр:          %5d  (%5.1f%%)\n", digits, (double)digits / symb * 100);
    printf("Пробілів:      %5d  (%5.1f%%)\n", spaces, (double)spaces / symb * 100);
}

void sortWords(char **arr, int count) {
    if (count == 0) return;
    char **sorted_words = new char*[count];

    for (int i = 0; i < count; i++) {
        sorted_words[i] = arr[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(sorted_words[j], sorted_words[j + 1]) > 0) {
                char *temp = sorted_words[j];
                sorted_words[j] = sorted_words[j + 1];
                sorted_words[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        printf("%s ", sorted_words[i]);
    }
    printf("\n");

    delete[] sorted_words;
}

void sortWordsBySize(char **arr, int count) {
    if (count == 0) return;

    char *max = arr[0];
    char *min = arr[0];
    float averageValue = 0;

        for (int j = 0; j < count; j++) {
            averageValue += strlen(arr[j]);

            if (strlen(arr[j]) > strlen(max)) {
                max = arr[j];
            }
            if (strlen(arr[j]) < strlen(min)) {
                min = arr[j];
            }
        }

    printf("Найдовше слово: %s  (%zu)\n", max, strlen(max));
    printf("Найкоротше слово: %s  (%zu)\n", min, strlen(min));
    printf("Середня довжина: %.2f\n", averageValue / count);

}

void showWordTable(char **words, int count) {
    printf("| %-3s | %-15s      | %-6s  |\n", "N", "Слово", "Довж.");
    for (int i = 0; i < count; i++) {
        printf("| %-3d | %-15s | %6d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    sortWordsBySize(words, count);
    printf("За абеткою: "); 
    sortWords(words, count);

    int count_w[count] = {0};
    for ( int i = 0; i < count; i++){
        for ( int j = 0; j < count; j++){
            if (strcmp(words[i], words[j]) == 0){
                count_w[i]++;
            }
        }
    }

    int max_count = 0;
    string most_frequent = "";

    for (int i = 0; i < count; i++) {
        if (count_w[i] > max_count) {
            max_count = count_w[i];
            most_frequent = words[i];
        }
    }

    printf("Найчастіше слово: %s ( %d )\n", most_frequent.c_str(), max_count);

}

bool isLatinWord(const string &word) {
    if (word.empty()) return false;
    for (char c : word) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return false; 
        }
    }
    return true;
}

bool isNumber(const string &word) {
    if (word.empty()) return false;
    for (char c : word) {
        if (!(c >= '0' && c <= '9')) {
            return false; 
        }
    }
    return true;
}

void replaceWord(char *text, char **&words, int &count) {
    string from, to;
    printf("Замінити слово: ");
    cin >> from;
    printf("На слово: ");
    cin >> to;

    if (isLatinWord(from) && !isLatinWord(to)){
        printf("Не можна замінити слово на цифру чи кирилицю.\n");
        return;
    }
    else if (isNumber(from) && !isNumber(to)){
        printf("Не можна замінити цифру на слово чи кирилицю.\n");
        return;
    }
    else if (!isLatinWord(from) && !isNumber(from)) {
        printf("Помилка: слово має складатися лише з латинських літер або цифр.\n");
        return;
    }

    int count_ch = 0;
    for ( int i = 0; i < count; i++){
        if ( words[i] == from){
            count_ch++;
            delete[] words[i];                      
            words[i] = new char[to.length() + 1];  
            strcpy(words[i], to.c_str());
        }
    }

    printf("Виконано замін: %d\n", count_ch);
    printf("Було: \"%s\"\n", text);

    text[0] = '\0';
    for ( int i = 0 ; i < count; i++){
        strcat(text, words[i]);
        if (i == count - 1) {
            strcat(text, "."); 
        } 
        else {
            strcat(text, " "); 
        }
        
    }
    
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", strlen(text));

}


void compareWords(){
    char *w1 = new char[50];
    char *w2 = new char [50];
    printf("Перше слово: ");
    fgets(w1, 50, stdin);
    w1[strcspn(w1, "\n")] = '\0';
    printf("Друге слово: ");
    fgets(w2, 50, stdin);
    w2[strcspn(w2, "\n")] = '\0';

    if (strcmp(w1, w2) < 0){
        printf ("strcmp: -1 -> перше слово менше \n");
    }
    else if (strcmp(w1, w2) > 0){
        printf("strcmp: 1 -> перше слово більше \n");
    }
    else {
        printf("strcmp: 0 -> слова однакові \n");
    }

    printf ("Рівні (==):  ");
    if ((strcmp(w1, w2) == 0)){
        printf ("так\n");
    }
    else{printf("ні\n");}

    printf ("Рівні без урахування регістру:  ");
    if (strlen(w1) == strlen (w2)){
        int a = 0;
        for ( int i = 0; w1[i] != '\0'; i++){
            if (tolower((unsigned char) w1[i]) != tolower((unsigned char) w2[i])){
                a++;
            }
        }
        if(a == 0){
            printf ("так\n");
        }
        else {printf("ні\n");}
    }
    else {printf("ні\n");}

    printf("Довжини:  %ld  i  %ld \n", strlen(w1), strlen(w2));
    
    size_t newLen = strlen(w1) + 3 + strlen(w2) + 1;

    char *concat = new char[newLen];

    strcpy(concat, w1); 
    strcat(concat, " & ");   
    strcat(concat, w2); 

    printf("Конкатенація: \"%s\"(%zu)\n", concat, strlen(concat));

    delete [] w1;
    w1 = nullptr;
    delete [] w2;
    w2 = nullptr;
    delete[] concat;
}



void charInfo(const char *text){
    unsigned char one_symbol;
    printf("Введіть символ: ");
    scanf(" %c", &one_symbol);
    printf ("Символ: '%c' \n", one_symbol);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", one_symbol, one_symbol, one_symbol);

    for (int i = 7; i >= 0; i--) {
        printf("%d", (one_symbol >> i) & 1);
    }
    printf(")\n");

    int upper = 0;
    int lower = 0;
    int space = 0;
    int number = 0;
    char type = one_symbol;

    printf("Тип: ");
    if (islower(one_symbol)){
        printf("мала літера \n");
        lower++;
    }
    else if (isupper(one_symbol)){
        printf("велика літера \n");
        upper++;
    }
    else if (isdigit(one_symbol)){
        printf("цифра \n");
        number++;
    }
    else if (isspace(one_symbol)){
        printf("пробіл \n");
        space++;
    }
    else {
        printf("інший символ\n");
    }

    if (space == 0 && number == 0){
        printf("Інший регістр: ");
        if (upper != 0){
            printf("'%c'\n", type + 32);
        }
        else if (lower != 0){
            printf("'%c'\n", type - 32);
        }
        char next = one_symbol;
        printf("Наступний символ:  '%c'\n", next + 1);
    }
    

    int count = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (*p == one_symbol) {
            count++;
        }
    }
    
    if (count == 0){
        printf(" Входжень у тексті: у тексті не трапляється\n");
    }
    else{
        const char *posPtr = strchr(text, one_symbol);
        int pos = posPtr - text + 1;
        printf("Входжень у тексті: %d, перше на позиції %d \n", count, pos);
    }

}




void newSentence(char *text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова): \n");

    int new_count = 0;
    string sentence = "";
    char word[32];
    while (cin >> word) {
        new_count++;
        int len = strlen(word);
        sentence += word;
        if (word[len - 1] == '.') break;
        if (new_count > 0){
            sentence += " ";
        }
    }

    size_t len = sentence.length();

    if (len == 0 || sentence[len - 1] != '.' || len > 255) {
        printf("Помилка: некоректне речення або перевищено 255 символів. \n");
        return;
    }

    if (!correctText(sentence.c_str(), len)) {
        return;
    }

    freeWords(words, count);

    count = new_count;

    strcpy(text, sentence.c_str());

    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: \n");
    printf("...\n");
    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces);
    showStats(text, count);

    printf("Нова довжина: %zu\n", strlen(text));

}

int main() {
    char text[256];
    char **words = NULL;
    int wordCount = 0;

    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    if (!fgets(text, sizeof(text), stdin)) return 0;

    size_t len = strlen(text);

    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--; 
    }

    if (len == 0 || text[len - 1] != '.') {
        printf("Помилка: текст має складатися з латинських літер, цифр та пробілів та завершуватися крапкою. \n");
        return 1;
    }

    if (!correctText(text, len)) {
        return 1;
    }

    words = splitWords(text, wordCount);

    int choice = 1;
    do {
        printf("\nМеню: \n");
        printf(" 1 - Показати текст та статистику \n");
        printf(" 2 - Таблиця слів \n");
        printf(" 3 - Замінити слово \n");
        printf(" 4 - Порівняти два слова \n");
        printf(" 5 - Інформація про символ \n");
        printf(" 6 - Ввести нове речення \n");
        printf(" 0 - Вийти \n");
        printf(" > ");
        
        // Виправлено повторне оголошення int choice
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("Некоректний ввід. \n");
            continue;
        }
        while (getchar() != '\n');

        printf("\n");

        switch (choice) {
            case 1:
                showStats(text, wordCount);
                printf("\n");
                break;

            case 2:
                showWordTable(words, wordCount);
                printf("\n");
                break;

            case 3:
                replaceWord(text, words, wordCount);
                printf("\n");
                break;

            case 4:
                compareWords();
                printf("\n");
                break;

            case 5:
                charInfo(text);
                printf("\n");
                break;

            case 6:
                newSentence(text, words, wordCount);
                printf("\n");
                break;

            case 0:
                choice = 0;
                printf("\n");
                break;

            default:
                printf("Некоректний пункт меню.\n");
                break;
        }

    } while (choice != 0);

    freeWords(words, wordCount);

    return 0;
}