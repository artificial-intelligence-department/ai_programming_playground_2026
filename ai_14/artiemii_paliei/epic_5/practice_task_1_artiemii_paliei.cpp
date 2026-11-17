#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

// Пам’ять і буфер

void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++)
        delete[] words[i];

    delete[] words;
    words = nullptr;
    count = 0;
}

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n')
        ;
}

// Ввід і валідація

bool validInput(const char *text)
{
    int length = strlen(text);
    bool has_word = 0;

    if (length == 0)
        return 0;
    if (text[length - 1] != '.')
        return 0;
    for (const char *i = text; i < text + length - 1; i++)
    {
        if (!(isalpha(*i)) && !(isdigit(*i)) && !(isspace(*i)))
            return 0;
        if (isalnum(*i))
            has_word = 1;
    }
    return has_word;
}

char **splitWords(const char *text, int &words_count)
{
    words_count = 0;
    char *text_copy = new char[strlen(text) + 1];

    strcpy(text_copy, text);

    char *token = strtok(text_copy, " .");
    while (token != NULL)
    {
        words_count++;
        token = strtok(NULL, " .");
    }

    if (words_count == 0)
    {
        delete[] text_copy;
        return nullptr;
    }

    strcpy(text_copy, text);

    char **words = new char *[words_count];
    token = strtok(text_copy, " .");
    for (int i = 0; i < words_count && token != NULL; i++)
    {
        words[i] = new char[strlen(token) + 1];
        strcpy(words[i], token);
        token = strtok(NULL, " .");
    }

    delete[] text_copy;
    text_copy = nullptr;

    return words;
}

// Пунк 1

void symbolsCounter(const char *text, int &chars, int &digits, int &spaces)
{
    for (const char *i = text; i < text + strlen(text); i++)
    {
        if (isalpha(*i))
            chars++;
        if (isdigit(*i))
            digits++;
        if (isspace(*i))
            spaces++;
    }
}

void option1(const char *text, int words_count)
{
    int chars_count = 0, digits_count = 0, spaces_count = 0, symbols_count = strlen(text);
    double chars_percentage, digits_percentage, spaces_percentage;

    symbolsCounter(text, chars_count, digits_count, spaces_count);
    chars_percentage = chars_count / double(symbols_count) * 100;
    digits_percentage = digits_count / double(symbols_count) * 100;
    spaces_percentage = spaces_count / double(symbols_count) * 100;

    printf("Текст:\t\"%s\"\n", text);   
    printf("Символів:\t%d\n", symbols_count);
    printf("Слів:\t\t%d\n", words_count);
    printf("Літер:\t\t%2d (%5.1f%%)\n", chars_count, chars_percentage);
    printf("Цифр:\t\t%2d (%5.1f%%)\n", digits_count, digits_percentage);
    printf("Пробілів:\t%2d (%5.1f%%)\n", spaces_count, spaces_percentage);
}

// Пункт 2

char *findLongest(char **words, int words_count)
{
    if (words_count == 0)
        return nullptr;
    char *longest_ptr = words[0];

    for (int i = 1; i < words_count; i++)
    {
        if (strlen(longest_ptr) < strlen(words[i]))
            longest_ptr = words[i];
    }
    return longest_ptr;
}

char *findShortest(char **words, int words_count)
{
    if (words_count == 0)
        return nullptr;
    char *shortest_ptr = words[0];

    for (int i = 1; i < words_count; i++)
    {
        if (strlen(shortest_ptr) > strlen(words[i]))
            shortest_ptr = words[i];
    }
    return shortest_ptr;
}

void printTable(char **words, int words_count)
{
    const char FRAME[] = "+----+-----------------+-------+";
    printf("%s\n", FRAME);
    printf("|%3s | %-21s|%10s |\n", "N", "Слово", "Довж.");
    printf("%s\n", FRAME);
    for (int i = 0; i < words_count; i++)
        printf("|%3d | %-16s|%6zu |\n", i + 1, words[i], strlen(words[i]));
    printf("%s\n", FRAME);
}

void insertionSort(char **words, int words_count)
{
    for (int i = 1; i < words_count; i++)
    {
        int j = i;
        while (j > 0 && strcmp(words[j - 1], words[j]) > 0)
        {
            char *temp = words[j - 1];
            words[j - 1] = words[j];
            words[j] = temp;
            j--;
        }
    }
}

