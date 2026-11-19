/*
Редактор текстового повідомлення
    Челяда Андрій, ШІ - 13
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

bool isValidText(const char *text); // перевіряє текст: латинські літери, цифри, пробіли і крапка в кінці
char **splitWords(const char *text, int &count); // розбиває текст на слова, кількість повертає через посилання
void freeWords(char **&words, int &count); // звільняє памʼять масиву слів і обнуляє вказівник
void countChars(const char *text, int &letters, int &digits, int &spaces); // рахує літери, цифри і пробіли, обходить текст вказівником
void showStats(const char *text, int wordsCount); // пункт 1: текст і статистика
void compareWords(); // пункт 4: порівняння двох слів
bool isValidWord(const char *w); // перевіряє слово: лише латинські літери і цифри
void symbolInfo(const char *text); // пункт 5: інформація про символ
void newSentence(char *text, char **&words, int &wordsCount); // пункт 6: нове речення через cin >>
void replaceWord(char *text, char **&words, int &wordsCount); // пункт 3: заміна цілого слова засобами string
void wordsTable(char **words, int wordsCount); // пункт 2: таблиця слів, сортування, найчастіше слово

int main() {
    char text[256];
    // Введення тексту рядком цілком через fgets
    printf("Введіть текст (до 255 символів, з крапкою в кінці): ");
    fgets(text, sizeof(text), stdin);
    text[ strcspn(text, "\n")] = '\0'; // прибираємо Enter, який fgets записав у масив
    // Некоректний текст: повідомляємо і завершуємо програму
    if(!isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    // Розбиття тексту на слова в динамічний масив
    int wordsCount = 0;
    char **words = splitWords(text, wordsCount);

    // Меню повторюється, доки користувач не вибере 0
    int choice = -1;
    do {
        printf("------Меню-------\n");
        printf("1) Показати текст і статистику\n");
        printf("2) Таблиця слів\n");
        printf("3) Замінити слово\n");
        printf("4) Порівняти два слова\n");
        printf("5) Інформація про символ\n");
        printf("6) Ввести нове речення\n");
        printf("0) Вийти\n");
        printf("Ваш вибір: ");

        // Нечислове введення: чистимо ввід до Enter і показуємо меню знову
        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            choice = -1; // щоб цикл не завершився, якщо після помилки choice став 0
            continue;
        }
        switch(choice){
            case 1:
                showStats(text, wordsCount);
                break;
            case 2:
                wordsTable(words, wordsCount);
                break;
            case 3:
                replaceWord(text, words, wordsCount);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                symbolInfo(text);
                break;
            case 6:
                newSentence(text, words, wordsCount);
                break;
            case 0:
                printf("Вихід з програми\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
                break;
        }
    } while(choice != 0);

    // Звільнення памʼяті перед завершенням програми
    freeWords(words, wordsCount);
    return 0;
}

bool isValidText(const char *text){
    int len = strlen(text);
    if(len == 0 || text[len - 1] != '.'){
        return false;
    }
    bool hasWord = false;
    // Перевіряємо всі символи перед крапкою
    for(int i = 0; i < len - 1; i ++){
        char c = text[i];
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')){
            hasWord = true;
        }
        else if(c != ' '){
            return false;
        }
    }
    if(!hasWord){
        return false;
    }
    return true;
}

char **splitWords(const char *text, int &count){
    char buf[256]; // копія, бо strtok змінює рядок
    strcpy(buf, text);
    int len = strlen(buf);
    // Прибираємо крапку, щоб вона не прилипла до останнього слова
    if(len > 0 && buf[len - 1] == '.'){
        buf[len - 1] = '\0';
    }
    char **words = new char*[128]; // у 255 символах не більше 128 слів
    count = 0;
    char *t = strtok(buf, " ");
    while (t != NULL){
        words[count] = new char[strlen(t) + 1]; // місце для слова і '\0'
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " "); // NULL - продовжуємо з місця, де зупинились
    }
    return words;
}

void freeWords(char **&words, int &count){
    for(int i = 0; i < count; i++){
        delete[] words[i]; // спершу кожне слово
    }
    delete[] words; // потім масив вказівників
    words = NULL; // вказівник більше ні на що не вказує
    count = 0;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;
    // Обхід тексту вказівником
    for(const char *p = text; *p != '\0'; p++){
        if(isalpha(*p)){
            letters++;
        }
        else if(isdigit(*p)){
            digits++;
        }
        else if(*p == ' '){
            spaces++;
        }
    }
}

void showStats(const char *text, int wordsCount){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int total = strlen(text);
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %d\n", total);
    printf("Слів: %d\n", wordsCount);
    printf("Літер: %d (%5.1f%%)\n", letters, letters * 100.0 / total); // 100.0, щоб ділення було дробовим
    printf("Цифр: %d (%5.1f%%)\n", digits, digits * 100.0 / total);
    printf("Пробілів: %d (%5.1f%%)\n", spaces, spaces * 100.0 / total);
}

bool isValidWord(const char *w){
    for(const char *p = w; *p != '\0'; p++){
        if(!isalpha(*p) && !isdigit(*p)){
            return false;
        }
    }
    return true;
}

void compareWords(){
    char a[32], b[32];
    printf("Перше слово: ");
    scanf("%31s", a); // не більше 31 символу, щоб не вийти за межі масиву
    printf("Друге слово: ");
    scanf("%31s", b);
    if (!isValidWord(a) || !isValidWord(b)){
        printf("Помилка: слова мають складатися лише з латинських літер і цифр.\n");
        return;
    }
    // strcmp повертає будь-яке відʼємне чи додатне число, тому виводимо -1, 0 або 1
    int r = strcmp(a, b);
    if(r < 0){
        printf("strcmp: -1 -> Перше слово менше\n");
    }
    else if(r > 0){
        printf("strcmp: 1 -> Друге слово менше\n");
    }
    else{
        printf("strcmp: 0 -> Слова однакові\n");
    }
    string sa = a;
    string sb = b;
    if(sa == sb){
        printf("Рівні (==): так\n");
    }
    else{
        printf("Рівні (==): ні\n");
    }
    // Порівняння без урахування регістру: обидві літери переводимо в малий
    bool same = (sa.length() == sb.length());
    for(int i = 0; a[i] != '\0'; i++){
        if(tolower(a[i]) != tolower(b[i])){
            same = false;
        }
    }
    if(same){
        printf("Рівні без урахування регістру: так\n");
    }
    else{
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());
    string c = sa + " & " + sb; // конкатенація
    printf("Конкатенація: \"%s\" (%d)\n", c.c_str(), (int)c.length());
}

void symbolInfo(const char *text){
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c); // пробіл пропускає Enter після вибору пункту меню
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", c, c, c);
    // Двійковий код: зсуваємо потрібний біт у кінець і беремо лише його
    for(int i = 7; i >= 0; i--){
        printf("%d", (c >> i) & 1);
    }
    printf(")\n");
    if(isupper(c)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(c));
    }
    else if(islower(c)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(c));
    }
    else if(isdigit(c)){
        printf("Тип: цифра\n");
    }
    else if(isspace(c)){
        printf("Тип: пробільний символ\n");
    }
    else{
        printf("Тип: інший символ\n");
    }
    printf("Наступний символ: '%c'\n", c + 1); // наступний символ має код на 1 більший
    int count = 0;
    for(int i = 0; text[i] != '\0'; i++){
        if(text[i] == c){
            count++;
        }
    }
    const char *first = strchr(text, c); // NULL, якщо символу в тексті немає
    if(first == NULL){
        printf("Символ у тексті не зустрічається\n");
    }
    else{
        int firstIndex = first - text;
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstIndex + 1);
    }
}

void newSentence(char *text, char **&words, int &wordsCount){
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence = "";
    string word;
    int count = 0;
    // Читаємо по слову, доки не трапиться слово з крапкою в кінці
    while(cin >> word){
        count++;
        if(sentence.length() > 0){ // пробіл лише між словами, перед першим не ставимо
            sentence += " ";
        }
        sentence += word;
        if(word[word.length() - 1] == '.'){
            break;
        }
    }
    if(sentence.length() > 255){
        printf("Помилка: речення довше за 255 символів. Текст не змінено.\n");
        return;
    }
    if(!isValidText(sentence.c_str())){
        printf("Помилка: некоректне речення. Текст не змінено.\n");
        return;
    }
    // Нове речення замінює текст, а масив слів будуємо заново
    strcpy(text, sentence.c_str());
    freeWords(words, wordsCount);
    words = splitWords(text, wordsCount);
    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}

void replaceWord(char *text, char **&words, int &wordsCount){
    char from[32];
    char to[32];
    printf("Замінити слово: ");
    scanf("%31s", from);
    printf("На слово: ");
    scanf("%31s", to);
    if(!isValidWord(from) || !isValidWord(to)){
        printf("Помилка: слова мають складатися лише з латинських літер і цифр. Текст не змінено.\n");
        return;
    }
    string stext = text;
    string sfrom = from;
    string sto = to;

    int changes = 0;
    size_t pos = 0; // позиція, з якої шукаємо
    // Шукаємо старе слово, доки find не поверне npos
    while((pos = stext.find(sfrom, pos)) != string::npos){
        // Замінюємо лише ціле слово: зліва початок тексту або пробіл, справа пробіл або крапка
        bool left = (pos == 0 || stext[pos - 1] == ' ');
        size_t end = pos + sfrom.length();
        bool right = (stext[end] == ' ' || stext[end] == '.');
        if(left && right){
            stext.replace(pos, sfrom.length(), sto);
            changes++;
            pos += sto.length(); // перескакуємо нове слово, щоб не знайти старе в ньому (cat -> cats)
        }
        else{
            pos++;
        }
    }
    // Масив text ще не змінений, тому при помилці лишається старим
    if(stext.length() > 255){
        printf("Помилка: результат перевищує 255 символів. Текст не змінено.\n");
        return;
    }
    printf("Замін виконано: %d\n", changes);
    printf("Було: \"%s\"\n", text);
    // Записуємо результат у text і будуємо масив слів заново
    strcpy(text, stext.c_str());
    freeWords(words, wordsCount);
    words = splitWords(text, wordsCount);
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}

void wordsTable(char **words, int wordsCount){
    // Заголовок пишемо вручну: кирилиця з шириною поля зсуває рамку
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for(int i = 0; i < wordsCount; i++){
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");
    int maxlen = 0; // індекс найдовшого слова
    int minlen = 0; // індекс найкоротшого слова
    // Строгі > і < : при однаковій довжині лишається перше слово
    for(int i = 1; i < wordsCount; i++){
        if(strlen(words[i]) > strlen(words[maxlen])){
            maxlen = i;
        }
        if(strlen(words[i]) < strlen(words[minlen])){
            minlen = i;
        }
    }
    double total = 0;
    for(int i = 0; i < wordsCount; i++){
        total += strlen(words[i]);
    }
    double average = total / wordsCount;
    printf("Найдовше слово: %s (%d)\n", words[maxlen], (int)(strlen(words[maxlen])));
    printf("Найкоротше слово: %s (%d)\n", words[minlen], (int)(strlen(words[minlen])));
    printf("Середня довжина: %.2f\n", average);

    // Сортуємо копію масиву адрес, щоб порядок слів у words не змінився
    char **copies = new char*[wordsCount];
    for(int i = 0; i < wordsCount; i++){
        copies[i] = words[i];
    }
    for(int i = 0; i < wordsCount; i++){
        for(int j = 0; j < wordsCount - 1; j++){
            if(strcmp(copies[j], copies[j + 1]) > 0){
                char* temp = copies[j]; // міняємо місцями лише адреси слів
                copies[j] = copies[j + 1];
                copies[j + 1] = temp;
            }
        }
    }
    printf("За абеткою:");
    for(int i = 0; i < wordsCount; i++){
        printf(" %s", copies[i]);
    }
    printf("\n");
    int mostFrequent = 0;
    int nummf = 0; // індекс найчастішого слова в copies
    // Для кожного слова рахуємо, скільки разів воно трапляється
    for(int i = 0; i < wordsCount; i++){
        int count = 0;
        for(int j = 0; j < wordsCount; j++){
            if(strcmp(copies[i], copies[j]) == 0){
                count++;
            }
        }
        // Строгий > : при однаковій кількості лишається перше за абеткою
        if(count > mostFrequent){
            mostFrequent = count;
            nummf = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", copies[nummf], mostFrequent);
    delete[] copies; // звільняємо лише копію, самі слова ще потрібні
}
