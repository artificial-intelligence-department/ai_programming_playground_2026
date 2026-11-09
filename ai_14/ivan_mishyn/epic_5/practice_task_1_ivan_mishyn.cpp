#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;

void freeWords(char **&words, int &count){
    for(int i=0; i<count; i++){
        delete[] words[i];
    }
    delete[] words;
    words=nullptr;
}


char **splitWords(const char *text, int &count) {
    char temp[256], copy[256];
    strcpy(temp, text);
    temp[strlen(temp) - 1] = '\0';
    strcpy(copy, temp);

    count = 0;
    for (char *t = strtok(copy, " "); t; t = strtok(nullptr, " ")) count++;

    char **words = new char*[count];
    int i = 0;
    for (char *t = strtok(temp, " "); t; t = strtok(nullptr, " ")) {
        words[i] = new char[strlen(t) + 1];
        strcpy(words[i++], t);
    }
    return words;
}


bool valideText(char text[]){
    bool isAnyChar=false;
    bool isCorrect=true;
    int len=strlen(text);
    if(len==0){
        return 0;
    }
    if(text[len-1]!='.'){
        isCorrect=false;
    }
    for(int i=0;i<=len-2;i++){
        if (isalnum(text[i])) {
            if(isalpha(text[i])){
                isAnyChar=true;
            }
        }
        else if (text[i]  != ' ') {
            isCorrect=false;
        }
    }
    if(isCorrect && isAnyChar){
        return true;
    }
    else{
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
        return false;
       
    }

}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    int len=strlen(text);
    for(int i=0;i<len;i++){
        if(isalpha(text[i]))letters++;
        else if(isdigit(text[i]))digits++;
        else if(text[i]==' ')spaces++;
    }
}

void  stats(const char text[], int count){
    int letters=0;
    int digits=0;
    int spaces=0;
    int len=strlen(text);
    countChars(text, letters, digits, spaces);
    printf("\nТекст:\t\"%s\"",text);
    printf("\nСимволів:%6d",len);
    printf("\nCлів:%10d",count);
    printf("\nЛітер:%9d (%5.1f%%)",letters, (float)letters/len*100);
    printf("\nЦифр:%10d (%5.1f%%)",digits, (float)digits/len*100);
    printf("\nПробілів:%6d (%5.1f%%)",spaces, (float)spaces/len*100);
}   

void statsByWord(char** words,int count){
    int longest=-1;
    int indexLon;
    int shortest=2147483647;
    int indexShort;
    float avg=0;
    char **sortWords = new char*[count];
    for (int i=0; i<count; i++) {
        sortWords[i] = new char[strlen(words[i]) + 1];
        strcpy(sortWords[i], words[i]);
    }
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(strcmp(sortWords[i],sortWords[j])>0){
                char temp[strlen(sortWords[i])+1];
                strcpy(temp,sortWords[i]);
                strcpy(sortWords[i],sortWords[j]);
                strcpy(sortWords[j],temp);
            }
        }
    }
    int ii=0;
    int indexBest=0;
    int countBest=0;
    while(ii<count){
        int countt=1;
        while(ii+countt<count && strcmp(sortWords[ii],sortWords[ii+countt])==0){
            countt++;
        }
        if(countt>countBest){
            indexBest=ii;   
            countBest=countt;
        }
        ii+=countt;
    }
    printf("\n+----+-----------------+-------+");
    printf("\n| N  | Слово           | Довж. |");
    printf("\n+----+-----------------+-------+");
    for(int i=0;i<count;i++){
        int len=strlen(words[i]);
        avg+=len;
        if(len>longest){
            longest=len;
            indexLon=i;
        }
        else if(len<shortest){
            shortest=len;
            indexShort=i;
        }
        printf("\n|%3d | %16s|%6d |", i, words[i], len);
    }
    printf("\n+----+-----------------+-------+");


    avg/=count;
    printf("\nНайдовше слово: %s (%ld)",words[indexLon], strlen(words[indexLon]));
    printf("\nНайкоротше слово: %s (%ld)",words[indexShort], strlen(words[indexShort]));
    printf("\nСередня довжина: %.2f",avg);
    printf("\nЗа абеткою: ");
    for(int i=0;i<count;i++){
        printf("%s ",sortWords[i]);
    }
    printf("\nНайчастіше слово: %s (%d)",sortWords[indexBest], countBest);


    for(int i=0;i<count;i++){
        delete[] sortWords[i]; 
    }
    delete[] sortWords;
    sortWords=nullptr;
}

void replaceWord(char text[], char **&words, int &count) {
    char oldBuf[256], newBuf[256];
    printf("\nВведіть слово, яке треба замінити: ");
    scanf("%255s", oldBuf);
    printf("Введіть нове слово: ");
    scanf("%255s", newBuf);

    for (int i = 0; newBuf[i] != '\0'; i++) {
        if (!isalnum(newBuf[i])) {
            printf("Помилка: нове слово має складатися лише з латинських літер і цифр!\n");
            return;
        }
    }

    string str = text;
    string oldWord = oldBuf;
    string newWord = newBuf;
    int replacements = 0;
    size_t pos = 0;

    while ((pos = str.find(oldWord, pos)) != string::npos) {
        bool leftOk = (pos == 0) || !isalnum(str[pos - 1]);
        bool rightOk = (pos + oldWord.length() == str.length()) || !isalnum(str[pos + oldWord.length()]);

        if (leftOk && rightOk) {
            str.replace(pos, oldWord.length(), newWord);
            pos += newWord.length();
            replacements++;
        } else {
            pos += oldWord.length();
        }
    }

    if (str.length() > 255) {
        printf("Помилка: довжина тексту після заміни перевищує 255 символів!\n");
        return;
    }

    printf("\nКількість замін: %d", replacements);
    printf("\nТекст до заміни:    \"%s\"", text);
    printf("\nТекст після заміни: \"%s\"", str.c_str());
    printf("\nНова довжина: %ld\n", str.length());

    strcpy(text, str.c_str());

    freeWords(words, count);
    words = splitWords(text, count);
}