char *wordsCounter(char **sorted_words, int words_count, int &most_common_quantity)
{
    char *most_common = sorted_words[0];
    most_common_quantity = 1;
    for (int i = 0; i < words_count; i++)
    {
        char *temp = sorted_words[i];
        int temp_quantity = 1;
        for (int j = i + 1; j < words_count; j++)
        {
            if (strcmp(temp, sorted_words[j]) == 0)
                temp_quantity++;
        }
        if (most_common_quantity < temp_quantity)
        {
            most_common_quantity = temp_quantity;
            most_common = sorted_words[i];
        }
    }
    return most_common;
}

void option2(char **words, int words_count)
{
    int total_len = 0;
    int count_copy = words_count;
    char **words_copy = new char *[words_count];
    for (int i = 0; i < words_count; i++)
    {
        words_copy[i] = new char[strlen(words[i]) + 1];
        strcpy(words_copy[i], words[i]);
    }

    char *shortest_ptr = findShortest(words, words_count);
    char *longest_ptr = findLongest(words, words_count);

    printTable(words, words_count);

    printf("Найдовше слово: %s (%zu)\n", longest_ptr, strlen(longest_ptr));
    printf("Найкоротше слово: %s (%zu)\n", shortest_ptr, strlen(shortest_ptr));

    for (int i = 0; i < words_count; i++)
        total_len += strlen(words[i]);
    printf("Середня довжина: %.2f\n", (double)total_len / words_count);

    insertionSort(words_copy, words_count);

    printf("За абеткою: ");
    for (int i = 0; i < words_count; i++)
        printf("%s ", words_copy[i]);
    printf("\n");

    int common_quantity = 1;
    char *most_common = wordsCounter(words_copy, words_count, common_quantity);

    printf("Найчастіше слово: %s (%d)\n", most_common, common_quantity);

    freeWords(words_copy, count_copy);
}

void option3(char **&words, char *text, int &words_count)
{
    std::string from, to, string_text = text;
    int replaces = 0;
    bool bad_word = 0;

    printf("Замінити слово: ");
    std::getline(std::cin, from);
    for (size_t i = 0; i < from.length(); i++)
    {
        if (!isalnum(from[i]))
            bad_word = 1;
    }
    if (bad_word || from.empty() || from.length() >= 31)
    {
        printf("Помилка: введене слово повинно містити лише латинські букви, цифри і мати довжину меншу 31\n");
        return;
    }

    bad_word = 0;
    printf("На слово: ");
    std::getline(std::cin, to);

    for (size_t i = 0; i < to.length(); i++)
    {
        if (!isalnum(to[i]))
            bad_word = 1;
    }

    if (bad_word || to.empty() || to.length() >= 31)
    {
        printf("Помилка: введене слово повинно містити лише латинські букви, цифри і мати довжину меншу 31\n");
        return;
    }

    size_t pos1 = string_text.find(from);
    while (pos1 != std::string::npos)
    {
        size_t pos2 = string_text.find_first_of(" .", pos1);

        if ((pos1 == 0 || string_text[pos1 - 1] == ' ') && pos2 - pos1 == from.length())
        {
            string_text.replace(pos1, from.length(), to);
            replaces++;
            pos1 = string_text.find(from, pos1 + to.length());
        }
        else
            pos1 = string_text.find(from, pos1 + from.length());
    }

    if (string_text.length() > 255)
    {
        printf("Замін не відбулось: новий текст перевищує дозволений розмір (255)\n");
        return;
    }

    if (replaces)
    {
        printf("Виконано замін: %d\n", replaces);
        printf("Було: %s\n", text);
        printf("Стало: %s\n", string_text.c_str());
        printf("Нова довжина: %zu\n", string_text.length());
        freeWords(words, words_count);
        strcpy(text, string_text.c_str());
        words = splitWords(text, words_count);
    }
    else
        printf("Замін не відбулось\n");
}

// Пункт 4

void option4()
{
    char a[32] = "";
    char b[32] = "";
    bool is_equal = 1;
    std::string string_a, string_b;

    printf("Перше слово: ");
    scanf("%31s", a);
    clearBuffer();
    string_a = a;
    for (size_t i = 0; i < string_a.length(); i++)
        if (!isalnum(string_a[i]))
        {
            printf("Помилка: введене слово повинно містити лише латинські букви, цифри і мати довжину меншу 31\n");
            return;
        }

    printf("Друге слово: ");
    scanf("%31s", b);
    clearBuffer();
    string_b = b;
    for (size_t i = 0; i < string_b.length(); i++)
        if (!isalnum(string_b[i]))
        {
            printf("Помилка: введене слово повинно містити лише латинські букви, цифри і мати довжину меншу 31\n");
            return;
        }

    int compare_index = strcmp(a, b);
    if (compare_index < 0)
        printf("strcmp: -1 -> перше слово менше\n");
    else if (compare_index > 0)
        printf("strcmp: 1 -> перше слово більше\n");
    else
        printf("strcmp: 0 -> слова однакові\n");

    printf("Рівні (==): ");
    string_a == string_b ? printf("так\n") : printf("ні\n");

    printf("Рівні без урахування регістру: ");
    if (string_a.length() == string_b.length())
    {
        for (size_t i = 0; i < string_a.length(); i++)
            if (tolower(string_a[i]) != tolower(string_b[i]))
            {
                is_equal = 0;
                break;
            }
        if (is_equal)
            printf("так\n");
        else
            printf("ні\n");
    }
    else
        printf("ні\n");

    printf("Довжини: %zu і %zu\n", string_a.length(), string_b.length());

    std::string concatenation = string_a + " & " + string_b;
    printf("Конкатенація: \"%s\" (довжина: %zu)\n", concatenation.c_str(), concatenation.length());
}

