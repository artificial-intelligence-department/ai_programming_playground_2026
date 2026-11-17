#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

//Інформація про символ
void info(const char text[]){
    char buf[256];
printf("Введіть символ: ");
fgets(buf, sizeof(buf), stdin);
char ch= buf[0];
unsigned char code=(unsigned char)ch;
printf("Символ: '%c'\n", ch);
char bin[9];
bin[8]='\0';
unsigned char temp=code;
    for (int i=7; i>=0; i--){
        bin[i]=(temp%2)+'0';
        temp=temp/2;
    }
printf("Код: %d (hex 0x%x, oct0%o, bin%s)\n", code, code, code, bin);
if (isupper(code)){
    printf("Тип: велика літера\n");
    printf("Інший регістр: '%c\n", (char)tolower(code));
}else if(islower(code)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", (char)toupper(code));
    }else if(isdigit(code)){
        printf("Тип: цифра\n");
    }else if(isspace(code)){
        printf("Тип: пробіл\n");
}else{
    printf("Тип: інший символ\n");
}
printf("Наступний символ: '%c'\n", (char)(code+1));
int count_ch=0;
int firstpos=-1;
    for (int i=0; text[i]!='\0'; i++){
        if (text[i]==ch){
            count_ch++;
            if (firstpos==-1){
                firstpos=i+1;
            }
        }
    }
    if (count_ch>0){
        printf("Входжень у тексті: %d, перше на позиції %d\n", count_ch, firstpos);
    }else{
        printf("Символ у тексті відсутній. \n");
    }
}
//Валідація для заміни та порівняння
 bool validnew_words(const string &w){
    if (w.empty()) return false;
        for (size_t i=0; i<w.length(); i++){
            if (!isalpha((unsigned char)w[i]) && !isdigit((unsigned char)w[i])){
                return false;
            }
        }
        return true;
    }
//Порівняння слів
void comparative(){
    char buf1[256];
    char buf2[256];
    int c;
    printf("Введіть перше слово: ");
    scanf("%255s", buf1);
    while((c=getchar()) != '\n' && c != EOF);
    printf("Введіть друге слово: ");
    scanf("%255s", buf2);
    while((c=getchar()) != '\n' && c != EOF);
    string w1=buf1;
    string w2=buf2;
        if (!validnew_words(w1) || !validnew_words(w2)) {
    printf("Помилка вводу! Слово повинно складатись з латинських літер і цифр.\n");
    return;
} 
int cmp= strcmp(buf1, buf2);
if (cmp>0){
    printf("(strcmp-> >1) Слово %s більше за слово %s \n", buf1, buf2);
}else if(cmp<0){
    printf("(strcmp-> <1) Слово %s менше за слово %s \n", buf1, buf2);
}else if(cmp==0){
    printf("(strcmp-> =0) Слова однакові\n");
}
if (w1==w2){
    printf("Рівні (==): так\n");
}else{
    printf("Рівні (==): ні\n");
}
int length1=w1.length();
int length2=w2.length();
string low1=w1;
string low2=w2;
int total_length=length1+length2;
printf("Довжини: %d і %d\n", length1, length2);
for (size_t i=0; i<low1.length(); i++){
    low1[i]=tolower((unsigned char)low1[i]);
}
for (size_t i=0; i<low2.length(); i++){
    low2[i]=tolower((unsigned char)low2[i]);
}
if (low1==low2){
    printf("Рівні без урахування регістру: так\n");
}else{
    printf("Рівні без урахування регістру: ні\n");
}
string cat= w1+" & "+ w2;
printf("Конкатенація: \"%s\" (%zu)\n", cat.c_str(), cat.length());
}
//Заміна слова
void replaceword(char text[]){
    char old_buf[256];
    char new_buf[256];
    int c;
printf("Замінити слово: ");
scanf("%255s", old_buf);
        while((c=getchar()) != '\n' && c!=EOF);
printf("На слово: ");
scanf("%255s", new_buf);
        while((c=getchar()) != '\n' && c!=EOF);
        string new_word=new_buf;
        string old_word=old_buf;
        string stext=text;
        if (!validnew_words(old_word)||!validnew_words(new_word)){
            printf("Помилка вводу! Слово повинно складатись з латинських літер і цифр. Текст не змінено!");
        return;
        }
        string before=stext;
        int counter=0;
        size_t pos=0;
    while ((pos=stext.find(old_word, pos))!=string::npos){
        size_t right=pos+old_word.length();
        bool right_ok=(right>=stext.length()||stext[right]==' '|| stext[right]=='.');
        bool left_ok=(pos==0 || stext[pos-1]==' ');
        if (left_ok && right_ok){
            stext.replace(pos, old_word.length(), new_word);
            counter++;
            pos +=new_word.length();
        }else{
            pos+=1;
        }
    }
        if (stext.length()>255){
            printf("Помилка! Заміна перевищує максимальну кількість слів у реченні.");
            return;
        }
        strcpy(text, stext.c_str());
        if (counter==0){
            printf("Слово '%s' не знайдено, текст не змінено.", old_word.c_str());
        }else{
            printf("Замін виконано: %d\t", counter);
            printf("\nБуло: \"%s\" ", before.c_str());
            printf("\nСтало: \"%s\" ", text);
            printf("\nНова довжина: %zu \t", strlen(text));

        }
    }
