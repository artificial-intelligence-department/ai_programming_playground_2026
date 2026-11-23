/* 
Епік 5. practice_task_1
Авторка: Софія Ліс
Група: ші-11
*/

#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>
#include <cctype>

using namespace std;

void clearWords(char ** &words, int &count) {
    for(int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

//перевірка тексту
bool checkText(const char * text) {
    size_t n = strlen(text);
    if (n == 0 || text[n - 1] != '.') {
        return false;
    }
    for(int i = 0; i + 1 < n; i++) {
        char c = text[i];
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ';
        if (!ok) {    
            return false;
        }
    }
    return true;
}

bool checkWord(const char * text) {
    size_t n = strlen(text);
    if (n == 0) {
        return false;
    }
    for(int i = 0; i < n; i++) {
        char c = text[i];
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ';
        if (!ok) {    
            return false;
        }
    }
    return true;
}


//перевід тексту в масив рядків
char **splitWords(const char *text, int &count) {
    char * copytext = new char[strlen(text) + 1];
    char ** words = new char * [128];

    strcpy(copytext, text);
    copytext[strlen(copytext) - 1] = '\0';

    char *word = strtok(copytext, " ");
    while (word != NULL) {
        words[count] = new char[strlen(word) + 1];
        strcpy(words[count], word);
        count++;
        word = strtok(NULL, " ");
    }
    delete[] copytext;
    return words;
}

//допоміжні функції для 1 пункту
void countChars(const char * text, int &letters, int &digits, int &spaces) {
    for(int i = 0; i < strlen(text); i++) {
        if(isalpha(text[i])) {
            letters++;
        }
        if(isdigit(text[i])) {
            digits++;
        }
        if(isspace(text[i])) {
            spaces++;
        }
    }
}

//1 пункт меню
void statistics(const char * text, int count) {
    printf("Текст:   \t\"%s\"\n", text);
    printf("Символів:\t%3zu\n", strlen(text));
    printf("Cлів:    \t%3d\n", count);

    int letters = 0;
    int digits = 0;
    int spaces = 0;

    countChars(text, letters, digits, spaces);

    double letper = ((double)letters/strlen(text))*100;
    double digper = ((double)digits/strlen(text))*100;
    double spaper = ((double)spaces/strlen(text))*100;

    printf("Літер:   \t%3d (%5.1f%%)\n", letters, letper);
    printf("Цифр:    \t%3d (%5.1f%%)\n", digits, digper);
    printf("Пробілів:\t%3d (%5.1f%%)\n", spaces, spaper);
}

//сортування слів злиттям
void merge(char **a, char **tmp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (strcmp(a[i], a[j]) <= 0) tmp[k++] = a[i++];
        else                         tmp[k++] = a[j++];
    }
    while (i <= mid)   tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];
    for (k = left; k <= right; k++) a[k] = tmp[k];
}

void mergeSort(char **a, char **tmp, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, tmp, left, mid);
    mergeSort(a, tmp, mid + 1, right);
    merge(a, tmp, left, mid, right);
}

//2 пункт меню
void table(char ** words, int count) {
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }

    char **tmp = new char*[count];
    mergeSort(sorted, tmp, 0, count - 1);

    int maxword = 0;
    int minword = 0;
    int sum = 0;
    
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    
    for(int i = 0; i < count; i++) {
        printf("|%3d | %-15s | %5zu |\n", i + 1, words[i], strlen(words[i]));
        if(strlen(words[i]) > strlen(words[maxword])) {
            maxword = i;
        }
        if(strlen(words[i]) < strlen(words[minword])) {
            minword = i;
        }
        sum += strlen(words[i]);
    }
    printf("+----+-----------------+-------+\n");

    printf("Найдовше слово: %s (%zu)\n", words[maxword], strlen(words[maxword]));
    printf("Найкоротше слово: %s (%zu)\n", words[minword], strlen(words[minword]));
    printf("Середня довжина: %.2f\n", (double)sum / count);
    printf("За абеткою: ");
    for(int i = 0; i < count; i++) {
        printf("%s ", sorted[i]);
    }
    printf("\n");

    const char * bestword = sorted[0];
    int bestcount = 1, run = 1;

    for(int i = 1; i < count; i++) {
        if(strcmp(sorted[i], sorted[i - 1]) == 0) {
            run++;
        }
        else run = 1;

        if(run > bestcount) {
            bestcount = run;
            bestword = sorted[i];
        }
    }
    printf("Найчастіше слово: %s (%d)\n", bestword, bestcount);

    delete[] tmp;
    delete[] sorted;
}

