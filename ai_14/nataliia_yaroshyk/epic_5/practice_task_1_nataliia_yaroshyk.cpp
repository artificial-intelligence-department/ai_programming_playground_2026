#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

// Валідація тексту
bool isValidText(const char *text){
    int len = strlen(text);
    if(len == 0 || len > 255 || text[len - 1] != '.') return false;

    bool hasWord = false;
    for(int i = 0; i < len - 1; i++){
        if(isalnum(text[i])){
            hasWord = true;
        } else if(text[i] != ' '){
            return false;
        }
    }
    return hasWord;
}

// Валідація слова 
bool isValidWord(const char *word){
    int len = strlen(word);
    if(len == 0 || len > 31) return false;
    for(int i = 0; i < len; i++){
        if(!isalnum(word[i])) return false;
    }
    return true;
}

char **splitWords(const char *text, int &count){
    count = 0;

    char *temp = new char[strlen(text) + 1];
    strcpy(temp, text);

    char *dot = strchr(temp, '.');
    if(dot != nullptr) *dot = '\0';

    char *tempWords[128];
    char *token = strtok(temp, " ");

    while(token != nullptr){
        tempWords[count] = new char[strlen(token) + 1];
        strcpy(tempWords[count], token);
        count++;
        token = strtok(nullptr, " ");
    }

    delete[] temp;
    if(count == 0) return nullptr;

    char **words = new char*[count];
    for(int i = 0; i < count; i++){
        words[i] = tempWords[i];
    }
    
    return words;
}

