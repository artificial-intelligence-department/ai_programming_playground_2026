#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

//Функція для меню
int menu(){
    //мітка goto
    invalidOption:
    //ініціалізація answear
    int answear;
    //виведення меню
    std::cout << std::endl;
    std::cout << "1   Показати текст і статистику" << std::endl;
    std::cout << "2   Таблиця слів" << std::endl;
    std::cout << "3   Замінити слово" << std::endl;
    std::cout << "4   Порівняти два слова" << std::endl;
    std::cout << "5   Інформація про символ" << std::endl;
    std::cout << "6   Ввести нове речення" << std::endl;
    std::cout << "0   Вийти" << std::endl;
    //відпоівідь
    std::cin >> answear;
    //перевірка на помилку і виведення ще раз за потреби
    if(std::cin.fail()) {
       printf("некоректний пункт меню");
       return 0;
    }  
    //повернення відповіді
    return answear;
}

//Функція звільнення памʼяті
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

//Підрахунок літер, цифр та пробілів у тексті
void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;
    
    //Посимвольний обхід до \0
    const char *p = text;
    while (*p != '\0') {
        if (*p == ' ') {
            spaces++;
        } else if (isalpha(*p)) {
            letters++;
        } else if (isdigit(*p)) {
            digits++;
        }
        p++;
    }
}

//Масив з слів
char **splitWords(const char *text, int &count){

    //Робим копію
    char copy[256];
    strcpy(copy, text);

    //Забираєм крапку
    if (strlen(copy) > 0 && copy[strlen(copy) - 1] == '.') {
        copy[strlen(copy) - 1] = '\0';
    }

    //Копія для підрахунку слів
    char copyForCount[256];
    strcpy(copyForCount, copy);

    //підрахунок слів
    char *word = strtok(copyForCount, " ");
    int i = 0;
    while(word != nullptr){
        i++;
        word = strtok(nullptr, " ");
    }
    count = i;

    //виділення пам'яті слова
    char **words = new char*[count];

    //вписування слів в памяті
    word = strtok(copy, " ");
    i = 0;
    while(i < count){
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        i++;
        word = strtok(nullptr, " ");
    }

    return words;
}

//Меню 1
void menu1(const char *text, int count){
    int letters, digits, spaces;

    //Рахуєм символи
    countChars(text, letters, digits, spaces);

    //Вивід
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:    %d\n", (int)strlen(text));
    printf("Слів:        %d\n", count);
    printf("Літер:       %2d ( %2.1f%%)\n", letters, ((double)letters/strlen(text)*100));
    printf("Цифр:        %2d ( %2.1f%%)\n", digits, ((double)digits/strlen(text)*100));
    printf("Пробілів:    %2d ( %2.1f%%)\n", spaces, ((double)spaces/strlen(text)*100));
    
}




