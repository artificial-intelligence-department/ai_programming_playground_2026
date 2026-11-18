/*
 * Задача: Редактор текстового повідомлення
 * Автор: Морикишка Данило
 * Група: ШІ-11
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;
bool isValidText(const char *text);
void showMenu();
char **splitWords(const char *text, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void ShowStats(char *text);
void wordsTable(char *text);
void replaceWord(char *text);
void symbolStats(char *text, int count);
void compareTwo();
void newSentence(char * text);
void freeWords(char ** words, int count);
const int MAX_COUNT_OF_SYMBOLS = 256;
const int MAX_COMPARABLE_WORD_LENGTH = 32;
int main()
{
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    char text[MAX_COUNT_OF_SYMBOLS];
    if(fgets(text, MAX_COUNT_OF_SYMBOLS, stdin) == NULL){
        printf("Помилка. Некоректний ввід даних.");
        return 1;
    }
    text[strcspn(text, "\n")] = '\0'; 
    if(!isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
        return 1;
    }
    int userChoice;
    bool isWork = true;
    do{
        printf("Меню:\n");
        showMenu();
        printf("Введіть ваш вибір: ");
        scanf("%d", &userChoice);
        switch (userChoice)
        {
        case 1:
            ShowStats(text);
            break;
        case 2:
            wordsTable(text);
            break;
        case 3:
            replaceWord(text);
            break;
        case 4:
            compareTwo();
            break;
        case 5:
            symbolStats(text, strlen(text));
            break;
        case 6:
            newSentence(text);
            break;
        case 0:
            printf("Вихід з програми.\n");
            isWork = false;
            break;
        default:
            printf("Помилка. Введено некоректне значення, програма завершується через аварійний стан...\n");
            return 1;
        }
    }
    while (isWork);
    return 0;
}
bool isValidText(const char *text)
{
    int len = strlen(text);
    if(len < 2){
        return false;
    }
    for (int i = 0; i < len - 1; i++){
        if(!isalnum(text[i]) && text[i] != ' '){
            return false;
        }
    }
    if(text[strlen(text) - 1] != '.'){
        return false;
    }
    return true;
}
void showMenu()
{
    printf("%-5s%20s" , "Пункт", "Операція\n");
    printf("%-8d%s" , 1, "Показати текст і статистику\n");
    printf("%-8d%s" , 2, "Таблиця слів\n");
    printf("%-8d%s" , 3, "Замінити слово\n");
    printf("%-8d%s" , 4, "Порівняти два слова\n");
    printf("%-8d%s" , 5, "Інформація про символ\n");
    printf("%-8d%s" , 6, "Ввести нове речення\n");
    printf("%-8d%s" , 0, "Вийти\n");
}
char **splitWords(const char *text, int &count){
    char d[] = " .";
    char copy[MAX_COUNT_OF_SYMBOLS];
    strcpy(copy, text);
    char *wordA = strtok(copy, d);
    while (wordA != NULL)
    {
        count++;
        wordA = strtok(NULL, d);
    }
    char **words = new char*[count];
    strcpy(copy, text);
    int k = 0;
    wordA = strtok(copy, d);
    while (wordA != NULL)
    {
        words[k] = new char[strlen(wordA) + 1];
        strcpy(words[k], wordA);
        k++;
        wordA = strtok(NULL, d);
    }
    return words;
}
void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    int word = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if(*(text + i) == ' ' ){
            spaces++;
        }
        else if(*(text + i) == '.'){
            word++;
        }
        if(isalpha(*(text + i))){
            letters++;
        }
        if(isdigit(*(text + i))){
            digits++;
        }
    }
}
void ShowStats(char *text)
{   int letters = 0;
    int digits = 0;
    int spaces = 0;
    countChars(text, letters, digits, spaces);
    int wordCount = 0;
    char** listOfWords = splitWords(text, wordCount);
    int len = strlen(text);
    printf("Текст: \"%s\"\n", text);
    printf("Символів: %d\n", strlen(text));
    printf("Слів: %d\n", wordCount);
    printf("Літер: %d(%5.1f%%)\n", letters, 100.0 * letters / len);
    printf("Цифр: %d(%5.1f%%)\n", digits, 100.0 * digits / len);
    printf("Пробілів: %d(%5.1f%%)\n", spaces, 100.0 * spaces/len);
    freeWords(listOfWords, wordCount);
}
void wordsTable(char *text)
{
    int count = 0;
    char **words = splitWords(text, count);
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    int total = 0;
    int longest = 0;
    int shortest = 0;
    for (int i = 0; i < count; i++)
    {
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
        total += len;
        if(len > strlen(words[longest])){
            longest = i;
        }
        if(len < strlen(words[shortest])){
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)total / count);
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++)
    {
       sorted[i] = words[i];
    }
    for (int i = 0; i < count -1; i++)
    {
        for (int j = 0; j < count -1; j++)
        {
            if(strcmp(sorted[j], sorted[j + 1]) > 0){
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    printf("За абеткою: ");
    for (int i = 0; i < count; i++)
    {
        printf(" %s", sorted[i]);
    }
    printf("\n");
    int bestIndex = 0;
    int bestCount = 0;
    int  i = 0;
    while (i < count)
    {
        int j = i;
        while (j < count && strcmp(sorted[j], sorted[i]) == 0)
        {
            j++;
        }
        if(j - i > bestCount){
            bestCount = j -i;
            bestIndex = i;
        }
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);
    delete[] sorted; 
    freeWords(words, count);
}
void replaceWord(char *text)
{
    printf("Замінити слово: ");
    char from[MAX_COMPARABLE_WORD_LENGTH];
    scanf("%31s", from);
    printf("На слово: ");
    char to[MAX_COMPARABLE_WORD_LENGTH];
    scanf("%31s", to);
    int count = 0;
    string result;
    int replaced = 0;
    char **words = splitWords(text, count);
    for (int i = 0; i < count; i++)
    {
        if(result != ""){
            result += ' ';
        }
        if(strcmp(words[i], from) == 0){
            result += to;
            replaced++;
        }
        else{
            result += words[i];
        }
    }
    result += '.';
    
    if(result.size() <= MAX_COUNT_OF_SYMBOLS - 1){
     printf("Замін виконано: %d\n", replaced);
     printf("Було:  \"%s\"\n", text);
     strcpy(text, result.c_str());
     printf("Стало: \"%s\"\n", text);
     printf("Нова довжина: %d\n", (int)strlen(text));
    }
    else{
        printf("Помилка: після заміни текст перевищить 255 символів.\n");
    }
    freeWords(words, count);
}
void compareTwo()
{
    printf("Перше слово: ");
    char a[MAX_COMPARABLE_WORD_LENGTH];
    scanf("%31s", a);
    printf("Друге слово: ");
    char b[MAX_COMPARABLE_WORD_LENGTH];
    scanf("%31s", b);
    b[strcspn(b, "\n")] = '\0'; 
    string word1 = "";
    for (int i = 0; i < strlen(a); i++)
    {
        word1 += a[i];
    }
    string word2 = "";
    for (int i = 0; i < strlen(b); i++)
    {
        word2 += b[i];
    }
    printf("strcmp: ");
    if(strcmp(a, b) != 0){
        if(strcmp(a, b) > 0){
            printf("1 -> перше слово більше\n");
        }
        else{
            printf("-1 -> перше слово менше\n");
        }
    }
    else{
        printf("0 -> слова однакові\n");
    }
    printf("Рівні (==): ");
    if(word1 == word2){
        printf("так\n");
    }
    else{
        printf("ні\n");
    }
    printf("Рівні без урахування регістру: ");
    if(strlen(a) != strlen(b)){
        printf("ні\n");
    }
    else{
        bool isOk = true;
        for (int i = 0; i < strlen(a); i++)
        {
        if(tolower(a[i]) !=  tolower(b[i])){
            isOk = false;
            break;
        }
        }
        if(isOk){
        printf("так\n");
        }
        else{
        printf("ні\n");
        }
    }
    printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));
    string connector = " & ";
    string concat = word1;
    concat += connector;
    concat += word2;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
}
void symbolStats(char *text, int count)
{
    printf("Введіть символ: ");
    char c;
    scanf(" %c" , &c);
    printf("Символ: ");
    printf("'%c'\n", c);
    printf("Код: %d",  c);
    printf(" (hex %#x", c);
    printf(", oct %#o", c);
    printf(", bin ");
    for (int b = 7; b >= 0; b--)
    {
        printf("%d", (c >> b) & 1);
    }
    printf(")\n");
    printf("Тип: ");
    if(islower(c)){
        printf("мала літера\n");
    }
    else if(isdigit(c)){
        printf("цифра\n");
    }
    else if(isupper(c)){
        printf("велика літера\n");
    }
    else if(ispunct(c)){
        printf("розділовий знак, спеціальні символи\n");
    }
    printf("Інший регістр: ");
    if(isalpha(c) && islower(c)){
        printf("'%c'\n", (toupper(c)));
    }
    else if(isalpha(c) && isupper(c)){
        printf("'%c'\n", (tolower(c)));
    }
    else{
        printf("Іншого регістру для даного символу не існує\n");
    }
    printf("Наступний символ: '%c'\n", c + 1);
    int countInTxt = 0;
    int frstIn = 0;
    bool hasFound = false;
    for (int i = 0; i < count; i++)
    {
        if(countInTxt == 0 && c == text[i]){
            frstIn = i + 1;
            hasFound = true;
            countInTxt++;
        }
        else if(c == text[i]){
            countInTxt++;
        }
    }
    if(!hasFound){
        printf("Цього символу немає в тексті.\n");
    }
    else{
         printf("Входжень у тексті: %d", countInTxt);
        printf(", перше на позиції %d\n", frstIn );
    }
}
void newSentence(char * text)
{
    string word;
    string sentence;
    int countOfWords = 0;
    int i = 0;
    while (cin >> word)
    {
        countOfWords++;
        if (!sentence.empty()) {
        sentence += ' ';
        }
        sentence += word;
        if(word.back() == '.'){
            break;
        }
    }
    printf("Прочитано слів: %d\n", countOfWords);
    if(sentence.length() <= MAX_COUNT_OF_SYMBOLS - 1 && isValidText(sentence.c_str())){
        strcpy(text, sentence.c_str());
        printf("Новий текст: \"%s\"\n", text);
        printf("Довжина: %d\n", (int)strlen(text));
    }
    else{
        printf("Помилка. Речення не коректне\n");
    }
}
void freeWords(char ** words, int count)
{
    for (int i = 0; i < count; i++)
    {
        delete[] words[i];
    }
    delete[] words;   
}
