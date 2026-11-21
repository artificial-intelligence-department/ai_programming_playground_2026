/*
Задача: Lab 6 Task 1 Variant 22
Виконав: Сукач Андрій (ШІ-14)
*/

#include <stdio.h>
#include <cstring>

using namespace std;
int main(){
    char s[256];
    fgets(s, sizeof(s), stdin);
    int slovoA = 0;
    char *token = strtok(s, " \n\t.");
    
    // Поки є слова у рядку
    while (token != NULL) { //для українських strncmp порівнює перші два байти слова з літерою а,А
        if (strncmp(token, "а", 2) == 0 || strncmp(token, "А", 2) == 0 || token[0] == 'a' || token[0] == 'A') {
            slovoA++;
        }
        
        // Переходимо до наступного слова
        token = strtok(NULL, " \n\t.");
    }
  printf("кількість слів що починаються на букву а: %d\n", slovoA);
    
    return 0;
}