/*
Епік 5. Практичне завдання: Редактор текстового повідомлення
Автор: Боднар Василь Іванович
Група: ШІ-12
*/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

bool read(char text[256]){
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(fgets(text, 256, stdin) == NULL){
        printf("Помилка: неправильний ввід.\n");
        return false;
    }

    char *lastSym = nullptr;
    lastSym = text;
    while(*lastSym != '\n' && *lastSym != '\0'){
        lastSym++;
    }
    if(*lastSym == '\0'){
        int c = getchar();
        if (c != EOF && c != '\n'){
            printf("Помилка: текст не повинен перевищувати 255 символів.\n");
            return false;
        }
    }
    *lastSym = '\0';

    int t_l = lastSym - text;
    if(t_l == 0 || *(lastSym-1) != '.'){
        printf("Помилка: дозволені лише латинські літери, цифри та пробіли. Текст має закінчуватися крапкою.\n");
        return false;
    }

    bool anyWords = false;
    for(char *i=text;i<lastSym - 1;i++){
        if((*i >= 'A' && *i <= 'Z') || (*i >= 'a' && *i <= 'z') || (*i >= '0' && *i <= '9')){
            anyWords = true;
        }
        else if(*i != ' '){
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return false;
        }
    }
    if(!anyWords){
        printf("Помилка: в тексті немає ні літер, ні цифр.\n");
        return false;
    }
    return true;
}

bool validWord(const char *w){
    int n = strlen(w);
    if(n == 0 || n > 31){
        return false;
    }
    //валідація чи є недозволені символи
    for(int i=0;i<n;i++){
        bool ok = (w[i] >= 'A' && w[i] <= 'Z') || (w[i] >= 'a' && w[i] <= 'z') || (w[i] >= '0' && w[i] <= '9');
        if(!ok){
            return false;
        }
    }
    return true;
}

char **splitWords(const char *text, int &count){
    char buf[256];
    strcpy(buf, text);

    count = 0;
    for(char *t = strtok(buf, " ."); t != NULL; t = strtok(NULL, " .")){
        count++;
    }

    char **words = new char*[count];

    strcpy(buf, text);
    int k = 0;
    for(char *t = strtok(buf, " ."); t != NULL; t = strtok(NULL, " .")){
        words[k] = new char[strlen(t) + 1];
        strcpy(words[k], t);
        k++;
    }
    return words;
}

void freeWords(char **&words, int count){
    for(int i=0;i<count;i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0, digits = 0, spaces = 0;
    const char *p = text;
    while(*p != '\0'){
        if(*p == ' '){
            spaces++;
        }
        else if(isdigit(*p)){
            digits++;
        }
        else if(isalpha(*p)){
            letters++;
        }
        p++;
    }
}

void showTextAndStats(const char *text, int words){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);

    int totalC = strlen(text);

    double lettersP = 0, digitsP = 0, spacesP = 0;
    if(totalC > 0){
        lettersP = letters * 100.0 / totalC;
        digitsP  = digits  * 100.0 / totalC;
        spacesP  = spaces  * 100.0 / totalC;
    }

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%2d\n", totalC);
    printf("Слів:\t\t%2d\n", words);
    printf("Літер:\t\t%2d (%5.1f%%)\n", letters, lettersP);
    printf("Цифр:\t\t%2d (%5.1f%%)\n", digits, digitsP);
    printf("Пробілів:\t%2d (%5.1f%%)\n", spaces, spacesP);
}

void wordsTable(char **w, int words){
    int *l = new int[words];
    //заповннення масиву довжини слів
    for(int i=0;i<words;i++){
        l[i] = strlen(w[i]);
    }
    int longest = l[0], shortest = l[0],  pos_l = 0, pos_s = 0;
    double avg = l[0];
    for(int i=0;i<words-1;i++){
        if(longest < l[i+1]){
            longest = l[i+1];
            pos_l = i+1;
        }
        if(shortest > l[i+1]){
            shortest = l[i+1];
            pos_s = i+1;
        }
        avg += l[i+1];
    }
    avg = avg/words;

    char **abc = new char*[words];
    for(int i=0;i<words;i++){
        abc[i] = w[i];
    }
    //сортування в копійованому масиві по алфавіту
    for(int i=0;i<words;i++){
        for(int j=0;j<words-1;j++){
            if(strcmp(abc[j], abc[j+1]) > 0){
                char *tmp = abc[j+1];
                abc[j+1] = abc[j];
                abc[j] = tmp;
            }
        }
    }
    int freq = 0, pos_f = 0;
    for(int i=0;i<words;i++){
        int tmp = 0;
        for(int j=0;j<words;j++){
            if(strcmp(abc[i], abc[j]) == 0){
                tmp++;
            }
        }
        if(tmp > freq){
            freq = tmp;
            pos_f = i;
        }
    }

    printf("+----+------------------------------+-------+\n");
    printf("| N  | Слово                        | Довж. |\n");
    printf("+----+------------------------------+-------+\n");
    for(int i=0; i<words;i++){
        printf("|%3d | %-28s |%6d |\n", i+1, w[i], l[i]);
    }
    printf("+----+------------------------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", w[pos_l], longest);
    printf("Найкоротше слово: %s (%d)\n", w[pos_s], shortest);
    printf("Середня довжина: %.2f\n", avg); 
    printf("За абеткою: ");
    for(int i=0;i<words;i++){
        printf("%s ", abc[i]);
    }
    printf("\nНайчастіше слово: %s (%d)\n", abc[pos_f], freq);

    delete[] abc;
    delete[] l;
}

