#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

/*
 * Задача: Practice task
 * Щербак Орислав
 * Група ШІ-11
 */

bool textValidation(const char* text){
    int length = strlen(text);
    if(length == 0 || text[length-1] != '.'){
        return false;
    }
    bool hasWord = false;
    for(size_t i = 0; i < length - 1; i++){
        unsigned char c = text[i];
        if(isdigit(c) || isalpha(c)){
            hasWord = true;
        }
        else if(c != ' '){
            return false;
        }
    }
    return hasWord;
}
void freeWords(char**& words, int &count){
    if(words != nullptr){
        for(int i = 0; i < count; i++){
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
}
char** splitWords(const char* text, int &count){
    char copy[256];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';
    count = 0;
    char* token = strtok(copy, " ");
    while(token != nullptr){
        count++;
        token = strtok(nullptr, " ");
    }
    char** result = new char*[count];
    strcpy(copy, text);
    copy[strlen(copy) - 1] = '\0';
    token = strtok(copy, " ");
    for(int i = 0; i < count; i++){
        result[i] = new char[strlen(token) + 1];
        strcpy(result[i], token);
        token = strtok(nullptr, " ");
    }
    return result;
}
void countChars(const char* text, int& letters, int& digits, int& spaces){
    letters = 0;
    digits = 0;
    spaces = 0;
    int length = strlen(text);
    for(size_t i = 0; i < length; i++){
        if(isdigit(*(text+i))){
            digits++;
        }
        else if(isalpha(*(text+i))){
            letters++;
        }
        else if(*(text+i) == ' '){
            spaces++;
        }
    }
}
void showStats(const char* text, int count){
    printf("Текст: \t\"%s\"\n", text);
    int symbols = strlen(text);
    int letters, digits, spaces;
    printf("Символів: \t%d\n", symbols);
    printf("Слів: \t\t%d\n", count);
    countChars(text, letters, digits, spaces);
    double letterspercent = ((double)letters / symbols) * 100;
    double digitspercent = ((double)digits / symbols) * 100;
    double spacespercent = ((double)spaces / symbols) * 100;
    printf("Літер: \t\t%d ( %.1f%%)\n", letters, letterspercent);
    printf("Цифр: \t\t%d ( %.1f%%)\n", digits, digitspercent);
    printf("Пробілів: \t%d ( %.1f%%)\n", spaces, spacespercent);
}
void showTable(char** words, int count){
    printf("|  N |Слово            | Довж. |\n");
    for(int i = 0; i < count; i++){
        int length = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i+1, words[i], length);
    }
    int shortest = 0;
    int longest = 0;
    int total = 0;
    for(int i = 0; i < count; i++){
        int length = strlen(words[i]);
        if(length > strlen(words[longest])){
            longest = i;
        }
        else if(length < strlen(words[shortest])){
            shortest = i;
        }
        total += length;
    }
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", double(total) / count);
    char** sorted = new char*[count];
    for(int i = 0; i < count; i++){
        sorted[i] = words[i];
    }
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(strcmp(sorted[j], sorted[j+1]) > 0){
                char* temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    printf("За абеткою: ");
    for(int i = 0; i < count; i++){
        printf("%s ", sorted[i]);
    }
    printf("\n");
    int mostfrequentcounter = 0;
    char* mostfrequent = words[0];
    for(int i = 0; i < count; i++){
        int counter = 0;
        for(int j = 0; j < i + 1; j++){
            if(strcmp(sorted[i], sorted[j]) == 0){
                counter++;
            }
        }
        if(counter > mostfrequentcounter){
            mostfrequentcounter = counter;
            mostfrequent = sorted[i];
        }
    }
    printf("Найчастіше слово: %s (%d)\n", mostfrequent, mostfrequentcounter);
    delete[] sorted;
}
bool isValidWord(const char* word){
    if(word[0] == '\0'){
        return false;
    }
    int length = strlen(word);
    for(size_t i = 0; i < length; i++){
        unsigned char c = word[i];
        if(!isalnum(c)){
            return false;
        }
    }
    return true;
}
bool readWord(char word[32]){
    if(scanf("%31s", word) != 1){
        printf("Помилка: слово має складатись лише з латинських літер і цифр, та має бути до 31 символа\n");
        return false;
    }
    int next = getchar();
    bool ok = isValidWord(word) && isspace(next);
    if(!ok){
        printf("Помилка: слово має складатись лише з латинських літер і цифр, та має бути до 31 символа\n");
        while(next != '\n'){
            next = getchar();
        }
        return false;
    }
    ungetc(next, stdin);
    return true;
}
void replaceWord(char text[256], char**& words, int& count){
    char from[32], to[32];
    printf("Замінити слово: ");
    if(!readWord(from)){
        return;
    }
    printf("На слово: ");
    if(!readWord(to)){
        return;
    }
    string newword = to;
    string oldword = from;
    string oldtext = text;
    string newtext = oldtext;
    int replacements = 0;   
    size_t pos = newtext.find(oldword);
    while(pos != string::npos){
        size_t end = pos + oldword.length();
        bool start1 = (pos == 0) || !isalnum((unsigned char)newtext[pos - 1]);
        bool end1 = (end >= newtext.length() || !isalnum((unsigned char)newtext[end]));
        if(start1 && end1){
            newtext.replace(pos, oldword.length(), newword);
            replacements++;
            pos = newtext.find(oldword, pos + newword.length());
        }
        else{
            pos = newtext.find(oldword, pos + 1);
        }
    }
    if(newtext.length() > 255){
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        return;
    }
    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", oldtext.c_str());
    printf("Стало: \"%s\"\n", newtext.c_str());
    printf("Нова довжина: %d\n", (int)newtext.length());
    if(replacements>0){
        strcpy(text, newtext.c_str());
        freeWords(words, count);
        words = splitWords(text, count);
    }
}
void compareWords(){
    char a[32], b[32];
    printf("Перше слово: ");
    if(!readWord(a)){
        return;
    }
    printf("Друге слово: ");
    if(!readWord(b)){
        return;
    }
    int cmp = strcmp(a, b);
    int result;
    if(cmp < 0){
        result = -1;
    }
    else if(cmp > 0){
        result = 1;
    }
    else{
        result = 0;
    }
    string explanation;
    if(result == -1){
        explanation = "перше слово менше";
    }
    else if(result == 1){
        explanation = "перше слово більше";
    }
    else if(result == 0){
        explanation = "слова рівні";
    }
    string s1 = a;
    string s2 = b;
    printf("strcmp: %d -> %s\n", result, explanation.c_str());
    if(s1==s2){
        printf("Рівні (==): так\n");
    }
    else{
        printf("Рівні (==): ні\n");
    }
    int s1length = s1.length();
    int s2length = s2.length();
    bool equal = true;
    if(s1.length() != s2.length()){
        equal = false;
    }
    else{
        for(size_t i = 0; i < s1.length(); i++){
            if(tolower((unsigned char)s1[i]) != tolower((unsigned char)s2[i])){
                equal = false;
                break;
            }
        }   
    }
    if(equal == true){
        printf("Рівні без урахування регістру: так\n");
    }
    else{
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %d і %d\n", s1length, s2length);
    string joined = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}
void charInfo(const char* text){
    int ch;
    while((ch = getchar()) != '\n'){}
    printf("Введіть символ: ");
    char c;
    if(scanf("%c", &c) != 1 || c == '\n'){
        printf("Помилка: потрібно ввести один символ.\n");
        return;
    }
    int next = getchar();
    if(next != '\n'){
        printf("Помилка: потрібно ввести лише один символ.\n");
        while(next != '\n'){
            next = getchar();
        }
        return;
    }
    int code = (unsigned char)c;
    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex %#x, oct %#o, bin ", code, code, code);
    char bits[9];
    bits[8] = '\0';
    int temp = code;
    for(int i = 7; i >= 0; i--){
        bits[i] = '0' + (temp & 1);
        temp = temp >> 1;
    }   
    printf("%s)\n", bits);
    const char* type;
    if(isupper(code)){
        type = "велика літера";
    }
    else if(islower(code)){
        type = "мала літера";
    }
    else if(isdigit(code)){
        type = "цифра";
    }
    else if(isspace(code)){
        type = "пробільний символ";
    }
    else{
        type = "інший символ";
    }
    printf("Тип: %s\n", type);
    if(isupper(code)){
        char updatedcode = tolower(code);
        printf("Інший регістр: '%c'\n", updatedcode);
    }
    else if(islower(code)){
        char updatedcode = toupper(code);
        printf("Інший регістр: '%c'\n", updatedcode);
    }
    int nextcode = code + 1;
    printf("Наступний символ: '%c'\n", nextcode);
    int count = 0;
    int first = 0;
    int length = strlen(text);
    for(int i = 0; i < length; i++){
        if(text[i] == c){
            count++;
            if(count == 1){
                first = i + 1;
            }
        }
    }
    if(count > 0){
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, first);
    }
    else{
        printf("Входжень у тексті: 0, символ у тексті не зустрічається\n");
    }
}
void newSentence(char text[256], char**& words, int& count){
    printf("Введіть речення (крапка після останнього слова): ");
    string sentence;
    string w;
    int readCount = 0;
    while(cin >> w){
        if(w != "."){
            readCount++;
        }
        if(!sentence.empty()){
            sentence += " ";
        }
        sentence += w;
        if(w[w.length() - 1] == '.'){
            break;
        }
    }
    if(!cin){
        cin.clear();
    }
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF){}
    if(sentence.length() > 255){
        printf("Помилка: речення перевищує 255 символів, текст не змінено.\n");
        return;
    }
    if(!textValidation(sentence.c_str())){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", readCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}
int main(){
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(fgets(text, 256, stdin) == NULL){
        printf("Помилка зчитування тексту.");
        return 1;
    }
    char *newline = strchr(text, '\n');
    if(newline != nullptr){
        *newline = '\0';
    }
    else{
    int ch = getchar();
    if(ch != '\n'){
        printf("Помилка: текст перевищує 255 символів.\n");
        return 1;
    }
    }
    if(!textValidation(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }
    int count = 0;
    char** words = splitWords(text, count);
    int choice = -1;
    do{
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");
        int status = scanf("%d", &choice);
        if(status != 1){
            printf("Помилка: введіть номер пункту меню.\n");
            char rest[256];
            if(fgets(rest, 256, stdin) == nullptr){
                break;
            }
            continue;
        }
        int after = getchar();
        if(after != '\n'){
            printf("Помилка: введіть номер пункту меню.\n");
            while(after != '\n'){
                after = getchar();
            }
            continue;
        }   
        if(choice < 0 || choice > 6){
            printf("Помилка: пункту %d немає в меню.\n", choice);
            continue;
        }
        switch (choice)
        {
        case 1:{
            showStats(text, count);
            break;
        }
        case 2:{
            showTable(words, count);
            break;
        }
        case 3: {
            replaceWord(text, words, count);
            break;
        }
        case 4:{
            compareWords();
            break;
        }
        case 5:
            charInfo(text);
            break;
        case 6:
            newSentence(text, words, count);
            break;
        default:
            break;
        }
    }while(choice != 0);
    freeWords(words, count);
    return 0;
}