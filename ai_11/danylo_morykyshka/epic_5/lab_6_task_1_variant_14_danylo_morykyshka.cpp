#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;
const int MAX_SYMBOLS_COUNT = 255;
bool hasLetter(string word);
bool hasDigit(string word);
int main()
{
    printf("Введіть рядок:\n");
    char txt[MAX_SYMBOLS_COUNT];
    if(fgets(txt, MAX_SYMBOLS_COUNT, stdin) == NULL){
        printf("Помилка. Некоректний ввід даних.");
        return 1;
    }
    txt[strcspn(txt, "\n")] = '\0';
    if(strlen(txt) == 0){
        printf("Помилка. Рядок занадто короткий.");
        return 1;
    }
     if(txt[strlen(txt) - 1] != '.'){
        printf("Помилка: текст має завершуватися крапкою.");
        return 1;
    }
    string words[MAX_SYMBOLS_COUNT];
    int count = 0;

    char d[] = " .";
    char *wordA = strtok(txt, d);
    while (wordA != NULL)
    {
        words[count] = wordA;
        count++;
        wordA = strtok(NULL, d);
    }
    printf("Список слів: \n");
    for (int i = 0; i < count; i++)
    {
        printf("%3s\n", words[i].c_str());
    }
    string updList[count];
    int newCount = 0;
    for (int i = 0; i < count; i++)
    {
        if(hasLetter(words[i]) && hasDigit(words[i])){
                updList[newCount] = words[i];
                newCount++;
            }
    }
    printf("Оновлений рядок:\n");
    for (int i = 0; i < newCount; i++)
    {
        printf("%s\n", updList[i].c_str());
    }
}
bool hasLetter(string word)
{
        for (int j = 0; j < word.size(); j++)
        {
            if(isalpha(word[j])){
                return true;
            }
        }  
    
    return false;
}
bool hasDigit(string word)
{
        for (int j = 0; j < word.size(); j++)
        {
            if(isdigit(word[j])){
                return true;
            }
        }  
        return false;
}
