/*
Редактор текстового повідомлення
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <cstdio>   
#include <cstring>  
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

int readWord(char w[])
{
    if (scanf("%31s", w) != 1) return 0;
    int c = getchar();                     
    if (c != '\n')                         
    {
        while (getchar() != '\n');       
        return 0;
    }
    return 1;
}
int isValidText(const char text[])
{
    int len = strlen(text),i=0;
    bool hasWord=false;
    if(len<2)return 1;
    if(text[len-1]!='.'||text[len-2]==' ') return 1;
    for(i=0;i<len-1;i++)
    {
        if(text[i]==' ');
        else if((text[i]>='a'&&text[i]<='z')||(text[i]>='A'&&text[i]<='Z'))hasWord=true;
        else if(isdigit(text[i]))hasWord=true;
        else return 1;
        
    }
    if(!hasWord) return 1;
     else return 0;
}
char **splitWords(const char *text, int &count)
{
    int len = strlen(text);
    char *buf = new char[len+1];
    strcpy(buf,text);
    count=0;
    char *t = strtok(buf," .");
    while(t!=NULL)
    {
        t=strtok(NULL," .");
        count++;
    }
    char **word = new char*[count];
    strcpy(buf,text);
    t = strtok(buf," .");
    int i=0;
    while(t!=NULL)
    {
        word[i] = new char[strlen(t)+1];
        strcpy(word[i],t);
        t = strtok(NULL," .");
        i++;
    }
    delete[] buf;
    return word;

}
void freeWords(char **&words, int &count)
{
    for (int i = 0; i < count; i++) delete[] words[i];
    delete[] words;
    words = nullptr;    
    count=0;
}
void countChars(const char *text, int &letters, int &digits, int &spaces)
{
    letters = 0;
    digits = 0;
    spaces = 0;

    while (*text != '\0')          
    {
        if ((*text >= 'a' && *text <= 'z') || (*text >= 'A' && *text <= 'Z'))
            letters++;
        else if (*text >= '0' && *text <= '9')
            digits++;
        else if (*text == ' ')
            spaces++;

        text++;                    
    }
}
void punct1(const char *text, int letters, int digits, int spaces, int count)
{
    int len = strlen(text);
    double letper, digper,spaceper;
    letper = 100.0*letters/len;
    digper = 100.0*digits/len;
    spaceper = 100.0*spaces/len;
    printf("\nТекст:\t\"%s\"\n",text);
    printf("Символів:%6d\n",len);
    printf("Слів:%10d\n",count);
    printf("Літер:%9d (%5.1f%%)\n",letters,letper);
    printf("Цифр:%10d (%5.1f%%)\n",digits,digper);
    printf("Пробілів:%6d (%5.1f%%)\n",spaces,spaceper);
}
void punct2(char **words, int count)
{
    char *Max=words[0],*Min=words[0];
    double average=0;
    printf("+----+-----------------+-------+\n");
    printf("| %2s | %-20s | %5s |\n", "N", "Слово", "Довж.");
    printf("+----+-----------------+-------+\n");   
    for(int i=0;i<count;i++)
    {
        printf("| %2d | %-15s | %5d |\n", i + 1, words[i], (int)strlen(words[i]));
        if((int)strlen(Max)<(int)strlen(words[i]))Max=words[i];
        if((int)strlen(Min)>(int)strlen(words[i]))Min=words[i];
        average +=(int)strlen(words[i]);
    }
    printf("+----+-----------------+-------+\n");
    average = average / count;
    printf("Найдовше слово: %s (%d)\n",Max,(int)strlen(Max));
    printf("Найкоротше слово: %s (%d)\n",Min,(int)strlen(Min));
    printf("Середня довжина: %.2f\n",average);
        
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++)
        sorted[i] = words[i];
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (strcmp(sorted[j], sorted[j + 1]) > 0) 
            {
                char *t = sorted[j];          
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = t;
            }
    char *mostWord = sorted[0];   
    int maxCnt = 1;               
    int cnt = 1;                  
    for (int i = 1; i < count; i++) {
        if (strcmp(sorted[i], sorted[i - 1]) == 0)cnt++;                            
        else cnt = 1;                          
        if (cnt > maxCnt)
        {                   
            maxCnt = cnt;
            mostWord = sorted[i];
        }
    }

    printf("За абеткою: ");
    for(int i=0;i<count;i++)
        printf("%s ",sorted[i]);
    printf("\nНайчастіше слово: %s (%d)\n",mostWord,maxCnt);
    delete[] sorted; 

}
int isValidWord(const char w[])
{
    if (w[0] == '\0') return 0;                  

    for (int i = 0; w[i] != '\0'; i++)
    {
        if (w[i] >= 'a' && w[i] <= 'z');         
        else if (w[i] >= 'A' && w[i] <= 'Z');    
        else if (w[i] >= '0' && w[i] <= '9');    
        else return 0;                           
    }
    return 1;                                   
}
void punct3(char text[], char **&words, int &count)
{
    char from[32], to[32];          

    printf("Замінити слово: ");
    if (readWord(from) == 0)
    {
        printf("Помилка: введіть одне слово до 31 символу. Спробуйте ще раз.\n");
        return;
    }     

    printf("На слово: ");
    if (readWord(to) == 0)
    {
        printf("Помилка: введіть одне слово до 31 символу. Спробуйте ще раз.\n");
        return;
    }
    if (isValidWord(to) == 0)
    {
        printf("Помилка: нове слово має складатися лише з латинських літер і цифр. Спробуйте ще раз.\n");
        return;                          
    }
    if (isValidWord(from) == 0)
    {
    printf("Помилка: слово має складатися лише з латинських літер і цифр. Спробуйте ще раз.\n");
    return;
    }
    string s = text;          
    string f = from;                     
    string t = to;                       
    int replaced = 0;  
    size_t pos = s.find(f);                 

    while (pos != string::npos)          
    {
        size_t end = pos + f.length();   
        int leftOk = 0;
        if (pos == 0 || s[pos - 1] == ' ')
            leftOk = 1;
        int rightOk = 0;
        if (end == s.length() || s[end] == ' ' || s[end] == '.')
            rightOk = 1;

        if (leftOk == 1 && rightOk == 1)
        {
            s.replace(pos, f.length(), t);
            replaced++;
            pos = s.find(f, pos + t.length());
        }
        else
        {
            pos = s.find(f, pos + 1);
        }
    }  
    if (replaced == 0)
    {
    printf("Слово \"%s\" у тексті не знайдено.\n", from);
    return;        
    }
    if (s.length() > 255)
    {
        printf("Помилка: після заміни текст перевищить 255 символів. Спробуйте ще раз.\n");
        return;                          
    }
    printf("Замін виконано: %d\n",replaced);
    printf("Було: \"%s\"\n",text);
    strcpy(text, s.c_str()); 
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Стало: \"%s\"\n",text);
    printf("Нова довжина: %d\n", (int)strlen(text));
}
int equalsIgnoreCase(const char a[], const char b[])
{
    if (strlen(a) != strlen(b))          
        return 0;

    for (int i = 0; a[i] != '\0'; i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
    }
    return 1;              
}
void punct4()
{
    char a[32] = "", b[32] = "";

    printf("Перше слово: ");
        if (readWord(a) == 0)
    {
        printf("Помилка: введіть одне слово до 31 символу. Спробуйте ще раз.\n");
        return;
    }

    printf("Друге слово: ");
    if (readWord(b) == 0)
    {
        printf("Помилка: введіть одне слово до 31 символу. Спробуйте ще раз.\n");
        return;
    }
    if (isValidWord(a) == 0 || isValidWord(b) == 0)
    {
        printf("Помилка: слова мають складатися лише з латинських літер і цифр. Спробуйте ще раз.\n");
        return;
    }


    int r = strcmp(a, b);
    if (r < 0) r = -1;                  
    else if (r > 0) r = 1;               
    if(r==-1)printf("strcmp: %d -> перше слово менше\n",r);
    if(r==0)printf("strcmp: %d -> слова однакові\n",r);
    if(r==1)printf("strcmp: %d -> перше слово більше\n",r);
    string sa = a;
    string sb = b;
    printf("Рівні (==): ");
    if(sa==sb)printf("так\n");
    else printf("ні\n");
    if(equalsIgnoreCase(a,b)==1)printf("Рівні без урахування регістру: так\n");
    else printf("Рівні без урахування регістру: ні\n");
    printf("Довжини: %d і %d\n",(int)sa.length(),(int)sb.length());
    
    string c = sa + " & " + sb;  
    printf("Конкатенація: \"%s\" (%d)\n",c.c_str(),(int)c.length());
}
void punct5(const char text[])
{
    printf("Введіть символ: ");
    int c = getchar();                       

    if (c == '\n')                
    {
        printf("Помилка: введіть один символ. Спробуйте ще раз.\n");
        return;
    }
    int next = getchar();                    
    if (next != '\n')                       
    {
        while (getchar() != '\n');           
        printf("Помилка: введіть один символ. Спробуйте ще раз.\n");
        return;
    }

    printf("Символ: '%c'\n", c);
    printf("Код: %d (hex %#x, oct %#o, bin ", c, c, c);
    for (int i = 7; i >= 0; i--)        
    {
        printf("%d", (c >> i) & 1);        
    }

    printf(")\n");

    if (isupper(c))       printf("Тип: велика літера\n");
    else if (islower(c))  printf("Тип: мала літера\n");
    else if (isdigit(c))  printf("Тип: цифра\n");
    else if (isspace(c))  printf("Тип: пробільний символ\n");
    else                  printf("Тип: інший символ\n");

    if(isupper(c))printf("Інший регістр: '%c'\n",tolower(c));
    else if(islower(c))printf("Інший регістр: '%c'\n",toupper(c));
    
    printf("Наступний символ: '%c'\n", c + 1);
    
    
    const char *p = strchr(text, c); 
    if (p == NULL)
    {
        printf("Символ у тексті не зустрічається.\n");
    }
    else
    {
        int res=0;
        for(int i=0;text[i]!='\0';i++)
        {
            if(text[i]==c)res++;
        }
        printf("Входжень у тексті: %d, перше на позиції %d\n",res,(int)(p-text+1));
    }
}
void punct6(char text[], char **&words, int &count)
{
    printf("Введіть речення (крапка після останнього слова):\n");
    string word, sentence;
    int n = 0;                                   
    while (cin >> word)                          
    {
        n++;
        if (n > 1) sentence += " ";              
        sentence += word;                        
        if (word[word.length() - 1] == '.')      
            break;                               
    }
    if (n == 0 || word[word.length() - 1] != '.')     
    {
        cin.clear();
        clearerr(stdin);
        printf("Помилка: речення має закінчуватися крапкою. Спробуйте ще раз.\n");
        return;
    }
    int extra = 0;                               
    int ch;                                      
    while ((ch = getchar()) != '\n'&& ch != EOF)             
    {
        if (ch != ' ' && ch != '\t')             
            extra = 1;
    }
    if (extra == 1)
    {
        printf("Помилка: після крапки не має бути інших слів. Спробуйте ще раз.\n");
        return;                                  
    }
    if(sentence.length() > 255) {printf("Помилка: речення довше за 255 символів. Спробуйте ще раз.\n");return;}
    if(isValidText(sentence.c_str()) == 1){printf("Помилка: речення має складатися з латинських літер, цифр і пробілів та завершуватися крапкою. Спробуйте ще раз.\n");return;}
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n",n);
    printf("Новий текст: \"%s\"\n",text);
    printf("Довжина: %d\n",(int)strlen(text));
}
int main()
{
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    fgets(text,sizeof(text),stdin);
    if (strchr(text, '\n') == NULL)          
    {
    int c = getchar();                
    if (c != '\n')            
    {
        printf("Помилка: текст довший за 255 символів.\n");
        return 0;
    }
    }   
    text[strcspn(text, "\n")] = '\0';
    if(isValidText(text)==1){printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");return 0;}
    int count=0;
    char **word = splitWords(text,count);
    int flag =1;
    int choice;
    do
    {
        printf("\n======== Меню ========\n");
        printf("Пункт    Операція\n");
        printf("1        Показати текст і статистику\n");
        printf("2        Таблиця слів\n");
        printf("3        Замінити слово\n");
        printf("4        Порівняти два слова\n");
        printf("5        Інформація про символ\n");
        printf("6        Ввести нове речення\n");
        printf("0        Вийти\n");
        printf("Ваш вибір: ");
        if (scanf("%d", &choice) != 1)  
        {
            while (getchar() != '\n');
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        }
        int c = getchar();                     
        if (c != '\n')                       
        {
            while (getchar() != '\n');       
            printf("Помилка: введіть номер пункту меню.\n");
            continue;
        } 

        if (choice < 0 || choice > 6) {
            printf("Помилка: пункту %d немає в меню.\n", choice);
            continue;
        }
        switch(choice)
        {
            case 1:
                int letters,digits,spaces;
                countChars(text,letters,digits,spaces);
                punct1(text,letters,digits,spaces,count);
                break;
            case 2:
                punct2(word,count);
                break;
            case 3:
                punct3(text, word, count);
                break;
            case 4:
                punct4();
                break;
            case 5:
                punct5(text);
                break;
            case 6:
                punct6(text, word, count); 
                break;
            case 0:
            flag=0;
            break;
        }
        
    } while (flag!=0);
    freeWords(word, count);
}