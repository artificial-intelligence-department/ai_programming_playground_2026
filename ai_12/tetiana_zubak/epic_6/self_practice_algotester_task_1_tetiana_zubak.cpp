#include <cstdio>

int main(){
    int n;
    scanf("%d", &n);
    int *a = new int[n + 1]();
    int *st = new int[n + 1]();
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    int top = 1;
    st[0] = a[0];
    long long res = 0;
    for(int i = 1; i < n; i++){
        if(a[i] == 7){
            while(top > 1 && st[top - 1] == 4){
                top--;
                res += a[i] + st[top - 1];
            }
            st[top++] = 7;
        }
        if(a[i] == 4){
            if(i != n - 1 && st[top - 1] == 7) res += 7 + a[i + 1];
            else st[top++] = 4;
        }
    }

    int seven = 0;
    if(st[0] == 4) seven = 1;
    for(int i = seven + 1; i < top - 1; i++){
        res += st[seven] + st[i + 1];
    }
    if(seven == 1 && top > 2) res += st[0] + st[top - 1];
    printf("%lld", res);

    delete[] a;
    delete[] st;
    return 0;
}