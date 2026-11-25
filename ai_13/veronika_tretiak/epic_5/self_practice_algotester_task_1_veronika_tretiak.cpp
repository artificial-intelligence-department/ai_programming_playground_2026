/*
Задача: Щасливі рядки
*/
#include <cstdio>
int main(){
    int n,m;
    scanf("%d %d", &n, &m);
    char s[100005], t[100005];
    scanf("%100000s", s);
    scanf("%100000s", t);
    long long s4 = 0;
    long long s7 = 0;
    long long t4 = 0;
    long long t7 = 0;
    for(int i = 0; i < n; i++){
        if(s[i] =='4'){
            s4++;
        }else{
            s7++;
        }
    }
    for(int i = 0; i < m; i++){
        if(t[i] == '4'){
            t4++;
        }else{
            t7++;
        }
}
long long answer = n + m + s4 * t7 + s7 * t4;
printf("%lld\n", answer);
return 0;
}