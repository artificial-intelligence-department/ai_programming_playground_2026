/*
Task: Practice_task: Редактор текстового повідомлення 
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <string>
#include <cstring> 
#include <cctype>
#include <cstdio>

using namespace std;

const int MAXLEN = 255;

char **splitWords(const char *text, int &count, int len);
bool isTextValid(char *text, int &len);
void clearBuffer();
void countChars(const char *text, int &letters, int &digits, int &spaces);
void textStatistic(const char *text, int letters, int digits, int spaces, int count, int len);
void tableOfWords(const char *text, int count, int len, char **splitedWords);
char** sortingText(const char *text, int count, int len, char **splitedWords);
void changeWord(char *text, int &len, int &count, char **&splitedWords);
void wordComparison();
bool isWordChar(char c);
void symbolInfo(const char *text, int len);
void newSentence(char *text, int &count, int &len, char **&splitedWords);
void freeWords(char **&words, int &count);

int main (){

    char text[MAXLEN + 2];
    int count = 0;
    int len = 0;

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, sizeof(text), stdin);


    if(!isTextValid(text, len)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }
    char **splitedWords = splitWords(text, count, len);

    int letters, digits, spaces;
    int action = 0;    

     do{
        printf("\n");
        printf("\n======================МЕНЮ==========================\n");
        printf("1 \t Показати текст і статистику\n");
        printf("2 \t Таблиця слів\n");
        printf("3 \t Замінити слово\n");
        printf("4 \t Порівняти два слова\n");
        printf("5 \t Інформація про символ\n");
        printf("6 \t Ввести нове речення\n");
        printf("0 \t ВИЙТИ\n");


        action = -1;
        char term;

        printf("Оберіть ДІЮ: ");
        if(scanf("%d%c", &action, &term) != 2 || term != '\n'){
             printf("Помилка: введіть номер пункту меню! \n");
             clearBuffer();
             continue; 
        }

        switch (action)
        {
        case 1:
            textStatistic(text, letters, digits, spaces, count, len);
            break;
        case 2:
            tableOfWords(text, count, len, splitedWords);
            break;    
        case 3:
            changeWord(text, len, count, splitedWords);
            break;
        case 4: 
            wordComparison ();
            break;  
        case 5:
            symbolInfo(text, len);
            break;
        case 6:
            newSentence(text, count, len, splitedWords);
            break;
        case 0:
            break;
        default:
            printf("Помилка: пункту %d немає у меню! \n", action);
            break;
        }



    } while (action != 0);


    freeWords(splitedWords, count);


    return 0;
}
    
void freeWords(char **&words, int &count){
    for(int i = 0; i < count; i++){
        delete [] words[i];
    }
    delete[] words;

}
    //іункція для очистки буферу після не вдалого вводу
void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);

}

    //Функція для перевірки тексту на коректність
bool isTextValid(char *text, int &len){
     len = strlen(text);

    //Прибираємо символ перенесення рядка '\n'
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    //Перевіряємо, чи рядок не порожній і чи закінчується крапкою '.'
    if (len == 0 || text[len - 1] != '.') {
        return false;
    }

    bool hasWord = false;

    for (int i = 0; i < len - 1; i++) {
        unsigned char ch = static_cast<unsigned char>(text[i]);

        // Перевірка на латинські літери, цифри або пробіл
        bool isLatin = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
        bool isDigit = isdigit(ch);
        bool isSpace = isspace(ch);

        if (!isLatin && !isDigit && !isSpace) {
            return false; 
        }

        if (isLatin || isDigit) {
            hasWord = true;
        }
    }

    //Текст коректний, тільки якщо знайдено хоча б одне слово
    return hasWord;
}


    //Функція для зберігання слів з тексту
char **splitWords(const char *text, int &count, int len){

    char *temp = new char[len+1];
    
    strcpy(temp, text);
    temp[len - 1] = '\0';

    char **words = new char*[len];
    count = 0;
    char *t = strtok(temp, " ");
    while (t != NULL) {
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }

    delete [] temp;

    return words;
}

    //функція для обрахунку літер цифр і пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces){

    letters = 0;
    digits = 0;
    spaces = 0;
    
    const char *temp = text;
    

     while(*temp != '\0'){
        if(isalpha((unsigned char)*temp)){
            letters++;
        }else if(isdigit((unsigned char)*temp)){
            digits++;
        }else if(isspace((unsigned char)*temp)){
            spaces++;
        }

        temp++;
     }

}

    //функція для виводу тексту і статистики
void textStatistic(const char *text, int letters, int digits, int spaces, int count, int len){


    countChars(text, letters, digits, spaces);
    double letPercent = (static_cast<double>(letters)/len)*100;
    double digPercent = (static_cast<double>(digits)/len)*100;
    double spcPercent = (static_cast<double>(spaces)/len)*100;

    printf("\n=============== Текст і статистика =================\n");
    printf("Текст: \t \"%s\" \n", text);
    printf("Символів: \t %d \n", len);
    printf("Слів: \t\t %d \n", count);
    printf("Літер: \t\t %d (%.1f%%) \n", letters, letPercent);
    printf("Цифр: \t\t %d (%.1f%%) \n", digits, digPercent);
    printf("Пробілів: \t %d (%.1f%%) \n", spaces, spcPercent);



}
    //Функція для виводу таблиці слів, найдовшого/найкоротшого, середнє знач., за абеткою та найчастіше слово
void tableOfWords(const char *text, int count, int len, char **splitedWords){
    char **temp = splitedWords;

    int theLongest = strlen(temp[0]);
    int theShortest = strlen(temp[0]);
    int totallen = 0;

    char *ThelongW = temp[0];
    char *TheShortW = temp[0];

    printf("+----+---------------+--------+\n");
    printf("|  N | Слово         | Довж.  |\n");
    printf("+----+---------------+--------+\n"); 

    //рахуємо найдовше і найменше і виводимо слова
    for (int i = 0; i < count; i++){
        int wordLen = strlen(temp[i]);
        totallen += wordLen;

        if(wordLen > theLongest){
            theLongest = wordLen;
            ThelongW =  temp[i];
        }else if(wordLen < theShortest){
            theShortest = wordLen;
            TheShortW = temp[i];
        }
        printf("| %2d | %-13s | %6d |\n", (i+1), temp[i], wordLen);
    }
    printf("+----+---------------+--------+\n");

    printf("Найдовше слово: %s (%d)\n", ThelongW, theLongest);
    printf("Найкоротше слово: %s (%d)\n", TheShortW, theShortest);
    printf("Середня довжина: %.2f\n", static_cast<double>(totallen) / count);
    char **sortedWords = sortingText(text, count, len, splitedWords);
    printf("За абеткою: ");
    for(int i = 0; i < count; i++){
        printf("%s ", sortedWords[i]);
    }

    int maxCount = 1;
    int currentWcount = 1;
    char *maxWord = sortedWords[0];

    //шукаємо найчастіше слово
    for(int i = 1; i < count; i++){
        if(strcmp(sortedWords[i], sortedWords[i-1]) == 0){
            currentWcount++;
        }else{
            currentWcount = 1;
        }
        if(currentWcount > maxCount){
            maxCount = currentWcount;
            maxWord = sortedWords[i];
        }

    }
    printf("\nНайчастіше слово: ");
    
    printf("%s (%d)\n", maxWord, maxCount); 

    //звільняємо лише масив вказівників
    delete[] sortedWords;
}

    //функція сортування слів в реченні
char** sortingText(const char *text, int count, int len, char **splitedWords){
    char **sortedtext = new char*[count];

    //копіюємо елементи
    for (int i = 0; i < count; i++) {
        sortedtext[i] = splitedWords[i];
    }

    //сортуємо insection sort
    for (int i = 1; i < count; i++) {
        char *temp = sortedtext[i];
        int j = i - 1;
        while (j >= 0 && strcmp(sortedtext[j], temp) > 0) {
            sortedtext[j + 1] = sortedtext[j];
            j--;
        }
        sortedtext[j + 1] = temp;
    }
    return sortedtext;
}

// чи символ може бути частиною слова
bool isWordChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}


    //Функція для заміни слова
void changeWord(char *text, int &len, int &count, char **&splitedWords){
    char oldWordBuf[32];
    char newWordBuf[32];

    printf("Замінити слово: ");

    scanf("%32s", oldWordBuf);
    clearBuffer();
    
    if(strlen(oldWordBuf) > 31) {
        printf("Помилка: задовге слово! (не більше 31 символа) \n");
        return;
    }
    for (int i = 0; oldWordBuf[i] != '\0'; i++) {
        if (!isWordChar(oldWordBuf[i])) {
            printf("Помилка: слово повинне складатися тільки з латинських літер і цифр!\n");
            return;
        }
    }


    printf("На слово: ");
    scanf("%32s", newWordBuf);
    clearBuffer();

    if(strlen(newWordBuf) > 31) {
        printf("Помилка: задовге слово! (не більше 31 символа) \n");
        return;
    }
    for (int i = 0; newWordBuf[i] != '\0'; i++) {
        if (!isWordChar(newWordBuf[i])) {
            printf("Помилка: слово повинне складатися тільки з латинських літер і цифр!\n");
            return;
        }
    }

    //перевірка нового слова
    for (int i = 0; newWordBuf[i] != '\0'; i++) {
        if (!isWordChar(newWordBuf[i])) {
            printf("Помилка: слово повинне складатися тільки з латинських літер і цифр!\n");
            return;
        }
    }

    string oldWord = oldWordBuf;
    string newWord = newWordBuf;
    string source = text;
    string result;
    int replaced = 0;

    //проходимо по тексту
    int i = 0;
    while (i < source.size()) {
        if (isWordChar(source[i])) {
            int j = i;
            while (j < source.size() && isWordChar(source[j])) {
                j++;
            }
            string word = source.substr(i, j - i);   // ціле слово

            if (word == oldWord) {
                result += newWord;
                replaced++;
            } else {
                result += word;
            }
            i = j;
        } else {
            result += source[i];   // пробіл або крапка
            i++;
        }
    }

    //перевірка довжини
    if (result.size() >= MAXLEN) {
        printf("Помилка: результат довший за %d символів! Текст не змінено.\n", MAXLEN);
        return;
    }
    printf("Замін виконано: %d\n", replaced);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %d\n", (int)result.size());

    //зберігаємо новий текст
    strcpy(text, result.c_str());
    len = result.size();

    // перебудовуємо масив слів
    for (int i = 0; i < count; i++) {
        delete[] splitedWords[i];
    }
    delete[] splitedWords;
    splitedWords = splitWords(text, count, len);
}


//функція для порівняння слів
void wordComparison (){
    char a [32];
    char b [32];

    //Просимо ввести слова на порівняння та валідуємо їх
    printf("Введіть перше слово: ");
    scanf("%32s", a);
    
    clearBuffer();
    if(strlen(a) > 31) {
        printf("Помилка: задовге слово! (не більше 31 символа) \n");
        return;
    }
    for (int i = 0; a[i] != '\0'; i++) {
        if (!isWordChar(a[i])) {
            printf("Помилка: слово повинне складатися тільки з латинських літер і цифр!\n");
            return;
        }
    }

    printf("Введіть друге слово: ");
    scanf("%32s", b);
    clearBuffer();
    if(strlen(b) > 31) {
        printf("Помилка: задовге слово! (не більше 31 символа) \n");
        return;
    }
    for (int i = 0; b[i] != '\0'; i++) {
        if (!isWordChar(b[i])) {
            printf("Помилка: слово повинне складатися тільки з латинських літер і цифр!\n");
            return;
        }
    }


    //порівнюємо і виводимо наше порівняння

    int comparison = strcmp(a,b);

    if(comparison < 0){
        printf("strcmp: -1 -> перше слово менше\n");
    }else if(comparison > 0){
        printf("strcmp: 1 -> перше слово більше\n");
    }
    printf("Рівні (==): ");
    if(comparison == 0){
        printf("Так\n");
    }else{
        printf("Ні\n");
    }


    //порівнюємо без урахування регістру
    printf("Рівні без урахування регістру: ");
    if(strcasecmp(a, b) == 0){
        printf("Так\n");
    }else{
        printf("Ні\n");
    }
    
    printf("Довжини: %zu і %zu \n", strlen(a), strlen(b));


    //виконуємо конкатенацію
    string aStr = a;
    string bStr = b;
    string res = aStr + " & " + bStr;
    printf("Конкатенація: \"%s\" (%zu)\n", res.c_str(), res.size());
    

}

    //інформація про символ
void symbolInfo(const char *text, int len){
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c);


    printf("Символ: '%c' \n", c);

    int code = static_cast<unsigned char>(c);

    //виводимо код у відповідних системах числення
    printf("Код: %d, (hex 0x%X, oct %#o, bin ", code, code, code);
    for (int i = 7; i >= 0; i--) printf("%d", (code & (1 << i)) ? 1 : 0);
    printf(")\n");


    //перевіряємо тип
    bool isLatinSm = (c >= 'a' && c <= 'z');
    bool isLatinCap = (c >= 'A' && c <= 'Z');
    bool isDigit = isdigit(c);
    bool isSpace = isspace(c);

    printf("Тип: ");
    if(isLatinSm){
        printf("мала літера \n");
        printf("Інший регістер: '%c' \n", c - 32);
        printf("Наступний символ: '%c' \n", c + 1);
    }else if(isLatinCap){
        printf("велика літера \n");
        printf("Інший регістер: '%c' \n", c + 32);
        printf("Наступний символ: '%c' \n", c + 1);
    }
    else if(isDigit){
        printf("цифра \n");
    }
    else if(isSpace){
        printf("пробільний символ \n");
    }else{
        printf("не розпізнаний символ \n");
    }
    int countTheSame = 0;
    int first = 0;


    //рахуємо скільки в тексті є таких символів
    for(int i = 0; i < len; i++){
        if(c == text[i]){
            countTheSame++;
            if(countTheSame == 1){
                first = i+1;
            }
        }
    }

    printf("Входжень у тексті: %d, перше на позиції %d \n", countTheSame, first);


}
    //функція для задання нового речення
void newSentence(char *text, int &count, int &len, char **&splitedWords){
    string NewWord;
    string newText;
    int sumlen = 0;
    int Wcount = 0;

    cout << "Введіть речення (крапка після останнього слова): ";


    //зчитуємо слова
    while (cin >> NewWord) {
        int len = NewWord.size();
        sumlen += len;
        if (NewWord[len - 1] == '.'){
            if(!newText.empty()){
            newText += ' ';
            } 
            newText += NewWord;
            Wcount++;
            break;
        }
        if(sumlen > MAXLEN) {
            printf("Помилка: задовге речення! (до 254 символів) ");
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        if(!newText.empty()){
            newText += ' ';
           
        } 
        newText += NewWord;
        Wcount++;
    
    } 
    char *temp = new char[MAXLEN];
    strcpy(temp, newText.c_str());
    int newLen = newText.size();


    if(!isTextValid(temp, newLen)){
         printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    

    cout << "Прочитано слів: " << Wcount << endl;
    cout << "Новий текст: \"" << newText << "\"" << endl; 
    cout << "Довжина нового тексту: " << newLen << endl;
        
    //замінюємо старий текст на новий
    strcpy(text, newText.c_str());
    len = newLen;

    // перебудовуємо масив слів
    for (int i = 0; i < count; i++) {
        delete[] splitedWords[i];
    }
    delete[] temp;
    delete[] splitedWords;
    splitedWords = splitWords(text, count, len);

}