void menu2(char** words, int count){
    int min = strlen(words[0]);
    int max = strlen(words[0]);
    int maxi = 0;
    int mini = 0;
    int sum = 0;

    printf("+----+-----------------+-------+\n| N  | Слово           | Довж. |\n+----+-----------------+-------+\n");
    //Вивід таблиці слів та найкоротших довших слів
    for(int i = 0; i< count; i++){
        printf("|%3d | %-15s | %-5d |\n", i+1, words[i], (int)strlen(words[i]));
        if(strlen(words[i]) > max){
            max = strlen(words[i]);
            maxi = i;
        }
        if(strlen(words[i]) < min){
            min = strlen(words[i]);
            mini = i;
        }
        sum = sum + strlen(words[i]);
    }
    //Вивід статистики
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[maxi], max);
    printf("Найкоротше слово: %s (%d)\n", words[mini], min);
    printf("Середня довжина: %.2f\n", (double)sum/count);


    //Копія для сортування
    char *sortedWords[256];
    for(int i = 0; i < count; i++) {
        sortedWords[i] = words[i];
    }


    //Сортування бульбашкою
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(strcmp(sortedWords[j], sortedWords[j + 1]) > 0){
                char *temp = sortedWords[j];
                sortedWords[j] = sortedWords[j + 1];
                sortedWords[j + 1] = temp;
            }
        }
    }

    //Вивід посортованого
    printf("За абеткою: ");
    for(int i = 0; i < count; i++){
        printf("%s", sortedWords[i]);
        if(i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Пошук найчастішого слова
    char *mostFrequent = sortedWords[0];
    int maxFreq = 1;
    int currentFreq = 1;

    //Пошук частоти
    for(int i = 1; i < count; i++){
        if(strcmp(sortedWords[i], sortedWords[i - 1]) == 0){
            currentFreq++;
        } else {
            currentFreq = 1;
        }

        if(currentFreq > maxFreq){
            maxFreq = currentFreq;
            mostFrequent = sortedWords[i];
        }
    }

    printf("Найчастіше слово: %s (%d)\n", mostFrequent, maxFreq);
}

//заміна через string
void menu3(char *text, char **&words, int &count){
    char oldWord[256];
    char newWord[256];

    cin.ignore(10000, '\n');

    //Ввід
    printf("Замінити слово: ");
    fgets(oldWord, sizeof(oldWord), stdin);
    oldWord[strcspn(oldWord, "\n")] = '\0';

    printf("На слово: ");
    fgets(newWord, sizeof(newWord), stdin);
    newWord[strcspn(newWord, "\n")] = '\0';

    //перевірка
    for(int i = 0; i < strlen(newWord); i++){
        if(!isalnum(newWord[i])){
            printf("Неприпустимий ввід");
            return;
        }
    }

    string strText(text);
    string strOld(oldWord);
    string strNew(newWord);


    int i = 0;
    int done = 0;
    while(true){
        //знайдення позиції
        i = strText.find(strOld, i);
        if(i == string::npos){
            break;
        }
        //перевірка
        bool leftOk = (i == 0) || !isalnum(strText[i - 1]);
        bool rightOk = ((i + strOld.length()) >= strText.length()) || !isalnum(strText[i + strOld.length()]);

        //якщо проходить, то замінюєм
        if(rightOk && leftOk){
            strText.replace(i, strOld.length(), strNew);
            i = i + strNew.length();
            done++;
        } else{
            i++;
        }
    }

    //Якщо не знайшли
    if(done == 0){
        printf("Слово '%s' не знайдено", oldWord);
        return;
    }

    //Якщо не влізає
    if(strText.length() > 255){
        printf("текст занадто довгий (більше 255 символів)");
        return;
    }

    //Було і стало
    printf("Замін виконано: %d\n", done);
    printf("Було:  %s\n", text);
    

    strcpy(text, strText.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Стало:  %s\n", text);
    printf("Нова довжина: %d\n", (int)strlen(text));

}

void menu4(){
    char word1[256];
    char word2[256];

    cin.ignore(10000, '\n');

    //Ввід

    printf("Перше слово: \n");
    fgets(word1, sizeof(word1), stdin);
    word1[strcspn(word1, "\n")] = '\0';

    printf("Друге слово: \n");
    fgets(word2, sizeof(word2), stdin);
    word2[strcspn(word2, "\n")] = '\0';

    // Перевірка на ввід 
    if(strlen(word1) == 0 || strlen(word2) == 0){
        printf("Помилка: слова не можуть бути порожніми.\n");
        return;
    }

    if (strchr(word1, ' ') != nullptr || strchr(word2, ' ') != nullptr) {
        printf("Помилка: введіть одне слово без пробілів.\n");
        return;
    }

    //Порівняння через strcmp
    int cmp = strcmp(word1, word2);
    if(cmp < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    } else if(cmp > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова рівні\n");
    }

    string s1(word1);
    string s2(word2);

    //Рівні з урахуванням регістру
    if(s1 == s2) {
        printf("Рівні (==): так\n");
    } 
    else {
        printf("Рівні (==): ні\n");
    }

    string s1low = s1;
    string s2low = s2;

    for(int i = 0; i< s1.length(); i++){
        s1low[i] = tolower(s1low[i]);
    }
    for(int i = 0; i< s2.length(); i++){
        s2low[i] = tolower(s2low[i]);
    }

    //Рівні без урахування регістру
    if(s1low == s2low) {
        printf("Рівні без урахування регістру: так\n");
    } 
    else {
        printf("Рівні без урахування регістру: ні\n");
    }

    // Довжини обох слів
    printf("Довжини: %d і %d\n", (int)s1.length(), (int)s2.length());

    // Конкатенація через " & " та її довжина
    string both = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%d)\n", both.c_str(), (int)both.length());
}

void menu5(char* text){
    char symbol[3];
    cin.ignore(10000, '\n');

    //Ввід
    printf("Введіть символ: ");
    fgets(symbol, sizeof(symbol), stdin);

    symbol[1] = '\0';

    int symcode = symbol[0];

    //вивід інфо
    printf("Символ: '%s'\n", symbol);
    printf("Код: %d (hex 0x%X, oct 0%o, bin ", symcode, symcode, symcode);
    for(int i = 7; i >= 0; i--){
        printf("%d", (symcode >> i) & 1);
    }
    printf(")\n");

    printf("Тип: ");
    if (isupper(symbol[0])) {
        printf("велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(symbol[0]));
    } else if (islower(symbol[0])) {
        printf("мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(symbol[0]));
    } else if (isdigit(symbol[0])) {
        printf("цифра\n");
    } else if (isspace(symbol[0])) {
        printf("пробіл\n");
    } else {
        printf("інший символ\n");
    }

    printf("Наступний символ: '%c'\n", symbol[0]+1);

    int count = 0;
    int first = -1;
    for (int i = 0; i < strlen(text); i++){
        if(tolower(text[i]) == tolower(symbol[0])){
            count++;
            if(first == -1){
                first = i;
            }
        }
    }
    if (count == 0) {
        printf("У тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, first + 1);
    }


}




void menu6(char *text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");
    string word;
    string sentence;
    int cinCount = 0;

    //ввід
    while(cin >> word){
        cinCount++;
        //додаєм пробіл
        if(!sentence.empty()){
            sentence += " ";
        }
        sentence = sentence + word;

        //Виходимо, якшо дойшли до крапки
        if(!word.empty() && word[word.length() - 1] == '.'){
            break;
        }

        //Перевірка по довжні
        if(sentence.length() > 255){
            printf("Помилка: текст занадто довгий (понад 255 символів).\n");
            std::cin.ignore(10000, '\n');
            return;
        }
    }

    //Перевірки
    if(cinCount == 0 || sentence.empty()){
        printf("Помилка: некоректне речення.\n");
        return;
    }


    if(sentence[0] == ' ' || (!isalpha(sentence[0]) && !isdigit(sentence[0]))){
        printf("Помилка: речення має починатися з літери або цифри та закінчуватися крапкою.\n");
        return;
    }

    if(sentence[sentence.length() - 1] != '.'){
        printf("Помилка: речення має закінчуватися крапкою.\n");
        return;
    }

    for(int i = 0; i < sentence.length() - 1; i++){
        if(!isalpha(sentence[i]) && !isdigit(sentence[i]) && sentence[i] != ' '){
            printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
            return;
        }
    }

    //Запис у words
    strcpy(text, sentence.c_str());

    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", (int)strlen(text));
}




int main(){
    char text[256];
    int answear;
    bool exit = 0;

    //ввід тексту
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    fgets(text, sizeof(text), stdin);

    //забираємо н
    text[strcspn(text, "\n")] = '\0';

    //Перевірка тексту
    if(strlen(text) == 0){
        printf("Некоректний ввід (текст має містити слова)");
        return 0;
    } else if(text[0] == ' '|| (!isalpha(text[0]) && !isdigit(text[0]))){
        printf("Некоректний ввід (текст має починатись з слова)");
        return 0;
    } else if(text[strlen(text) - 1] != '.'){
        printf("Некоректний ввід (немає крапки в кінці)");
        return 0;
    }
    for(int i = 0; i < strlen(text)-1; i++){
        if (!(isalpha(text[i]) || isdigit(text[i]) || text[i] == ' ')) {
            printf("Некоректний ввід (не може бути символів)");
            return 0;
        }
    }

    //Підрахунок слів
    int count = 0;
    char **words = splitWords(text, count);

    //Цикл для меню
    do {
        answear = menu();
        switch (answear)
        {
        case 0:
            exit = 1;
            freeWords(words, count);
            break;
        case 1:
            menu1(text, count);
            break;
        case 2:
            menu2(words, count);
            break;
        case 3:
            menu3(text, words, count);
            break;
        case 4:
            menu4();
            break;
        case 5:
            menu5(text);
            break;
        case 6:
            menu6(text, words, count);
            break;
        default:
            exit = 1;
            printf("некоректний пункт меню");
            break;
        }
    } while (!exit);
    
    freeWords(words, count);
}