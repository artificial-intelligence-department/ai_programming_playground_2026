#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;
const int maxtext=256;
const int maxword=32;
//викидає все що лишилось у рядку вводу до enter включно
void clearline(){
    int k;
    while ((k=getchar())!='\n' && k!=EOF){

    }
}
//чи складається слово лише з латинських літер та цифр
bool iswordnum(const char *w){
    if (*w=='\0'){
        return false;
    }
    for (const char *p=w; *p!='\0'; p++){
        if (!isalnum((unsigned char)*p)){
            return false;
        }
    }
    return true;
}
//перевірка на коректність вводу (є 1 слово, лише латин.літери, цифри та пробіли, в кінці крапка)
bool isvalid(const char *t){
    int len=strlen(t);
    if (len<2){
        return false;
    }
    if (t[len-1]!='.'){
        return false;
    }
    if (!isalnum((unsigned char)t[len-2])){
        return false;
    }
    for (int i=0; i<len-1; i++){
        unsigned char c=t[i];
        if (!isalnum(c) && c!=' '){
            return false;
        }
    }
    return true;
}
//порівняння двох слів без урахування регістру (пункт 4)
bool Ignore(const char *a, const char *b){
    while (*a!='\0' && *b!='\0'){
        if (tolower((unsigned char)*a)!=tolower((unsigned char)*b)){
            return false;
        }
        a++;
        b++;
    }
    return *a==*b;
}
//перевірка на читання одного слова (пункт3,4)
bool readword(char *buf){
    if (scanf("%31s",buf)!=1){
        return false;
    }
    int k=getchar();
    bool ok=(k=='\n' || k==EOF || k==' ' || k=='\t');
    while (k!='\n' && k!=EOF){
        if (!isspace(k)){
            ok=false;
        }
        k=getchar();
    }
    return ok;
}
//розбиття тексту на слова, повертає масив слів
char **splitwords(const char *text, int &count){
    count=0;
    for (const char *p=text; *p!='\0'; p++){
        if (isalnum((unsigned char)*p) && (p==text || *(p-1)==' ')){
            count++;
        }
    }

    char **words=new char *[count];
    //копія тексту
    char buf[maxtext];
    strcpy(buf,text);
    char *dot=strchr(buf,'.');
    if (dot!=NULL){
        *dot='\0';
    }
    int i=0;
    char *token=strtok(buf, " ");
    while (token!=NULL && i<count)
    {
        words[i]=new char[strlen(token)+1];
        strcpy(words[i],token);
        i++;
        token=strtok(NULL, " ");
    }
    return words;
}
//звільнення памяті
void freeWords(char **&words, int &count){
    for (int i=0; i<count; i++){
        delete[] words[i];
    }
    delete[] words;
    words=NULL;
    count=0;
}
//підрахунок літер, цифр і пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters=0;
    digits=0;
    spaces=0;
    for (const char *p=text; *p!='\0'; p++){
        unsigned char c=*p;
        if (isalpha(c)){
            letters++;
        }
        else if (isdigit(c)){
            digits++;
        }
        else if (c==' '){
            spaces++;
        }
    }
}
//1 пункт меню
void showstatistic(const char *text, int wordcount)
{
    int letters,digits,spaces;
    countChars(text,letters,digits,spaces);
    int total=strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:%6d\n", total);
    printf("Слів:%10d\n", wordcount);
    printf("Літер:%9d (%5.1f%%)\n", letters, letters * 100.0 / total);
    printf("Цифр:%10d (%5.1f%%)\n", digits, digits * 100.0 / total);
    printf("Пробілів:%6d (%5.1f%%)\n", spaces, spaces * 100.0 / total);
}
//межі таблиці
void printborder(int w){
    printf("+----+");
    for (int i=0; i<w+2; i++){
        printf("-");
    }
    printf("+-------+\n");
}
//2 пункт (таблиця, min\max, середня довжина, за абеткою, найчастіше слово)
void showtable(char **words, int count){
    int w=15;
    for (int i=0; i<count; i++){
        int len=strlen(words[i]);
        if (len>w){
            w=len;
        }
    }
    printborder(w);
    printf(" N  | Слово%*s | Довж. |\n", w-5, "");
    printborder(w);
    for (int i=0; i<count; i++){
        printf("| %2d | %-*s | %5d |\n", i+1, w,words[i], (int)strlen(words[i]));
    }
    printborder(w);
    int longest=0, shortest=0, sum=0;
    for (int i=0; i<count; i++){
        int len=strlen(words[i]);
        sum+=len;
        if (len>(int)strlen(words[longest])){
            longest=i;
        }
        if (len<(int)strlen(words[shortest])){
            shortest=i;
        }
    }
    printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)sum/count);
    //копія масиву для сортування за абеткою
    char **sorted=new char *[count];
    for (int i=0; i<count; i++){
        sorted[i]=words[i];

    }
    for (int i=0; i<count-1; i++){
        for (int j=0; j<count-1-i; j++){
            if (strcmp(sorted[j], sorted[j+1])>0){
                char *t=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=t;
            }
        }
    }
    printf("За абеткою:");
    for (int i=0; i<count; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");
    //найчастіше слово
    int index=0, Count=0;
    int i=0;
    while (i<count)
    {
        int j=i;
        while(j<count && strcmp(sorted[j], sorted[i])==0){
            j++;
        }
        if (j-i>Count){
            Count=j-i;
            index=i;
        }
        i=j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[index], Count);
    delete [] sorted;
}
//3 пункт (замінити слово)
void replace(char *text, char **&words, int &count){
    char from[maxword], to[maxword];
    printf ("Замінити слово: ");
    if (!readword(from) || !iswordnum(from)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    printf ("На слово: ");
    if (!readword(to) || !iswordnum(to)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    string s=text;
    string f=from;
    string t=to;
    int replaced=0;
    size_t pos= s.find(f);
    while (pos!=string::npos){
        size_t end=pos+f.length();
        bool leftok=(pos==0 || s[pos-1]==' ');
        bool rightok=(end==s.length() || s[end]==' ' || s[end]=='.');
        if (leftok && rightok){
            s.replace(pos,f.length(), t);
            replaced++;
            pos=s.find(f,pos+t.length());
        }
        else{
            pos=s.find(f,pos+1);
        }
    }
    if (s.length()> maxtext-1){
        printf("Помилка: після заміни текст мав би %d символів (максимум %d). Текст не змінено.\n",
               (int)s.length(), maxtext-1);
        return;
    }
    printf("Замін виконано: %d\n", replaced);
    if (replaced==0){
        printf("Слово \"%s\" у тексті не знайдено.\n",from);
        return;
    }
    printf("Було:  \"%s\"\n", text);
    strcpy(text, s.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));
    freeWords(words,count);
    words=splitwords(text,count);
}
//4 пункт (порівняння 2 слів)
void compare(){
    char a[maxword], b[maxword];
    printf("Перше слово: ");
    if (!readword(a) || !iswordnum(a)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    printf("Друге слово: ");
    if (!readword(b) || !iswordnum(b)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }
    //порівняння кодів символів
    int r=strcmp(a,b);
    if (r<0){
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (r>0){
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else{
        printf("strcmp: 0 -> слова однакові\n");
    }
    string sa=a, sb=b;
    printf("Рівні (==): %s\n", sa == sb ? "так" : "ні");
    printf("Рівні без урахування регістру: %s\n", Ignore(a, b) ? "так" : "ні");
    printf("Довжини: %d і %d\n", (int)sa.length(), (int)sb.length());
    string joined=sa+" & "+sb;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}
//5 пункт (інофрмація про символ)
void charinfo(const char *text){
    char c;
    printf("Введіть символ: ");
    if (scanf("%c", &c)!=1 || c=='\n'){
        printf ("Помилка: символ не введено.\n");
        return;
    }
    int ch=getchar();
    if (ch!='\n' && ch!=EOF){
        clearline();
        printf("Помилка: введіть рівно 1 символ\n");
        return;
    }
    unsigned char code=c;
    char bin[9];
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = ((code >> i) & 1) ? '1' : '0';
    }
    bin[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", code, code, code, bin);

    if (isupper(code)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", c - 'A' + 'a');
    } else if (islower(code)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", c - 'a' + 'A');
    } else if (isdigit(code)) {
        printf("Тип: цифра\n");
    } else if (isspace(code)) {
        printf("Тип: пробільний символ\n");
    } else {
        printf("Тип: інший символ\n");
    }

    unsigned char next=code + 1;
    if (isprint(next)) printf("Наступний символ: '%c'\n", next);
    else printf("Наступний символ: код %d (недрукований)\n", next);

    // Пошук у тексті через strchr
    const char *p=strchr(text, c);
    if (p==NULL) {
        printf("У тексті символ не зустрічається.\n");
        return;
    }
    int firstPos=p-text+1;
    int occurrences=0;
    while (p!=NULL) {
        occurrences++;
        p=strchr(p+1, c);
    }
    printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, firstPos);
}
//6 пункт (ввести нове речення)
void newsentence(char *text, char **&words, int &count){
    printf("Введіть речення(крапка після останнього слова):\n");
    string sentence;
    string word;
    int wordread=0;
    bool finished=false;
    while (cin>>word){
        wordread++;
        if (!sentence.empty()){
            sentence+=" ";

        }
        sentence+=word;
        if (word[word.length()-1]=='.'){
            finished=true;
            break;
        }
    }
    cin.ignore(10000, '\n');
    if (!finished){
        cin.clear();
        printf("Помилка: речення не завершено крапкою.\n");
        return;
    }
    if (sentence.length()>maxtext-1){
        printf("Помилка: речення довше за %d символів.\n", maxtext-1);
        return;
    }
    if (!isvalid(sentence.c_str())){
        printf("Помилка: речення має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    strcpy(text,sentence.c_str());
    freeWords(words,count);
    words=splitwords(text,count);
    printf("Прочитано слів: %d\n", wordread);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}
//ввід тексту
bool readtext(char *text){
    printf("Введіть текст(до 255 символів, крапка в кінці): \n");
    //читаємо цілий рядок через fgets
    if (fgets(text,maxtext,stdin)==NULL){
        printf("Помилка: текст не введено.\n");
        return false;
    }
    char *n=strchr(text,'\n');
    if (n!=NULL){
        *n='\0';
    }
    else{
        int k=getchar();
        if (k!='\n' && k!=EOF){
            clearline();
            printf("Помилка: текст довший за 255 символів.\n");
            return false;
        }
    }
    int len=strlen(text);
    while (len>0 && (text[len-1]=='\r' || text[len-1]==' ')){
        len--;
    }
    text[len]='\0';
    if (!isvalid(text)){
        printf("Помилка: текст має складатись з латинських літер, цифр і пробілів і завершуватись крапкою. \n");
        return false;
    }
    return true;
}
void printmenu(){
    printf ("\n==========Меню==========\n");
    printf("1 - Показати текст і статистику\n");
    printf("2 - Таблиця слів\n");
    printf("3 - Замінити слово\n");
    printf("4 - Порівняти два слова\n");
    printf("5 - Інформація про символ\n");
    printf("6 - Ввести нове речення\n");
    printf("0 - Вийти\n");
    printf("Ваш вибір: ");
}
//читає номер меню і перевіряє його
int readmenu(){
    char line[64];
    if (fgets(line, sizeof(line), stdin)==NULL)
    {
        return 0;
    }
    if (strchr(line,'\n')==NULL){
        clearline();
    }
    char *p=line;
    while(*p==' ' || *p=='\t'){
        p++;
    }
    int value=0, digits=0;
    while (isdigit((unsigned char)*p)){
        if (digits<6){
            value=value*10+(*p-'0');
        }
        digits++;
        p++;
    }
    while (*p==' ' || *p=='\t' || *p=='\r' || *p=='\n'){
        p++;
    }
    if (digits==0 || *p!='\0'){
        printf("Помилка: введіть номер пункту меню.\n");
        return -1;
    }
    if (value>6 || digits>6){
        printf("Помилка: пункту %d немає в меню.\n", value);
        return -1;
    }
    return value;
}
int main()
{
    char text[maxtext];
    if (!readtext(text)){
        return 1;
    }
    int count=0;
    char **words=splitwords(text,count);
    int choice;
    do {
        printmenu();
        choice=readmenu();
        //вибір choice
        switch(choice){
            case 1:
            showstatistic(text, count);
            break;
            case 2:
            showtable(words, count);
            break;
            case 3:
            replace(text,words,count);
            break;
            case 4:
            compare();
            break;
            case 5:
            charinfo(text);
            break;
            case 6:
            newsentence(text,words,count);
            break;
            case 0:
            printf("Вихід\n");
            break;
            default: break;
        }
    }
    while (choice!=0);
    freeWords(words,count);
    return 0;
}