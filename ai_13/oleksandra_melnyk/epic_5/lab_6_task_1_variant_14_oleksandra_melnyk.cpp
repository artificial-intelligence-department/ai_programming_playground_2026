#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int maxlen=256;

bool Haslettersnumbers(const char *word)
{
    bool Hasletters=false;
    bool Hasnumbers=false;
    for (int i=0; word[i]!= '\0'; i++){
        unsigned char c=word[i];
        if (isdigit(c)){
            Hasnumbers=true;
        }
        else if (isalpha(c)){
            Hasletters=true;
        }
    }
    return Hasletters && Hasnumbers;
}

void String(char s[]){
    char result[maxlen]="";
    bool first=true;
    char *word=strtok(s, " \t");
    while (word!=NULL){
        if (Haslettersnumbers(word)){
            if (!first) strcat(result, " ");
                strcat(result,word);
                first=false;
        }
        word=strtok(NULL," \t");
    }
    strcat(result, ".");
    strcpy(s,result);
}
int main()
{
    char s[maxlen];
    puts("Текст: ");
    if (fgets(s,maxlen,stdin)==NULL){
        puts("Помилка.");
        return 1;
    }

    s[strcspn(s, "\r\n")]='\0';
    int len=strlen(s);
    while(len>0 && s[len-1]==' '){
        len--;
    }
    if (len>0 && s[len-1]=='.'){
        len--;
    }
    while(len>0 && s[len-1]==' '){
        len--;
    }
    s[len]='\0';

    printf("Початковий текст: %s.\n", s);
    String(s);
    puts("Результат: ");
    puts(s);
    return 0;
}