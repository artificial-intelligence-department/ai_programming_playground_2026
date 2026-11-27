#include <cstdio>
#include <cstring>
#include <cctype>
#include <string> 
#include <iostream>

using namespace std;

void freeWords(char **words, int &count){
    for(int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces){
    while(*text != '\0'){
        if(isalpha(*text)){
            letters++;
        }
        else if(isdigit(*text)){
            digits++;
        }
        else if(isspace(*text)){
            spaces++;
        }
        text++;
    }
}

void statistics(const char *text, int count){
    int letters = 0, digits = 0, spaces = 0;
    printf("Текст:\t\"%s\"\n", text);
    countChars(text, letters, digits, spaces);
    int len = strlen(text);
    
    printf("Символів:\t%d\n", len);
    printf("Слів:\t%d\n", count);
    printf("Літер:\t%d (%3.1f%%)\n", letters, float(letters)*100/len);
    printf("Цифр:\t%d (%3.1f%%)\n", digits, float(digits)*100/len);
    printf("Пробілів:\t%d (%3.1f%%)\n", spaces, float(spaces)*100/len);  
}

char **splitWords(const char *text, int &count){
    char** words = new char*[128];

    count = 0;
    int i = 0;
    bool newWord = true;
    while(text[i] != '.'){
        if(text[i] != ' ' && newWord){
            words[count] = new char[256];
            int j = 0;
            while(text[i+j] != ' ' && text[i+j] != '.'){
                words[count][j] = text[i+j];
                j++;
            }
            words[count][j] = '\0';
            count++;
            i += j-1;
            newWord = false;
        }
        else{
            newWord = true;
        }
        i++;
    }

    return words;
}

void table(char **words ,int count){
    printf("+----+-----------------+-------+ \n| N  | Слово           | Довж. | \n+----+-----------------+-------+ \n");
    for(int i = 0; i < count; i++){
        printf("|  %3d | %-15s|    %d |\n", i, words[i], int(strlen(words[i])));
    }
    printf("+-----+----------------+-------+ \n");

    int min = strlen(words[0]), max = strlen(words[0]), minInd = 0, maxInd = 0, sum = 0; 
    for(int i = 0; i < count; i++){
        if(strlen(words[i]) > max){
            max = strlen(words[i]);
            maxInd = i;
        }
        if(strlen(words[i]) < min){
            min = strlen(words[i]);
            minInd = i;
        }
        sum += strlen(words[i]);
    }
    printf("Найдовше слово: %s (%d)\n", words[maxInd], max);
    printf("Найкоротше слово: %s (%d)\n", words[minInd], min);
    printf("Середня довжина: %.2f\n", float(sum)/count);

    int *tmp = new int[128];

    for(int i = 0; i < count; i++){
        tmp[i] = i;
    }

    printf("За абеткою: ");
    for(int i = 0; i < count; i++){
        int minInd = i; 
        for(int j = i; j < count; j++){
            if(strcmp(words[tmp[j]],words[tmp[minInd]]) < 0){
                minInd = j;
            }
        }
        int temp = tmp[i];
        tmp[i] = tmp[minInd];
        tmp[minInd] = temp;
        printf("%s ", words[tmp[i]]);
    }
    printf("\n");

    int length = 1;
    int maxLength = 1;
    int maxStart = 0;

    for (int i = 0; i < count - 1; i++) {
        if (strcmp(words[tmp[i]], words[tmp[i + 1]]) == 0) {
            length++;
            if (length > maxLength) {
                maxLength = length;
                maxStart = i;
            }
        } else {
            length = 1;
        }
    }

    printf("Найчастіше слово: %s (%d)\n", words[tmp[maxStart]], maxLength);

    delete[] tmp;
}

void changeWord(char *text, char **&words, int count){
    char wordToChange[32];
    char newWord[32];
    printf("Замінити слово:");

    fgets(wordToChange, sizeof(wordToChange), stdin);
    int len = strlen(wordToChange);

    char *check = strchr(wordToChange, '\n');

    if(check != NULL){
        *check = '\0';
        len--;
    }
    else{
        printf("Помилка: слово задовге.");
        return;
    }
    
    for(int i = 0; i < len; i++){
        if(isalpha(wordToChange[i]) == 0 && isdigit(wordToChange[i]) == 0){
            printf("Помилка: слово є некоректним");
            return;
        }
    }

    printf("На слово:");
    fgets(newWord, sizeof(newWord), stdin);
    len = strlen(newWord);

    check = strchr(newWord, '\n');

    if(check != NULL){
        *check = '\0';
        len--;
    }
    else{
        printf("Помилка: слово задовге.");
        return;
    }
    
    for(int i = 0; i < len; i++){
        if(isalpha(newWord[i]) == 0 && isdigit(newWord[i]) == 0){
            printf("Помилка: слово є некоректним");
            return;
        }
    }

    string newText = text;
    string word = newWord;
    string word1 = wordToChange;
    int changes = 0;
    int shift = 0;

    for(int i = 0; i < count; i++){
        string word2 = words[i];
        if(word1 == word2){
            newText.replace(shift, word2.length(), word);
            changes++;
            shift += word.length() + 1;
            while(newText[shift] == ' ' && newText[shift] != '.'){shift++;}
        }
        else{
            shift += word2.length() + 1;
            while(newText[shift] == ' ' && newText[shift] != '.'){shift++;}
        }
    }

    if(newText.length() > 255){
        printf("Помилка: новий текст задовгий.");
        return;
    }
    else{
        printf("Замін виконано: %d\n", changes);
        printf("Було: \"%s\"\n", text);
        strcpy(text, newText.c_str());
        printf("Стало: \"%s\"\n", text);
        printf("Нова довжина: %zu\n", strlen(text));
    }

    freeWords(words, count);

    words = splitWords(text, count);

    return;
}

void cmp2Words(){
    char a[32];
    char b[32];

    printf("Введіть перше слово: ");
    scanf("%31s", a);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int i = 0;
    while(a[i] != '\0'){
        if(isalpha(a[i]) == 0 && isdigit(a[i]) == 0){
            printf("Помилка: ви ввели некоректне слово\n");
            return;
        }
        i++;
    }

    printf("Введіть друге слово: ");
    scanf("%31s", b);
    while ((c = getchar()) != '\n' && c != EOF);

    i = 0;
    while(b[i] != '\0'){
        if(isalpha(b[i]) == 0 && isdigit(b[i]) == 0){
            printf("Помилка: ви ввели некоректне слово\n");
            return;
        }
        i++;
    }

    printf("Перше слово: %s\nДруге слово: %s\n", a, b);
    int cmp = strcmp(a,b);
    printf("strcmp: %d -> ", cmp);
    if(cmp == 0){
        printf("Слова рівні\n");
    }
    else if(cmp < 0){
        printf("Перше слово менше\n");
    }
    else if(cmp > 0){
        printf("Перше слово більше\n");
    }

    string str_a = a;
    string str_b = b;

    printf("Рівні (==): %s", str_a==str_b ? "Так\n" : "Ні\n");
    printf("Рівні без урахування регістру: %s", strcasecmp(a,b) == 0 ? "Так\n" : "Ні\n");
    printf("Довжини: %zu і %zu \n", strlen(a), strlen(b));
    
    string cat = str_a + " & " + str_b;
    printf("Конкатенація: \"%s\" (%zu)\n", cat.c_str(), cat.length());
}

void symbolInfo(char *text){
    char symbol;
    printf("Введіть символ: ");
    scanf("%c", &symbol);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if(isalpha(symbol) == 0){
        printf("Помилка: це не символ.\n");
        return;
    }

    printf("Символ: \'%c\'\n", symbol);
    printf("Код: %d (hex: 0x%x oct: %o bin 0", symbol, symbol, symbol);

    int num = symbol;
    for(int i = 6; i >= 0; i--){
        printf("%d", ((1 << i) & num)>0);
    }
    printf(")\n");

    if(isupper(symbol)){
        printf("Тип: велика літера\nІнший регістр: %c\n", tolower(symbol));

    }
    else if(islower(symbol)){
        printf("Тип: мала літера\nІнший регістр: %c\n", toupper(symbol));
    }
    printf("Наступний символ: \'%c\'\n", char(symbol+1));

    int i = 0;
    int includes = 0;
    int firstAppear = 0;
    while(text[i] != '.'){
        if(text[i] == symbol){
            includes++;
        }
        i++;
    }

    i = 0;
    while(text[i] != '.'){
        if(text[i] == symbol){
            firstAppear = i;
            break;
        }
        i++;
    }

    printf("Входжень у тексті: %d, перше на позиції: %d\n", includes, firstAppear+1);
}

void newText(char *text, char **&words, int &counts){
    string sentence;
    string word;

    freeWords(words, counts);

    counts = 0;

    while(cin >> word){
        counts++;
        if(word[word.length()-1] == '.'){
            sentence = sentence + word;
        }
        else{
            sentence = sentence + word + " ";
        }

        if(word[word.length()-1] == '.'){
            while(cin.peek() == ' ' || cin.peek() == '\t'){
                cin.get();
            }

            if(cin.peek() == '\n' || cin.peek() == EOF){
                break;
            }
            else{
                printf("Помилка\n");
                return;
            }
        }
        
    }

    bool hasLetter = false;
    int len = sentence.length();

    if(len > 255){printf("Помилка: текст занадто довгий.\n"); return;}
    if(sentence[len-1] == '\n'){sentence[len-1] = '\0'; len--;}
    if(sentence[len-1] != '.' && sentence[len-2] != '.'){
        std::cout << "Помилка! Текст має закінчуватися крапкою";
        return;
    }

    for(int i = 0; i < len-1; i++){
        if(isalpha(sentence[i])){hasLetter = true;}
        if(isalpha(sentence[i]) == 0 && isdigit(sentence[i]) == 0 && sentence[i] != ' '){
            std::cout << "Помилка! текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.";
            return;
        }
    }
    if(!hasLetter){
        std::cout << "Помилка! Текст повинен мати хоча б одне слово.";
        return;
    }

    strcpy(text, sentence.c_str());

    printf("Прочитано слів: %d\n", counts);
    printf("Новий текст: %s\n", text);
    printf("Довжина: %zu\n", strlen(text));

    words = splitWords(text, counts);
}


int main(){
    char text[256];

    printf("%s\n","Введіть текст (до 255 символів, крапка в кінці):");
    fgets(text, sizeof(text), stdin);

    int len = strlen(text);
    char *check = strchr(text, '\n');

    if(check != NULL){
        *check = '\0';
        len--;
    }
    else{
        printf("Помилка: рядок задовгий.");
        return 1;
    }

    if(text[len-1] != '.' && text[len-2] != '.'){
        std::cout << "Помилка! Текст має закінчуватися крапкою";
        return 1;
    }

    bool hasLetter = false;
    for(int i = 0; i < len-1; i++){
        if(isalpha(text[i])){hasLetter = true;}
        if(isalpha(text[i]) == 0 && isdigit(text[i]) == 0 && text[i] != ' '){
            std::cout << "Помилка! текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.";
            return 1;
        }
    }
    if(!hasLetter){
        std::cout << "Помилка! Текст повинен мати хоча б одне слово.";
        return 1;
    }

    int count = 0;
    char** words = splitWords(text, count);

    bool show = true;

    do{
        int action = 0;

        input:
        printf("%s","Оберіть дію: ");
        if(scanf("%d", &action) == 0){
            printf("%s\n", "Помилка: введіть номер пункту меню.");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            goto input;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if(action < 0 || action > 6){
            printf("%s%d%s\n","Помилка: пункту ",action," немає в меню.");
        }

        switch(action){
            case 1: statistics(text, count); break;
            case 2: table(words, count); break;
            case 3: changeWord(text, words, count); break;
            case 4: cmp2Words(); break;
            case 5: symbolInfo(text); break;
            case 6: newText(text, words, count); break;
            case 0: show = false; break;
        }
    } while(show);

    freeWords(words, count);
    return 0;
}