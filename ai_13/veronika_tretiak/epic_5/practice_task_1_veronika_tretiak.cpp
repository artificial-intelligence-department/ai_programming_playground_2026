/*
Задача: Редактор текстового повідомлення
Автор: Вероніка Третяк
Група: ШІ-13
*/
#include <iostream> 
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;
//Оголошення функцій
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showStatistics(const char *text, int countwords);
void quickSort(char **sorted, int left, int right);
void Tableline(int width);
void showtable( char **words, int countwords);
bool readword(char word[]);
void replaceWord(char text[256], char **words, int countwords);
void comparewords();
void symbolInfo(const char text[]);
void newSentence(char text[], char**&words, int &count);


int main(){
char text[256];
int count = 0;
int choice;
//Зчитування початкового тексту
printf("Введіть текст (до 255 символів, крапка в кінці): ");
fgets(text, 256, stdin);
//Видалення символу нового рядка
int len = strlen(text);
if(len > 0 && text[len - 1] == '\n' ){
    text[len - 1] = '\0';
    len--;
}
//Перевірка введення
if(len > 0 && text[len - 1] == '.'){
    for(int i = 0; i < len - 1; i++){
        char c = text[i];
        if(c == ' '){
            continue;
        }
        if(isalpha(static_cast<unsigned char>(c)) || isdigit(static_cast<unsigned char>(c)))
        {
        count++;
        } else{
        count = 0;
        break;
        }
    }
}
if(count == 0){
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. \n");
            return 0;
        }
        //Розбиваємо текст на слова
        int countwords = 0;
        char** words = splitWords(text, countwords);
do{//Виводимо меню програми
    printf( "Меню:\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    int symbol = getchar();
    if(symbol < 0){
        break;
    }
    int next = symbol;
    if(symbol != '\n'){
        next = getchar();
 }
 if(symbol < '0' || symbol > '6' || next != '\n'){
    while(next >= 0 && next != '\n'){
        next = getchar();
    }
    printf("Помилка: Введіть пункт з меню\n");
    choice = -1;
    continue;
 }
 choice = symbol - '0';
 //Виконання окремого вибраного пункту
 switch(choice){
    case 1: {
    showStatistics(text, countwords);
    break;
    }
    case 2: {
    showtable(words, countwords);
    break;
    }
    case 3: {
    replaceWord(text, words, countwords);
    break;
    }
    case 4: {
    comparewords();
    break;
    }
    case 5: {
    symbolInfo(text);
    break;
    }
    case 6: {
    newSentence(text, words, countwords);
    break;
    }
 }
    

}while(choice != 0);
}
//Функція для поділу на окремі слова
char **splitWords(const char *text, int &count){
    count = 0;
    for(int i = 0; text[i] != '.'; i++){
        if(text[i] != ' ' && (i == 0 || text[i - 1] == ' ')){
            count++;
        }
    }
char ** words = new char*[count];
char copytext[256];
strcpy(copytext, text);
char* word = strtok(copytext, " .");
int k = 0;
while(word != nullptr){
    words[k] = new char[strlen(word) + 1];
    strcpy(words[k], word);
    k++;
    word = strtok(nullptr, " .");
}
return words;
}
//Функція для звільнення памʼяті, яку ми виділяли для слів
void freeWords(char **&words, int &count){
    for(int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}
//Функція, що рахує кількість літер, цифр та пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces){
 letters = 0;
 digits = 0;
 spaces = 0;
 const char *p = text;
 while(*p != '\0'){
    if(isalpha(static_cast<unsigned char>(*p))){
        letters++;
    } else if(isdigit(static_cast<unsigned char>(*p))){
        digits++;
    } else if(isspace(static_cast<unsigned char>(*p))){
        spaces++;
    }
    p++;
 }
}
//Функція для виведення статистики тексту
void showStatistics(const char *text, int countwords){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);
    printf("Текст: \t\"%s\"\n", text);
    printf("Символів: %3d\n", len);
    printf("Слів: %3d\n", countwords);
    printf("Літер: %3d (%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр: %3d (%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів: %3d (%5.1f%%)\n", spaces, 100.0 * spaces / len);

}
//Функція сортує слова за алфавітом
void quickSort(char **sorted, int left, int right){
    if(left >= right){
        return;
    }
    int i = left;
    int j = right;
    const char *pivot = sorted[(left + right) / 2];
    while(i <= j){
        while(strcmp(sorted[i], pivot) < 0){
            i++;
        }
        while(strcmp(sorted[j], pivot) > 0){
            j--;
        }
        if(i <= j){
            char *tmp = sorted[i];
            sorted[i] = sorted[j];
            sorted[j] = tmp;
            i++;
            j--;
        }
    }
    quickSort(sorted, left, j);
    quickSort(sorted, i, right);
}
//Функція малює лінію таблиці для другого пункту
void Tableline(int width){
    printf("+-----+");
    for(int i = 0; i <  width + 2; i++){
    printf("-");
    }
    printf("+-------+\n");
}
//Функція виводить таблицю слів та інформацію про них
void showtable( char **words, int countwords){
    if(countwords == 0){
        printf("Слів немає\n");
        return;
    }
    int longest = 0;
    int shortest = 0;
    int sum = 0;
    for(int i = 0; i < countwords; i++){
        int len = strlen(words[i]);
        sum += len;
       if (strlen(words[i]) > strlen(words[longest])){
            longest = i;
        }
        if (strlen(words[i]) < strlen(words[shortest])){
            shortest = i;
        }
    }
    printf("|   N |       Слово      |  Довж.|\n");
    for(int i = 0; i < countwords; i++){
        int len = strlen(words[i]);
        printf("| %3d | %-16s | %5d |\n", i + 1, words[i], len);
    }
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина слова: %.2f\n", static_cast<double>(sum) / countwords);
    char **sorted = new char*[countwords];
    for(int i = 0; i < countwords; i++){
        sorted[i] = words[i];
    }
    quickSort(sorted, 0, countwords - 1);
    printf("За абеткою: ");
    for(int i = 0; i < countwords; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");

    const char *freq = sorted[0];
    int max = 1;
    int currentcount = 1;
    for(int i = 1; i < countwords; i++){
        if(strcmp(sorted[i], sorted[i - 1]) == 0){
            currentcount++;
        } else{
            currentcount = 1;
        }
        if(currentcount > max){
            max = currentcount;
            freq = sorted[i];
        }
    }
    printf("Найчастіше слово: %s (%d)\n", freq, max);
    delete[] sorted;
}
//Функція зчитує слово та перевіряє його правильність
bool readword(char word[]){
    if(scanf("%31s", word) != 1){
        printf("Помилка введення\n");
        return false;
    }
    if(strlen(word) > 31){
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF){
        }
        printf("Помилка: Слово може містити до 31 символу.\n");
        return false;
    }
    for(int i = 0; word[i] != '\0'; i++){
        unsigned char c = word[i];
        if( c > 127 || (!isalpha(c) && !isdigit(c))){
            printf("Помилка: Дозволені лише латинські літери та цифри.\n");
            return false;
        }
    }
    return true;
}
//Функція замінює задане слово в тексті
void replaceWord(char text[256], char **words, int countwords){
   char from[32];
   char to[32];
   printf("Замінити слово: ");
   if(!readword(from)){
    return;
   }
   printf("На слово: ");
   if(!readword(to)){
    return;
   }
   string result = text;
   int changes = 0;
   size_t position = 0;
   while((position = result.find(from, position)) != string::npos){
    size_t after = position +strlen(from);
    bool left = (position == 0 || result[position - 1] == ' ');
    bool right = (result[after] == ' ' || result[after] == '.');
    if(left && right){
        result.replace(position, strlen(from), to);
        changes++;
        position += strlen(to);
    }
    else {
        position++;
    }

   }
   if(result.length() > 255){
    printf("Помилка: Після замін текст перевищить 255 символів.\n");
    return;
   }
   printf("Замін було виконано: %d\n", changes);
   printf("Було: \"%s\"\n", text);
   strcpy(text, result.c_str());
   for( int i = 0; i < countwords; i++){
    if(strcmp(words[i], from) == 0){
        char* newword = new char[strlen(to) + 1];
        strcpy(newword, to);
        delete[] words[i];
        words[i] = newword;
    }
   }
   printf("Стало: \"%s\"\n", text);
   printf("Нова довжина: %zu\n", result.length());

}
//Функція порівнює два введені слова
void comparewords(){
    char a[32];
    char b[32];

    printf("Перше слово: ");
    if(!readword(a)){
        return;
    }
    printf("Друге слово: ");
    if(!readword(b)){
        return;
    }
    int result = strcmp(a, b);
    if(result < 0){
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if(result > 0){
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else{
        printf("strcmp: 0 -> слова рівні\n");
}
string first = a;
string second = b;
if(first == second){
    printf("Рівні (==): так\n");
}
else{
    printf("Рівні (==): ні\n");
}
string lowerf = first;
string lowers = second;
for(size_t i = 0; i < lowerf.length(); i++){
lowerf[i]= tolower(lowerf[i]);
}
for(size_t i = 0; i < lowers.length(); i++){
    lowers[i]= tolower(lowers[i]);
}
if(lowerf == lowers){
    printf("Рівні без урахування регістру: так\n");
}
else{
    printf("Рівні без урахування регістру: ні\n");
}
printf("Довжини: %zu і %zu\n", first.length(), second.length());
string joined = first + " & " + second;
printf("Конкатенація: \"%s\" (%zu)\n", joined.c_str(), joined.length());
}
//Функція виводить інформацію про заданий символ
void symbolInfo(const char text[]){
char input[3];
printf("Введіть символ: ");
if(fgets(input, sizeof(input), stdin) == nullptr){
    return ;
}
if(input[0] == '\n'){
    printf("Помилка: Введіть символ.");
    return;
}
char c = input[0];
unsigned int code = static_cast<unsigned char>(c);
printf("Символ: '%c'\n", c);
printf("Код: %u (hex 0x%02X, oct 0%o, bin ", code, code, code);
for(int div = 128; div >= 1; div /= 2){
    printf("%u", (code / div) % 2);
}
printf(")\n");
if(isupper(code)){
    printf("Тип: велика літера\n");
    printf("Інший регістр: '%c'\n", tolower(code));
}
else if(islower(code)){
    printf("Тип: мала літера\n");
    printf("Інший регістр: '%c'\n", toupper(code));
}
else if(isdigit(code)){
printf("Тип: цифра\n");
}
else if(isspace(code)){
    printf("Тип: пробіл\n");
}
else{
    printf("Тип: інший символ\n");
}
if(code < 255){
    int next = static_cast<int>(code) + 1;
    if(isprint(next)){
        printf("Наступний символ: '%c'\n ", next);
    }
    else {
        printf("Наступний символ: недрукований (код %d)\n", next);
    }
}
else {
    printf("Наступного символу немає\n");
}
int count = 0;
int fposition = 0;
for(int i = 0; text[i] != '\0'; i++){
    if(text[i] == c){
        count++;
        if(count == 1){
            fposition = i + 1;
        }
    }
}
if(count == 0){
    printf("Символ у тексті відсутній\n");
}
else {
    printf("Входжень у тексті: %d, перше на позиції %d\n", count, fposition);
}
}
//Функція для введення нового речення
void newSentence(char text[], char**&words, int &count){
    string sentence;
    string word;
    int wordsread = 0;
    printf("Введіть речення (крапка після останнього слова): \n");
    while(cin >> word){
        if(wordsread > 0){
            sentence += ' ';
        }
        sentence += word;
        wordsread++;
        if(word.back() == '.'){
            break;
        }
    }
    int len = sentence.length();
    if(len < 2 || len > 255 || sentence[len - 1] != '.'){
        printf("Помилка: некоректне речення\n");
        return;
    }
    int lettordit = 0;
    for(int i = 0; i < len - 1; i++){
        unsigned char c = static_cast<unsigned char>(sentence[i]);
        if(c == ' '){
            continue;
        }
        if(isalpha(c) || isdigit(c)){
            lettordit++;
        }
        else{
            printf("Помилка: Дозволені лише латинські літери, цифри, пробіли\n");
            return;
        }
    }
    if(lettordit == 0){
        printf("Помилка: введіть хоча б одну літеру або цифру\n");
        return;
    }
    int newcount = 0;
    char** newwords = splitWords(sentence.c_str(), newcount);
    freeWords(words, count);
    words = newwords;
    count = newcount;
    strcpy(text, sentence.c_str());
    printf("Прочитано слів: %d\n", wordsread);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}

