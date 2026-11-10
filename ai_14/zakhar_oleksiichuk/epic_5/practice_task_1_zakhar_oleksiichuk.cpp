#include <iostream> 
#include <cstring> 
#include <string> 
#include <cstdio> 
#include <ctype.h> 
#include <iomanip>

using namespace std;

bool validateText(const char *text)
{
    int len = strlen(text);
    if (len == 0)
        return false;

    if (text[len - 1] != '.')
        return false;

    bool hasWord = false;

    for (int i = 0; i < len - 1; i++)
    {
        char ch = text[i];
        if (!(isalpha(ch) || isdigit(ch) || isspace(ch)))
            return false;
        if (isalnum(ch))
            hasWord = true;
    }

    return hasWord;
}

void freeWords(char **&words, int &count) {
    if (words != nullptr) {
        for (int i = 0; i < count; i++) {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
}

char **splitWords(const char *text, int &count)
{
    count = 0;

    char *temp = new char[strlen(text) + 1];
    strcpy(temp, text);

    char *tempCount = new char[strlen(text) + 1];
    strcpy(tempCount, text);
    char *token = strtok(tempCount, " .");
    int numCount = 0;
    while (token != nullptr)
    {
        numCount++;
        token = strtok(nullptr, " .");
    }
    delete[] tempCount;
    count = numCount;

    if (numCount == 0)
    {
        delete[] temp;
        return nullptr;
    }

    char **words = new char *[numCount];
    token = strtok(temp, " .");
    int ind = 0;
    while (token != nullptr)
    {
        words[ind] = new char[strlen(token) + 1];
        strcpy(words[ind], token);
        ind++;
        token = strtok(nullptr, " .");
    }
    delete[] temp;
    return words;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    const char *ptr = text;

    while (*ptr != '\0')
    {
        if (isalpha(*ptr))
            letters++;
        else if (isdigit(*ptr))
            digits++;
        else if (isspace(*ptr))
            spaces++;
        ptr++;
    }
}

void ShowStatistics(const char *text, int wordsCount)
{
    char *temp = new char[strlen(text) + 1];
    strcpy(temp, text);
    printf("Текст:\t\t\"%s\"\n", temp);

    int charCount = strlen(temp);
    printf("Символів:\t%d\n", charCount);
    printf("Слів:\t\t%d\n", wordsCount);

    int lettersCount, digitsCount, spacesCount;
    countChars(text, lettersCount, digitsCount, spacesCount);

    float lettersPercentage = (float)lettersCount / charCount * 100;
    float digitsPercentage = (float)digitsCount / charCount * 100;
    float spacesPercentage = (float)spacesCount / charCount * 100;
    printf("Літер:\t\t%d (%.1f%%)\n", lettersCount, lettersPercentage);
    printf("Цифр:\t\t%d (%.1f%%)\n", digitsCount, digitsPercentage);
    printf("Пробілів:\t%d (%.1f%%)\n", spacesCount, spacesPercentage);

    delete[] temp;
}

void ShowTable(char **words, int count)
{
    cout << "+----+-----------------+-------+" << endl;
    cout << "| N  | Слово           | Довж. |" << endl;
    cout << "+----+-----------------+-------+" << endl;
    int maxLen = strlen(words[0]);
    int minLen = strlen(words[0]);
    string biggest = words[0];
    string smallest = words[0];
    int totalLen = 0;
    for (int i = 0; i < count; i++)
    {
        int len = strlen(words[i]);
        totalLen += len;
        if (len > maxLen)
        {
            maxLen = len;
            biggest = words[i];
        }
        else if (len < minLen)
        {
            minLen = len;
            smallest = words[i];
        }
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
    }
    cout << "+----+-----------------+-------+" << endl;
    cout << "Найдовше слово: " << biggest << " (" << maxLen << ')' << endl;
    cout << "Найкоротше слово: " << smallest << " (" << minLen << ')' << endl;
    cout << "Середня довжина: " << fixed << setprecision(2) << (float)totalLen / count << endl;

    char **copy = new char *[count];
    for (int i = 0; i < count; i++)
    {
        int wordLen = strlen(words[i]);
        copy[i] = new char[wordLen + 1];
        strcpy(copy[i], words[i]);
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(copy[j], copy[j + 1]) > 0)
            {
                char *temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    cout << "За абеткою: ";
    for (int i = 0; i < count; i++)
    {
        cout << copy[i] << " ";
    }
    cout << endl;

    int maxRepeats = 1;
    int currentRepeats = 1;
    string mostRepWord = copy[0];
    for (int i = 0; i < count-1; i++) {
        if (strcmp(copy[i], copy[i+1]) == 0) {
            currentRepeats++;
            if (currentRepeats > maxRepeats) {
                maxRepeats = currentRepeats;
                mostRepWord = copy[i];
            } 
        }
        else {
            currentRepeats = 1;
        }
    }
    cout << "Найчастіше слово: " << mostRepWord << " (" << maxRepeats << ')' << endl;
}

bool CheckWordBoundary(const string Text, int pos, int wordLen) {
    if (pos > 0 && isalnum(Text[pos-1])) {
        return false;
    }
    if (pos+wordLen < Text.length() && isalnum(Text[pos+wordLen])) {
        return false;
    }
    return true;
}

void ReplaceWords(char *text, char **&words, int &count) {
    char from[32]{};
    char to[32]{};
    printf("Замінити слово: ");
    scanf("%31s", from);
    printf("На слово: ");
    scanf("%31s", to);

    for (int i = 0; i < strlen(to); i++) {
        if (!isalnum(to[i])) {
            cout << "Невірний ввід";
            return;
        }
    }

    string sText(text);
    int pos = sText.find(from, 0);
    int fromLen = strlen(from);
    int replacementCount = 0;
    while (pos != string::npos) {
        if (CheckWordBoundary(sText, pos, fromLen)) {
            sText.replace(pos, fromLen, to);
            replacementCount++;
            pos += strlen(to);
        } else {
            pos += fromLen;
        }
        pos = sText.find(from, pos);
    }
    if (sText.length() > 255) {
        cout << "Перевищення розміру";
        return;
    }
    printf("Замін виконано: %d", replacementCount);
    cout << "\nБуло: \"" << text << '"' << endl;
    cout << "Стало: \"" << sText << '"' << endl;
    cout << "Нова довжина: " << sText.length();   
    strcpy(text, sText.c_str());

    freeWords(words, count);

    words = splitWords(text, count);
}

void ToLowerCase(string &text) {
    for (char &c : text) {
        if (c >= 'A' && c <= 'Z') c = c + 32;
    }
};

void CompareWords() {
    char a[32];
    char b[32];
    printf("Перше слово: ");
    scanf("%31s", a);
    printf("Друге слово: ");
    scanf("%31s", b);
    int compareRes = strcmp(a, b);
    if (compareRes < 0) {
        printf("strcmp: -1 -> перше слово менше\n");
    }
    else if (compareRes > 0) {
        printf("strcmp: 1 -> перше слово більше\n");
    }
    else {
        printf("strcmp: 0 -> слова однакові\n");
    }
    

    string sA(a);
    string sB(b);
    bool equivalent = (sA == sB); 
    printf("Рівні (==): %s\n", (equivalent ? "так" : "ні"));

    string sA_lower = sA;
    string sB_lower = sB;
    ToLowerCase(sA_lower);
    ToLowerCase(sB_lower);

    equivalent = (sA_lower == sB_lower); 
    printf("Рівні без урахування регістру: %s\n", (equivalent ? "так" : "ні"));
    printf("Довжини: %zu і %zu\n", sA.length(), sB.length());
    string Concatenated = "\"" + sA + " & " + sB + "\" (" + to_string(sA.length()+sB.length()+3) + ')';
    cout << "Конкатенація: " << Concatenated << endl;
}

void ToBinaryChar(unsigned char c, char binStr[9]) {
    for (int i = 7; i >= 0; i--) {
        binStr[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    binStr[8] = '\0'; 
}

void SymbolInfo(const char *text) {
    char c;
    printf("Введіть символ: ");
    scanf(" %c", &c);
    printf("Символ: '%c'\n", c);

    char binChar[9];
    ToBinaryChar(c, binChar);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", c, c, c, binChar);
    if (isalpha(c)) {
        if (c >= 'a' && c <= 'z') {
            printf("Тип: мала літера\n");
            printf("Інший регістр: '%c'\n", c-32);
            printf("Наступний символ: '%c'\n", c+1);
        }
        else {
            printf("Тип: велика літера\n");
            printf("Інший регістр: '%c'\n", c+32);
            printf("Наступний символ: '%c'\n", c+1);
        }
    }
    else if (isdigit(c)) {
        printf("Тип: цифра\n");
    }
    else if (isspace(c)) {
        printf("Тип: пробільний символ\n");
    }
    else {
        printf("Тип: символ\n");
    }

    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == c) count++;
    }

    char *firstPos = strchr((char*)text, c); 
    if (firstPos != nullptr) {
        int ind = (firstPos - text) + 1; 
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, ind);
    } else {
        printf("У тексті не зустрічається\n");
    }
}

void ChangeSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string word;
    string sentence = "";
    int wordsCount = 0;
    while (cin >> word) {
        if (!sentence.empty()) {
            sentence += " ";
        }
        sentence += word;
        wordsCount++;
        
        if (!word.empty() && word[word.length()-1] == '.') {
            break;
        }
    }

    if (sentence.length() > 255) {
            cout << "Ліміт перевищено.";
            return;
    }

    if (!validateText(sentence.c_str())) {
        cout << "Помилка: речення некоректне. Текст не змінено." << endl;
        return;
    }

    cout << "Прочитано слів: " << wordsCount << endl;
    cout << "Новий текст: \"" << sentence << '"' << endl;
    cout << "Довжина: " << sentence.length() << endl;

    strcpy(text, sentence.c_str());

    freeWords(words, count);
    words = splitWords(text, count);
}

int main()
{
    char text[256];
    cout << "Введіть текст (до 255 символів, крапка в кінці):" << endl;
    if (!fgets(text, sizeof(text), stdin) || text[0] == 0)
    {
        cout << "Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою." << endl;
        return 0;
    }

    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
    }

    if (!validateText(text))
    {
        cout << "Помилка: Текст введено некоректно!" << endl;
        return 0;
    }
    int count = 0;
    char **words = splitWords(text, count);

    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << "            МЕНЮ              \n";
        cout << "==============================\n";
        cout << "1. Показати текст і статистику\n";
        cout << "2. Таблиця слів\n";
        cout << "3. Замінити слово\n";
        cout << "4. Порівняти два слова\n";
        cout << "5. Інформація про символ\n";
        cout << "6. Ввести нове речення\n";
        cout << "0. Вийти\n";
        cout << "Вибір: ";

        while (scanf("%d", &choice) != 1)
        {
            printf("Невірний ввід! Спробуйте ще раз: ");
            while (getchar() != '\n');
        }

        switch (choice)
        {
        case 1:
            cout << "\n1. Статистика\n";
            ShowStatistics(text, count);
            break;

        case 2:
            cout << "\n2. Вивід таблиці\n";
            ShowTable(words, count);
            break;

        case 3:
            cout << "\n3. Заміна слова\n";
            ReplaceWords(text, words, count);
            break;

        case 4:
            cout << "\n4. Порівняння слів\n";
            CompareWords();
            break;

        case 5:
            cout << "\n5. Інформація про символ\n";
            SymbolInfo(text);
            break;

        case 6:
            cout << "\n6. Нове речення\n";
            ChangeSentence(text, words, count);
            break;

        case 0:
            cout << "Завершення..." << endl;
            break;

        default:
            printf("Помилка: пункту %d немає в меню.\n", choice);
            break;
        }

    } while (choice != 0);

    freeWords(words, count);
    return 0;
}