#include <cstdio>

using namespace std;

struct box{long long a; long long c; long long pos; box *next;};

int main(){
    int n;
    long long ans, b;
    box *first = NULL, *last = NULL;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        long long a;
        scanf("%lld", &a);

        box *p = new box;
        p->a = a;
        p->pos = i;
        p->c = 0;
        p->next = NULL;
        if(first == NULL) first = p;
        else last->next = p;
        last = p;
    }

    scanf("%lld", &b);
    long long *price = new long long[n];
    for(int i = 0; i < n; i++)
        scanf("%lld", &price[i]);

    box *p = first;
    for(int i = 0; i < n; i++){
        p->c = price[i];
        p = p->next;
    }
    for(int i = 0; i < n; i++){
        long long sum = i * b;

        p = first;
        while(p != NULL){
            sum += p->a * p->c;
            p = p->next;
        }
        if(i == 0 || sum < ans) ans = sum;

        p = first;
        while(p != NULL){
            p->pos = (p->pos + 1) % n;
            if(price[p->pos] < p->c) p->c = price[p->pos];
            p = p->next;
        }
    }
    printf("%lld", ans);

    p = first;
    while(p != NULL){
        box *pp = p;
        p = p->next;
        delete pp;
    }

    delete[] price;
    return 0;
}