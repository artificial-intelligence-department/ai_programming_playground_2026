//Найкращий акумулятор
#include <cstdio>
#include <cstring>
#include <cctype>

int main(){

    //оголошення та ввід
    int n;
    char c;
    char s[100003];
    char s0[100003];
    char sfin[100003];
    scanf("%d %c", &n, &c);
    
    //цикл слів
    for (int i = 0; i < n; ++i) {
        scanf("%100000s", s);

        //Шукаємо куди вставити c
        int pos = strlen(s);
        for (int i = 0; i < strlen(s); ++i) {
            if (s[i] > c) {
                pos = i;
                break;
            }
        }

        //будуємо кандидата s0 з c
        int k = 0;
        for (int i = 0; i < pos; ++i) {
            s0[k++] = s[i];
        }
        s0[k++] = c;
        for (int i = pos; i < strlen(s); ++i) {
            s0[k++] = s[i];
        }
        s0[k] = '\0';

        //Порівнюємо з найкращим кандидатом
        if (i == 0 || strcmp(s0, sfin) < 0) {
            strcpy(sfin, s0);
        }
    }
    
    //Виводив найкращого кандидата
    printf("%s\n", sfin);
    
}