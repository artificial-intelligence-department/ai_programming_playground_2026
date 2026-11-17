/*
    Задача: Редактор текстового повідомлення
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

bool finishLine();
bool validText(const char *text);
bool readWord(const char *message, char *word);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showStatistics(const char *text, int count);
void showWords(char **words, int count);
void replaceWord(char *text, char **&words, int &count);
void compareWords();
void showCharacter(const char *text);
void readSentence(char *text, char **&words, int &count);

int main (){

    char text [256];

    printf ("Введіть текст (до 255 символів, крапка в кінці): ");
    if (fgets(text, sizeof(text), stdin) == nullptr){
        printf ("Помилка: не вдалося зчитати текст.\n");
        return 1;
    }

    int length = strlen(text);
    if (length > 0 && text[length - 1] == '\n'){
        text[length - 1] = '\0';
    }
    else if (length == 255){
        // Відрізняємо рівно 255 символів від надто довгого рядка.
        int c = getchar();
        if (c != '\n' && c != EOF){
            while ((c = getchar()) != '\n' && c != EOF){}
            printf ("Помилка: текст перевищує 255 символів.\n");
            return 1;
        }
    }

    length = strlen(text);
    if (length == 0 || text[length - 1] != '.'){
        printf ("Помилка: некоректний ввід\n");
        return 1;
    }

    bool hasWord = false;
    for (int i = 0; i < length - 1; i++){
        if (!((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9') || text[i] == ' ')){
            printf("Помилка: недопустимий символ\n");
            return 1;
        }
        if (text[i] != ' '){
            hasWord = true;
        }
    }
    if (!hasWord){
        printf ("Помилка: некоректний ввід\n");
        return 1;
    }

    int count = 0;
    char **words = splitWords(text, count);
    int choice = -1;

    do {
        printf("\n1 — Текст і статистика\n");
        printf("2 — Таблиця слів\n");
        printf("3 — Замінити слово\n");
        printf("4 — Порівняти два слова\n");
        printf("5 — Інформація про символ\n");
        printf("6 — Ввести нове речення\n");
        printf("0 — Вихід\n");
        printf("Ваш вибір: ");

        // Ширина 1 не дозволяє переповнити int надто довгим числом.
        int result = scanf("%1d", &choice);
        if (result == EOF){
            break;
        }

        bool correctLine = finishLine();
        if (result != 1 || !correctLine){
            printf("Помилка: пункту %d немає в меню.\n", choice);
            choice = -1;
            continue;
        }

        switch (choice){
            case 1:
                showStatistics(text, count);
                break;
            case 2:
                showWords(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharacter(text);
                break;
            case 6:
                readSentence(text, words, count);
                break;
            case 0:
                printf("Завершення роботи.\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    } while (choice != 0);

    freeWords(words, count);
    return 0;
}

//Функція, щою перевірити чи в кінці рядка лишилися букви для валідації вводу пункту меню
bool finishLine(){
    int c;
    bool correct = true;

    while ((c = getchar()) != '\n' && c != EOF){
        if (c != ' ' && c != '\t' && c != '\r'){
            correct = false;
        }
    }
    return correct;
}

//Функція для первіпки введеного тексту
bool validText(const char *text){
    int length = strlen(text);
    if (length == 0 || length > 255 || text[length - 1] != '.'){
        return false;
    }

    bool hasWord = false;
    for (int i = 0; i < length - 1; i++){
        bool letter = (text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z');
        bool digit = text[i] >= '0' && text[i] <= '9';

        if (!letter && !digit && text[i] != ' '){
            return false;
        }
        if (letter || digit){
            hasWord = true;
        }
    }
    return hasWord;
}

// Функція для перевірки правильності введеного слова, максимум 31 символ.
bool readWord(const char *message, char *word){
    printf("%s", message);
    int result = scanf("%31s", word);
    if (result == EOF){
        return false;
    }

    bool correctLine = finishLine();
    if (result != 1 || !correctLine){
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return false;
    }

    for (int i = 0; word[i] != '\0'; i++){
        bool letter = (word[i] >= 'A' && word[i] <= 'Z') ||
                      (word[i] >= 'a' && word[i] <= 'z');
        bool digit = word[i] >= '0' && word[i] <= '9';

        if (!letter && !digit){
            printf("Помилка: слово має містити лише латинські літери й цифри.\n");
            return false;
        }
    }
    return true;
}

//Функція для розділення речення на слова
char **splitWords(const char *text, int &count){
    char copy[256];
    strcpy(copy, text);

    count = 0;
    char *word = strtok(copy, " .");
    while (word != nullptr){
        count++;
        word = strtok(nullptr, " .");
    }

    char **words = new char*[count];
    strcpy(copy, text);
    word = strtok(copy, " .");
    int i = 0;

    while (word != nullptr){
        words[i] = new char[strlen(word) + 1];
        strcpy(words[i], word);
        i++;
        word = strtok(nullptr, " .");
    }
    return words;
}

//Функція для звільнення памʼяті
void freeWords(char **&words, int &count){
    for (int i = 0; i < count; i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

//Функція для підрахунку цифр, букв і пробілів
void countChars(const char *text, int &letters, int &digits, int &spaces){
    letters = 0;
    digits = 0;
    spaces = 0;

    for (const char *p = text; *p != '\0'; p++){
        unsigned char c = static_cast<unsigned char>(*p);
        if (isalpha(c)){
            letters++;
        }
        else if (isdigit(c)){
            digits++;
        }
        else if (c == ' '){
            spaces++;
        }
    }
}

//Функція для показу статистики
void showStatistics(const char *text, int count){
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int length = strlen(text);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %6d\n", length);
    printf("Слів:     %6d\n", count);
    printf("Літер:    %6d (%5.1f%%)\n", letters, letters * 100.0 / length);
    printf("Цифр:     %6d (%5.1f%%)\n", digits, digits * 100.0 / length);
    printf("Пробілів: %6d (%5.1f%%)\n", spaces, spaces * 100.0 / length);
}

//Функція для таблиці слів
void showWords(char **words, int count){
    int longest = 0;
    int shortest = 0;
    int total = 0;
    int width = 15;

    //Пошук найдовшого, найкоротшого слова
    for (int i = 0; i < count; i++){
        int length = strlen(words[i]);
        total += length;
        if (length > static_cast<int>(strlen(words[longest]))){
            longest = i;
        }
        if (length < static_cast<int>(strlen(words[shortest]))){
            shortest = i;
        }
        if (length > width){
            width = length;
        }
    }

    //Виведення таблиці
    string border = "+-----+" + string(width + 2, '-') + "+-------+\n";

    printf("%s", border.c_str());
    printf("| %3s | %-*s | %5s |\n", "N", width, "Word", "Len");
    printf("%s", border.c_str());
    for (int i = 0; i < count; i++){
        printf("| %3d | %-*s | %5d |\n", i + 1, width, words[i],
               static_cast<int>(strlen(words[i])));
    }
    printf("%s", border.c_str());

    printf("Найдовше слово: %s (%d)\n", words[longest],
           static_cast<int>(strlen(words[longest])));
    printf("Найкоротше слово: %s (%d)\n", words[shortest],
           static_cast<int>(strlen(words[shortest])));
    printf("Середня довжина: %.2f\n", static_cast<double>(total) / count);

    char **sorted = new char*[count];
    for (int i = 0; i < count; i++){
        sorted[i] = words[i];
    }

    //Сортування слів за абеткою
    for (int i = 0; i < count - 1; i++){
        for (int j = 0; j < count - 1 - i; j++){
            if (strcmp(sorted[j], sorted[j + 1]) > 0){
                char *temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("За абеткою:");
    for (int i = 0; i < count; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");

    //Знаходження слова яке трапляється найчастіше
    int best = 0;
    int bestCount = 0;
    int i = 0;
    while (i < count){
        int j = i + 1;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0){
            j++;
        }
        if (j - i > bestCount){
            bestCount = j - i;
            best = i;
        }
        i = j;
    }

    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);
    delete[] sorted;
}

//Функція для заміни слів
void replaceWord(char *text, char **&words, int &count){
    char from[32], to[32];
    if (!readWord("Замінити слово: ", from)){
        return;
    }
    if (!readWord("На слово: ", to)){
        return;
    }

    string before = text;
    string after = before;
    string oldWord = from;
    string newWord = to;
    string::size_type pos = 0;
    int replacements = 0;

    while ((pos = after.find(oldWord, pos)) != string::npos){
        string::size_type end = pos + oldWord.length();
        bool left = pos == 0 || after[pos - 1] == ' ';
        bool right = end == after.length() || after[end] == ' ' || after[end] == '.';

        if (left && right){
            after.replace(pos, oldWord.length(), newWord);
            replacements++;
            pos += newWord.length();
        }
        else {
            pos += oldWord.length();
        }

        if (after.length() > 255){
            printf("Помилка: після заміни текст перевищує 255 символів.\n");
            printf("Поточний текст не змінено.\n");
            return;
        }
    }

    strcpy(text, after.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %d\n", static_cast<int>(after.length()));
}

//Функція порівняння слів
void compareWords(){

    char a[32], b[32];
    if (!readWord("Перше слово: ", a)){
        return;
    }
    if (!readWord("Друге слово: ", b)){
        return;
    }

    int result = strcmp(a, b);
    if (result < 0){
        printf("strcmp: -1. Перше слово менше\n");
    }
    else if (result > 0){
        printf("strcmp: 1. Перше слово більше\n");
    }
    else {
        printf("strcmp: 0. Слова однакові\n");
    }

    string first = a;
    string second = b;
    printf("Рівні (==): %s\n", first == second ? "так" : "ні");

    string lowerFirst = first;
    string lowerSecond = second;
    for (string::size_type i = 0; i < lowerFirst.length(); i++){
        lowerFirst[i] = static_cast<char>(tolower(static_cast<unsigned char>(lowerFirst[i])));
    }
    for (string::size_type i = 0; i < lowerSecond.length(); i++){
        lowerSecond[i] = static_cast<char>(tolower(static_cast<unsigned char>(lowerSecond[i])));
    }

    printf("Рівні без урахування регістру: %s\n", lowerFirst == lowerSecond ? "так" : "ні");
    printf("Довжини: %d і %d\n", static_cast<int>(first.length()), static_cast<int>(second.length()));

    string joined = first + " & " + second;
    printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), static_cast<int>(joined.length()));
}

//Функція показу інформації про символ
void showCharacter(const char *text){
    char c;
    printf("Введіть символ (можна пробіл): ");
    if (scanf("%c", &c) != 1){
        return;
    }
    if (c == '\n'){
        printf("Помилка: символ не введено.\n");
        return;
    }

    bool correctLine = finishLine();
    unsigned char symbol = static_cast<unsigned char>(c);
    if (!correctLine || symbol > 127){
        printf("Помилка: введіть один ASCII-символ.\n");
        return;
    }

    unsigned int code = symbol;
    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex %#x, oct %#o, bin ", code, code, code);
    for (int bit = 7; bit >= 0; bit--){
        printf("%u", (code >> bit) & 1u);
    }
    printf(")\n");

    if (isupper(symbol)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(symbol));
    }
    else if (islower(symbol)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(symbol));
    }
    else if (isdigit(symbol)){
        printf("Тип: цифра\n");
    }
    else if (isspace(symbol)){
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: інший символ\n");
    }

    // Для непечатного наступного символу показуємо його код.
    int next = code + 1;
    if (next <= 127 && isprint(next)){
        printf("Наступний символ: '%c'\n", next);
    }
    else {
        printf("Наступний символ: непечатний, код %d\n", next);
    }

    int occurrences = 0;
    for (int i = 0; text[i] != '\0'; i++){
        if (text[i] == c){
            occurrences++;
        }
    }

    const char *first = strchr(text, c);
    if (first == nullptr){
        printf("Символ у тексті не зустрічається.\n");
    }
    else {
        printf("Входжень у тексті: %d, перше на позиції %d\n",
               occurrences, static_cast<int>(first - text) + 1);
    }
}

//Функція заміни речення
void readSentence(char *text, char **&words, int &count){
    printf("Введіть речення (крапка після останнього слова):\n");

    string sentence;
    string word;
    int readCount = 0;
    bool tooLong = false;
    bool finished = false;

    while (cin >> word){

        // Якщо речення надто довге, дочитуємо його до крапки.
        if (!tooLong){
            int separator = sentence.empty() ? 0 : 1;
            if (word.length() > 255 || sentence.length() + separator + word.length() > 255){
                tooLong = true;
            }
            else {
                if (!sentence.empty()){
                    sentence += ' ';
                }
                sentence += word;
            
                if (word != "."){
                    readCount++;
                }
            }
        }

        if (word[word.length() - 1] == '.'){
            finished = true;
            break;
        }
    }

    if (!finished){
        printf("Помилка: введення завершилося до крапки. Текст не змінено.\n");
        return;
    }

    bool correctLine = finishLine();
    if (tooLong || !correctLine || !validText(sentence.c_str())){
        printf("Помилка: некоректне речення або перевищено 255 символів.\n");
        printf("Поточний текст не змінено.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);

    printf("Прочитано слів: %d\n", readCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", static_cast<int>(sentence.length()));
}
