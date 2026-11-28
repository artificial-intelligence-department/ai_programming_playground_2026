#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

char **splitWords(const char *text, int &count)
{
    char **words = new char*[count];
    int j = 0;
    int len = strlen(text)-1;

    for (int i = 0; i < count; i++){
        while (j < len && isspace(text[j])){
            j++;
        }
        int k = 0;
        while (j < len && !isspace(text[j])){
            k++;
            j++;
        }
        words[i] = new char[k+1];
    }

    j = 0;
    for (int i = 0; i < count; i++){
        while (j < len && isspace(text[j])){
            j++;
        }
        int k = 0;
        while (j < len && !isspace(text[j])){
            words[i][k] = text[j];
            k++;
            j++;
        }
        words[i][k] = '\0';
    }
    return words;
}

void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    int i = 0;
    while(*(text+i) != '\0'){
        int index = *(text+i);
        if (isalpha(index)){
            letters++;
        } else if(isdigit(index)){
            digits++;
        } else if(isspace(index)){
            spaces++;
        }
        i++;
    }
}

void textStats(const char *text, int count)
{
    int count_digit = 0;
    int count_letter = 0;
    int count_space = 0;
    countChars(text, count_letter, count_digit, count_space);
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%zu\n", strlen(text));
    printf("Слів:    \t%d\n", count);
    printf("Літер:   \t%d (%.1f%%)\n", count_letter, 100*((float)count_letter/strlen(text)));
    printf("Цифр:    \t%d (%.1f%%)\n", count_digit, 100*((float)count_digit/strlen(text)));
    printf("Пробілів:\t%d (%.1f%%)\n", count_space, 100*((float)count_space/strlen(text)));
}

