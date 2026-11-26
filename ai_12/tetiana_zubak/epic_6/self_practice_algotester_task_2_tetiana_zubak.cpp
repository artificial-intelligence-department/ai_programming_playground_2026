#include <cstdio>

struct node {int el; node *next;};

node *made(int x){
    node *p = new node{x, NULL};
    return p;
}

void push(node *&top, int x){
    node *p = made(x);
    p->next = top;
    top = p;
}

void pop(node *&top){
    node *p = top;
    top = top->next;
    delete p;
}

int main(){
    int n;
    scanf("%d", &n);
    int *p = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    node *top = NULL;
    long long res = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (top != NULL && p[top->el] > p[i]) {
            pop(top);
        }
        int next = n;
        if (top != NULL) next = top->el;
        res += next - i - 1;
        push(top, i);
    }

    while (top != NULL) {
        pop(top);
    }
    for (int i = 0; i < n; i++) {
        while (top != NULL && p[top->el] > p[i]) {
            pop(top);
        }
        int prev = -1;
        if (top != NULL) prev = top->el;
        res += i - prev - 1;
        push(top, i);
    }
    while (top != NULL) {
        pop(top);
    }
    printf("%lld", res);

    delete[] p;
    return 0;
}