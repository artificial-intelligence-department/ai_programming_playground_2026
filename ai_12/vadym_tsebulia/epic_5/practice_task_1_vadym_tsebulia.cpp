/*
Редактор текстового повідомлення
Цебуля Вадим
ШІ-12
*/
#include <cstdio>    
#include <cstring>    
#include <cctype>     
#include <string>    
#include <iostream>   

using namespace std;

const int MAX_TEXT = 256;   
const int MAX_WORD = 32;    

// Перевірка тексту: лише латинські літери, цифри, пробіли; закінчується крапкою; є хоча б одне слово
bool validText(const char *text){
        int len = strlen(text);
        if (len < 2 || len > MAX_TEXT - 1) return false;
        if (text[len - 1] != '.') return false;

        bool hasWord = false;
        for (int i = 0; i < len - 1; i++){
                char c = text[i];
                bool latin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
                bool digit = (c >= '0' && c <= '9');
                if (latin || digit) hasWord = true;
                else if (c != ' ') return false;
        }
        // крапка має стояти одразу після останнього слова
        return hasWord && text[len - 2] != ' ';
}

// Перевірка слова: лише латинські літери й цифри, довжина від 1 до 31
bool validWord(const char *w){
        int len = strlen(w);
        if (len == 0 || len > MAX_WORD - 1) return false;
        for (int i = 0; i < len; i++){
                char c = w[i];
                bool latin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
                bool digit = (c >= '0' && c <= '9');
                if (!latin && !digit) return false;
        }
        return true;
}

// Зчитування одного слова через scanf з перевіркою довжини й символів (пункти 3 і 4)
bool readWord(const char *prompt, char *w){
        int ch;
        printf("%s", prompt);
        if (scanf("%31s", w) != 1) return false;
        ch = getchar();
        bool tooLong = (ch != EOF && !isspace(ch));   // слово не вмістилось у 31 символ
        while (ch != '\n' && ch != EOF) ch = getchar(); // викидаємо залишок рядка
        if (tooLong){
                printf("Помилка: слово довше за %d символ.\n", MAX_WORD - 1);
                return false;
        }
        if (!validWord(w)){
                printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
                return false;
        }
        return true;
}

// Розбиття тексту на слова у динамічний масив рядків
char **splitWords(const char *text, int &count){
        // strtok псує рядок, тому працюємо з локальними копіями
        char copy[MAX_TEXT];
        strcpy(copy, text);

        // Перший прохід: рахуємо слова
        count = 0;
        char *token = strtok(copy, " .");
        while (token != nullptr){
                count++;
                token = strtok(nullptr, " .");
        }
        if (count == 0) return nullptr;

        // Другий прохід: копіюємо кожне слово в окрему пам'ять
        char **words = new char*[count];
        strcpy(copy, text);
        int i = 0;
        token = strtok(copy, " .");
        while (token != nullptr){
                words[i] = new char[strlen(token) + 1];
                strcpy(words[i], token);
                i++;
                token = strtok(nullptr, " .");
        }
        return words;
}

// Звільнення динамічної пам'яті масиву слів
void freeWords(char **&words, int &count){
        if (words == nullptr) return;
        for (int i = 0; i < count; i++){
                delete[] words[i];   // звільняємо кожне слово
        }
        delete[] words;              // звільняємо масив вказівників
        words = nullptr;
        count = 0;
}

// Підрахунок літер, цифр і пробілів обходом тексту вказівником
void countChars(const char *text, int &letters, int &digits, int &spaces){
        letters = 0, digits = 0, spaces = 0;
        for (const char *p = text; *p != '\0'; p++){
                if (isalpha(*p)) letters++;
                else if (isdigit(*p)) digits++;
                else if (isspace(*p)) spaces++;
        }
}

// Перебудова масиву слів після зміни тексту (пункти 3 і 6)
void rebuildWords(const char *text, char **&words, int &count){
        freeWords(words, count);
        words = splitWords(text, count);
}

