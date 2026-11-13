#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;
bool validateInput(const char *text){
    int len = strlen(text);
    bool is_correct =0;
    if (text[len-1]!='.') return 0;
    for (int i =0; i<len-1; i++){
        if(isalnum(text[i])){
            is_correct = 1;
        }else if (text[i]!=' ') return 0;
    }
    return is_correct;
    
}

void freeWords(char **&words, int &count){
    
    for (int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
    
    words = nullptr;
    count = 0;
}

char **splitWords(const char *text, int &count){
     
    int len = strlen(text);
    
    char* temp = new char [len +1];
    strcpy(temp, text);
    if (len > 0 && temp[len - 1] == '.') {
        temp[len - 1] = '\0';
    }
    char* token = strtok(temp, " ");
    
    while(token!=NULL){
        count++;
        token=strtok(NULL," ");        
    }
    strcpy(temp, text);
    temp[len-1]='\0';

    char** words = new char*[count];
    token = strtok(temp, " ");
    for (int i =0; i<count; i++){
        if (token == NULL) break;
        words[i]= new char[strlen(token)+1];
        strcpy(words[i], token);
        token=strtok(NULL, " ");
    }
    delete [] temp;
    return words;

}
void countChars(const char *text, int &letters, int &digits, int &spaces){
    int len=strlen(text);
    for (int i =0; i<len; i++){
        if (isalpha(*(text+i))) letters++;
        else if (isdigit(*(text+i))) digits++;
        else if(*(text+i)==' ') spaces++;
    }
}
void showText (const char *text, int count){
    int len = strlen(text);
    int letters =0, digits = 0, spaces =0;
    countChars(text, letters, digits, spaces);
    float letters_perc = (letters/(float)len)*100;
    float digits_perc = (digits/(float)len)*100;
    float spaces_perc = (spaces/(float)len)*100;

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", len);
    printf("Cлів:\t%d\n", count);
    printf("Літер:\t%d ( %3.1f%%)\n", letters, letters_perc);
    printf("Цифр:\t%d ( %3.1f%%)\n", digits, digits_perc);
    printf("Пробілів:\t%d ( %3.1f%%)\n", spaces, spaces_perc);
}
void sortAlphabet(char **words, int count){
    char**sort= new char*[count];
    for (int i = 0; i < count; i++) sort[i] = words[i];
    for (int i =0; i<count-1; i++){
        for (int j = 0; j<count-1; j++){
            if (strcmp(sort[j], sort[j+1])>0){
                char* temp = sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=temp;
            }
        }
    }
    printf("За абеткою:");
    for (int i = 0; i < count; i++) printf(" %s", sort[i]);
    printf("\n");
    
    delete[] sort;
    return;

}
void mostFrequentWord(char **words, int count){
    int most_index=0;
    int freq_num = 0;
    for (int i =0; i<count; i++){
        int n=0;
        for (int j =0; j<count; j++){
            if (strcmp(words[i],words[j])==0) n++;
        }
        if(n>freq_num) {
            most_index=i;
            freq_num=n;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", words[most_index],freq_num);
    return;
}

void showWords(char **words, int count){
    printf("+----+-----------------+-------+\n| N  | Слово           | Довж. |\n+----+-----------------+-------+\n");
    for (int i =0; i<count; i++){
        printf("|%3d | %-15s | %5d |\n",i+1,words[i],(int)strlen(words[i]));
    }
    int longest = 0, shortest = 0, total = 0;
    for (int i = 0; i < count; i++){
        size_t len = strlen(words[i]);
        total += len;
        if (len > strlen(words[longest]))   longest = i;
        if (len < strlen(words[shortest]))  shortest = i;
    }
    printf("Найдовше слово: %s (%d)\n",   words[longest],  (int)strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)total / count);
    sortAlphabet(words, count);
    mostFrequentWord(words, count);
}

bool isWordsValid(char from[], char to[]){
    size_t len_f = strlen(from);
    size_t len_t = strlen(to);
    if (len_f>31 || len_t>31 || from[0]=='\n'||to[0]=='\n'){
        return 0;
    }
    
    for (size_t i =0;i<len_f; i++){
        if (!(isalnum(from[i]))) return 0;
    }
    for (size_t i =0;i<len_t; i++){
        if (!(isalnum(to[i]))) return 0;
    }
    return 1;
}
void clearInput(){
    int x;
    while ((x = getchar()) != '\n') {}
}
void replaceWords(char *text,char **&words, int &count){
    char from[33]={}, to[33]={};
    printf("Замінити слово: ");
    scanf("%32s", from);
    clearInput();

    printf("На слово: ");
    scanf("%32s", to);
    clearInput();
    if(!isWordsValid(from,to)){
        printf("Помилка. Слова мають бути до 31 символа, складатись з латинських літер або цифр\n");
        return;
    }
    string copy= text, sfrom = from, sto=to;
    size_t pos = copy.find(sfrom);
    int total=0;
    while (pos != string::npos){
        bool left = (pos == 0) || copy[pos - 1] == ' ';
        int end= pos + sfrom.length();
        bool right= (end == copy.length()) || copy[end] == ' ' || copy[end] == '.';

        if (left && right){
            copy.replace(pos, sfrom.length(), sto);
            total++;
            pos += sto.length();
        } else {
            pos+=sfrom.length();
        }
        pos = copy.find(sfrom, pos);
    }
    if (copy.length()>255){
        printf("Результат перевищує 255 символів. Заміни не відбулось.");
        return;
    }else if (total==0) {
        printf("Збігів не знайдено.");
        return;
    }else{
    printf("Замін виконано: %d\n", total);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", copy.c_str());
    printf("Нова довжина: %d\n", (int)copy.length());
    }
    strcpy(text, copy.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

}

bool equalWithoutReg(const string &a, const string &b){
    if (a.length() != b.length()) return false;
    for (int i = 0; i < a.length(); i++)
        if (tolower((char)a[i]) != tolower((char)b[i]))
            return false;
    return true;
}
void compareWords(){
    
    char ch_a[33]={},ch_b[33] ={};
    printf("Перше слово: ");
    scanf("%32s", ch_a);
    clearInput();

    printf("Друге слово: ");
    scanf("%32s", ch_b);
    clearInput();

    if(!isWordsValid(ch_a,ch_b)){
        printf("Помилка. Слова мають бути до 31 символа, складатись з латинських літер або цифр\n");
        return;
    }

    int compare = strcmp(ch_a,ch_b);
    if(compare < 0){
        printf("strcmp: %d -> перше слово менше\n", compare);
    } else if(compare>0){
        printf("strcmp: %d -> перше слово більше\n", compare);
    } else printf("strcmp: %d -> рівні\n", compare);
    
    string s_a = ch_a, s_b = ch_b;
    if (s_a!=s_b){
        printf("Рівні(==): ні\n");
    } else printf("Рівні(==): так\n");
    if(equalWithoutReg(s_a, s_b)) {
        printf("Рівні без урахування регістру: так\n");
    }else printf("Рівні без урахування регістру: ні\n");

    printf("Довжини: %d i %d\n", (int)s_a.length(),(int)s_b.length());
    string joined = s_a + " & " + s_b;
    printf("Конкатенація: \"%s\" (%d)\n",joined.c_str(),(int) joined.length());
}

void whatType(char c){
    if (isdigit(c)) printf(" цифра\n");
    else if(c==' ') printf("пробільний символ\n");
    else if(isalpha(c)){
        if(islower(c)){
            printf(" мала літера\nІнший регістр'%c'\n",c-32);
        }else{
            printf(" велика літера\nІнший регістр'%c'\n",c+32);
        }
    }else printf("інший символ\n");
}
void freqCount(const char* text, char c){
    int freq=0, firstly_index=-1;
    int len = strlen(text);
    for (int i =0; i<len+1; i++){
        if (text[i]==c) freq++;
        if (text[i]==c && firstly_index==-1) firstly_index=i;
    }
    printf("Входжень у тексті: %d, перше на позиції %d\n", freq, firstly_index+1);
}
void charInfo(const char* text){
    printf("Введіть символ:\n");
    char c;
    scanf("%c", &c);
    
    printf("Символ: %c\n", c);
    
    printf("Код:%d hex %x, oct %o, bin ",c, c,c);
    for(int i = 7; i>=0;i--){
        int bin = (c>>i)&1;
        printf("%d", bin);
    }
    printf("\nТип:");
    whatType(c);
    printf("Наступний символ: \'%c\'\n", c+1);
    freqCount(text, c);
}

void newSentence(char* text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");
    string temp, word;
    while(cin>>word){
        if (!temp.empty()) temp += ' ';
        temp+=word;
        if(word[word.length()-1]=='.') break;    
    }
    clearInput();
    if (temp.length()>255){
        printf("Текст має бути максимум 255 символів. Речення не змінено.\n");
        return;
    }

    if (validateInput(temp.c_str())){
       freeWords(words,count);
       strcpy(text,temp.c_str());
       words=splitWords(text,count);
    }else{
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }
    showText(text, count);
    return;
}

int main(){

    char text [256]= {};
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(fgets(text, sizeof(text), stdin)==nullptr){
        printf("Текст має складатись з символів (1-255).");
        return 1;
    }
    char* n = strchr(text, '\n');
    if(n !=nullptr){
        *n='\0';
    }else{
        char next[2];
        fgets(next,sizeof(next)-1,stdin);
        if(next[0]!='\n'){
          printf("Текст максимум 255 символів.");
          return 1;  
        }
    }

    if(!validateInput(text)){
        printf("Помилка: текст має складатися з латинських літер, цифрі пробілів та завершуватися крапкою.\n");
        return 0;
    }

    int count = 0;
    char** words=splitWords(text,count);

    int choice = -1;
    do{
        while(true){
            printf("Меню:\n1 Показати текст і статистику \n2 Таблиця слів \n3 Замінити слово \n4 Порівняти два слова \n5 Інформація про символ \n6 Ввести нове речення\n0 Вийти\n");
            if (scanf("%d", &choice) != 1) {
                printf("Помилка: введіть номер пункту меню.\n");
                clearInput();
                continue;
            }
            clearInput();
            if (choice==1||choice==2||choice==3||choice==4||choice==5 || choice==6||choice==0) break;
        }
        switch(choice){
            case 1:
                showText(text,count);
                break;
            case 2:
                showWords(words,count);
                break;
            case 3:
                replaceWords(text, words,count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                charInfo(text);
                break;
            case 6:
                newSentence(text, words, count);
                
                break;
            case 0:
                printf("Ви обрали вихід з програми.\n");
                freeWords(words,count);
                break;
            default:
                printf("Непередбачена дія. Введіть доступну цифру з меню.\n");
                break;
    }
    }while(choice!=0);
    return 0;
}
