/* Редактор текстового повідомлення
Конопка Марта СШІ-13
*/

#include<iostream>
#include<string>
#include<cstdio>
#include<cctype>
#include<cstring>

using namespace std;

// Перевірка коректності окремого слова
bool isValidWord(const char* word){
    if(word[0] == '\0'){
        return false;
    }
    for(int i = 0; word[i] != '\0'; i++){
        unsigned char c = word[i];
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))){
            return false;
        }
    }
    return true;
}
//Перевірка коректності всього речення
bool isValidText(const char* text){
    int length = strlen(text);
    if(length == 0 || length > 255){
        return false;
    }
    if(text[length - 1] != '.'){
        return false;
    }
    int wordsCharacters = 0;
    for(int i = 0; i < length - 1; i++){
        unsigned char c = text[i];
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){
            wordsCharacters++;
        }
        else if(c != ' '){
            return false;
        }
    }
    return wordsCharacters > 0;
}
//Розбитя тексту на динамічний масив слів
char** splitWords(const char* text, int &count){
    count = 0;
    char copy[256];
    strcpy(copy, text);

    char* token = strtok(copy, " .");
    while(token != nullptr && token[0] != '\0'){
        count++;
        token = strtok(nullptr, " .");
    }
    if(count == 0){
        return nullptr;
    }
    char** words = new char*[count];

    strcpy(copy, text);
    token = strtok(copy, " .");

    for(int i = 0; i < count; i++){
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(nullptr, " .");
    }
    return words;

}
//Звільнення динамічної пам'ятіб, виділеної під масив слів
void freeWords(char**& words, int& count){
    for(int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;

}
// Підрахунок літер, цифр та пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces){
    
    letters = 0;
    digits = 0;
    spaces = 0;
    int len = strlen(text);

    const char* pointer = text;
    while(*pointer != '\0'){
        unsigned char c = *pointer;
        if(isalpha(c)){
            letters++;
        }
        else if(isdigit(c)){
            digits++;
        }
        else if(c == ' '){
            spaces++;
        }
        pointer++;
    }
    printf("Літер:\t%d (%.1f%%)\n", letters, letters * 100.0 / len);
    printf("Цифр:\t%d (%.1f%%)\n", digits, digits * 100.0 / len);
    printf("Пробілів:\t%d (%.1f%%)\n", spaces, spaces * 100.0 / len);

}
// Пункт 1: виведення тексту, кількості символів, слів та статистики
void showStatistics(const char *text, int &letters, int &digits, int &spaces, int count){
    printf("Текст:\t\"%s\"\n", text);
    int len = strlen(text);
    printf("Символів:\t%d\n", len);
    printf("Слів:\t%d\n", count);
    countChars(text, letters, digits, spaces);

}
// Сортування злиттям
void mergeWords(char** words, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char** L = new char*[n1];
    char** R = new char*[n2];

    for(int i = 0; i < n1; i++){
        L[i] = words[left + i];
    }
      for(int j = 0; j < n2; j++){
        R[j] = words[mid + 1 + j];
}
int i = 0;
int j = 0;
int k = left;
while(i < n1 && j < n2){
    if(strcmp(L[i], R[j]) <= 0){
        words[k] = L[i];
        i++;
    }
    else{
        words[k] = R[j];
        j++;
    }
    k++;
}
while(i < n1){
    words[k] = L[i];
    i++;
    k++;
}
while(j < n2){
    words[k] = R[j];
    j++;
    k++;
}
delete[] L;
delete[] R;
}