//3 пункт меню
void replaceWords(char * text, char ** &words, int count) {
    printf("Замінити слово: ");
    char * from = new char[32];
    char * to = new char[32];

    if(scanf("%31s", from) != 1) {
        printf("Введіть значення до 31!\n");
        while (getchar() != '\n');
        delete[] from;
        delete[] to;
        return;
    }
    
    if(!checkWord(from)) {
        printf("Помилка: текст має складатися з латинських літер і цифр\n");
        delete[] from;
        delete[] to;
        return;
    } 
    
    printf("На слово: ");

    if(scanf("%31s", to) != 1) {
        printf("Введіть дійсне значення до 31!\n");
        while (getchar() != '\n');
        delete[] from;
        delete[] to;
        return;
    }
    
    if(!checkWord(to)) {
        printf("Помилка: текст має складатися з латинських літер і цифр\n");
        delete[] from;
        delete[] to;
        return;
    } 

    //конструктор, що ініціалізує string з масиву char
    string txt(text); 
    string fromtxt(from);
    string totxt(to);

    int replaced = 0;

    size_t pos = 0;

    while((pos = txt.find(from, pos)) != string::npos) {
        size_t end = pos + fromtxt.length();
        bool startok = (pos == 0 || txt[pos - 1] == ' ');
        bool endok = (end == txt.length() || txt[end] == ' ' || txt[end] == '.');
        if(startok && endok) {
            txt.replace(pos, fromtxt.length(), totxt);
            pos += totxt.length();
            replaced++;
        }
        else {
            pos++;
        }
    }

    if (txt.length() > 255) {
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        delete[] from;
        delete[] to;
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", txt.c_str());
    printf("Нова довжина: %zu\n", txt.length());
    
    strcpy(text, txt.c_str());

    clearWords(words, count);
    
    words = splitWords(text, count);
    delete[] from;
    delete[] to;
}

//4 пункт меню
void compareWords() {
    printf("Перше слово: ");
    char * first = new char[32];
    char * second = new char[32];

    if(scanf("%31s", first) != 1) {
        printf("Введіть значення до 31!\n");
        while (getchar() != '\n');
        delete[] first;
        delete[] second;
        return;
    }
    
    if(!checkWord(first)) {
        printf("Помилка: текст має складатися з латинських літер і цифр\n");
        delete[] first;
        delete[] second;
        return;
    } 
    
    printf("Друге слово: ");

    if(scanf("%31s", second) != 1) {
        printf("Введіть дійсне значення до 31!\n");
        while (getchar() != '\n');
        delete[] first;
        delete[] second;
        return;
    }
    
    if(!checkWord(second)) {
        printf("Помилка: текст має складатися з латинських літер і цифр\n");
        delete[] first;
        delete[] second;
        return;
    } 

    int result = strcmp(first, second);

    printf("strcmp: %d -> ", result);
    if(result >= 1) {
        printf("перше слово більше\n");
    }
    if(result <= -1) {
        printf("перше слово менше\n");
    }
    if(result == 0) {
        printf("слова рівні\n");
    }

    string firststr(first);
    string secondstr(second);

    if(firststr == secondstr) {
        printf("Рівні (==): так\n");
    }
    else {
        printf("Рівні (==): ні\n");
    }

    for(int i = 0; i < firststr.length(); i++) {
        firststr[i] = tolower(firststr[i]);
    }
    
    for(int i = 0; i < secondstr.length(); i++) {
        secondstr[i] = tolower(secondstr[i]);
    }

    if(firststr == secondstr) {
        printf("Рівні без урахування регістру: так\n");
    }
    else {
        printf("Рівні без урахування регістру: ні\n");
    }

    printf("Довжини: %zu і %zu\n", strlen(first), strlen(second));
    
    string f(first);
    string s(second);

    string concat = f + " & " + s;

    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());

    delete[] first;
    delete[] second;
}