// Сортування вставками за strcmp
void sortWords(char **arr, int n){
        for (int i = 1; i < n; i++){
                char *key = arr[i];
                int j = i - 1;
                while (j >= 0 && strcmp(arr[j], key) > 0){
                        arr[j + 1] = arr[j];
                        j--;
                }
                arr[j + 1] = key;
        }
}

// == Функції пунктів меню ==

// 1. Текст і статистика
void Stats(const char *text, int wordCount){
        int letters, digits, spaces;
        countChars(text, letters, digits, spaces);
        int len = strlen(text);

        printf("Текст:\t\t\"%s\"\n", text);
        printf("Символів:\t%4d\n", len);
        printf("Слів:\t\t%4d\n", wordCount);
        printf("Літер:\t\t%4d (%5.1f%%)\n", letters, letters * 100.0 / len);
        printf("Цифр:\t\t%4d (%5.1f%%)\n", digits, digits * 100.0 / len);
        printf("Пробілів:\t%4d (%5.1f%%)\n", spaces, spaces * 100.0 / len);
}

// 2. Таблиця слів, екстремуми, абетка, найчастіше слово
void WordTable(char **words, int count){
        printf("+----+-----------------+-------+\n");
        printf("| N  | Слово           | Довж. |\n");
        printf("+----+-----------------+-------+\n");

        int longest = 0, shortest = 0, sumLen = 0;
        for (int i = 0; i < count; i++){
                int len = strlen(words[i]);
                printf("| %2d | %-15s | %5d |\n", i + 1, words[i], len);
                sumLen += len;
                // строге порівняння: при рівності лишається перше слово
                if (len > (int)strlen(words[longest])) longest = i;
                if (len < (int)strlen(words[shortest])) shortest = i;
        }
        printf("+----+-----------------+-------+\n");

        printf("Найдовше слово: %s (%d)\n", words[longest], (int)strlen(words[longest]));
        printf("Найкоротше слово: %s (%d)\n", words[shortest], (int)strlen(words[shortest]));
        printf("Середня довжина: %.2f\n", (double)sumLen / count);

        // Сортуємо копію вказівників, щоб порядок у words не змінився
        char **sorted = new char*[count];
        for (int i = 0; i < count; i++){
                sorted[i] = words[i];
        }
        sortWords(sorted, count);

        printf("За абеткою:");
        for (int i = 0; i < count; i++){
                printf(" %s", sorted[i]);
        }
        printf("\n");

        // У відсортованому масиві однакові слова стоять поруч
        int bestIndex = 0, bestCount = 0;
        int i = 0;
        while (i < count){
                int j = i;
                while (j < count && strcmp(sorted[j], sorted[i]) == 0) j++;
                if (j - i > bestCount){
                        bestCount = j - i;
                        bestIndex = i;
                }
                i = j;
        }
        printf("Найчастіше слово: %s (%d)\n", sorted[bestIndex], bestCount);

        delete[] sorted;   // самі слова належать words, тому звільняємо лише масив вказівників
}

// 3. Заміна слова через std::string
void replaceWord(char *text, char **&words, int &count){
        char from[MAX_WORD], to[MAX_WORD];
        if (!readWord("Замінити слово: ", from)) return;
        if (!readWord("На слово: ", to)) return;

        string before = text;
        string result = before;
        string oldWord = from, newWord = to;
        int replaced = 0;

        size_t pos = result.find(oldWord);
        while (pos != string::npos){
                size_t end = pos + oldWord.length();
                // ціле слово: зліва початок або пробіл, справа пробіл або крапка
                bool leftOk = (pos == 0 || result[pos - 1] == ' ');
                bool rightOk = (result[end] == ' ' || result[end] == '.');
                if (leftOk && rightOk){
                        result.replace(pos, oldWord.length(), newWord);
                        replaced++;
                        pos = result.find(oldWord, pos + newWord.length());   // шукаємо за вставленим словом
                } else {
                        pos = result.find(oldWord, pos + 1);
                }
        }

        // довжину перевіряємо ДО запису в text
        if (result.length() > MAX_TEXT - 1){
                printf("Помилка: після заміни текст мав би %d символів (максимум %d). Текст не змінено.\n", (int)result.length(), MAX_TEXT - 1);
                return;
        }

        printf("Замін виконано: %d\n", replaced);
        printf("Було:  \"%s\"\n", before.c_str());
        printf("Стало: \"%s\"\n", result.c_str());
        printf("Нова довжина: %d\n", (int)result.length());

        strcpy(text, result.c_str());
        rebuildWords(text, words, count);
}

