/*
Практична задача: Редактор текстового повідомлення
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;
const int n=256;
int number_of_words(const char *text, int &count)
{
    int number1=0;
    int number2=0;
    for(int i=0; i<count-2; i++)
    {
        if(!(text[i]==' '))
        {
            if(number2==0){number1++;}
            number2++;
        }
        else
        {
            number2=0;
        }
    }
    return number1;
}
char **splitWords(const char *text, int &count)
{
    int number1=0;
    int number2=0;
    int num_w = number_of_words(text, count);
    char** words = new char*[num_w];
    for(int i=0; i<num_w; i++)
    {
        words[i] = new char[n]();
    }
    for(int i=0; i<count-2; i++)
    {
        if(!(text[i]==' '))
        {
            words[number1][number2]=text[i];
            number2++;
        }
        else
        {
            words[number1][number2] = '\0';
            number1++;
            number2=0;
        }
    }
    if(num_w > 0)
    {
        words[num_w - 1][number2] = '\0';
    }
    return words;
}
void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters=0;
    digits=0;
    spaces=0;
    for(int i=0; i<strlen(text)-1; i++)
    {
        if((text[i]>='a' && text[i]<='z') || (text[i]>='A' && text[i]<='Z'))
        {
            letters++;
        }
        if(text[i]>='0' && text[i]<='9')
        {
            digits++;
        }
        if(text[i]==' ')
        {
            spaces++;
        }
    }
}
void change_word(char** words, string a, string b, char *text, int &count)
{
    int number=number_of_words(text, count);
    char new_text[n];
    int number_of_times=0;
    for(int i=0; i<number; i++)
    {
        string str(words[i]);
        if(str==a)
        {
            int z;
            if(b.size()>=strlen(words[i]))
            {
                z=b.size();
            }
            else
            {
                z=strlen(words[i]);
            }
            for(int j=0; j<z; j++)
            {
                if(j>b.size())
                {
                    words[i][j]='\0';
                    continue;
                }
                char ch=b[j];
                words[i][j]=ch;
            }
            number_of_times++;
        }
    }
    int size=number;
    for(int i=0; i<number; i++)
    {
        size+=strlen(words[i]);
    }
    if(size>255)
    {
        printf("%s", "Розмір тексту вийде завеликий(більший за 255 символів)");
    }
    else
    {
        printf("%s", "Замін виконано: ");
        printf("%d\n", number_of_times);
        printf("Було:  ");
        printf("\"%s\"\n", text);
        int x=0;
        for(int i=0; i<number; i++)
        {
            for(int j=0; j<strlen(words[i]); j++)
            {
                text[x]=words[i][j];
                x++;
            }
            if(i<number-1)
            {
                text[x]=' ';
                x++;
            }
        }
        text[x]='.';
        text[x + 1] = '\0';
        printf("%s", "Стало: ");
        printf("\"%s\"\n", text);
        printf("%s", "Нова довжина: ");
        printf("%d\n", size);
    }
}
void two_words(char c[], char d[])
{
    printf("strcmp: ");
    printf("%d", strcmp(c, d));
    printf(" -> ");
    if(strcmp(c, d)==-1)
    {
        printf("перше слово менше\n");
    }
    else if(strcmp(c, d)==0)
    {
        printf("слова рівні\n");
    }
    else if(strcmp(c, d)==1)
    {
        printf("друге слово менше\n");
    }
    printf("Рівні (==): ");
    string s1=c;
    string s2=d;
    string s12=s1+" & "+s2;
    if(s1==s2)
    {
        printf("так\n");
    }
    else
    {
        printf("ні\n");
    }
    printf("Рівні без урахування регістру: ");
    if(s1.size()==s2.size())
    {
        for(int i=0; i<s1.size(); i++)
        {
            s1[i]=tolower(s1[i]);
            s2[i]=tolower(s2[i]);
        }
        if(s1==s2)
        {
            printf("так\n");
        }
        else
        {
            printf("ні\n");
        }
    }
    else
    {
        printf("ні\n");
    }
    printf("Довжини: ");
    printf("%d", s1.size());
    printf(" і ");
    printf("%d\n", s2.size());
    printf("Конкатенація: ");
    printf("\"%s\"", s12.c_str());
    printf(" (");
    printf("%d", s12.size());
    printf(")\n");
}
void word_table(char** words, char *text, int &count)
{
    int number = number_of_words(text, count);
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for(int i=0; i<number; i++)
    {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");
    int max_idx = 0;
    int min_idx = 0;
    int max_len = strlen(words[0]);
    int min_len = strlen(words[0]);
    for(int i=1; i<number; i++)
    {
        int len = strlen(words[i]);
        if(len > max_len)
        {
            max_len = len;
            max_idx = i;
        }
        if(len < min_len)
        {
            min_len = len;
            min_idx = i;
        }
    }
    printf("Найдовше слово: %s (%d)\n", words[max_idx], max_len);
    printf("Найкоротше слово: %s (%d)\n", words[min_idx], min_len);
    double sum = 0;
    for(int i=0; i<number; i++)
    {
        sum += strlen(words[i]);
    }
    double avg = sum / number;
    printf("Середня довжина: %.2f\n", avg);
    char** sorted_words = new char*[number];
    for(int i=0; i<number; i++)
    {
        sorted_words[i] = words[i];
    }
    for(int i=0; i<number-1; i++)
    {
        for(int j=0; j<number-i-1; j++)
        {
            if(strcmp(sorted_words[j], sorted_words[j+1]) > 0)
            {
                char* temp = sorted_words[j];
                sorted_words[j] = sorted_words[j+1];
                sorted_words[j+1] = temp;
            }
        }
    }
    printf("За абеткою: ");
    for(int i=0; i<number; i++)
    {
        printf("%s", sorted_words[i]);
        if(i < number - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
    char* most_freq = sorted_words[0];
    int max_freq = 0;
    int current_freq = 1;
    for(int i=0; i<number; i++)
    {
        if(i < number - 1 && strcmp(sorted_words[i], sorted_words[i+1]) == 0)
        {
            current_freq++;
        }
        else
        {
            if(current_freq > max_freq)
            {
                max_freq = current_freq;
                most_freq = sorted_words[i];
            }
            current_freq = 1;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", most_freq, max_freq);
    delete[] sorted_words;
}
void symbol_info(const char *text)
{
    int ch1;
    while((ch1 = getchar()) != '\n' && ch1 != EOF);
    printf("Введіть символ: ");
    char ch;
    scanf("%c", &ch);
    printf("Символ: '%c'\n", ch);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", (unsigned char)ch, (unsigned char)ch, (unsigned char)ch);
    for(int i = 7; i >= 0; i--)
    {
        printf("%d", ((unsigned char)ch >> i) & 1);
    }
    printf(")\n");
    printf("Тип: ");
    if(ch >= 'a' && ch <= 'z')
    {
        printf("мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(ch));
    }
    else if(ch >= 'A' && ch <= 'Z')
    {
        printf("велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(ch));
    }
    else if(ch >= '0' && ch <= '9')
    {
        printf("цифра\n");
    }
    else if(ch == ' ')
    {
        printf("пробільний символ\n");
    }
    else
    {
        printf("інший символ\n");
    }
    printf("Наступний символ: '%c'\n", ch + 1);
    int occurrences = 0;
    int first_pos = -1;
    int len = strlen(text);
    for(int i = 0; i < len; i++)
    {
        if(text[i] == ch)
        {
            occurrences++;
            if(first_pos == -1)
            {
                first_pos = i + 1;
            }
        }
    }
    if(occurrences > 0)
    {
        printf("Входжень у тексті: %d, перше на позиції %d\n", occurrences, first_pos);
    }
    else
    {
        printf("Символ відсутній у тексті\n");
    }
}
void new_sentence(char *text, int &count, char** &words)
{
    int ch1;
    while((ch1 = getchar()) != '\n' && ch1 != EOF);
    printf("Введіть речення (крапка після останнього слова):\n");
    string temp_text = "";
    string word;
    int word_count = 0;
    while(cin >> word)
    {
        word_count++;
        if(temp_text.empty())
        {
            temp_text=word;
        }
        else
        {
            temp_text+=" "+word;
        }
        if(word[word.length() - 1]=='.')
        {
            break;
        }
    }
    int len = temp_text.length();
    if(len >= 256)
    {
        printf("Будь ласка, тут введіть текст коротший за 256 символів із латинських літер, цифр, пропусків із крапкою в кінці\n");
        return;
    }
    bool valid = true;
    for(int i = 0; i < len - 1; i++)
    {
        char c = temp_text[i];
        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == ' ')))
        {
            valid = false;
            break;
        }
    }
    if(len == 0 || temp_text[len - 1] != '.')
    {
        valid = false;
    }
    if(!valid)
    {
        printf("Будь ласка, тут введіть текст коротший за 256 символів із латинських літер, цифр, пропусків із крапкою в кінці\n");
        return;
    }
    int old_num = number_of_words(text, count);
    for(int i = 0; i < old_num; i++)
    {
        delete[] words[i];
    }
    delete[] words;
    strcpy(text, temp_text.c_str());
    count=strlen(text)+1;
    words=splitWords(text, count);
    printf("Прочитано слів: %d\n", word_count);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %d\n", strlen(text));
}
int main()
{
    string a, b;
    int letters=0;
    int digits=0;
    int spaces=0;
    char text[n];
    char c[n];
    char d[n];
    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, n, stdin);
    text[strcspn(text, "\n")] = '\0';
    int count=strlen(text)+1;
    int characters=count-1;
    if(count==1)
    {
        printf("Будь ласка, тут введіть текст коротший за 256 символів із латинських літер, цифр, пропусків із крапкою в кінці");
        return 1;
    }
    for(int i=0; i<count-2; i++)
    {
        if(!(text[i]>='a' && text[i]<='z') && !(text[i]>='A' && text[i]<='Z') && !(text[i]>='0' && text[i]<='9') && !(text[i]==' '))
        {
            printf("Будь ласка, тут введіть текст коротший за 256 символів із латинських літер, цифр, пропусків із крапкою в кінці");
            return 1;
        }
        if(!(text[count-2]=='.'))
        {
            printf("Будь ласка, тут введіть крапку в кінці також");
            return 1;
        }
    }
    char** words=splitWords(text, count);
    int choice;
    do
    {
        printf("1-Показати текст і статистику\n");
        printf("2-Таблиця слів\n");
        printf("3-Замінити слово\n");
        printf("4-Порівняти два слова\n");
        printf("5-Інформація про символ\n");
        printf("6-Ввести нове речення\n");
        printf("0-Вийти\n");
        printf("Будь ласка, виберіть дію:\n");
        if(scanf("%d", &choice)==1)
        {
            if(choice<0 || choice>6)
            {
                printf("Будь ласка, одну з доступних в програмі дій(0-6)\n");
            }
        }
        else
        {
            printf("Будь ласка, одну з доступних в програмі дій(0-6)\n");
            return 0;
        }
        switch(choice)
        {
            case 1:
            {
                countChars(text, letters, digits, spaces);
                int characters=strlen(text);
                printf("%-10s \"%s\"\n", "Текст:   ", text);
                printf("%-10s%6d\n", "Символів:", characters);
                printf("%-10s%6d\n", "Слів:    ", number_of_words(text, count));
                printf("%-10s%6d%s%.1f%s\n", "Літер:   ", letters, " ( ", ((float)letters*100)/characters, "%)");
                printf("%-10s%6d%s%.1f%s\n", "Цифр:    ", digits, " ( ", ((float)digits*100)/characters, "%)");
                printf("%-10s%6d%s%.1f%s\n", "Пробілів:", spaces, " ( ", ((float)spaces*100)/characters, "%)");
                break;
            }
            case 2: 
            {
                word_table(words, text, count);
                break;
            }
            case 3: 
            {
                a.resize(256);
                b.resize(256);
                printf("Замінити слово: ");
                scanf("%255s", a.data());
                a.resize(std::strlen(a.c_str()));
                printf("На слово: ");
                scanf("%255s", b.data());
                b.resize(std::strlen(b.c_str()));
                if(a.size()>31 || b.size()>31)
                {
                    printf("Будь ласка, тут введіть слова довжиною максимум 31 символ\n");
                }
                else
                {
                    change_word(words, a, b, text, count);
                }
                break;
            }
            case 4:
            {
                int ch1;
                while((ch1=getchar())!='\n' && ch1!=EOF);
                printf("Перше слово: ");
                fgets(c, n, stdin);
                c[strcspn(c, "\n")] = '\0';
                printf("Друге слово: ");
                fgets(d, n, stdin);
                d[strcspn(d, "\n")] = '\0';
                two_words(c, d);
                break;
            }
            case 5: 
            {
                symbol_info(text);
                break;
            }
            case 6: 
            {
                new_sentence(text, count, words);
                break;
            }
            default: 
            {
                break;
            }
        }
    } while(choice!=0);
    int number_of_w = number_of_words(text, count);
    for(int i = 0; i < number_of_w; i++)
    {
        delete[] words[i];
    }
    delete[] words;
}