void compareWords() {
    char w1[256], w2[256];
    printf("\nВведіть перше слово: ");
    scanf("%255s", w1);
    printf("Введіть друге слово: ");
    scanf("%255s", w2);

    for (int i = 0; w1[i] != '\0'; i++) {
        if (!isalnum(w1[i])) {
            printf("Помилка: перше слово має містити лише латинські літери та цифри!\n");
            return;
        }
    }
    for (int i = 0; w2[i] != '\0'; i++) {
        if (!isalnum(w2[i])) {
            printf("Помилка: друге слово має містити лише латинські літери та цифри!\n");
            return;
        }
    }

    string s1 = w1;
    string s2 = w2;

    printf("\nПерше слово: %s\n", w1);
    printf("Друге слово: %s\n", w2);

    int cmp = strcmp(w1, w2);
    printf("strcmp: %d -> ", cmp);
    if (cmp < 0) printf("перше слово менше\n");
    else if (cmp > 0) printf("перше слово більше\n");
    else printf("слова однакові\n");

    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

    int len1 = s1.length();
    int len2 = s2.length();
    bool eqNoCase = false;

    if (len1 == len2) {
        eqNoCase = true;
        for (int i = 0; i < len1; i++) {
            if (tolower(w1[i]) != tolower(w2[i])) {
                eqNoCase = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: %s\n", eqNoCase ? "так" : "ні");

    printf("Довжини: %d і %d\n", len1, len2);

    string concat = s1 + " & " + s2;
    int lenConcat = concat.length();
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), lenConcat);
}


void charStats(char text[]){
    char CharStat;
    printf("\nВведіть символ: ");
    scanf(" %c", &CharStat);
    printf("\nСимвол: \'%c\'", CharStat);
    printf("\nКод: %d (hex %x, oct %o, bin ", CharStat, CharStat, CharStat);
    for(int i = 7; i >= 0; i--) {
        printf("%d", (CharStat >> i) & 1);
    }
    printf(")");
    if(isalpha(CharStat)){
        bool isLower=islower(CharStat);
        printf("\nТип: %s", isLower ? "мала літера":"велика літера");
        printf("\nІнший регістр: \'%c\'", isLower ? toupper(CharStat) : tolower(CharStat));
        printf("\nНаступний символ: \'%c\'", CharStat+1);
    }
    else if(isdigit(CharStat)){
        printf("\nТип: число");
    }
    else if(CharStat==' '){
        printf("\nТип: пробіл");
    }
    else printf("\nТип: інший символ");
    
    
    int len=strlen(text);
    int count=0;
    char *found = strchr(text, CharStat);
    for(int i=0; i<len;i++){
        if(text[i]==CharStat){
            count++;
        }
    }
    int index =found-text+1;
    printf("\nВходжень у тексті: ");
    if(count == 0) printf("символ у тексті відсутній");
    else printf("%d, перше на позиції %d", count , index);
}

void NewText(char text[],char **&words, int &count){
    string newText;
    printf("\nВведіть речення (крапка після останнього слова): \n");
    while(true){
        string part;
        cin>>part;
        newText+=part;
        if(part[part.length()-1]=='.'){
            break;
        }
        newText+=' ';
    }
    if (newText.length() > 255) {
        printf("\nПомилка: довжина речення перевищує 255 символів! Текст не змінено.\n");
        return;
    }
    char tempText[256];
    strcpy(tempText, newText.c_str());
    if(!valideText(tempText)) {
        printf("\nПомилка: некоректні символи! Текст не змінено.");
        return;
    }
    strcpy(text, tempText);
    freeWords(words, count);
    words=splitWords(text,count);
    printf("\nПрочитано слів: %d", count);
    printf("\nНовий текст: \"%s\"", text);
    printf("\nДовжина: %ld", strlen(text));
}


int main(){
    char text[256];
    int count=0;
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    fgets(text, 256, stdin);
    int len=strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }   
    if(!valideText(text)) {
        return 0;
    }    
    char **words=splitWords(text, count);
    int input=-1;
    do{
        printf("\n\n             Меню");
        printf("\n1-Показати текст і статистику");
        printf("\n2-Таблиця слів");
        printf("\n3-Замінити слово");
        printf("\n4-Порівняти два слова");
        printf("\n5-Інформація про символ");
        printf("\n6-Ввести нове речення");
        printf("\n0-Вихід\n");

        input=-1;
        scanf("%d", &input);
        switch(input){
            case 1:
            stats(text, count);
            break;
            case 2:
            statsByWord(words,count);
            break;
            case 3:
            replaceWord(text, words, count);
            break;
            case 4:
            compareWords();
            break;
            case 5:
            charStats(text);
            break;
            case 6:
            NewText(text, words, count);
            break;
            default:
            if(input!=-1){
                printf("Помилка: пункту %d немає в меню.", input);
            }
            else{
                printf("Помилка: введіть номер пункту меню.");
            }
            cin.clear();
            cin.ignore(1000, '\n');
            break;

        }
    }while(input!=0);
    freeWords(words, count);
    printf("\nВихід");
    return 0;
}