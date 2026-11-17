#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int TEXT_SIZE = 256;
const int WORD_SIZE = 32;

void showMenu()
{
    printf("\n====Меню====\n");
    printf("1. Показати текст і статистику\n");
    printf("2. Таблиця слів\n");
    printf("3. Замінити слово\n");
    printf("4. Порівняти два слова\n");
    printf("5. Інформація про символ\n");
    printf("6. Ввести нове речення\n");
    printf("0. Вийти\n");
    printf("Виберіть пункт: ");
}

char** splitWords(const char* text, int& count){

    count = 0;
    char copy[TEXT_SIZE];

    strcpy(copy, text);
    char *token = strtok(copy, " ");

    while (token != nullptr)
    {
        count++;
        token = strtok(nullptr, " ");
    }

    if (count == 0)  { return nullptr;  }
    char **words = new char *[count];

    strcpy(copy, text);
    int len = strlen(copy);
    if (len > 0 && copy[len-1]=='.') {
        copy[len - 1] = '\0';
    }

    token = strtok(copy, " ");
    int index = 0;
    while (token != nullptr)
    {
        int wordLen = strlen(token);
        words[index] = new char[wordLen + 1];
        strcpy(words[index], token);

        index++;
        token = strtok(nullptr, " ");
    }
    return words;
}

void freeWords(char** &words, int &count){
    for (int i = 0; i < count; i++) {
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
}

bool isValidText(const char *text)
{
    int len = strlen(text);
    if (len < 2 || text[len - 1] != '.')
        return false;

    bool hasWord = false;
    for (int i = 0; i < len - 1; i++)
    {
        char elem = text[i];
        if (isalpha(elem) || isdigit(elem))
            hasWord = true;
        else if (text[i] != ' ')
            return false;
    }
    return hasWord;
}
bool isValidWord(const char *word){
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        char elem = word[i];
        if (!isalpha(elem) && !isdigit(elem)) {
            return false;
        }
    }
    return true;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;

    const char *symb = text;
    while (*symb != '\0')
    {
        if (isalpha(*symb)) {
            letters++;
        }
        else if (isdigit(*symb)) {
            digits++;
        }
        else if (*symb == ' ') {
            spaces++;
        }
        symb++;
    }
}
void showStats(const char* text, int wordCount){

    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    int len = strlen(text);

    printf("\nТекст:\t\t\"%s\"\n",text);
    printf("Символів:\t%3d\n", len);
    printf("Слів:\t\t%3d\n", wordCount);
    printf("Літер:\t\t%3d ( %4.1f%%)\n", letters, letters * 100.0 / len);
    printf("Цифр:\t\t%3d ( %4.1f%%)\n", digits, digits * 100.0 / len);
    printf("Пробілів:\t%3d ( %4.1f%%)\n", spaces, spaces * 100.0 / len);
}

void showWordsTable(char **&words, int wordCount){

    int longest, shortest, totaLen;
    longest = shortest = totaLen = 0;
    printf("\n+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    for (int i = 0; i < wordCount; i++)
    {
        int len = strlen(words[i]);
        totaLen += len;
        
        if (len > strlen(words[longest])) {
            longest = i;
        }
        if (len < strlen(words[shortest])) {
            shortest = i;
        }

        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%d)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%d)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", (double)totaLen / wordCount);

    char **sorted = new char *[wordCount];
    for (int i = 0; i < wordCount; i++) {
        sorted[i] = words[i];
    }

    for (int i = 0; i < wordCount-1; i++)
    {
        int minIndex = i;
        for (int j = i+1; j < wordCount; j++)
        {
            if (strcmp(sorted[j],sorted[minIndex]) < 0){
                minIndex = j;
            }
        }
        char *tmp = sorted[i];
        sorted[i] = sorted[minIndex];
        sorted[minIndex] = tmp;
    }

    printf("За абеткою: ");
    for (int i = 0; i < wordCount; i++) {
        printf("%s%s", sorted[i], (i == wordCount - 1 ? "\n" : " "));
    }

    int maxFrequency = 0;
    int mostFrequent = 0;

    for (int i = 0; i < wordCount; i++)
    {
        int counter = 0;
        for (int j = 0; j < wordCount; j++)
        {
            if (strcmp(sorted[i], sorted[j]) == 0) {
                counter++;
            }
        }
        if (counter > maxFrequency) {
            maxFrequency = counter;
            mostFrequent = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[mostFrequent], maxFrequency);
    delete[] sorted;
}

void replaceWord(char* text, char**&words, int& wordsCount){

    char from[WORD_SIZE];
    char to[WORD_SIZE];

    printf("Введіть слово для заміни: ");
    if (scanf("%31s", from) != 1) {
        return;
    }
    printf("Введіть нове слово: ");
    if (scanf("%31s", to) != 1) {
        return;
    }

    if (!isValidWord(from) || !isValidWord(to))
    {
        printf("Обидва зчення мають містити лише латинські літери та цифри!\n");
        return;
    }

    int replacesCount = 0;
    string strText = text;
    string replacedText = strText;

    int findPos = 0;
    while ((findPos = replacedText.find(from, findPos)) != string::npos)
    {
        bool leftThreshold = findPos == 0 || !isalnum(replacedText[findPos - 1]);
        int rigthPos = findPos + strlen(from);
        bool rightThreshold = rigthPos == replacedText.length() || !isalnum(replacedText[rigthPos]);

        if (leftThreshold && rightThreshold)
        {
            replacedText.replace(findPos, strlen(from), to);
            replacesCount++;
            findPos += strlen(to);
        }
        else {
            findPos += strlen(from);
        }
    }

    if (replacedText.length() > TEXT_SIZE - 1){
        printf("Після заміни текст перевищить 255 символів! Текст не змінено\n");
        return;
    }

    printf("Замін виконано: %d\n", replacesCount);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", replacedText.c_str());
    printf("Нова довжина: %d\n", replacedText.length());

    freeWords(words, wordsCount);
    strcpy(text, replacedText.c_str());
    words = splitWords(text, wordsCount);
}

void compareTwoWords(){

    char a[WORD_SIZE];
    char b[WORD_SIZE];

    printf("Перше слово: ");
    if (scanf("%31s", a) != 1) {
        return;
    }
    printf("Друге слово: ");
    if (scanf("%31s", b) != 1) {
        return;
    }

    if (!isValidWord(a) || !isValidWord(b))
    {
        printf("Обидва зчення мають містити лише латинські літери та цифри!\n");
        return;
    }

    int res = strcmp(a, b);
    int userResp;
    string stringResp;

    if (res > 0) {
        userResp = 1;
        stringResp = "перше слово більше\n";
    }
    else if (res < 0) {
        userResp = -1;
        stringResp = "перше слово менше\n";
    }
    else {
        userResp = 0;
        stringResp = "слова одинакові\n";
    }
    printf("strcmp: %d -> %s", userResp, stringResp.c_str());

    string first = a;
    string second = b;
    printf("Рівні (==): %s\n", (first == second ? "так" : "ні"));

    string first_lower = first;
    string second_lower = second;

    for (int i = 0; i < first.length(); i++) {
        first_lower[i] = tolower(first[i]);
    }
    for (int i = 0; i < second.length(); i++) {
        second_lower[i] = tolower(second[i]);
    }

    printf("Рівні без урахування регістру: %s\n", (first_lower == second_lower ? "так" : "ні"));
    printf("Довжини: %d і %d\n", first.length(), second.length());

    string concat = first + " & " + second;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), concat.length());
}

