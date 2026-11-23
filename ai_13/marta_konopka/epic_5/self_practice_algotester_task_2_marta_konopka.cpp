#include <cstdio>

char s[100005];
char t[100005];

int main(){
    long long n,m;
    if(scanf("%lld %lld", &n, &m) != 2){
        return 0;
    }
    scanf("%s %s", s, t);
    long long s4 = 0; 
    long long s7 = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '4'){
            s4++;
        }
        else{
            s7++;
       }
    }
    long long t4 = 0;
    long long t7 = 0;
    for(int j = 0; j < m; j++){
        if(t[j] == '4'){
            t4++;
        }
        else{
            t7++;
        }
    }
    long long total = (n + 1) * (m + 1) - 1;
    long long dublicates = s4 * t4 + s7* t7;
    long long a = total - dublicates;
    printf("%lld\n", a);
    return 0;

}