// рекурсивне сортування злиттям масиву слів за абеткою
void mergeSort(char** words, int left, int right){
    if(left >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(words, left, mid );
    mergeSort(words, mid + 1, right);
    mergeWords(words, left, mid, right);
}
// Виведення слів за абеткою та пошук слова, що зустрічаєтся найчастіше
void printAlphabetandMostFrequent(char** words, int count){
    char** sortedWords = new char*[count];
    for(int i = 0; i < count; i++){
        sortedWords[i] = words[i];
    }
    mergeSort(sortedWords, 0, count - 1);
    printf("За абеткою:");
    for(int i = 0; i < count; i++){
        printf(" %s", sortedWords[i]);
    }
    printf("\n");

    char* mostFrequent = sortedWords[0];
    int maxFrequent = 1;
    int currentFrequent = 1;
    for(int i = 1; i < count; i++){
        if(strcmp(sortedWords[i], sortedWords[i - 1]) == 0){
            currentFrequent++;
            if (currentFrequent > maxFrequent){
                maxFrequent = currentFrequent;
                mostFrequent = sortedWords[i];
            }
        }
        else{
             currentFrequent = 1;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxFrequent);

    delete[] sortedWords;
}
// Пункт 2: вивід таблиці слів, пошук найдовшого та найкоротшого слова, середньої довжини
void showWords(char** words, int count){
    int longest = 0;
    int shortest = 0;
    double totallength = 0;
    printf("+----+-----------------+-------+\n");
    printf("| %2s | %-20s | %5s | \n",
           "N", "Слово", "Довж.");
    printf("+----+-----------------+-------+\n");
    for(int i = 0; i < count; i++){
        int len = strlen(words[i]);
        printf("| %2d | %-15s | %5d | \n" ,  i + 1, words[i], len);
               totallength += len;
               if(len > strlen(words[longest])){
                longest = i;
               }
                if(len < strlen(words[shortest])){
                    shortest = i;
                }
            }
               printf("+----+-----------------+-------+\n");
               printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
               printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
               printf("Середня довжина: %.2f\n", totallength / count);
}
// Пункт 3: заміна всіх входжень та оновлення динамічного масиву слів
void replaceWord(char* text, char**& words, int& count){
    char from[32];
    char to[32];
   
    printf("Замінити слово: ");
   if(scanf("%31s", from) != 1){
    printf("Помилка введення\n");
    return;
   }

    printf("На слово: ");
   if(scanf("%31s", to) != 1){
     printf("Помилка введення\n");
    return;
   } 
   int ch;
   while((ch = getchar()) != '\n' && ch != EOF){
   }

   if(!(isValidWord(from) && isValidWord(to))){
     printf("Помилка: можна використовувати лише латинські літери та цифри\n");
     return;

   }
   string result = text;
   string oldText = text;
   int replace = 0;
   size_t position = 0;
   while((position = result.find(from, position)) != string::npos){
    
    bool left = position == 0 || result[position - 1] == ' ';
    size_t rightPosition = position + strlen(from);

    bool right = result[rightPosition] == ' ' || result[rightPosition] == '.';
    if(left && right){

        result.replace(position,strlen(from), to);
        replace++;
        position += strlen(to);
    }
    else{
        position++;
    }

   }
   if(result.length() > 255){
    printf("Помилка: текст не має перевищувати 255 символів.\n");
    return;
   }
   strcpy(text, result.c_str());

   printf("Замін виконано: %d\n", replace);
   printf("Було: \"%s\"\n", oldText.c_str());
   printf("Стало: \"%s\"\n", text);
   printf("Нова довжина: %zu\n", strlen(text));

   freeWords(words, count);
   words = splitWords(text, count);
}
// Пункт 4: порівнянння слів через strcmp та оператори std:string
void compareWords(){
    char first[32];
    char second[32];

    printf("Перше слово: ");
    if((scanf("%31s", first) != 1)){
        printf("Помилка введення.\n");
        return;
    }
     printf("Друге слово: ");
    if((scanf("%31s", second) != 1)){
        printf("Помилка введення.\n");
        return;
    }
    int ch;
   while((ch = getchar()) != '\n' && ch != EOF){
   }
   if(!(isValidWord(first) && isValidWord(second))){
    printf("Помилка: можна використовувати лише латинські літери та цифри\n");
    return;
   }
    int comp = strcmp(first, second);
    if(comp < 0){
        comp = -1;
    }
    else if(comp > 0){
        comp = 1;
    }
    else{
        comp = 0;
    }
    printf("strcmp: %d -> ", comp);
    if(comp == -1){
        printf("перше слово менше\n");
    }
    else if(comp == 1){
        printf("перше слово більше\n");
    }
    else if (comp == 0){
         printf("слова однакові\n");
    }
    
    string a = first;
    string b = second;
    printf("Рівні(==): %s\n", a == b ? "так" : "ні");

    string lowerA = a;
    string lowerB = b;

    for(int i = 0; i < (int)lowerA.length(); i++){
        lowerA[i] = tolower((unsigned char)lowerA[i]);
    }
      for(int j = 0; j < (int)lowerB.length(); j++){
        lowerB[j] = tolower((unsigned char)lowerB[j]);
      }
      printf("Рівні без урахування регістру: %s\n", lowerA == lowerB ? "так" : "ні");
      printf("Довжини: %zu і %zu\n", (unsigned long)a.length(), (unsigned long)b.length());

      string combined = a + " & " + b;
      printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), (unsigned long)combined.length());
}
// Пункт 5: аналіз коду та типу символу, пошук його входжень у тексті
void informationCharacters(const char* text){
    char c;
    printf("Введіть символ: ");
    if(scanf("%c", &c) != 1){
        printf("Помилка введення\n");
        return;
    }

if(c != '\n'){ 
   int ch;
   while((ch = getchar()) != '\n' && ch != EOF){
   }
}
   unsigned char code = (unsigned char)c;
   printf("Символ: '%c'\n", c);
   printf("Код: %u (hex 0x%02X, oct 0%03o, bin ", code, code,code);
   for(int i = 7; i >= 0; i--){
    printf("%d", (code >> i) & 1);
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
    printf("Тип: пробільний символ\n");
   }
   else{
    printf("Тип: інший символ\n");
   }
   if(code < 255){
    printf("Наступний символ: '%c'\n", code + 1);
   }
   else{
    printf("Наступного символу немає\n");
   }

   int occur = 0;
   int firstPosition = -1;

   const char* pointer = strchr(text, c);
    if(pointer != nullptr){
        firstPosition = (int)(pointer - text) + 1;
        while(pointer != nullptr){
            occur++;
            pointer = strchr(pointer + 1, c);
        }
}
if(occur > 0){
    printf("Входжень у тексті: %d, перше на позиції %d\n", occur, firstPosition);
}
else{
    printf("Символа у тексті немає\n");
}
}
// Пункт 6: зчитування нового речення по словах та оновлення даних
void newSentence(char* text, char**& words, int& count){
    string sentence;
    string word;
    int readWords = 0;
    bool valid = true;
    bool finished = false;
printf("Введіть речення (крапка після останнього слова): ");
while(cin >> word){
    bool dot = false;
    if(!word.empty() && word[word.length() - 1] == '.'){
        dot = true;
        word.erase(word.length() - 1);
    }
    if(!isValidWord(word.c_str())){
        valid = false;
    }
    else{
        if(readWords > 0){
            sentence += " ";
        }
            sentence += word;
            readWords++;
    }
        if(dot){
            finished = true;
            break;
        }
}
    if(finished){
        sentence += ".";
    }
    cin.clear();
    cin.ignore(10000, '\n');

    if(!finished || !valid || readWords == 0 || sentence.length() > 255 || !isValidText(sentence.c_str())){
        printf("Помилка: некоректне речення\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main(){
    char text[256];
    int letters;
    int digits;
    int spaces;
    int count = 0;

    //Зчитування тексту, контроль переповнення
    printf("Введіть текст: ");
    if(fgets(text, sizeof(text), stdin) == nullptr){
        printf("Помилка введення\n");
        return 1; 
    }
    // Перевірка довжини тексту
    if(strchr(text, '\n') == nullptr){
        printf("Помилка: текст задовгий(максимум 255 символів)\n");
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';
    if(!isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр, пробілів та закінчуватися крапкою\n");
        return 1;
    }
    // Розбиття тексту на динамічний масив
    char** words = splitWords(text, count);
    
         int choice;
         char menu[100];
    
         do{
            printf("Пункт           Операція\n");
            printf("1               Показати текст і статистику\n"); 
            printf("2               Таблиця слів\n"); 
            printf("3               Замінити слово\n"); 
            printf("4               Порівняти два слова\n"); 
            printf("5               Інформація про символ\n"); 
            printf("6               Ввести нове речення\n"); 
            printf("0               Вийти\n"); 

            printf("Введіть пункт меню: ");
            if(fgets(menu, sizeof(menu), stdin) == nullptr){
                break;
            }
            // Перевірка вибору пункту меню
            char extra;
            if(sscanf(menu, "%d %c", &choice, &extra) != 1){
                printf("Помилка: введіть номер пункту меню\n");
                continue;
            }
            switch(choice){
                case 1: 
                showStatistics(text, letters, digits, spaces, count); 
                break;
                case 2:
                showWords(words,count);
                printAlphabetandMostFrequent(words, count);
                break;
                case 3: 
                replaceWord(text, words,count);
                break;
                case 4: 
                compareWords();
                break;
                case 5: 
                informationCharacters(text);
                break;    
                case 6: 
                newSentence(text, words, count);
                break;
                case 0:
                freeWords(words, count);
                printf("Програму завершено\n");
                break;
                default: 
                printf("Помилка: оберіть пункт з меню\n");
                break;
            }
         }
        while(choice != 0);

    return 0;
}  