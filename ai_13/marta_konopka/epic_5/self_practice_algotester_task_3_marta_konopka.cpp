#include <cstdio>

char s[200005];

int main(){
    int n;
    if(scanf("%d", &n) != 1){
        return 0;
    }
    scanf("%s", s);
    long long c[4] = {0, 0, 0, 0};
    c[0] = 1;

    long long a[4] = {0, 0, 0, 0};
    int curXor = 0;
    for(int i = 0; i < n; i++){
        int val = 0;
        if(s[i] == 'A'){
            val = 1;
        }
            else if(s[i] == 'B'){
                val = 2;
            }
            else if(s[i] == 'C'){
                val = 3;
            }
            curXor ^= val;
            for(int prevXor = 0; prevXor < 4; prevXor++){
                int result = curXor ^ prevXor;
                a[result] += c[prevXor];
            }
            c[curXor]++;
        }
        printf("%lld %lld %lld %lld\n", a[0], a[1], a[2], a[3]);
        return 0;
    }