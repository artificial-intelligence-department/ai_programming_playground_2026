/*Практична задача - "Редактор текстового повідомлення"
Максімко Павло - СШІ-13*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;

//Оголошую константи для максимальної довжини тексту та слова (з урахуванням '\0'), щоб не передавати їх окремими параметрами
const int MAX = 256;
const int WORD_MAX = 32;

//Прототипи функцій, щоб main міг викликати їх до того, як вони визначені нижче
void clearBuffer();
bool validText(const char *text);
bool validWord(const char *word);
bool lengthCheck(int length_cur, int length_max);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
bool inputCheck(int input, char **&words, int &count);
void countChars(const char *text, int &letters, int &digits, int &spaces);
void stats(const char *text, int count);
void minmaxWidth(char **words, int count, int &max_width, int &min_width);
int sumWidth(char **words, int count);
void maxRepeated(char **words, int count, int &repeated_word, int &max_repeat);
void wordsTable(char **words, int count);
void replaceWords(char *text, char **&words, int &count, char *from, char *to);
void compareWords(char *a, char *b);
string binary(int num);
void informationSymbol(char c, const char *text);
void sentenceCin(char *text, char **&words, int &count);


int main()
{
    char text[MAX];
    printf("Введіть текст (до %d символів, крапка в кінці): ", MAX - 1);
    //Зчитуємо вхідний рядок разом із пробілами та перевіряємо на помилку читання
    if(fgets(text, sizeof(text), stdin) == nullptr)
    {
        printf("Помилка: Неправильно введений текст \n");
        return 1;
    }
    char *enter = strchr(text, '\n');
    if(enter != nullptr) *enter = '\0';
    else
    {
        //Якщо '\n' не вмістився у буфер, перевіряємо наступний символ, щоб не відхилити рядок довжиною рівно 255 символів
        int ch = getchar();
        if(ch != '\n' && ch != EOF)
        {
            printf("Помилка: Текст повинен не перевищувати %d символів!\n", MAX - 1);
            return 1;
        }
    }
    if(!validText(text))
    {
        printf("Помилка: Текст повинен складатися лише з латинських символів, цифр або пробілів і мати крапку в кінці!\n");
        return 1;
    }
    int count = 0;
    //Розбиваємо введений текст на динамічний масив окремих слів
    char **words = splitWords(text, count);
    do
    {
        printf("========== МЕНЮ ========== \n");
        printf("Дія 1 - Показати текст і статистику \n");
        printf("Дія 2 - Таблиця слів \n");
        printf("Дія 3 - Замінити слово \n");
        printf("Дія 4 - Порівняти два слова \n");
        printf("Дія 5 - Інформація про символ \n");
        printf("Дія 6 - Ввести нове речення \n");
        printf("Дія 0 - Вийти \n");
        int action;
        printf("Ваш вибір: ");
        int input = scanf("%d", &action);
        //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл
        if(inputCheck(input, words, count)) return 0;  
        if(input != 1)
        {
            printf("Помилка: Пункт меню повинен бути цілим числом від 0 до 6 включно!\n");
            //Очищуємо буфер введення, щоб програма не зациклювалася через неправильне введення даних
            clearBuffer();
            continue;
        }
        switch(action)
        {
            case 1:
                printf("Ви вибрали дію 1: \n");
                printf("-----СТАТИСТИКА----- \n");
                stats(text, count);
                break;
            case 2:
                printf("Ви вибрали дію 2: \n");
                printf("-----ТАБЛИЦЯ-----\n");
                wordsTable(words, count);
                break;
            case 3:
                printf("Ви вибрали дію 3: \n");
                printf("-----ЗАМІНА-----\n");
                char from[WORD_MAX + 1], to[WORD_MAX + 1];
                printf("Замінити слово: ");
                //Зчитуємо до 32 символів у буфер розміром 33, щоб вчасно виявити перевищення ліміту у 31 символ
                input = scanf("%32s", from);
                //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл
                if(inputCheck(input, words, count)) return 0;  
                clearBuffer();
                if(lengthCheck((int)strlen(from), WORD_MAX - 1))
                {   
                    printf("Помилка: Довжина слова не повинна перевищувати %d символів! \n", WORD_MAX - 1);
                    continue;
                }
                if(!validWord(from))
                {
                    printf("Помилка: Слово повинне складатися суто з латинських літер або цифр! \n");
                    continue;
                }
                printf("На слово: ");
                //Зчитуємо до 32 символів у буфер розміром 33, щоб вчасно виявити перевищення ліміту у 31 символ
                input = scanf("%32s", to);
                //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл
                if(inputCheck(input, words, count)) return 0; 
                clearBuffer();
                if(lengthCheck((int)strlen(to), WORD_MAX - 1))
                {   
                    printf("Помилка: Довжина слова не повинна перевищувати %d символів! \n", WORD_MAX - 1);
                    continue;
                }
                if(!validWord(to))
                {
                    printf("Помилка: Слово повинне складатися суто з латинських літер або цифр! \n");
                    continue;
                }
                replaceWords(text, words, count, from, to);
                break;
            case 4:
                printf("Ви вибрали дію 4: \n");
                printf("-----ПОРІВНЯННЯ-----\n");
                char a[WORD_MAX + 1], b[WORD_MAX + 1];
                printf("Перше слово: ");
                //Зчитуємо до 32 символів у буфер розміром 33, щоб вчасно виявити перевищення ліміту у 31 символ
                input = scanf("%32s", a);
                //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл
                if(inputCheck(input, words, count)) return 0; 
                clearBuffer();
                if(lengthCheck((int)strlen(a), WORD_MAX - 1))
                {   
                    printf("Помилка: Довжина слова не повинна перевищувати %d символів! \n", WORD_MAX - 1);
                    continue;
                }
                if(!validWord(a))
                {
                    printf("Помилка: Слово повинне складатися суто з латинських літер або цифр! \n");
                    continue;
                }
                printf("Друге слово: ");
                //Зчитуємо до 32 символів у буфер розміром 33, щоб вчасно виявити перевищення ліміту у 31 символ
                input = scanf("%32s", b);
                //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл
                if(inputCheck(input, words, count)) return 0; 
                clearBuffer();
                if(lengthCheck((int)strlen(b), WORD_MAX - 1))
                {   
                    printf("Помилка: Довжина слова не повинна перевищувати %d символів! \n", WORD_MAX - 1);
                    continue;
                }
                if(!validWord(b))
                {
                    printf("Помилка: Слово повинне складатися суто з латинських літер або цифр! \n");
                    continue;
                }
                compareWords(a, b);
                break;
            case 5:
                //Очищуємо буфер від залишкового '\n' після scanf("%d"), інакше специфікатор %c зчитає саме його
                clearBuffer();
                char c;
                printf("Ви вибрали дію 5: \n");
                printf("-----ІНФОРМАЦІЯ-----\n");
                printf("Введіть символ: ");
                input = scanf("%c", &c);
                if(inputCheck(input, words, count)) return 0; 
                informationSymbol(c, text);
                //Очищуємо буфер лише якщо користувач не натиснув одразу Enter, щоб уникнути зайвого очікування вводу
                if(c != '\n') clearBuffer();
                break;
            case 6:
                printf("Ви вибрали дію 6: \n");
                printf("-----ВВЕДЕННЯ-----\n");
                sentenceCin(text, words, count);
                break;
            case 0:
                printf("Ви вибрали дію 0: \n");
                printf("-----ВИХІД-----\n");
                printf("До побачення!\n");
                //Звільняємо динамічну пам'ять перед завершенням програми, щоб уникнути її витоку
                freeWords(words, count);
                return 0;
            default:
                printf("Помилка: Пункту %d не існує! Спробуйте знову: \n", action);
                continue;
        }
    } while (true);
    
}

void clearBuffer()
{
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    return;
}

bool validText(const char *text)
{
    //Змінна alnum гарантує наявність хоча б одного слова, щоб уникнути ділення на нуль у статистиці
    bool alnum = false;
    int length = strlen(text);
    for(int i = 0; i < length; i++)
    {
        //Приводимо char до unsigned char, щоб уникнути невизначеної поведінки функцій <cctype> для символів поза ASCII
        if(isalnum((unsigned char)text[i])) alnum = true;
        if(i != (length - 1) && (!isalnum((unsigned char)text[i]) && text[i] != ' ')) return false;
        else if(i == (length - 1) && text[i] != '.') return false; 
    }
    if(alnum) return true;
    else return false;
}

bool validWord(const char *word)
{
    bool alnum = false;
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        if(isalnum((unsigned char)word[i])) alnum = true;
        if(!isalnum((unsigned char)word[i])) return false;
    }
    if(alnum) return true;
    else return false;
}

bool lengthCheck(int length_cur, int length_max)
{
    return (length_cur > length_max);
}

char **splitWords(const char *text, int &count)
{
    count = 0;
    //Створюємо копію тексту, оскільки функція strtok модифікує вхідний рядок, замінюючи роздільники на '\0'
    char text_copy[MAX];
    strcpy(text_copy, text);
    char *dot = strchr(text_copy, '.');
    if(dot != nullptr) *dot = '\0';
    //Виділяємо динамічний масив вказівників під слова, оскільки їхня кількість заздалегідь невідома
    char **words = new char*[MAX/2];
    char *t = strtok(text_copy, " ");
    while(t != NULL)
    {
        //Виділяємо точний обсяг пам'яті під кожне окреме слово з урахуванням нуль-термінатора '\0'
        words[count] = new char[strlen(t) + 1];
        strcpy(words[count], t);
        count++;
        t = strtok(NULL, " ");
    }
    return words;
}

void freeWords(char **&words, int &count)
{
    for(int i = 0; i < count; i++)
    {
        delete[] words[i];
        words[i] = nullptr;
    }
    
    delete[] words;
    words = nullptr;
    count = 0;
    return;
}

bool inputCheck(int input, char **&words, int &count)
{
    //Обробляємо кінець потоку введення, щоб коректно звільнити пам'ять і завершити роботу
    if(input == EOF)
    {
        printf("До побачення! \n");
        freeWords(words, count);
        return true;
    }   
    return false;
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    //Використовуємо арифметику вказівників для посимвольного обходу рядка
    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha((unsigned char)*(text + i))) letters++;
        else if(isdigit((unsigned char)*(text + i))) digits++;
        else if(isspace((unsigned char)*(text + i))) spaces++;
    }
}

void stats(const char *text, int count)
{
    printf("Текст:   \"%s\" \n", text);
    printf("Символів: %5zu \n", strlen(text));
    printf("Слів: %9d \n", count); 
    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);
    if(strlen(text) != 0)
    {
        //Перетворюємо чисельник на тип double, щоб уникнути цілочисельного ділення при обчисленні відсотків
        printf("Літер:  %7d (%5.1f%%) \n", letters, (double)letters * 100 / strlen(text));
        printf("Цифр:  %8d (%5.1f%%) \n", digits, (double)digits * 100 / strlen(text));
        printf("Пробілів:  %4d (%5.1f%%) \n", spaces, (double)spaces * 100 / strlen(text));
    }
    return;
}

void minmaxWidth(char **words, int count, int &max_width, int &min_width)
{
    for(int i = 0; i < count; i++)
    {
        if(strlen(words[i]) > strlen(words[max_width])) max_width = i;
        if(strlen(words[i]) < strlen(words[min_width])) min_width = i;
    }
    return;
}

int sumWidth(char **words, int count)
{
    int sum = 0;
    for(int i = 0; i < count; i++)
    {
        sum += (int)strlen(words[i]);
    }
    return sum;
}

void maxRepeated(char **words, int count, int &repeated_word, int &max_repeat)
{
    //Підраховуємо повтори у вже відсортованому за абеткою масиві, де однакові слова йдуть підряд
    int repeat = 1; 
    max_repeat = 1; 
    repeated_word = 0;
    for(int i = 0; i < count; i++)
    {
        if(i != 0 && strcmp(words[i], words[i - 1]) == 0) repeat++;
        if((i != 0 && strcmp(words[i], words[i - 1]) != 0) || i == count - 1) 
        {
            if(max_repeat < repeat)
            {
                repeated_word = i - 1;
                max_repeat = repeat;
            }
            repeat = 1;
        }
    }
}

void wordsTable(char **words, int count)
{
    int max_width = 0;
    int min_width = 0;
    int sum_width = sumWidth(words, count);
    double avg_width = (double)sum_width / count;
    minmaxWidth(words, count, max_width, min_width);

    printf("+-----+--------------------+-------+\n");
    printf("|  N  | Слово              | Довж. |\n");
    printf("+-----+--------------------+-------+\n");
    for(int i = 0; i < count; i++)
    {
        printf("| %3d | %-18s | %5zu |\n", i + 1, words[i], strlen(words[i]));
    }
    printf("+-----+--------------------+-------+\n");

    //Створюємо поверхневу копію масиву вказівників, щоб відсортувати слова без зміни їхнього початкового порядку в тексті
    char **words_copy = new char*[count];

    for(int i = 0; i < count; i++)
    {
        words_copy[i] = words[i];
    }

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(strcmp(words_copy[j], words_copy[j + 1]) > 0)
            {
                //Переставляємо лише адреси вказівників, не дублюючи самі рядки в пам'яті
                char *t = words_copy[j];
                words_copy[j] = words_copy[j + 1];
                words_copy[j + 1] = t;
            }
        }
    }

    printf("Найдовше слово: %s (%zu) \n", words[max_width], strlen(words[max_width]));
    printf("Найкоротше слово: %s (%zu) \n", words[min_width], strlen(words[min_width]));
    printf("Середня довжина: %0.2f \n", avg_width);

    printf("За абеткою: ");
    for(int i = 0; i < count; i++)
    {
        printf("%s ", words_copy[i]);
    }

    int repeated_word, max_repeat;
    maxRepeated(words_copy, count, repeated_word, max_repeat);
    printf("\nНайчастіше слово: %s (%d) \n", words_copy[repeated_word], max_repeat);

    //Звільняємо лише тимчасовий масив вказівників, не видаляючи самі рядки, оскільки вони ще потрібні в основному масиві words
    delete[] words_copy;
    words_copy = nullptr;
    return;
}

void replaceWords(char *text, char **&words, int &count, char *from, char *to)
{   
    string text_str(text);
    string from_str(from), to_str(to);
    int replace_count = 0;
    size_t pos = 0;
    while((pos = text_str.find(from_str, pos)) != string::npos)
    {
        //Перевіряємо межі слова (пробіл або крапка), щоб не замінити підрядок усередині іншого довшого слова
        if((pos == 0 || text_str[pos - 1] == ' ') && (text_str[pos + from_str.length()] == ' ' || text_str[pos + from_str.length()] == '.'))
        {    
            text_str.replace(pos, from_str.length(), to_str);
            replace_count++;
            pos += to_str.length();
        }
        else
        {
            pos += from_str.length();
        }
    }

    //Перевіряємо нову довжину до копіювання у C-рядок, щоб уникнути переповнення масиву text
    if(lengthCheck((int)text_str.length(), MAX - 1))
    {
        printf("Помилка: Текст повинен не перевищувати %d символів!\n", MAX - 1);
    }
    else
    {
        printf("Замін виконано: %d \n", replace_count);
        printf("Було: \"%s\" \n", text);
        strcpy(text, text_str.c_str());
        //Звільняємо старий динамічний масив слів і перестворюємо його для оновленого тексту
        freeWords(words, count);
        words = splitWords(text, count);
        printf("Стало: \"%s\" \n", text);
        printf("Нова довжина: %zu \n", strlen(text));
    }
    return;
}

void compareWords(char *a, char *b)
{
    printf("strcmp: %d -> ", ((strcmp(a, b) < 0) ? -1 : ((strcmp(a, b) > 0) ? 1 : 0)));
    (strcmp(a, b) < 0) ? printf("перше слово менше \n") : ((strcmp(a, b) > 0) ? printf("перше слово більше \n") : printf("слова рівні \n")); 
    string a_copy(a);
    string b_copy(b);
    printf("Рівні (==): ");
    (a_copy == b_copy) ? printf("так \n") : printf("ні \n");
    bool unregistered = true;
    if(a_copy.length() != b_copy.length()) unregistered = false;
    else
    {
        //Посимвольно порівнюємо слова у нижньому регістрі для перевірки без урахування регістру
        for(int i = 0; i < a_copy.length(); i++)
        {
            if(tolower((unsigned char)a_copy[i]) != tolower((unsigned char)b_copy[i])) unregistered = false;
        }
    }
    printf("Рівні без урахування регістру: ");
    unregistered ? printf("так \n") : printf("ні \n");
    printf("Довжини: %zu і %zu \n", strlen(a), strlen(b));
    string cat_str = a_copy + " & " + b_copy;
    char cat[MAX];
    strcpy(cat, cat_str.c_str());
    printf("Конкатенація: \"%s\" (%zu) \n", cat, strlen(cat));
}

string binary(int num)
{
    string bin = "";
    //За допомогою побітової маски (& 1) та зсуву праворуч (>>= 1) формуємо 8-бітне двійкове представлення коду ASCII
    for(int i = 0; i < 8; i++)
    {
        switch(num & 1)
        {
            case 1: 
                bin = "1" + bin;
                break;
            default:
                bin = "0" + bin;
                break;
        }
        num >>= 1;
    }
    return bin;
}

void informationSymbol(char c, const char *text)
{
    printf("Символ: '%c' \n", c);
    string bin = binary((unsigned char)c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", (unsigned char)c, (unsigned char)c, (unsigned char)c, bin.c_str());
    printf("Тип: ");
    if(isalpha((unsigned char)c)) 
    {
        if(islower((unsigned char)c)) 
        { 
            printf("мала літера \n"); 
            printf("Інший регістр: '%c' \n", toupper((unsigned char)c)); 
        } 
        else 
        {
            printf("велика літера \n");
            printf("Інший регістр: '%c' \n", tolower((unsigned char)c)); 
        }
    }
    else if(isdigit((unsigned char)c)) printf("цифра \n");
    else if(isspace((unsigned char)c)) printf("пробільний символ \n");
    else printf("інший символ \n");
    //Збільшуємо числовий код символу на 1, щоб отримати наступний символ у таблиці ASCII
    printf("Наступний символ: '%c' \n", c + 1);

    int pos = -1, count_symb = 0; 
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i] == c)
        {
            count_symb++;
            if(pos == -1) pos = i;
        }
    }
    if(pos != -1) printf("Входжень у тексті: %d, перше на позиції %d \n", count_symb, pos + 1);
    else printf("Входжень у тексті немає \n");
    return;
}

void sentenceCin(char *text, char **&words, int &count)
{  
    printf("Введіть речення (крапка після останнього слова): ");
    string word;
    string sentence = ""; 
    //Послівне зчитування через cin >> автоматично нормалізує зайві пробіли між словами
    while(cin >> word)
    {
        if(sentence == "") sentence += word;
        else sentence += " " + word;
        if(word.back() == '.' || sentence.length() >= MAX) break;
    }
    clearBuffer();
    if(lengthCheck((int)sentence.length(), MAX - 1))
    {
        printf("Помилка: Речення повинне не перевищувати %d символів!\n", MAX - 1);
    }
    else if(!validText(sentence.c_str()))
    {
        printf("Помилка: Текст повинен складатися лише з латинських символів, цифр або пробільних символів!\n");
    }
    else
    {
        strcpy(text, sentence.c_str());
        //Звільняємо пам'ять від попереднього речення та формуємо новий динамічний масив слів
        freeWords(words, count);
        words = splitWords(text, count);
        printf("Прочитано слів: %d \n", count);
        printf("Новий текст: \"%s\" \n", text);
        printf("Довжина: %zu \n", strlen(text));
    }
    return;
}