void option5(char *text)
{
    int counter = 0;
    char binary[9] = "00000000";
    char c;

    printf("Введіть символ: ");
    scanf("%c", &c);
    clearBuffer();

    for (int i = 7; i >= 0; i--)
    {
        binary[7 - i] = ((c >> i) & 1) + '0';
    }
    binary[8] = '\0';

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", int(c), int(c), int(c), binary);

    if (isalpha(c))
    {
        if (islower(c))
        {
            printf("Тип: мала літера\n");
            printf("Інший регістр: '%c'\n", toupper(c));
            if (c+1 <= 'z')
                printf("Наступний символ: '%c'\n", c + 1);
        }
        else
        {
            printf("Тип: велика літера\n");
            printf("Інший регістр: '%c'\n", tolower(c));
            if (c+1 <= 'Z')
                printf("Наступний символ: '%c'\n", c + 1);
        }
    }
    else if (isdigit(c))
        printf("Тип: цифра\n");
    else if (isspace(c))
        printf("Тип: пробільний символ\n");
    else
        printf("Тип: символ\n");

    char *ptr = strchr(text, c);

    if (ptr != nullptr)
    {
        for (int i = 0; i < strlen(text); i++)
        {
            if (text[i] == '\0')
                break;
            if (text[i] == c)
                counter++;
        }
        printf("Входжень у тексті: %d, перше на позиції %d\n", counter, int(ptr - text) + 1);
    }
    else
    {
        printf("Входжень у тексті: 0\n");
    }
}

void option6(char **&words, char *text, int &words_count)
{
    std::string word;
    std::string sentence = "";

    printf("Введіть речення (крапка після останнього слова):\n");
    while (std::cin >> word)
    {
        sentence.empty() ? sentence += word : sentence += ' ' + word;
        if (word[word.length() - 1] == '.')
            break;
    }
    clearBuffer();

    if (sentence.length() > 255)
    {
        printf("Нове речення перевищує ліміт символів (255)\n");
        return;
    }
    if (!validInput(sentence.c_str()))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, words_count);
    words = splitWords(text, words_count);

    printf("Прочитано слів: %d\n", words_count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", strlen(text));
}

int main()
{
    int count, input = 0;
    const int BUFFER_LIMIT = 256;
    char text[BUFFER_LIMIT] = "";
    char **words = NULL;

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    fgets(text, BUFFER_LIMIT, stdin);
    if (strlen(text) != 0)
        text[strcspn(text, "\n")] = '\0';

    if (!validInput(text))
    {
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.");
        return 1;
    }

    words = splitWords(text, count);

    do
    {
        printf("Пункт\tОперація\n");
        printf("1\tПоказати текст і статистику\n");
        printf("2\tТаблиця слів\n");
        printf("3\tЗамінити слово\n");
        printf("4\tПорівняти два слова\n");
        printf("5\tІнформація про символ\n");
        printf("6\tВвести нове речення\n");
        printf("0\tВихід\n");
        printf("Ваш вибір: ");
        if (scanf("%d", &input) != 1)
        {
            clearBuffer();
            printf("Помилка: введіть номер пункту меню.\n");
            input = -1;
            continue;
        }
        clearBuffer();
        switch (input)
        {
        case 0:
            break;
        case 1:
            option1(text, count);
            break;
        case 2:
            option2(words, count);
            break;
        case 3:
            option3(words, text, count);
            break;
        case 4:
            option4();
            break;
        case 5:
            option5(text);
            break;
        case 6:
            option6(words, text, count);
            break;
        default:
            printf("Пункту %d немає у меню.\n", input);
            input = -1;
            break;
        }
    } while (input != 0);

    freeWords(words, count);

    return 0;
}