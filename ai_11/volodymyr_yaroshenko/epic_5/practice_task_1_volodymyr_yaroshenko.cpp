/*  
Практичне завдання
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
using namespace std;
void freeWords(char **&words, int &count) {
    for(int i =0; i< count; i++) {
        delete[] words[i];
    }
   delete[] words;
   words = nullptr;
   count = 0;
}

bool check_text(char* text) {
    int i =0;
    int len = strlen(text);
    if(len == 0 || text[len-1] != '.') {
    printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
    return 0;
    }
    while(text[i] != '\0') {
  char sym = text[i];
  bool check = false;
  if(isalpha(sym) || isdigit(sym) || isspace(sym) || sym == '.'){
    check =true;
    }
    if(check == false) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    i++;
}
return 1;
}

char**splitWords(const char* text, int &count) {
char new_text[256];
strcpy(new_text, text);
new_text[strlen(new_text) - 1] = '\0';
count =0;
char **words = new char*[128];
char *t = strtok(new_text, " ");
while (t != NULL) {
    words[count] = new char[strlen(t) + 1];
    strcpy(words[count], t);
    t = strtok(NULL, " ");
    count++;
}
return words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    for(int i =0; i<strlen(text)-1; i++) {
        if(isalpha(text[i])){
        letters++;
        }
        if(isdigit(text[i])){
        digits++;
        }
        if(isspace(text[i])){
        spaces++;
        }
    }
}

int partitionWords(char** a, int low, int high) {
char* pivot = a[high];
int i = low - 1;
for (int j = low; j < high; j++) {
    if (strcmp(a[j], pivot) <= 0) {
        i++;
        char* temp = a[i];
        a[i] = a[j];
        a[j] = temp;    
    }
}
char* temp = a[i + 1];
a[i + 1] = a[high];
a[high] = temp;
return i + 1;
}

void quickSortWords(char** a, int low, int high) {
if (low < high) {
    int p = partitionWords(a, low, high);
    quickSortWords(a, low, p - 1);
    quickSortWords(a, p + 1, high);
    }
}

bool checkWord(char* word) {
    if(strlen(word) ==0) {
        return false;
    }
    for (int i = 0; i < strlen(word); i++) {
        if (!isalpha(word[i]) && !isdigit(word[i])) {
            return false;
        }
    }
    return true;
}

void replaceWord(char* text, char* from, char* to, char** &words, int& count) {
string result = "";
int replaceCount =0;
for(int i=0; i<count; i++) {
    if(strcmp(words[i], from) == 0) {
        result += to;
        replaceCount++;
    }
    else {
        result += words[i];
    }
    if (i < count - 1) {
        result += " ";
    }
}
result += ".";
if (result.length() > 255) {
    printf("Помилка: текст перевищує 255 символів!\n");
    return;
}
printf("Замін виконано: %d\n", replaceCount);
printf("Було: \"%s\"\n", text);
strcpy(text, result.c_str());
freeWords(words, count);
words = splitWords(text, count);
printf("Стало: \"%s\"\n", text);
printf("Нова довжина: %d\n", int(strlen(text)));
}

void case1(const char* text, int &count) {
int symvols = strlen(text);
int letters =0, digits =0, spaces =0;
countChars(text, letters, digits, spaces);
printf("%-12s \t\"%s\"\n", "Текст:", text);
printf("%-12s \t%d\n", "Символів:", symvols);
printf("%-12s \t%d\n", "Слів:", count);
printf("%-12s \t%d (%4.1f%%)\n", "Літер:", letters, (double)letters / symvols * 100);
printf("%-12s \t%d (%4.1f%%)\n", "Цифр: ", digits, (double)digits / symvols * 100);
printf("%-12s \t%d (%4.1f%%)\n", "Пробілів:", spaces, (double)spaces / symvols * 100);
}

void case2(const char* text,int &count, char** words) {
printf("+----+-----------------+-------+\n");
printf("| N  | Слово           | Довж. |\n");
printf("+----+-----------------+-------+\n");
for(int i=0; i<count;i++){
    printf("| %-2d | %-15s | %5d |\n", i+1, words[i], int(strlen(words[i])));
}
printf("+----+-----------------+-------+\n");
char* min = words[0];
char* max = words[0];
double sum = strlen(words[0]);
for(int i =1; i<count; i++) {
sum +=strlen(words[i]);
if(strlen(words[i]) < strlen(min)) {
    min = words[i];
}
if(strlen(words[i]) > strlen(max)) {
    max = words[i];
}
}
printf("Найдовше слово: %s (%d)\n", max, int(strlen(max)));
printf("Найкоротше слово: %s (%d)\n", min, int(strlen(min)));
printf("Середня довжина: %.2f\n", (sum/(count)));

char** sorted = new char*[count];
for (int i = 0; i < count; i++) {
    sorted[i] = words[i];
}
quickSortWords(sorted, 0, count-1);
printf("За абеткою: ");
for (int i = 0; i < count; i++) {
        printf("%s ", sorted[i]);
    }
char* most = sorted[0];
int Count = 0;
for (int i = 0; i < count; i++) {
    int currentCount = 0;
    for (int j = 0; j < count; j++) {
        if (strcmp(sorted[i], sorted[j]) == 0) {
            currentCount++;
        }
    }
    if (currentCount > Count) {
        Count = currentCount;
        most = sorted[i];
    }
}
printf("\nНайчастіше слово: %s (%d)\n", most, Count);
delete[] sorted;
}

void case3(char* text, int &count, char**& words) {
char from[256];
char to[256];
from:
printf("Замінити слово: ");
scanf("%255s", from);
if(!checkWord(from)) {
printf("Некоректне введення!\n");
return;
}
bool found = false;
for (int i = 0; i < count; i++) {
    if (strcmp(words[i], from) == 0) {
        found = true;
    } 
}
if(found == false) {
    printf("Такого слова немає в тексті, введіть ще раз:\n ");
    goto from;
}
printf("На слово: ");
scanf("%255s", to);
if(!checkWord(to)) {
printf("Некоректне введення!\n");
return;
}
replaceWord(text, from, to, words, count);
}

void case4() {
char a[32];
char b[32];
printf("Перше слово: ");
scanf("%s", a);
if(!checkWord(a)|| strlen(a) > 32) {
printf("Некоректне введення!\n");
return;
}
printf("Друге слово: ");
scanf("%s", b);
if(!checkWord(b) || strlen(b) >32) {
printf("Некоректне введення!\n");
return;
}
if(strcmp(a, b) == 0) {
    printf("strcmp: 0 -> cлова повністю однакові\n");
}
if(strcmp(a, b) < 0) {
    printf("strcmp: -1 -> перше слово менше\n");
}
if(strcmp(a, b) > 0) {
    printf("strcmp: 1 -> перше слово більше\n");
}
string(a) == string(b) ? printf("Рівні (==): так\n") : printf("Рівні (==): ні\n");
char aCopy[32];
char bCopy[32];
strcpy(aCopy, a);
strcpy(bCopy, b);
for (int i = 0;  i < strlen(aCopy); i++) {
    aCopy[i] = tolower(aCopy[i]);
}

for (int i = 0; i < strlen(bCopy); i++) {
    bCopy[i] = tolower(bCopy[i]);
}

if (strcmp(aCopy, bCopy) == 0) {
    printf("Рівні без урахування регістру: так\n");
}
else {
    printf("Рівні без урахування регістру: ні\n");
}
printf("Довжини: %d i %d\n", int(strlen(a)), int(strlen(b)));
char konk[strlen(a) + strlen(b) +3];
strcpy(konk, a);
strcat(konk, b);
printf("Конкатенація: \"%s & %s\" (%d)\n", a, b, int(sizeof(konk)));
}

void case5(const char* text) {
char c;

printf("Введіть символ: ");
scanf(" %c", &c);
while (getchar() != '\n');
char original = c;
printf("Cимвол: \'%c\'\n", c);
int code = c;
printf("Код: %d, (hex 0x%X, oct 0%o, bin ", code, code, code);
for (int i = 7; i >= 0; i--) {
    printf("%d", (code >> i) & 1);
}
printf(")\n");
if (islower(c)) {
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(c));
    }
    else if (isupper(c)) {
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(c));
    }
    else if (isdigit(c)) {
        printf("Тип: цифра\n");
    }
    else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: інший символ\n");
    }
printf("Наступний символ: \'%c\'\n",  char(original+1));
int count=0;
int index = -1;
for(int i =0; i < strlen(text); i++) {
    if(text[i] == original) {
    count++;        
if (index == -1) {
    index = i;
}
}
}
if(count>0) {
    printf("Входжень у тексті: %d, перше на позиції %d\n", count, index +1);
}
else {
    printf("Символ відсутній у тексті.\n");
}
}

void case6(char* text, int& count, char**& words) {
char sentence[256] = {};
char word[256];
int wordsCount =0;
printf("Введіть нове речення (крапка після останнього слова): ");
while (true) {
cin >> word; 
int len = strlen(sentence);
if (len + strlen(word) + 1 > 255) {
    printf("Помилка: текст перевищує 255 символів!\n");
    return;
}
if (len > 0) {
    strcat(sentence, " ");
    wordsCount++;
}
strcat(sentence, word);  
    if (word[strlen(word) - 1] == '.') break;
}
if (!check_text(sentence)) {
    return;
}
strcpy(text, sentence);
freeWords(words, count);
words = splitWords(text, count);
printf("Прочитано слів: %d\n", wordsCount +1);
printf("Новий текст \"%s\"\n", text);
printf("Довжина %d\n", int(strlen(text)));
}

int main(){
char text[256];
int count =0;
char choise[256];
int num;
char** words = nullptr;
printf("Введіть текст (до 255 символів, крапка в кінці):" );
fgets(text, 256, stdin);
text[strcspn(text, "\n")] = '\0';
if(!check_text(text)) {
goto clear;   
}
words = splitWords(text, count);
do { menu:
printf("%d) %s", 1, "Показати текст і статистику\n");
printf("%d) %s", 2, "Таблиця слів\n");
printf("%d) %s", 3, "Замінити слово\n");
printf("%d) %s", 4, "Порівняти два слова\n");
printf("%d) %s", 5, "Інформація про символ\n");
printf("%d) %s", 6, "Ввести нове речення\n");
printf("%d) %s", 0, "Вийти\n");
scanf("%255s", choise);
if (strlen(choise) != 1 || !isdigit(choise[0])) {
    printf("Помилка: введіть номер пункту меню.\n");
    goto menu;
}
num = choise[0] - '0';
if (num < 0 || num > 6) {
    printf("Помилка: пункту %d немає в меню.\n", num);
    goto menu;
}
switch(num) {
    case 1:
    case1(text, count);
    break;
    case 2:
    case2(text,count, words);
    break;
    case 3:
    case3(text, count, words);
    break;
    case 4:
    case4();
    break;
    case 5:
    case5(text);
    break;
    case 6:
    case6(text, count, words);
    break;
    case 0:
    printf("Ви вийшли з програми\n");
    break;
    default:
    printf("Помилка: некоректне знчення\n");
    break;
}
}
while(num !=0);
 clear:
freeWords(words, count); 
    return 0;   
}