//Таблиця
void showtable(char **words, int count){
    if (count<=0) return;
    int max=0;
    int min=0;
    int total_length=0;
    double avg=0;
    for (int j=0; j<count; j++){
        int len=strlen(words[j]);
        total_length+=len;
            if(len>strlen(words[max])){
                max=j;
            }
            if (len<strlen(words[min])){
            min=j;
            }
    }
            avg=(double)total_length/count;
printf("+----+-----------------+-------+");
printf("\n|  N | Слово           | Довж. |\n");
printf("+----+-----------------+-------+\n");

    for (int i=0; i<count; i++){
        int len=strlen(words[i]);
        printf("| %2d | %-10s      | %5d |\n", i+1, words[i], len);
    }
    printf("+----+-----------------+-------+");

printf("\nНайдовше слово: %s \t(%zu)", words[max], strlen(words[max]));
printf("\nНайкоротше слово: \t%s (%zu)", words[min], strlen(words[min]));
printf("\nСередня довжина: \t%.2f\n", avg);

    char **sortedwrds=new char*[count];
    for (int i=0; i<count;i++){
        sortedwrds[i]=words[i];
    }
    for (int i=0; i<count-1; i++){
        for (int j=0; j<count-1-i; j++){
            if (strcmp(sortedwrds[j], sortedwrds[j+1])>0){
                char *temp=sortedwrds[j];
                sortedwrds[j]=sortedwrds[j+1];
                sortedwrds[j+1]=temp;
            }
        }
    }
    printf("Слова за абеткою: ");
    for (int i=0; i<count; i++){
        printf("%s ", sortedwrds[i]);
    }
    printf("\n");
    char*mostoft=sortedwrds[0];
    int maxoften=1;
    char *currentwrd=sortedwrds[0];
    int currentoft=1;
        for (int i=1; i<count; i++){
            if (strcmp(sortedwrds[i], currentwrd)==0){
                currentoft++;
            }else{
                if(currentoft>maxoften){
                    maxoften=currentoft;
                    mostoft=currentwrd;
                }
                currentwrd=sortedwrds[i];
                currentoft=1;
            }
        }
        if (currentoft>maxoften){
    maxoften=currentoft;
    mostoft=currentwrd;
}
printf("Найчстіше слово: %s (%d)", mostoft, maxoften);
delete[] sortedwrds;
}

//Статистика
void showstats(const char *text, int ptr, int words, int letters, int digits, int spaces){
    double procent_l= (letters*100.0)/ptr;
    double procent_d=(digits*100.0)/ptr;
    double procent_s=(spaces*100.0)/ptr;
    printf("Текст:\t\t\"%s\"\n", text);
    printf("Символів:\t%d\n", ptr);
    printf("Слів:\t\t%d\n", words);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, procent_l);
    printf("Цифр:\t\t%2d (%5.1f%%)\n", digits, procent_d);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, procent_s);
}
void countChars(const char *text, int &total_c, int &words, int &letters, int &digits, int &spaces){
    total_c=0;
    letters=0;
    digits=0;
    spaces=0;
    words=0;
    const char *ptr=text;
        bool inwords=false;
    while( (*ptr)!='\0'){
            total_c++;
        if (isalpha((unsigned char)*ptr)){
            letters++;
        }
        else if (isdigit((unsigned char)*ptr)){
            digits++;
        }
        else if ((*ptr)==' '){
            spaces++;
        }
        if (*ptr!=' '&& *ptr!='\t' && *ptr!='\n'){
            if (!inwords){
                words++;
                inwords=true;
            }
            }else{
                inwords=false;
             }
                ptr++;
    }
}
//Розподіл речення по словах
char **splitWords(const char *text, int &count){
    count=0;
char **words=new char*[256];
char temp[256];
strcpy(temp, text);
char *t=strtok(temp, " .");
while (t!=nullptr){
    words[count]=new char[strlen(t)+1];
    strcpy(words[count], t);
    count++;
    t = strtok(nullptr, " .");
}
return words;
}
//Звільнення купи
void freeWords(char **&words, int &count) {
    if (words != nullptr) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}