// 4. Порівняння двох слів
void compareWords(){
        char a[MAX_WORD], b[MAX_WORD];
        if (!readWord("Перше слово: ", a)) return;
        if (!readWord("Друге слово: ", b)) return;

        // strcmp гарантує лише знак, тому нормалізуємо до -1, 0, 1
        int r = strcmp(a, b);
        r = (r < 0) ? -1 : (r > 0 ? 1 : 0);
        if (r < 0) printf("strcmp: -1 -> перше слово менше\n");
        else if (r > 0) printf("strcmp: 1 -> перше слово більше\n");
        else printf("strcmp: 0 -> слова однакові\n");

        string s1 = a, s2 = b;
        printf("Рівні (==): %s\n", (s1 == s2) ? "так" : "ні");

        // без урахування регістру: обидва слова в нижній регістр
        string low1 = s1, low2 = s2;
        for (size_t i = 0; i < low1.length(); i++) low1[i] = tolower(low1[i]);
        for (size_t i = 0; i < low2.length(); i++) low2[i] = tolower(low2[i]);
        printf("Рівні без урахування регістру: %s\n", (low1 == low2) ? "так" : "ні");

        printf("Довжини: %d і %d\n", (int)strlen(a), (int)strlen(b));

        string joined = s1 + " & " + s2;
        printf("Конкатенація: \"%s\" (%d)\n", joined.c_str(), (int)joined.length());
}

// 5. Інформація про символ
void charInfo(const char *text){
        char c;
        int ch;

        printf("Введіть символ: ");
        if (scanf(" %c", &c) != 1) return;   // пробіл перед %c пропускає Enter з минулого вводу
        while ((ch = getchar()) != '\n' && ch != EOF);

        if ((unsigned char)c > 127){
                printf("Помилка: підтримуються лише латинські символи (ASCII).\n");
                return;
        }

        // Двійковий код через побітові операції: від 7-го біта до 0-го
        char bin[9];
        for (int i = 7; i >= 0; i--){
                bin[7 - i] = ((c >> i) & 1) ? '1' : '0';
        }
        bin[8] = '\0';

        printf("Символ: '%c'\n", c);
        printf("Код: %d (hex 0x%02x, oct 0%o, bin %s)\n", c, c, c, bin);

        if (isupper(c)) printf("Тип: велика літера\n");
        else if (islower(c)) printf("Тип: мала літера\n");
        else if (isdigit(c)) printf("Тип: цифра\n");
        else if (isspace(c)) printf("Тип: пробільний символ\n");
        else printf("Тип: інший символ\n");

        if (isalpha(c)){
                char other = isupper(c) ? tolower(c) : toupper(c);
                printf("Інший регістр: '%c'\n", other);
        }
        printf("Наступний символ: '%c'\n", c + 1);

        // Позиція першого входження через strchr (різниця вказівників + 1)
        const char *first = strchr(text, c);
        if (first == nullptr){
                printf("Символ у тексті не зустрічається.\n");
                return;
        }
        int occurrences = 0;
        for (const char *p = first; p != nullptr; p = strchr(p + 1, c)){
                occurrences++;
        }
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, (int)(first - text) + 1);
}

