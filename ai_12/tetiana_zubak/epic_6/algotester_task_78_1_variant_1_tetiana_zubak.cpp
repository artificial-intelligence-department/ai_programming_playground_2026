/* 
Алготестер, варіант 1.1
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <cstdio>

using namespace std;

struct node{int el; node *next; node *prev;};

struct list{node* first = NULL; node* last = NULL; int t = 0;};

node pool[500001];
int pool_ptr = 0;

node* made(int a){
    pool[pool_ptr] = {a, NULL, NULL};
    return &pool[pool_ptr++];
}

ostream& operator<<(ostream& os, const list& l){
    node* p = l.first;
    while(p != NULL){
        os << p->el;
        if(p->next != NULL) os << " ";
        p = p->next;
    }
    return os;
}

node* find(list& l, int in){
    node* p;
    if(in < l.t - 1 - in){
        p = l.first;
        for(int i = 0; i < in; i++) p = p->next;
    } else{
        p = l.last;
        for(int i = l.t - 1; i > in; i--) p = p->prev;
    }
    return p;
}

void ins(list& l){
    int in, n, a;
    scanf("%d %d", &in, &n);
    if(n == 0) return;
    node* first = NULL;
    node* last = NULL;

    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        node* num = made(a);
        if(first == NULL) first = num;
        else{
            last->next = num;
            num->prev = last;
        }
        last = num;
    }
    if(in == 0){
        last->next = l.first;
        if(l.first != NULL) l.first->prev = last;
        else l.last = last;
        l.first = first;
    } 
    else if(in == l.t){
        first->prev = l.last;
        if(l.last != NULL) l.last->next = first;
        else l.first = first;
        l.last = last;
    } 
    else{
        node* p = find(l, in);
        first->prev = p->prev;
        last->next = p;
        p->prev->next = first;
        p->prev = last;
    }
    l.t += n;
}

void era(list& l){
    int in, n;
    scanf("%d %d", &in, &n);
    if(n <= 0) return;
    node* p = find(l, in);
    node* before = p->prev;

    for(int i = 0; i < n; i++){
        p = p->next;
    }
    if(before != NULL) before->next = p;
    else l.first = p;
    if(p != NULL) p->prev = before;
    else l.last = before;
    l.t -= n;
}

void siz(list& l){
    printf("%d\n", l.t);
}

void ge(list& l){
    int in;
    scanf("%d", &in);
    printf("%d\n", find(l, in)->el);
}

void se(list& l){
    int in, newval;
    scanf("%d %d", &in, &newval);
    find(l, in)->el = newval;
}

void pri(list& l){
    cout << l << "\n";
}

int main(){
    list l;
    int Q;
    if(scanf("%d", &Q) != 1) return 0;
    char que[10];

    while(Q--){
        scanf("%s", que);
        if(que[0] == 'i') ins(l);
        else if(que[0] == 'e') era(l);
        else if(que[0] == 'g') ge(l);
        else if(que[0] == 'p') pri(l);
        else if(que[0] == 's'){
            if(que[1] == 'i') siz(l);
            else se(l);
        }
    }

    return 0;
}