void changeWord(char *text, char **&words, int &count){
    char oldW[256], newW[256];
    printf("Замінити слово: ");
    scanf("%255s", oldW);
    printf("На слово: ");
    scanf("%255s", newW);

    if(!validWord(oldW) || !validWord(newW)){
        printf("Помилка: слова мають містити лише латинські літери і цифри(до 31 символу).\n");
        return;
    }

    string result = text;
    string from = oldW, to = newW;
    int replaced = 0;
    size_t pos = result.find(from);
    //заміна слів в копійованій стрічці
    while(pos != string::npos){
        size_t endPos = pos + from.length();
        bool left = (pos == 0 || result[pos-1] == ' ');
        bool right = (endPos == result.length() || result[endPos] == ' ' || result[endPos] == '.');
        if(left && right){
            result.replace(pos, from.length(), to);
            replaced++;
            pos = result.find(from, pos + to.length());
        }
        else{
            pos = result.find(from, pos + 1);
        }
    }

    if(result.length() > 255){
        printf("Помилка: результат перевищує 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);

    strcpy(text, result.c_str());

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)result.length());

    freeWords(words, count);
    words = splitWords(text, count);
}

void compareWords(){
    char a[256], b[256];
    printf("Перше слово: ");
    scanf("%255s", a);
    printf("Друге слово: ");
    scanf("%255s", b);

    if(!validWord(a) || !validWord(b)){
        printf("Помилка: слова мають містити лише латинські літери і цифри (до 31 символу).\n");
        return;
    }

    int r = strcmp(a, b);
    if(r < 0){
        r = -1;
    }
    else if(r > 0){
        r = 1;
    }

    printf("strcmp: %d -> ", r);
    if(r < 0){
        printf("перше слово менше\n");
    }
    else if(r > 0){
        printf("перше слово більше\n");
    }
    else {
        printf("слова однакові\n");
    }
    string s1 = a, s2 = b;
    printf("Рівні (==): %s\n", s1 == s2 ? "так" : "ні");

    string l1 = s1, l2 = s2;
    int n = l1.length();
    for(int i=0;i<n;i++){
        l1[i] = tolower(l1[i]);
    }
    n = l2.length();
    for(int i=0;i<n;i++){
        l2[i] = tolower(l2[i]);
    }
    printf("Рівні без урахування регістру: %s\n", l1 == l2 ? "так" : "ні");

    string res = s1 + " & " + s2;
    printf("Довжини: %d і %d\n", (int)s1.length(), (int)s2.length());
    printf("Конкатенація: \"%s\" (%d)\n", res.c_str(), (int)res.length());
}

void charStats(const char *text){
    char c;
    printf("Введіть символ: ");
    scanf("%c", &c);
    if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == '.')){
        printf("Помилка: введений символ заборонений.\n");
        return;
    }

    int charCount = 0;
    for(int i=0;text[i]!='\0';i++){
        if(text[i] == c){
            charCount++;
        }
    }
    const char *first = strchr(text, c);
    int pos_c = 0;
    if(first != NULL){
        pos_c = first - text + 1;
    }

    printf("Символ: \'%c\'\n", c);
    printf("Код: %d (hex %#x, oct %#o, bin ", c, c, c);
    for(int i=7;i>=0;i--){
        printf("%d", (c >> i) & 1);
    }
    printf(")\n");

    if(isupper(c)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: \'%c\'\n", c+32);
    }
    else if(islower(c)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: \'%c\'\n", c-32);
    }
    else if(isdigit(c)){
        printf("Тип: цифра\n");
    }
    else if(c == ' '){
        printf("Тип: пробіл\n");
    }
    else if(c == '.'){
        printf("Тип: крапка\n");
    }

    printf("Наступний символ: \'%c\'\n", c+1);

    if(pos_c != 0){
        printf("Входжень у тексті: %d, перше на позиції %d\n", charCount, pos_c);
    }
    else {
        printf("Введеного символу немає у тексті\n");
    }
}

void newSentence(char *text, char **&words, int &count){
    string sentence = "";
    string w;
    int read = 0;
    bool correct = true;
    bool ended = false;

    printf("Введіть речення(крапка в кінці):\n");

    while(!ended){
        if(!(cin >> w)){
            break;
        }
        read++;

        int len = w.length();
        if(w[len-1] == '.'){
            ended = true;
            len--;
        }
        if(len == 0) correct = false;

        for(int i=0;i<len;i++){
            char c = w[i];
            bool ok = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
            if(!ok) correct = false;
        }

        if(read > 1) sentence += ' ';
        sentence += w;
    }
    if(ended){
        cin.ignore(1000, '\n');
    }

    if(!ended) correct = false;
    if(sentence.length() > 255) correct = false;

    if(!correct){
        printf("Помилка: речення некоректне, текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    int len = sentence.length();

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", read);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", len);
}

int main() {
    char text[256];
    if(!read(text)){
        return 0;
    }

    int count;
    char **words = splitWords(text, count);

    bool run = true;
    while(run){
        int choice = -1;
        printf("\nМеню:\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");

        int res = scanf("%d", &choice);
        if(res == EOF){
            break;
        }
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF);
        if(res != 1){
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }

        switch(choice){
            case 1: showTextAndStats(text, count); break;
            case 2: wordsTable(words, count); break;
            case 3: changeWord(text, words, count); break;
            case 4: compareWords(); break;
            case 5: charStats(text); break;
            case 6: newSentence(text, words, count); break;
            case 0: run = false; break;
            default: printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    }

    freeWords(words, count);
    return 0;
}