//5 пункт меню
void symbolInfo(const char * text) {
    char symb;
    printf("Введіть символ: ");
    scanf("%c", &symb);
    printf("Символ: \'%c\'\n", symb);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", symb, symb, symb);
    for(int i = 8; i > 0; i--) {
        printf("%d", (symb >> (i - 1)) & 1);
    }
    printf(")\n");
    printf("Тип: ");
    if(symb >= 'A' && symb <= 'Z') {
        printf("велика літера");
    }
    else if(symb >= 'a' && symb <= 'z') {
        printf("маленька літера");
    }
    else if(isdigit(symb)) {
        printf("цифра");
    }
    else if(isspace(symb)) {
        printf("пробільний");
    }
    else if(symb == '.') {
        printf("крапка");
    }
    else {
        printf("інший символ");
    }

    printf("\n");

    if(isalpha(symb)) {
        printf("Інший регістр: ");
        if(symb >= 'a' && symb <= 'z') {
            printf("\'%c\'\n", toupper(symb));
        }
        else {
            printf("\'%c\'\n", tolower(symb));
        }
    }

    printf("Наступний символ: \'%c\'\n", symb + 1);

    int count = 0;
    int firstpos = -1;

    const char * p = strchr(text, symb);
    while (p != NULL) {
        if(count == 0) {
            firstpos = (int)(p - text) + 1;
        }
        count++;
        p = strchr(p + 1, symb);
    }
    if(count == 0) {
        printf("Входжень: 0\n");
    }
    else {
        printf("Входжень: %d, перше на позиції %d\n", count, firstpos);
    }
}

//6 пункт меню
void newSentence(char * text, char ** &words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence, word;
    bool done = false;
    while(!done && cin >> word) {
        if(!sentence.empty()) {
            sentence += " ";
        }
        sentence += word;
        if(word.back() == '.') {
            done = true;
        }
    }

    if(!checkText(sentence.c_str()) || sentence.length() > 255) {
        printf("Помилка! Розмір речення повинен бути до 255, містити латинські літери, пробіли та цифри\n");
        return;
    }

    strcpy(text, sentence.c_str());

    clearWords(words, count);

    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main() {

    char text[256];

    printf("Введіть текст (до 255 символів, крапка в кінці): ");

    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    if (!checkText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр  і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    int wordcount = 0;

    char ** words = splitWords(text, wordcount);

    int action;

    do{
        printf("Пункт   Операція\n");
        printf("1       Показати текст і статистику\n");
        printf("2       Таблиця слів\n");
        printf("3       Замінити слово\n");
        printf("4       Порівняти два слова\n");
        printf("5       Інформація про символ\n");
        printf("6       Ввести нове речення\n");
        printf("0       Вийти\n");

        if(scanf("%d", &action) != 1) {
            printf("Введіть дійсне значення меню!\n");
            while (getchar() != '\n');
            action = -1;
            continue;            
        }
        //прибираємо \n
        getchar();

        switch(action) {
            case 1:
                statistics(text, wordcount);
            break;
            case 2:
                table(words, wordcount);
            break;
            case 3:
                replaceWords(text, words, wordcount);
            break;
            case 4:
                compareWords();
            break;
            case 5:
                symbolInfo(text);
            break;
            case 6:
                newSentence(text, words, wordcount);
            break;
            case 0:
                printf("Вихід\n");
            break;
            default:
                printf("Введіть дійсне значення меню!\n");
            break;
        }
    }
    while(action != 0);

    clearWords(words, wordcount);

    return 0;
}