void freeWords(char **&words, int &count){
    if(words != nullptr){
        for(int i = 0; i < count; i++){
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

// 1. Показати текст і статистику
void showTextAndStat(const char *text, int count, int letters, int digits, int spaces){
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %3zu\n", strlen(text));
    printf("Слів:     %3d\n", count);
    printf("Літер:    %3d (%5.1f%%)\n", letters, 100.0 * letters / strlen(text));
    printf("Цифр:     %3d (%5.1f%%)\n", digits, 100.0 * digits / strlen(text));
    printf("Пробілів: %3d (%5.1f%%)\n", spaces, 100.0 * spaces / strlen(text));
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;

    while(*text != '\0'){
        if(isalpha(*text)) letters++;
        else if(isdigit(*text)) digits++;
        else if(*text == ' ') spaces++;
        text++;
    }
}

// 2. Таблиця слів
void wordTable(char **words, int count){
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    int totalLen = 0;
    int minIndx = 0;
    int maxIndx = 0;

    for(int i = 0; i < count; i++){
        int len = strlen(words[i]);
        totalLen += len;

        if(len > (int)strlen(words[maxIndx])) maxIndx = i;
        if(len < (int)strlen(words[minIndx])) minIndx = i;

        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
    }

    // Сортування копії слів за абеткою
    char **sorted = new char*[count];
    for(int i = 0; i < count; i++){
        sorted[i] = new char[strlen(words[i]) + 1];
        strcpy(sorted[i], words[i]);
    }

    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            if(strcmp(sorted[j], sorted[j + 1]) > 0){
                char *tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    // Пошук найчастішого слова у відсортованому масиві
    int maxFreq = 0;
    int mostFreqIdx = 0;
    for(int i = 0; i < count; i++){
        int freq = 0;
        for(int j = 0; j < count; j++){
            if(strcmp(sorted[i], sorted[j]) == 0) freq++;
        }
        if(freq > maxFreq){
            maxFreq = freq;
            mostFreqIdx = i;
        }
    }
  
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%zu)\n", words[maxIndx], strlen(words[maxIndx]));
    printf("Найкоротше слово: %s (%zu)\n", words[minIndx], strlen(words[minIndx]));
    printf("Середня довжина: %.2f\n", (double)totalLen / count);
    printf("За абеткою: ");
    for(int i = 0; i < count; i++){
        printf("%s%s", sorted[i], (i < count - 1) ? " " : "\n");
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[mostFreqIdx], maxFreq);

    int sortedCount = count;
    freeWords(sorted, sortedCount);
}

// 3. Замінити слово
void changeWord(char *text, char **&words, int &count){
    char fromBuf[256] = {}, toBuf[256] = {};

    printf("Замінити слово: ");
    scanf("%255s", fromBuf);

    printf("На слово: ");
    scanf("%255s", toBuf);

    if(!isValidWord(fromBuf) || !isValidWord(toBuf)){
        printf("Помилка: слова мають складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    string strText = text;
    string from = fromBuf;
    string to = toBuf;

    int replaced = 0;
    size_t pos = 0;

    while((pos = strText.find(from, pos)) != string::npos){
        bool leftOk = (pos == 0 || strText[pos - 1] == ' ');
        size_t afterPos = pos + from.length();
        bool rightOk = (afterPos < strText.length() && (strText[afterPos] == ' ' || strText[afterPos] == '.'));

        if(leftOk && rightOk){
            strText.replace(pos, from.length(), to);
            pos += to.length();
            replaced++;
        } else {
            pos += 1;
        }
    }

    if(strText.length() > 255){
        printf("Помилка: результат не може перевищувати 255 символів.\n");
        return;
    }

    printf("Замін виконано: %d\n", replaced);
    printf("Було: \"%s\"\n", text);
    
    strcpy(text, strText.c_str());

    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", strlen(text));

    freeWords(words, count);
    words = splitWords(text, count);
}

// 4. Порівняти два слова
void compareTwoWords(){
    char buf1[256] = {}, buf2[256] = {};

    printf("Перше слово: ");
    scanf("%255s", buf1);
    printf("Друге слово: ");
    scanf("%255s", buf2);

    if(!isValidWord(buf1) || !isValidWord(buf2)){
        printf("Помилка: слова мають складатися лише з латинських літер і цифр (до 31 символу).\n");
        return;
    }

    string w1 = buf1;
    string w2 = buf2;

    int rawCmp = strcmp(w1.c_str(), w2.c_str());
    int cmp = (rawCmp < 0) ? -1 : (rawCmp > 0 ? 1 : 0);
    const char *explanation = (cmp < 0) ? "перше слово менше"
                            : (cmp > 0) ? "перше слово більше"
                                        : "слова однакові";
    printf("strcmp: %d -> %s\n", cmp, explanation);

    printf("Рівні (==): %s\n", (w1 == w2) ? "так" : "ні");

    string low1 = w1, low2 = w2;
    for(size_t i = 0; i < low1.length(); i++) low1[i] = tolower(low1[i]);
    for(size_t i = 0; i < low2.length(); i++) low2[i] = tolower(low2[i]);
    printf("Рівні без урахування регістру: %s\n", (low1 == low2) ? "так" : "ні");

    string concat = w1 + " & " + w2;
    printf("Довжини: %zu і %zu\n", w1.length(), w2.length());
    printf("Конкатенація: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

// 5. Інформація про символ
void symbolInfo(const char *text){
    char ch;

    printf("Введіть символ: ");
    scanf(" %c", &ch);
    unsigned char uch = (unsigned char)ch;

    char bin[9] = {};
    for(int i = 7; i >= 0; i--){
        bin[7 - i] = ((uch >> i) & 1) ? '1' : '0';
    }

    printf("Символ: '%c'\n", ch);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", uch, uch, uch, bin);

    if(isupper(uch)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(uch));
    }else if(islower(uch)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(uch));
    }else if(isdigit(uch)){
        printf("Тип: цифра\n");
        printf("Інший регістр: немає\n");
    }else if(isspace(uch)){
        printf("Тип: пробільний символ\n");
        printf("Інший регістр: немає\n");
    }else{
        printf("Тип: інший символ\n");
        printf("Інший регістр: немає\n");
    }

    printf("Наступний символ: '%c'\n", (char)(uch + 1));

    int count = 0;
    int firstPos = -1;

    for(int i = 0; text[i] != '\0'; i++){
        if(text[i] == ch){
            if(firstPos == -1) firstPos = i + 1;
            count++;
        }
    }

    if(count == 0){
        printf("Входжень у тексті: символ у тексті відсутній\n");
    }else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    }
}

// 6. Ввести нове речення
void enterNewSentence(char *text, char **&words, int &count){
    string word, sentence;
    int wordsRead = 0;

    printf("Введіть речення (крапка після останнього слова): ");
   
    while(cin >> word){
        if(wordsRead > 0) sentence += " ";
        sentence += word;
        wordsRead++;

        if(strchr(word.c_str(), '.') != nullptr) break;
    }

    if(!isValidText(sentence.c_str())){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою (до 255 символів).\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", wordsRead);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main(){
    int num;
    int letters = 0, digits = 0, spaces = 0;
    char text[256] = {};

    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    if(!isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    int count = 0;
    char **words = splitWords(text, count);

    do{
        printf("\n1\tПоказати текст і статистику\n");
        printf("2\tТаблиця слів\n");
        printf("3\tЗамінити слово\n");
        printf("4\tПорівняти два слова\n");
        printf("5\tІнформація про символ\n");
        printf("6\tВвести нове речення\n");
        printf("0\tВийти\n");
        printf("Ваш вибір: ");

        if(scanf("%d", &num) != 1){
            printf("Помилка: введіть номер пункту меню.\n");
            char trash[256];
            fgets(trash, sizeof(trash), stdin); 
            num = -1;
            continue;
        } 

        if(num > 6 || num < 0){
            printf("Помилка: пункту %d немає в меню.\n", num);
            break;
        } 

        switch(num){
            case 1:
                countChars(text, letters, digits, spaces);
                showTextAndStat(text, count, letters, digits, spaces);
                break;
            case 2:
                wordTable(words, count);
                break;
            case 3:
                changeWord(text, words, count);
                break;
            case 4:
                compareTwoWords();
                break;
            case 5:
                symbolInfo(text);
                break;
            case 6:
                enterNewSentence(text, words, count);
                break;
            case 0:
                break;
        }
    }while(num != 0);

    freeWords(words, count);
    return 0;
}