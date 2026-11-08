/*
Lab 6 Task 1 Variant 11
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
    char** words = new char*[number_of_words(text, count)];
    for(int i=0; i<number_of_words(text, count); i++)
    {
        words[i] = new char[n];
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
            number1++;
            number2=0;
        }
    }
    return words;
}
int main()
{
    char text[n];
    printf("Введіть текст (до 255 символів, крапка в кінці): ");
    fgets(text, n, stdin);
    int count=strlen(text);
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
    int number=number_of_words(text, count);
    char** words=splitWords(text, count);
    char** new_words = new char*[number];
    for(int i=0; i<number; i++)
    {
        new_words[i] = new char[n];
    }
    for(int i=0; i<number; i++)
    {
        int len=strlen(words[i]);
        for(int j=0; j<strlen(words[i]); j++)
        {
            new_words[i][j]=words[i][len-1-j];
        }
    }
    printf("%s", "Ось текст з віддзеркаленими словами: ");
    for(int i=0; i<number-1; i++)
    {
        printf("%s%s", new_words[i], " ");
    }
    printf("%s", new_words[number-1]);
    printf("%s", ".");
    for(int i=0; i<number; i++)
    {
        delete[] words[i];
        delete[] new_words[i];
    }
    delete[] words;
    delete[] new_words;
}