// 6. Нове речення: читання по словах через cin >> у циклі while
void readSentence(char *text, char **&words, int &count){
        printf("Введіть речення (крапка після останнього слова):\n");
        fflush(stdout);

        string word, sentence;
        int wordsRead = 0;
        bool hasDot = false;
        while (!hasDot && cin >> word){
                wordsRead++;
                if (!sentence.empty()) sentence += " ";
                sentence += word;
                if (word[word.length() - 1] == '.') hasDot = true;
        }
        cin.ignore(10000, '\n');   // залишок рядка після крапки

        if (!hasDot){
                printf("Помилка: речення не завершено крапкою. Текст не змінено.\n");
                return;
        }
        if (sentence.length() > MAX_TEXT - 1){
                printf("Помилка: речення довше за %d символів. Текст не змінено.\n", MAX_TEXT - 1);
                return;
        }
        if (!validText(sentence.c_str())){
                printf("Помилка: речення має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. Текст не змінено.\n");
                return;
        }

        strcpy(text, sentence.c_str());
        rebuildWords(text, words, count);

        printf("Прочитано слів: %d\n", wordsRead);
        printf("Новий текст: \"%s\"\n", text);
        printf("Довжина: %d\n", (int)strlen(text));
}

int main(){
        char text[MAX_TEXT];
        int ch;

        // Ввід тексту
        printf("Введіть текст (до %d символів, крапка в кінці):\n", MAX_TEXT - 1);
        if (fgets(text, MAX_TEXT, stdin) == nullptr){
                printf("Помилка: текст не введено.\n");
                return 1;
        }

        // Прибираємо \n; якщо його немає — текст не вмістився в буфер
        int len = strlen(text);
        if (len > 0 && text[len - 1] == '\n'){
                text[--len] = '\0';
        } else {
                bool extra = false;
                while ((ch = getchar()) != '\n' && ch != EOF){
                        if (!isspace(ch)) extra = true;
                }
                if (extra){
                        printf("Помилка: текст довший за %d символів.\n", MAX_TEXT - 1);
                        return 1;
                }
        }

        if (!validText(text)){
                printf("Помилка: текст має складатися з латинських літер, цифр\nі пробілів та завершуватися крапкою.\n");
                return 1;
        }

        int count = 0;
        char **words = splitWords(text, count);

        // Головне меню
        int choice = -1;
        do {
                printf("\n=== Меню ===\n");
                printf("1. Показати текст і статистику\n");
                printf("2. Таблиця слів\n");
                printf("3. Замінити слово\n");
                printf("4. Порівняти два слова\n");
                printf("5. Інформація про символ\n");
                printf("6. Ввести нове речення\n");
                printf("0. Вийти\n");
                printf("Ваш вибір: ");

                int r = scanf("%d", &choice);
                if (r == EOF) break;

                // викидаємо залишок рядка і запам'ятовуємо, чи там був зайвий текст ("3abc")
                bool extra = false;
                while ((ch = getchar()) != '\n' && ch != EOF){
                        if (!isspace(ch)) extra = true;
                }
                if (r != 1 || extra){
                        printf("Помилка: введіть номер пункту меню.\n");
                        choice = -1;
                        continue;
                }

                switch (choice){
                        case 1:
                                Stats(text, count);
                                break;
                        case 2:
                                WordTable(words, count);
                                break;
                        case 3:
                                replaceWord(text, words, count);
                                break;
                        case 4:
                                compareWords();
                                break;
                        case 5:
                                charInfo(text);
                                break;
                        case 6:
                                readSentence(text, words, count);
                                break;
                        case 0:
                                printf("Вихід з програми.\n");
                                break;
                        default:
                                printf("Помилка: пункту %d немає в меню.\n", choice);
                }
        } while (choice != 0);

        freeWords(words, count);
        return 0;
}