/*
Задача: Редактор текстового повідомлення
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

char **splitWords(const char *text, int &count);
void showMenu();
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showTextStats(const char* text, int words_count);
void printWordsTable(char** words, int words_count);
char** sortWords(char** words, int words_count);
void replaceWord(char *text, char** &words, int &words_count);
void freeWords(char** &words, int &words_count);
void compareWords();
void showCharInfo(const char *text);
void enterNewSentence(char *text, char** &words, int &words_count);
bool validateText(const char *text);
bool validateWord(const char *word);

int main()
{
    char text[256];

    printf("Enter your text:\n");
    if(fgets(text, sizeof(text), stdin) == nullptr)
    {
        printf("Error: input failed.\n");
        return 1;
    }

    if(strlen(text) == 255 && text[254] != '\n')
    {
        int c = getchar();

        if(c != '\n' && c != EOF)
        {
            printf("Error: text is too long.\n");
            return 1;
        }
    }

    text[strcspn(text, "\n")] = '\0';

    if(!validateText(text))
    {
        printf("Error: invalid text.\n");
        return 1;
    }

    int count;
    char **words = splitWords(text, count);

    int choice = -1;

    do
    {
        showMenu();

        printf("Select your operation: ");

        int result = scanf("%d", &choice);
        int c;
        bool invalid = false;

        while((c = getchar()) != '\n' && c != EOF)
        {
            if(c != ' ' && c != '\t') invalid = true;
        }

        if(result == EOF) break;

        if(result != 1 || invalid)
        {
            printf("Error: incorrect input!\n");
            choice = -1;
            continue;
        }

        printf("\n");

        switch(choice)
        {
            case 1:
                showTextStats(text, count);
                break;
            case 2:
                printWordsTable(words, count);
                break;
            case 3:
                replaceWord(text, words, count);
                break;
            case 4:
                compareWords();
                break;
            case 5:
                showCharInfo(text);
                break;
            case 6:
                enterNewSentence(text, words, count);
                break;
            case 0:
                printf("Exit..");
                break;
            default:
                printf("Error: no such operation!\n");
                break;
        }
    }
    while(choice != 0);

    freeWords(words, count);

}

char **splitWords(const char *text, int &count)
{
    char **words = new char*[256];
    char *text_copy = new char[strlen(text)+1];
    strcpy(text_copy, text);

    count = 0;

    char *t = strtok(text_copy, " .");

    while(t != nullptr)
    {
        size_t len = strlen(t);
        words[count] = new char[len + 1];
        strcpy(words[count], t);

        count++;
        t = strtok(nullptr, " .");
    }

    delete[] text_copy;
    
    return words;
}

void showMenu()
{
    printf("\n%-3s %25s \n", "1", "Show text and stats");
    printf("%-3s %25s \n", "2", "Words table");
    printf("%-3s %25s \n", "3", "Replace a word");
    printf("%-3s %25s \n", "4", "Compare two words");
    printf("%-3s %25s \n", "5", "Info about a char");
    printf("%-3s %25s \n", "6", "Enter new sentence");
    printf("%-3s %25s \n\n", "0", "Exit");
}

void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    for(const char *p = text; *p != '\0'; p++)
    {
        if(isalpha(*p)) letters++;
        if(isdigit(*p)) digits++;
        if(*p == ' ') spaces++;
    }
}

void showTextStats(const char* text, int words_count)
{

    int letters_count;
    int digits_count;
    int spaces_count;

    size_t len = strlen(text);

    countChars(text, letters_count, digits_count, spaces_count);

    printf("Text:\t \"%s\" \n", text);
    printf("%-8s %3zu \n", "Chars:", len);
    printf("%-8s %3d \n", "Words:", words_count);
    printf("%-8s %3d (%5.1f%%) \n", "Letters:", letters_count, letters_count / (float)len * 100);
    printf("%-8s %3d (%5.1f%%) \n", "Digits:", digits_count, digits_count / (float)len * 100);
    printf("%-8s %3d (%5.1f%%) \n", "Spaces:", spaces_count, spaces_count / (float)len * 100);
}

void printWordsTable(char** words, int words_count)
{
    printf("+----+-----------------+-------+\n");
    printf("| %-2s | %-14s | %-6s |\n", "N", "Word", "Length");
    printf("+----+-----------------+-------+\n");

    size_t max_len = 0;
    size_t min_len = 256;
    int max_i = 0;
    int min_i = 0;
    int total_len = 0;

    for(int i = 0; i < words_count; i++)
    {
        size_t word_len = strlen(words[i]);
    
        if(word_len > max_len)
        {
            max_len = word_len;
            max_i = i;
        }
        if(word_len < min_len)
        {
            min_len = word_len;
            min_i = i;
        }

        total_len += word_len;
        
        printf("| %2d | %-14s | %6zu |\n", i+1, words[i], word_len);   
    }

    printf("+----+-----------------+-------+\n");

    float avg_len = total_len / (float)words_count;
    char **sorted_words = sortWords(words, words_count);

    printf("The longest word: %s (%zu)\n", words[max_i], max_len);
    printf("The shortest word: %s (%zu)\n", words[min_i], min_len);  
    printf("Average length: %.2f\n", avg_len);

    printf("In alphabetic order: ");  
    for(int i = 0; i < words_count; i++)
    {
        printf("%s ", sorted_words[i]);
    }

    printf("\n");

    int max_freq = 1;
    int max_freq_i = 0;
    int freq = 1;

    for(int i = 1; i < words_count; i++)
    {
        if(strcmp(sorted_words[i], sorted_words[i-1]) == 0)
        {
            freq++;
        }
        else
        {
            if(freq > max_freq)
            {
                max_freq = freq;
                max_freq_i = i - 1;
            }
            freq = 1;
        }

    }

    if(freq > max_freq)
    {
        max_freq = freq;
        max_freq_i = words_count - 1;
    }


    printf("Most frequent word: %s (%d)\n", sorted_words[max_freq_i], max_freq);

    delete[] sorted_words;
}

char** sortWords(char** words, int words_count)
{
    char **sorted = new char*[words_count];

    for(int i = 0; i < words_count; i++)
    {
        sorted[i] = words[i];
    }

    for(int i = 0; i < words_count - 1; i++)
    {
        for(int j = 0; j < words_count - i - 1; j++)
        {
            if(strcmp(sorted[j], sorted[j+1]) > 0)
            {
                char *t = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = t;
            }
        }
    }

    return sorted;
}

void replaceWord(char *text, char** &words, int &words_count)
{
    char from[256];
    char to[256];

    printf("Replace word: ");
    if(scanf("%255s", from) != 1) return;

    printf("Replace with: ");
    if(scanf("%255s", to) != 1) return;

    if(!validateWord(from) || !validateWord(to))
    {
        printf("Error: invalid word! Use 1-31 Latin letters or digits.\n");
        return;
    }

    string old_text = text;
    string new_text = text;
    string old_word = from;
    string new_word = to;

    int replacements = 0;
    size_t pos = 0;

    while((pos = new_text.find(old_word, pos)) != string::npos)
    {
        size_t end = pos + old_word.length();

        bool left = (pos == 0 || new_text[pos - 1] == ' ');
        bool right = (end < new_text.length() && (new_text[end] == ' ' || new_text[end] == '.'));

        if(left && right)
        {
            new_text.replace(pos, old_word.length(), new_word);
            replacements++;
            pos += new_word.length();
        }
        else
        {
            pos += old_word.length();
        }

    }

    if(new_text.length() > 255)
    {
        printf("Error: resulting text exceeds 255 characters.\n");
        return;
    }

    strcpy(text, new_text.c_str());
    freeWords(words, words_count);
    words = splitWords(text, words_count);

    printf("Replacements: %d\n", replacements);
    printf("Before: \"%s\"\n", old_text.c_str());
    printf("After: \"%s\"\n", text);
    printf("New length: %zu\n", strlen(text));

}

void freeWords(char** &words, int &words_count)
{
    for(int i = 0; i < words_count; i++)
    {
        delete[] words[i];
    }
    delete[] words;

    words = nullptr;
    words_count = 0;
}

void compareWords()
{
    char word1[256];
    char word2[256];

    printf("Enter first word: ");
    if(scanf("%255s", word1) != 1) return;

    if(!validateWord(word1))
    {
        printf("Error: invalid word!\n");
        return;
    }

    printf("Enter second word: ");
    if(scanf("%255s", word2) != 1) return;

    if(!validateWord(word2))
    {
        printf("Error: invalid word!\n");
        return;
    }

    string str_word1 = word1;
    string str_word2 = word2;

    int cmp = strcmp(word1, word2);

    if(cmp < 0) cmp = -1;
    else if(cmp > 0) cmp = 1;

    printf("strcmp: %d -> ", cmp);

    if(cmp == -1) printf("first word is smaller\n");
    else if(cmp == 1) printf("first word is greater\n");
    else printf("words are equal\n");

    printf("Equal (==): %s\n", (str_word1 == str_word2) ? "yes" : "no");

    bool case_insensitive_equal = true;

    if(str_word1.length() != str_word2.length())
    {
        case_insensitive_equal = false;
    }
    else
    {
        for(int i = 0; i < str_word1.length(); i++)
        {
            if(tolower(str_word1[i]) != tolower(str_word2[i]))
            {
                case_insensitive_equal = false;
                break;
            }
        }
    }

    printf("Are strings equal ignoring case: %s\n", case_insensitive_equal ? "yes" : "no");
    printf("Lengths: %zu and %zu\n", str_word1.length(), str_word2.length());
    string concat = str_word1 + " & " + str_word2;
    printf("Concatenation: \"%s\" (%zu)\n", concat.c_str(), concat.length());
}

void showCharInfo(const char *text)
{
    char c;
    printf("Enter a character: ");

    if(scanf("%c", &c) != 1)
    {
        printf("Error: failed to read character.\n");
        return;
    }

    if(c == '\n')
    {
        printf("Error: enter exactly one character.\n");
        return;
    }

    int next = getchar();

    if(next != '\n' && next != EOF)
    {
        while(next != '\n' && next != EOF)
        {
            next = getchar();
        }

        printf("Error: enter exactly one character.\n");
        return;
    }

    unsigned int code = c;

    printf("Character: '%c'\n", c);
    printf("Code: %u (hex 0x%02x, oct 0%o, bin ", code, code, code);

    for(int i = 7; i >= 0; i--)
    {
        printf("%u", (code >> i) & 1);
    }
    printf(")\n");

    if(isupper(c))
    {
        printf("Type: uppercase letter\n");
        printf("Other case: '%c'\n", tolower(c));
    }
    else if(islower(c))
    {
        printf("Type: lowercase letter\n");
        printf("Other case: '%c'\n", toupper(c));
    }
    else if(isdigit(c))
    {
        printf("Type: digit\n");
    }
    else if(isspace(c))
    {
        printf("Type: whitespace\n");
    }
    else
    {
        printf("Type: other character\n");
    }

    if(code < 255)
    {
        code++;
        printf("Next character: '%c'\n", code);
    }
    else
    {
        printf("Next character: unavailable\n");
    }

    int count = 0;

    int i = 0;
    while(text[i] != '\0')
    {
        if(text[i] == c) count++;
        i++;
    }

    const char *first = strchr(text, c);

    if(first != nullptr)
    {
        int position = first - text + 1;
        printf("Occurrences: %d, first at position %d\n", count, position);
    }
    else
    {
        printf("Character not found in the text.\n");
    }
}

void enterNewSentence(char *text, char** &words, int &words_count)
{
    string sentence = "";
    string word;
    int count = 0;

    printf("Enter new sentence (period after last word):\n");

    while(cin >> word)
    {
        count++;

        if(sentence != "")
        {
            sentence += " ";
        }

        sentence += word;

        if(word[word.length() - 1] == '.')
        {
            break;
        }
    }

    if(!validateText(sentence.c_str()))
    {
        printf("Error: invalid sentence!\n");
        return;
    }

    strcpy(text, sentence.c_str());
    freeWords(words, words_count);
    words = splitWords(text, words_count);

    printf("Words read: %d\n", count);
    printf("New text: \"%s\"\n", text);
    printf("New length: %zu\n", strlen(text));
}

bool validateText(const char *text)
{
    size_t len = strlen(text);

    if(len < 2 || len > 255 || text[len - 1] != '.') return false;

    if(text[len - 2] == ' ') return false;

    for(size_t i = 0; i < len - 1; i++)
    {
        char c = text[i];

        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ')) return false;
    }

    return true;
}

bool validateWord(const char *word)
{
    size_t len = strlen(word);

    if(len == 0 || len > 31)
    {
        return false;
    }

    for(int i = 0; i < len; i++)
    {
        char c = word[i];

        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
        {
            return false;
        }
    }

    return true;
}
