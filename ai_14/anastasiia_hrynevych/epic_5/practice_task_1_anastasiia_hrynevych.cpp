#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>


void clear() {
    while (getchar() != '\n');
}

void removeNewline(char* str) {
    char* pos = strchr(str, '\n');
    if (pos) *pos = '\0';
    pos = strchr(str, '\r');
    if (pos) *pos = '\0';
}

bool isValidText(const char* text) {
    int len = strlen(text);
    if (len == 0) return false;
    
    bool hasAlnum = false;
    bool hasDot = false;
    
    for (int i = 0; i < len; ++i) {
        if (text[i] == '.') {
            if (i == len - 1) {
                hasDot = true;
            } else {
                return false; // Крапка не в кінці
            }
        } else if (!isalnum(text[i]) && text[i] != ' ') {
            return false; // Недопустимий символ
        }
        
        if (isalnum(text[i])) hasAlnum = true;
    }
    return hasAlnum && hasDot;
}

bool isAlphanumericStr(const std::string& str) {
    if (str.empty()) return false;
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalnum(str[i])) return false;
    }
    return true;
}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters = digits = spaces = 0;
    const char* ptr = text;
    while (*ptr) {
        if (isalpha(*ptr)) letters++;
        else if (isdigit(*ptr)) digits++;
        else if (*ptr == ' ') spaces++;
        ptr++;
    }
}

char **splitWords(const char *text, int &count) {
    char temp[256];
    strcpy(temp, text);
    
    char* dot = strchr(temp, '.');
    if (dot) *dot = ' ';

    char **words = new char*[256];
    count = 0;
    
    char *token = strtok(temp, " ");
    while (token != nullptr) {
        words[count] = new char[strlen(token) + 1];
        strcpy(words[count], token);
        count++;
        token = strtok(nullptr, " ");
    }
    return words;
}

void freeWords(char **&words, int &count) {
    if (words) {
        for (int i = 0; i < count; ++i) {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    count = 0;
}

void menu1_Stats(const char* text, int wordCount) {
    int len = strlen(text);
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", len);
    printf("Слів:\t\t%d\n", wordCount);
    
    if (len > 0) {
        printf("Літер:\t\t%d (%.1f%%)\n", letters, (letters * 100.0) / len);
        printf("Цифр:\t\t%d (%.1f%%)\n", digits, (digits * 100.0) / len);
        printf("Пробілів:\t%d (%.1f%%)\n", spaces, (spaces * 100.0) / len);
    }
}

void menu2_Table(char** words, int count) {
    if (count == 0) return;

    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    
    int totalLen = 0;
    int maxLen = -1, minLen = 256;
    int maxIdx = 0, minIdx = 0;

    for (int i = 0; i < count; ++i) {
        int wLen = strlen(words[i]);
        totalLen += wLen;
        
        if (wLen > maxLen) { maxLen = wLen; maxIdx = i; }
        if (wLen < minLen) { minLen = wLen; minIdx = i; }
        
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], wLen);
    }
    printf("+----+-----------------+-------+\n");
    
    printf("Найдовше слово: %s (%d)\n", words[maxIdx], maxLen);
    printf("Найкоротше слово: %s (%d)\n", words[minIdx], minLen);
    printf("Середня довжина: %.2f\n", (float)totalLen / count);

    char** sorted = new char*[count];
    for (int i = 0; i < count; ++i) sorted[i] = words[i];

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(sorted[j], sorted[j+1]) > 0) {
                char* temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }

    printf("За абеткою: ");
    for (int i = 0; i < count; ++i) {
        printf("%s%s", sorted[i], (i == count - 1) ? "" : " ");
    }
    printf("\n");

    int maxFreq = 0, currentFreq = 1;
    char* mostFreqWord = sorted[0];
    for (int i = 1; i < count; ++i) {
        if (strcmp(sorted[i], sorted[i-1]) == 0) {
            currentFreq++;
        } else {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
                mostFreqWord = sorted[i-1];
            }
            currentFreq = 1;
        }
    }
    if (currentFreq > maxFreq) {
        maxFreq = currentFreq;
        mostFreqWord = sorted[count-1];
    }
    
    printf("Найчастіше слово: %s (%d)\n", mostFreqWord, maxFreq);
    delete[] sorted;
}