void table(char **words, int count)
{
    printf("+----+--------------------------------+-------+\n");
    printf("| N  | Слово                          | Довж. |\n");
    printf("+----+--------------------------------+-------+\n");
    for (int i = 0; i < count; i++){
        printf("| %2d | %-30s | %5zu |\n", i+1, words[i], strlen(words[i]));
    }
    printf("+----+--------------------------------+-------+\n");

    int max_len = 0;
    int maxword_index = 0;
    int min_len = 255;
    int minword_index = 0;
    int all_lens = 0;
    for (int i = 0; i < count; i++){
        if (max_len < strlen(words[i])){
            max_len = strlen(words[i]);
            maxword_index = i;
        }
        if (min_len > strlen(words[i])){
            min_len = strlen(words[i]);
            minword_index = i;
        }
        all_lens += strlen(words[i]);
    }

    printf("Найдовше слово: %s (%d)\n", words[maxword_index], max_len);
    printf("Найкоротше слово: %s (%d)\n", words[minword_index], min_len);
    printf("Середня довжина: %.2f\n", (float)all_lens/count);

    char **cmp_words = new char*[count];
    for (int i = 0; i < count; i++){
        cmp_words[i] = words[i];
    }

    for (int i = 0; i < count; i++){
        for (int j = 0; j < count; j++){
            if (strcmp(cmp_words[i], cmp_words[j]) < 0){
                swap(cmp_words[i], cmp_words[j]);
            }
        }
    }

    printf("За абеткою: ");
    for (int i = 0; i < count; i++){
        printf("%s ", cmp_words[i]);
    }
    printf("\n");

    int the_same = 1;
    int the_same_index = 0;
    int times = 1;
    for (int i = 0; i < count-1; i++){
        if (strcmp(cmp_words[i], cmp_words[i+1]) == 0){
            times++;
            if (times > the_same){
                the_same = times;
                the_same_index = i;
            } 
        } else if (strcmp(cmp_words[i], cmp_words[i+1]) != 0) {
                times = 1;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", cmp_words[the_same_index], the_same);
    delete[] cmp_words;
}

void wordReplace(char **&words, int &count, char *text)
{
    while (getchar() != '\n' && getchar() != EOF);

    char from[31] = {'\0'};
    char to[31] = {'\0'};

    printf("Замінити слово: ");
    scanf("%30s", from);
    int ch = getchar();
    if (ch != '\n' && ch != EOF){
        printf("Лише 1 слово до 30 букв!\n");
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    printf("На слово: ");
    scanf("%30s", to);
    ch = getchar();
    if (ch != '\n' && ch != EOF){
        printf("Лише 1 слово до 30 букв!\n");
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }

    string str_rep = from;
    string str_new = to;

    bool empty = true;
    for (int i = 0; i < str_new.length(); i++){
        bool upper = (to[i] >= 'A' && to[i] <= 'Z');
        bool lower = (to[i] >= 'a' && to[i] <= 'z');
        bool digit = (to[i] >= '0' && to[i] <= '9');
        if (!upper && !lower && to[i] != '\0' && !digit){
            printf("Лише 1 слово до 30 букв!\n");
            return;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Слово порожнє\n");
        return;
    }

    empty = true;
    for (int i = 0; i < str_rep.length(); i++){
        bool upper = (from[i] >= 'A' && from[i] <= 'Z');
        bool lower = (from[i] >= 'a' && from[i] <= 'z');
        bool digit = (from[i] >= '0' && from[i] <= '9');
        if (!upper && !lower && from[i] != '\0' && !digit){
            printf("Лише 1 слово до 30 букв!\n");
            return;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Слово порожнє\n");
        return;
    }

    string new_text = text;

    int repls = 0;
    size_t index = new_text.find(from);
    while (index != string::npos){
        repls++;
        new_text.replace(index, str_rep.length(), to);
        index = new_text.find(from, index + str_new.length());
    }
    printf("Замін виконано: %d\n", repls);

    if (new_text.length() >= 256){
        printf("Речення стане надто великим!\n");
        return;
    }

    printf("Було: \"%s\"\n", text);
    strcpy(text, new_text.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
    freeWords(words, count);
    words = splitWords(text, count);
}

void cmpWords()
{
    while (getchar() != '\n' && getchar() != EOF);

    char first[31] = {'\0'};
    char second[31] = {'\0'};
    printf("Перше слово: ");
    scanf("%30s", first);
    int ch = getchar();
    if (ch != '\n' && ch != EOF){
        printf("Лише 1 слово до 30 букв!\n");
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    first[strcspn(first, "\n")] = '\0';
    printf("Друге слово: ");
    scanf("%30s", second);
    ch = getchar();
    if (ch != '\n' && ch != EOF){
        printf("Лише 1 слово до 30 букв!\n");
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }

    bool empty = true;
    for (int i = 0; i < strlen(first); i++){
        bool upper = (first[i] >= 'A' && first[i] <= 'Z');
        bool lower = (first[i] >= 'a' && first[i] <= 'z');
        bool digit = (first[i] >= '0' && first[i] <= '9');
        if (!upper && !lower && first[i] != '\0' && !digit){
            printf("Лише 1 слово до 30 букв!\n");
            return;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Слово порожнє\n");
        return;
    }

    empty = true;
    for (int i = 0; i < strlen(second); i++){
        bool upper = (second[i] >= 'A' && second[i] <= 'Z');
        bool lower = (second[i] >= 'a' && second[i] <= 'z');
        bool digit = (second[i] >= '0' && second[i] <= '9');
        if (!upper && !lower && second[i] != '\0' && !digit){
            printf("Лише 1 слово до 30 букв!\n");
            return;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Слово порожнє\n");
        return;
    }

    int result = strcmp(first, second);
    string num;
    if (result < 0){
        num = "перше слово менше";
        printf("strcmp: %d -> %s\n", result, num.c_str());
    } else if (result > 0){
        num = "друге слово менше";
        printf("strcmp: %d -> %s\n", result, num.c_str());
    } else if (result == 0){
        num = "слова рівні";
        printf("strcmp: %d -> %s\n", result, num.c_str());
    }

    string str_fir = first;
    string str_sec = second;
    if (str_fir == str_sec){
        printf("Рівні (==): так\n");
    } else printf("Рівні (==): ні\n");

    if (str_fir.length() > str_sec.length()){
        printf("Рівні без урахування регістру: ні\n");
    } else if (str_fir.length() < str_sec.length()){
        printf("Рівні без урахування регістру: ні\n");
    } else if (str_fir.length() == str_sec.length()){
        bool equal = true;
        for (int i = 0; i < str_fir.length(); i++){
            if (tolower(str_fir[i]) != tolower(str_sec[i])){
                equal = false;
            }
        }
        if (equal){
            printf("Рівні без урахування регістру: так\n");
        } else printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %d і %d\n", str_fir.length(), str_sec.length());
    char cat[256] = {'\0'};
    strcat(cat, first);
    strcat(cat, " & ");
    strcat(cat, second);
    printf("Конкатенація: \"%s\" (%zu)\n", cat, strlen(cat));
}

void information(char *text)
{
    while (getchar() != '\n' && getchar() != EOF);
    char symbol;
    printf("Уведіть символ: ");
    scanf("%c", &symbol);
    printf("Символ: '%c'\n", symbol);

    char bin[9] = {'\0'};
    int j = 0;
    for (int i = 7; i >= 0; i--){
        if ((symbol >> i) & 1){
            bin[j] = '1';
        } else bin[j] = '0';
        j++;
    }
    printf("Код: %d (hex 0x%X, oct 0%o, bin %s)\n", symbol, symbol, symbol, bin);

    bool upper = (isupper(symbol));
    bool lower = (islower(symbol));
    bool space = (isspace(symbol));
    bool digit = (isdigit(symbol));
    if (upper){
        printf("Тип: велика літера\n");
        printf("Інший регістр: %c\n", symbol+32);
    } else if (lower){
        printf("Тип: мала літера\n");
        printf("Інший регістр: %c\n", symbol-32);
    } else if (space){
        printf("Тип: пробіл\n");
    } else if (digit){
        printf("Тип: цифра\n");
    } else {
        printf("Тип: інший символ\n");
    }

    printf("Наступний символ: %c\n", symbol+1);

    int count = 0;
    int pos = 257;
    for (int i = 0; i < strlen(text); i++){
        if (text[i] == symbol){
            count++;
            if (pos > i){
                pos = i;
            }
        }
    }
    if (pos == 257){
        printf("Входжень у тексті: %d\n", count);
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, pos+1);
    }
}

void newText(char *text, const int n, char **&words, int &count)
{
    printf("Уведіть речення (крапка після останнього слова): \n");
    string word;
    string str_new_text;
    while (cin >> word){
        if (!str_new_text.empty()){
            str_new_text += " ";
        }
        str_new_text += word;
        if (word[word.length()-1] == '.'){
            int ch;
            while ((ch = cin.get()) != '\n' && ch != EOF){}
            break;
        }
    }

    char new_text[256] = {'\0'};
    if (n <= str_new_text.length()){
        printf("Повідомлення завелике!\n");
        return;
    }
    strcpy(new_text, str_new_text.c_str());

    size_t len = strlen(new_text);
    if (len > 0 && new_text[len-1] == '\n'){
        new_text[len-1] = '\0';
        len--;
    }

    if (len == 0){
        printf("Речення порожнє!\n");
        return;
    } else if (new_text[len-1] != '.'){
        printf("Ви забули про крапку у кінці!\n");
        return;
    }

    bool empty = true;
    for (int i = 0; i < len-1; i++){
        bool upper = (new_text[i] >= 'A' && new_text[i] <= 'Z');
        bool lower = (new_text[i] >= 'a' && new_text[i] <= 'z');
        bool space = (new_text[i] == ' ');
        bool digit = (new_text[i] >= '0' && new_text[i] <= '9');
        if (!upper && !lower && !space && new_text[i] != '\0' && !digit){
            printf("Неприпустимий символ!\n");
            return;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Повідомлення не містить слів\n");
        return;
    }

    int new_count = 0;
    for (int i = 0; i < len-1; i++){
        if (!isspace(new_text[i]) && (i == 0 || isspace(new_text[i-1]))){
            new_count++;
        }
    }
    printf("Прочитано слів: %d\n", new_count);
    printf("Новий текст: %s\n", new_text);
    printf("Довжина: %zu\n", strlen(new_text));
    strcpy(text, new_text);
    freeWords(words, count);
    count = new_count;
    words = splitWords(text, count);
}

int main()
{
    const int n = 256;
    printf("Уведіть текст (до 255 символів, крапка в кінці):\n");
    char text[n] = {'\0'};
    fgets(text, n, stdin);

    size_t len = strlen(text);
    if (len > 0 && text[len-1] == '\n'){
        text[len-1] = '\0';
        len--;
    } else if (len == n-1){
        int ch = getchar();
        if (ch != '\n' && ch != EOF){
            printf("Повідомлення завелике!\n");
            return -1;
        }
    }

    if (len == 0){
        printf("Речення порожнє!\n");
        return -1;
    } else if (text[len-1] != '.'){
        printf("Ви забули про крапку у кінці!\n");
        return -1;
    }

    bool empty = true;
    for (int i = 0; i < len-1; i++){
        bool upper = (text[i] >= 'A' && text[i] <= 'Z');
        bool lower = (text[i] >= 'a' && text[i] <= 'z');
        bool space = (text[i] == ' ');
        bool digit = (text[i] >= '0' && text[i] <= '9');
        if (!upper && !lower && !space && text[i] != '\0' && !digit){
            printf("Неприпустимий символ!\n");
            return -1;
        } else if (upper || lower || digit){
            empty = false;
        }
    }
    if (empty){
        printf("Повідомлення не містить слів\n");
        return -1;
    }

    int count = 0;
    for (int i = 0; i < len-1; i++){
        if (!isspace(text[i]) && (i == 0 || isspace(text[i-1]))){
            count++;
        }
    }
    char **words = splitWords(text, count);
    
    int action;
    bool leave = false;
    do {
        printf(" > Меню\n");
        printf("1 < Показати текст і статистику\n");
        printf("2 < Таблиця слів\n");
        printf("3 < Замінити слово\n");
        printf("4 < Порівняти два слова\n");
        printf("5 < Інформація про символ\n");
        printf("6 < Ввести нове речення\n");
        printf("0 < Вийти\n");
        if (scanf("%d", &action) != 1){
            printf("Помилка: введіть номер пункту меню.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (action){
            case 0:
                leave = true;
                break;
            case 1:
                textStats(text, count);
                break;
            case 2:
                table(words, count);
                break;
            case 3:
                wordReplace(words, count, text);
                break;
            case 4:
                cmpWords();
                break;
            case 5:
                information(text);
                break;
            case 6:
                newText(text, n, words, count);
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", action);
                break;
        }
    } while (!leave);
    freeWords(words, count);
}