//Перевірка на крапку, символи, затирання enter 
    bool formattext(char text[]){
    int len_t=strlen(text);
    if (len_t>0 && text[len_t-1]=='\n'){
        text[len_t-1]='\0';
        len_t--;
    }
    if (len_t==0||text[len_t-1]!='.'){
        return false;
    }
    bool word=false;
    for (int i=0; i<len_t-1; i++){
        char c=text[i];
        bool letter=isalpha((unsigned char)c);
        bool digit=isdigit((unsigned char)c);
        bool space=(c==' ');
            if (!letter && !digit && !space){
                return false;
            }
            if (letter || digit){
                word=true;
            }
    }
    return word;
    }
    //Нове речення
void newSentence(char text[], char **&words, int &count) {
    printf("Введіть нове речення (завершіть словом з крапкою):\n");
    string word;
    string new_text = "";
    int read_words = 0;

    while (cin >> word) {
        if (!new_text.empty()) {
            new_text += " ";
        }
        new_text += word;
        read_words++;

        if (word.back() == '.') {
            break;
        }
    }
    cin.ignore(10000, '\n');

    if (new_text.length() > 255) {
        printf("Помилка! Речення перевищує 255 символів. Поточний текст не змінено.\n");
        return;
    }

    char temp_text[256];
    strcpy(temp_text, new_text.c_str());

    if (!formattext(temp_text)) {
        printf("Помилка! Некоректне речення. Поточний текст не змінено.\n");
        return;
    }

    strcpy(text, temp_text);
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", read_words);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}
    //Валідація
    void validation(char text[]){
    bool valid=false;
    do{
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, 256, stdin)!=NULL){
        valid=formattext(text);
        if (!valid){
            printf("Помилка! Некоректний текст, спробуйте ще раз. \n");
        }
    }
}
 while(!valid);
}
int main(){
   char text[256];
   validation(text);
   int count = 0;
char **words = splitWords(text, count);
    int choice;
    int total_c=0;
        int words_cnt=0;
        int letters=0;
        int digits=0;
        int spaces=0;
    do{
        printf("\n| Меню операцій:                  |\n");
        printf("\n| 1. Показати текст і статистику  |\n");
        printf("\n| 2. Таблиця слів                 |\n");
        printf("\n| 3. Замінити слово               |\n");
        printf("\n| 4. Порівняти два слова          |\n");
        printf("\n| 5. Інформація про символ        |\n");
        printf("\n| 6. Ввести нове речення          |\n");
        printf("\n| 0. Вийти                        |\n");
        printf("\n| Оберіть опцію:                  |\n");
    if (scanf("%d", &choice)!=1){
        printf("Помилка вводу! Введіть число від 0 до 6.\n");
        int c;
        while ((c=getchar()) !='\n' && c!=EOF);
        choice = -1;
        continue;
    }
    int c;
    while((c=getchar()) !='\n'&& c!=EOF);
    switch (choice){
        case 1:{
        countChars(text, total_c, words_cnt, letters, digits, spaces);
        showstats (text, total_c,  words_cnt,  letters,  digits,  spaces);
        break;
        }
        case 2:{
                if (count>0){
                    showtable(words, count);
                }else{
                    printf("Відсутні слова для опрацювання.");
                }
        break;
        }
        case 3:{
        replaceword(text);
        freeWords(words, count);
        words=splitWords(text, count);
        break;
        }
        case 4:{
            comparative();
        break;
        }
        case 5:{
            info(text);
        break;
        }
        case 6:{
        newSentence(text, words, count);
        break;
        }
        case 0:{
        printf("Вихід!");
        break;
        }
        default:{
            printf("Така опція відсутня.\n");
            break;
        }
    }
    }
        while (choice!=0);
    freeWords(words, count);
    return 0;
}
