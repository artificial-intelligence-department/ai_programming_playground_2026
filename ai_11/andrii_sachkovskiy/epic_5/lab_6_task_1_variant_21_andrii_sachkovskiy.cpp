/*
 * Задача: lab_6_task_1_variant_21
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
//задача вивести непарні слова
int main() {
    //користувач вводить слова
    char text[256];
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    char neParni[256];
    int k = 0;         
    int z = 0;         
    int start = 0;     

    for (int i = 0; ; i++) {
        //робим підрахунок символів в слові
        if (text[i] != ' ' && text[i] != '\0') {
            if (z == 0) start = i;//запомнили індекс з якого починається
            z++;
        }//записуємо непарні слова в масив 
        else {
            if (z % 2 != 0) {
                for (int j = start; j < start + z; j++)
                    neParni[k++] = text[j];
                neParni[k++] = ' ';
            }
            z = 0;
            if (text[i] == '\0')
                break;
        }
    }
//виводимо результат
    for (int i = 0; i < k - 1; i++)
        printf("%c", neParni[i]);
    printf("\n");

    return 0;
}