/*
 * Задача: self_practice_algotester_task_1
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
//суть завдання порахувати кількість полідромів
#include <iostream>
#include <string>
using namespace std;
int main(){
    int polik = 0;
    string word;
    while (cin >> word)
    {int lenWord = word.length();

        for (int i = 0; i < lenWord; i++) 
        // переводимо всі букви в малий регістр
        {
            if (word[i] >= 'A' && word[i] <= 'Z')
                word[i] = word[i] + 32;
        }

        if (lenWord % 2 == 0)
        {
            // парне слово
            int z = 0;
            for (int i = 0; i < lenWord / 2; i++)
            {
                if (word[i] == word[lenWord - 1 - i])
                    z++;
            }
            if (z == lenWord / 2)
                polik++;
        }
        else
        { // непарне слово
               int z = 0;
            for (int i = 0; i < lenWord / 2; i++)
            {
                if (word[i] == word[lenWord - 1 - i])
                    z++;
            }
            if (z == lenWord / 2)
                polik++;
        }}
    printf("%d\n", polik);}