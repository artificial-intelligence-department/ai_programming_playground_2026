/*
селф практіс, завдання 1, Фібонета
*/
#include <cstdio>
using namespace std;
void number(long long &a, long long &b){//щоб не переповнити стек ми юзаємо не рекурсію а перезаписуємо значення завдяки референсів
    long long temp = b;
    b = a + b;
    a = temp;
}
int main(){
    long long n, a0, a1;
    scanf("%lld %lld %lld", &n, &a0, &a1);//був експеримент з різними типами даних для сканф
    for(long long i = 0; i<n; i++){
        if(a0>0 && a1>0){
            printf("+");
            return 0;
        }
        if(a0<0 && a1<0){
            printf("-");
            return 0;
        }
        if(a0 == 0 && a1 == 0){//проміжні перевірки бо походу поклали такі тесткейси що оверфлоу навіть у long long
            printf("0");
            return 0;
        }
        number(a0, a1);
    }
    if(a0 > 0){
        printf("+");
    }else if(a0 < 0){
        printf("-");
    }else printf("0");
    return 0;
}