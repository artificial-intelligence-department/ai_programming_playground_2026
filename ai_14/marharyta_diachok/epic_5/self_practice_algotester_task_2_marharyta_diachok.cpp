/*  
Задача: Self-practice. Завдання №2.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <cstdio>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    printf("%.10f\n", (double)(n + 1) / (double)(n - k + 1));
    return 0;
}