void menu3_Replace(char* text, char**& words, int& wordCount) {
    char fromStr[32], toStr[32];
    printf("Замінити слово: ");
    scanf("%31s", fromStr);
    printf("На слово: ");
    scanf("%31s", toStr);
    clear();

    if (!isAlphanumericStr(toStr)) {
        printf("Помилка: нове слово має складатися лише з латинських літер і цифр.\n");
        return;
    }

    std::string sText = text;
    std::string sFrom = fromStr;
    std::string sTo = toStr;
    int replacements = 0;
    size_t pos = 0;

    while ((pos = sText.find(sFrom, pos)) != std::string::npos) {
        bool isStartWord = (pos == 0 || !isalnum(sText[pos - 1]));
        bool isEndWord = (pos + sFrom.length() == sText.length() || !isalnum(sText[pos + sFrom.length()]));

        if (isStartWord && isEndWord) {
            sText.replace(pos, sFrom.length(), sTo);
            replacements++;
            pos += sTo.length();
        } else {
            pos += sFrom.length();
        }
    }

    if (sText.length() > 255) {
        printf("Помилка: результат перевищує 255 символів. Текст не змінено.\n");
        return;
    }

    printf("Замін виконано: %d\n", replacements);
    printf("Було:  \"%s\"\n", text);
    strcpy(text, sText.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %lu\n", sText.length());

    freeWords(words, wordCount);
    words = splitWords(text, wordCount);
}

void menu4_Compare() {
    char w1[32], w2[32];
    printf("Перше слово: ");
    scanf("%31s", w1);
    printf("Друге слово: ");
    scanf("%31s", w2);
    clear();

    std::string s1 = w1, s2 = w2;
    int cmp = strcmp(w1, w2);
    
    printf("strcmp: %d -> ", cmp);
    if (cmp < 0) printf("перше слово менше\n");
    else if (cmp > 0) printf("перше слово більше\n");
    else printf("слова однакові\n");

    printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

    bool isEqualNoCase = true;
    if (s1.length() != s2.length()) {
        isEqualNoCase = false;
    } else {
        for (size_t i = 0; i < s1.length(); ++i) {
            if (tolower(s1[i]) != tolower(s2[i])) {
                isEqualNoCase = false;
                break;
            }
        }
    }
    printf("Рівні без урахування регістру: %s\n", isEqualNoCase ? "так" : "ні");
    
    printf("Довжини: %lu і %lu\n", s1.length(), s2.length());
    
    std::string concat = s1 + " & " + s2;
    printf("Конкатенація: \"%s\" (%lu)\n", concat.c_str(), concat.length());
}

void menu5_CharInfo(const char* text) {
    printf("Введіть символ: ");
    char c;
    scanf("%c", &c);
    clear();

    printf("Символ: '%c'\n", c);
    
    
    char binStr[9];
    for (int i = 7; i >= 0; --i) {
        binStr[7 - i] = ((c >> i) & 1) ? '1' : '0';
    }
    binStr[8] = '\0';

    printf("Код: %d (hex 0x%02x, oct 0%o, bin %s)\n", (unsigned char)c, (unsigned char)c, (unsigned char)c, binStr);

    printf("Тип: ");
    if (islower(c)) printf("мала літера\n");
    else if (isupper(c)) printf("велика літера\n");
    else if (isdigit(c)) printf("цифра\n");
    else if (isspace(c)) printf("пробільний символ\n");
    else printf("інший символ\n");

    if (isalpha(c)) {
        printf("Інший регістр: '%c'\n", islower(c) ? (char)toupper(c) : (char)tolower(c));
    }
    
    printf("Наступний символ: '%c'\n", (char)(c + 1));

    int count = 0, firstPos = -1;
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] == c) {
            count++;
            if (firstPos == -1) firstPos = i + 1; 
        }
    }

    if (count > 0) {
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, firstPos);
    } else {
        printf("Символ у тексті відсутній\n");
    }
}

void menu6_NewSentence(char* text, char**& words, int& wordCount) {
    printf("Введіть речення (крапка після останнього слова):\n");
    
    std::string newText = "";
    int readWords = 0;
    
    while (true) {
        std::string word;
        std::cin >> word;
        
        if (!newText.empty()) newText += " ";
        newText += word;
        readWords++;
        
        if (!word.empty() && word.back() == '.') {
            break; 
        }
    }
    clear(); 

    if (!isValidText(newText.c_str())) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    if (newText.length() > 255) {
        printf("Помилка: речення перевищує ліміт у 255 символів.\n");
        return;
    }

    printf("Прочитано слів: %d\n", readWords);
    printf("Новий текст: \"%s\"\n", newText.c_str());
    printf("Довжина: %lu\n", newText.length());

    strcpy(text, newText.c_str());
    freeWords(words, wordCount);
    words = splitWords(text, wordCount);
}


int main() {
    char text[256];
    char **words = nullptr;
    int wordCount = 0;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin) == nullptr) return 1;
    removeNewline(text);

    if (!isValidText(text)) {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }

    words = splitWords(text, wordCount);

    int choice;
    do {
        printf("\n--- Меню ---\n");
        printf("1. Показати текст і статистику\n");
        printf("2. Таблиця слів\n");
        printf("3. Замінити слово\n");
        printf("4. Порівняти два слова\n");
        printf("5. Інформація про символ\n");
        printf("6. Ввести нове речення\n");
        printf("0. Вийти\n");
        printf("Ваш вибір: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть номер пункту меню.\n");
            clear();
            continue;
        }
        clear(); 

        switch (choice) {
            case 1: menu1_Stats(text, wordCount); break;
            case 2: menu2_Table(words, wordCount); break;
            case 3: menu3_Replace(text, words, wordCount); break;
            case 4: menu4_Compare(); break;
            case 5: menu5_CharInfo(text); break;
            case 6: menu6_NewSentence(text, words, wordCount); break;
            case 0: break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
        }
    } while (choice != 0);

    freeWords(words, wordCount);

    return 0;
}