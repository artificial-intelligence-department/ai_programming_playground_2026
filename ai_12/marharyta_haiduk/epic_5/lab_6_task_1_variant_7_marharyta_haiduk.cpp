/*
    Задача: Лабораторна робота №6. Варіант №7
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <stdio.h>
#include <string.h>
int main() {
    char s[256];
    printf("Введіть рядок (до 255 символів): ");
    fgets(s, 256, stdin);
    int n = strlen(s);
    char digits[256];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            digits[count] = s[i];
            count++;
        }
    }
    for (int i = 0; i < count - 1; i++) 
    {
        int maxIndex = i;
        for (int j = i + 1; j < count; j++)
        {
            if (digits[j] > digits[maxIndex])
            {
                maxIndex = j;
            }
        }
        char temp = digits[i];
        digits[i] = digits[maxIndex];
        digits[maxIndex] = temp;
    }
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            s[i] = digits[count];
            count++;
        }
    }
    printf("Результат: %s", s);
    return 0;
}