void symbolInfo(const char *text){

    char symb;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    printf("Введіть символ: ");
    if (scanf("%c", &symb) != 1)  {
        return;
    }

    printf("Символ: \'%c\'\n", symb);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", symb, symb, symb);

    for (int i = 7; i >= 0; i--)
    {
        printf("%d",(symb >> i) & 1);
    }
    if (islower(symb)){
        printf("\nТип: мала літера\n");
        printf("Інший регістр: \'%c\'\n", toupper(symb));
    }
    else if(isupper(symb)) {
        printf("\nТип: велика літера\n");
        printf("Інший регістр: \'%c\'\n", tolower(symb));
    }
    else if(isdigit(symb)) {
        printf("\nцифра\n");
    }
    else if(isspace(symb)) {
        printf("\nпробіл\n");
    }
    printf("Наступний символ: \'%c\'\n", symb + 1);

    int occurances = 0;
    int first_occur = -1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i]==symb) {
            if (first_occur == -1){
                first_occur = i;
            }
            occurances++;
        }
    }
    if (occurances == 0){
        printf("Символ \'%c\' не з'являвся у тексті\n", symb);
    } else{
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurances, first_occur + 1);
    }
}

void enterNewSentence(char* text, char**& words, int& wordCount){

    string newSentence;
    string word;
    int newWordCount = 0;
    printf("Введіть речення (крапка після останнього слова): ");
    while (cin >> word)
    {
        newSentence += word + " ";
        newWordCount++;
        if (word[word.length() - 1] == '.') {
            break;
        }
    }
    if (newSentence[newSentence.length()-1]==' ') {
        newSentence.erase(newSentence.length() - 1, 1);
    }
    if (newSentence.length() > 255) {
        printf("Текст перевищує 255 символів!\n");
        return;
    }

    if (!isValidText(newSentence.c_str())){
        printf("Текст коректний, якщо містить хоча б одне слово, складається лише з латинських літер, цифр і пробілів та завершується крапкою!\n");
        return;
    }

    strcpy(text, newSentence.c_str());

    freeWords(words, wordCount);
    words = splitWords(text, newWordCount);
    wordCount = newWordCount;

    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", strlen(text));

}


int main(){

    char text[TEXT_SIZE];
    char **words = nullptr;
    int wordCount = 0;
    printf("Введіть текст (до 255 символів, крапка в кінці): ");

    if (fgets(text, TEXT_SIZE, stdin) == nullptr) {
        printf("Помилка читання тексту.\n");
        return 1;
    }

    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
        text[len - 1] = '\0';

    bool tooLong = false;
    if (len == TEXT_SIZE) {
        tooLong = true;
    }

    if (tooLong) {
        printf("Текст перевищує межі!");
        return 1;
    }

    if (!isValidText(text))
    {
        printf("Текст коректний, якщо містить хоча б одне слово, складається лише з латинських літер, цифр і пробілів та завершується крапкою!\n");
        return 1;
    }

    words = splitWords(text, wordCount);
    if (words == nullptr) {
        printf("Помилка: текст не містить слів.\n");
        return 1;
    }

    int choice = -1;
    do
    {
        showMenu();
        if (scanf(" %d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            showStats(text, wordCount);
            break;
        case 2:
            showWordsTable(words, wordCount);
            break;
        case 3:
            replaceWord(text, words, wordCount);
            break;
        case 4:
            compareTwoWords();
            break;
        case 5:
            symbolInfo(text);
            break;
        case 6:
            enterNewSentence(text, words, wordCount);
            break;
        case 0:
            printf("Exiting...");
            break;
        default:
            printf("Неправильний пункт меню!\n");
        }
    } while (choice != 0);

        freeWords(words, wordCount);
    return 0;
}
