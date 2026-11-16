/*"Редактор текстового повідомлення"
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;

void PrintMenu(){
    printf("\n------Меню------\n");
    printf("1\tПоказати текст і статистику\n");
    printf("2\tТаблиця слів\n");
    printf("3\tЗамінити слово\n");
    printf("4\tПорівняти два слова\n");
    printf("5\tІнформація про символ\n");
    printf("6\tВвести нове речення\n");
    printf("0\tВийти\n");
}
bool textValidation(const char *text) {
    int len = strlen(text);
    if (len == 0 || text[len - 1] != '.')
        return false;

    int words = 0;
    bool isword = false;
    for (int i = 0; i < len - 1; i++) {
        unsigned char c = text[i];
        if (isalnum(c)) {
            if (!isword) {
                words++;
                isword = true;
            }
        } else if (c == ' ') {
            isword = false;
        } else {
            return false;
        }
    }
    return words > 0;
}

char **splitWords(const char *text, int &count){
    count = 0;
    char text2[256];
    
    strcpy(text2, text);
    int len = strlen(text2);
    if (len > 0 && text2[len - 1] == '.') {
        text2[len - 1] = '\0';
    }
    char *token = strtok(text2, " ");
    while (token != nullptr) {
        if (strlen(token) > 0) {
            count++;
        }
        token = strtok(nullptr, " ");
    }
    if (count == 0) {
        return nullptr;
    }
    char **wordsArr = new char*[count];
    strcpy(text2, text);
    if (len > 0 && text2[len - 1] == '.') {
        text2[len - 1] = '\0';
    }
    token = strtok(text2, " ");
    int k = 0;
    while (token != nullptr) {
        if (strlen(token) > 0) {
            wordsArr[k] = new char[strlen(token) + 1];
            strcpy(wordsArr[k], token); 
            k++;
        }
        token = strtok(nullptr, " ");
    }
    return wordsArr;
}
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

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;
    const char *p = text;
    while(*p !='\0'){
        unsigned char c = *p;
        if(isalpha(c)) letters++;
        else if(isdigit(c)) digits++;
        else if(isspace(c)) spaces++;
        p++;
    }
}
void TextAndStatistics(const char *text, int count){
    int allChars = strlen(text);
    int letters = 0, digits = 0, spaces = 0;

    countChars(text, letters, digits, spaces);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символи:\t%d\n", allChars);
    printf("Слів:\t\t%d\n", count);

    double lettersPer = 100.0*letters/allChars;
    double digitsPer = 100.0*digits/allChars;
    double spacesPer = 100.0*spaces/allChars;
    
    printf("Літер:\t\t%d(%.1f%%)\n", letters, lettersPer);
    printf("Цифр:\t\t%2d(%.1f%%)\n", digits, digitsPer);
    printf("Пробілів:\t%d(%.1f%%)\n", spaces, spacesPer);

}

void MinMaxWord(char **words, int count){
    int Maxword = 0;
    int Minword = (int)strlen(words[0]);
    int i = 0, j=0;
    int maxplace = 0;
    int minplace = 0;
    while(i<count){
        if((int)strlen(words[i])>Maxword){
            Maxword=(int)strlen(words[i]);
            maxplace = i;
        }
        i++;
    }
    while(j < count){
        if((int)strlen(words[j]) < Minword){
            Minword=(int)strlen(words[j]);
            minplace = j;
        }
        j++;
    }
    printf("Найдовше слово: %s (%d)\n", words[maxplace], Maxword);
    printf("Найкоротше слово: %s (%d)\n", words[minplace], Minword);
}
void Averagelength(char **words, int count){
    int all = 0;
    for(int i=0; i< count; i++){
        all+=(int)strlen(words[i]);
    }
    double average=(double)all/count;
    printf("Середня довжина: %.2f\n", average);
}
void swapArrays(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(char **words, int low, int high){
    char *pivot = words[high];
    int i = low-1;

    for(int j = low; j<high; j++){
        if(strcmp(words[j],pivot)<=0){
            i++;
            swapArrays(&words[i], &words[j]);
        }
    }
    swapArrays(&words[i+1], &words[high]);
    return (i+1);
}
void QuickSort(char **words, int low, int high){
    if(low<high){
        int pi = Partition(words, low, high);
        QuickSort(words, low, pi-1);
        QuickSort(words, pi+1, high);
    }
}
void MostFrequentW(char **wordscopy, int count){
    char *MostFreq = wordscopy[0];
    int max = 1;
    int current = 1; 
    for(int i=1; i< count; i++){
        if(strcmp(wordscopy[i], wordscopy[i-1])==0){
            current++;
        }
        else current =1;
        if(current>max){
            max=current;
            MostFreq = wordscopy[i];
        }
    }
    printf("Найчастіше слово: %s (%d)\n", MostFreq, max);

}
void WordTable(char **words, int count){
    if (count <= 0 || words == nullptr) {
        printf("Помилка: слів для аналізу немає.");
        return;
    }
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");
    MinMaxWord(words, count);
    Averagelength(words, count);

    char **wordscopy = new char* [count];
    for(int i=0; i<count; i++){
        wordscopy[i]=words[i];
    }
    QuickSort(wordscopy, 0, count-1);
    printf("За абеткою: ");
    for(int i=0; i< count; i++){
        printf("%s ", wordscopy[i]);
    }
    printf("\n");
    MostFrequentW(wordscopy, count);
    delete [] wordscopy;
}


void ChangeWord(char text[], char **&words, int &count){
    char from2[32], to2[32];
    printf("Замінити слово: ");
    scanf("%31s", from2);    
    printf("На слово: ");
    scanf("%31s", to2);
    string from(from2);
    string to(to2);    

    for (int i=0; i<from.length(); i++) {
        unsigned char c=static_cast<unsigned char>(from[i]);
        if (!isalnum(c)) {
            printf("Помилка: слово для заміни має містити лише латинські літери та цифри.\n");
            return;
        }
    }

    for (int i=0; i<to.length(); i++) {
        unsigned char c=static_cast<unsigned char>(to[i]);
        if (!isalnum(c)) {
            printf("Помилка: нове слово має містити лише латинські літери та цифри.\n");
            return;
        }
    }

    string stText(text);
    int replacement=0;
    int pos=0;
    while ((pos = stText.find(from, pos)) != string::npos) {
        bool leftEmpty = (pos == 0 || !isalnum(static_cast<unsigned char>(stText[pos - 1])));
        bool rightEmpty = (pos + from.length() == stText.length() || !isalnum(static_cast<unsigned char>(stText[pos + from.length()])));

        if (leftEmpty && rightEmpty) {
            int newLength = stText.length() - from.length() + to.length();
            if (newLength >= 256) {
                printf("Помилка: текст перевищує 255 символів.\n");
                return;
            }
            stText.replace(pos, from.length(), to);
            replacement++;
            pos += to.length();
        } else {
            pos += from.length();
        }
    }

    if (replacement == 0) {
        printf("\nСлово не знайдено.\n");
        return;
    }

    printf("Замін виконано %d\n", replacement);
    printf("Було: \"%s\"\n", text);
    strcpy(text, stText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", stText.length());

    freeWords(words, count);
    words = splitWords(text, count);
}

bool RegisterCheck(const string &s1, const string &s2) {
    if (s1.length() != s2.length()) return false;
    for (int i = 0; i < s1.length(); i++) {
        if (tolower(static_cast<unsigned char>(s1[i])) != tolower(static_cast<unsigned char>(s2[i]))) {
            return false;
        }
    }
    return true;
}
void Compare() {
    char A[32], B[32];
    printf("Перше слово: ");
    scanf("%31s", A);
    printf("Друге слово: ");
    scanf("%31s", B);
    string a(A);
    string b(B);
    for (int i=0; i<a.length(); i++) {
        if (!isalnum((unsigned char)a[i])) {
            printf("Помилка: слова мають містити лише латинські літери та цифри.\n");
            return;
        }
    }
    for (int i=0; i<b.length(); i++) {
        if (!isalnum((unsigned char)b[i])) {
            printf("Помилка: слова мають містити лише латинські літери та цифри.\n");
            return;
        }
    }
    int result = strcmp(a.c_str(), b.c_str());
    printf("strcmp: ");
    if (result < 0) printf("-1 -> перше слово менше\n");
    else if (result == 0)printf("0 -> слова рівні\n");
    else printf("1 -> друге слово менше\n");

    printf("Рівні (==): ");
    if (a == b) printf("так\n");
    else printf("ні\n");

    printf("Рівні без урахування регістру: ");
    bool reg = RegisterCheck(a, b);
    if (reg) printf("так\n");
    else printf("ні\n");

    printf("Довжини: %zu і %zu\n", a.length(), b.length());
    string concatenated = a + " & " + b;
    printf("Конкатенація: \"%s\" (%zu)\n", concatenated.c_str(), concatenated.length());
}

void CharInfo(const char text[], int count){
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c);
    printf("Символ: \'%c\'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", c, c, c);
    for(int i=7; i>=0; i--){
        int bit = (c>>i) & 1;
        printf("%d", bit);
    }
    printf(")\n");
    printf("Тип: ");
    if(islower(c)) printf("мала літера\n");
    else if(isupper(c)) printf("велика літера\n");
    else if(isdigit(c)) printf("цифра\n");
    else if(isspace(c)) printf("пробіл\n");
    else printf("інший символ\n");

    printf("Інший регістр: ");
    char otherReg;
    if(isupper(c)){
        otherReg = tolower(c);
        printf("%c\n", otherReg);
    } 
    else if(islower(c)){
        otherReg = toupper(c);
        printf("%c\n", otherReg);
    }
    else printf("Символ не є літерою.\n");
    char next= c+1;
    printf("Наступний символ: %c\n", next);

    int amount = 0;
    int firstPos = -1;

    for (int i=0; text[i] !='\0'; i++) {
        if (text[i]==c) {
            amount++;
            if (firstPos==-1) firstPos = i+1; 
        }
    }
    if (amount>0) printf("Входжень у тексті: %d, перше на позиції %d\n", amount, firstPos);
    else printf("Цього символа не знайдено у тексті.\n");
    
}

void NewSentence(char text[], int &count, char **&words){
    string word, newSentence="";
    int wordsAmount=0;
    printf("Введіть речення(крапка після останнього слова): ");
    while(cin >> word){
        wordsAmount++;
        if(newSentence.empty()) newSentence =word;
        else newSentence += " " + word;
        if(!word.empty() && word.back() == '.') break;
    }
        if((newSentence.length() > 255)){
            printf("Помилка: довжина речення маж бути меншою за 256 символів.");
            return;
        }
        bool valid=textValidation(newSentence.c_str());
        if(!valid){
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
            return;
        }
        strcpy(text, newSentence.c_str());
        printf("Прочитано слів: %d\n", wordsAmount);
        printf("Новий текст: \"%s\"\n", newSentence.c_str());
        printf("Довжина: %zu\n", newSentence.length());
    freeWords(words, count);
    words = splitWords(text, count);
}

int main(){
    char text[256];
    char **words = nullptr;
    int menu =-1;
    int count =0;
    bool correct = false;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof text, stdin) != NULL) {
        char *nl = strchr(text, '\n');
        if (nl != NULL) {
            *nl = '\0';
            correct = textValidation(text);
        }
    }
    if (strlen(text) > 255) {
        printf("Помилка: довжина речення має бути меншою за 256 символів.");
        return 1;
    }
    if (!correct) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 1;
    }
    words= splitWords(text, count);
    do{
        PrintMenu();
        printf("Введіть пункт меню:");
        if (scanf("%d", &menu) != 1) {
            printf("Помилка: введіть числове значення!\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (menu < 0 || menu > 6) {
            printf("Помилка: пункту %d немає в меню.\n", menu);
            continue; 
        }
        switch(menu){
        case 1:TextAndStatistics(text, count); break;
        case 2:WordTable(words, count); break;
        case 3:ChangeWord(text, words, count);break;
        case 4:Compare(); break;
        case 5:CharInfo(text, count); break;
        case 6:NewSentence(text, count, words);  break;
    }
    }while(menu !=0);
    freeWords(words, count);
    return 0;
}