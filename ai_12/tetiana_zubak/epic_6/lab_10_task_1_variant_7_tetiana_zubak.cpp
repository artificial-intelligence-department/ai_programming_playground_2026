/*
Лабораторна робота №10, Варіант 7
Зубак Тетяна
ШІ-12
*/
#include <cstdio>

struct node{int el; node *next; node *prev;};

void clearbuf(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int inputCout(){
    int n;
    printf("Введіть кількість елементів: ");
    while(true){
        if(scanf("%d", &n) != 1){
            printf("Введено не ціле число. Введіть ще раз: ");
            clearbuf();
            continue;
        }
        if(n == 0){
            printf("Список порожній.\n");
            return 0;
        }
        if(n < 1){
            printf("Кількість елементів має бути не менше 1. Введіть ще раз: ");
            continue;
        }
        return n;
    }
}

void addLast(node *&first, node *&last, int a){
    node *p = new node;
    p->el = a;
    p->next = NULL;
    if(first == NULL){
        p->prev = NULL;
        first = p;
        last = p;
    } else{
        last->next = p;
        p->prev = last;
        last = p;
    }
}

void Cin(node *&first, node *&last, int n){
    first = NULL;
    last = NULL;
    int a;
    printf("Введіть елементи списку: ");
    for(int i = 0; i < n; i++){
        while(scanf("%d", &a) != 1){
            printf("Введено не ціле число. Введіть ще раз: ");
            clearbuf();
        }
        addLast(first, last, a);
    }
}

void Cout(node *first, const char *text){
    printf("%s", text);
    node *p = first;
    while(p != NULL){
        printf("%d ", p->el);
        p = p->next;
    }
    printf("\n");
}

int delFirst(node *&first, node *&last){
    node *p = first;
    int val = p->el;
    first = first->next;
    if(first != NULL) first->prev = NULL;
    else last = NULL;
    delete p;
    return val;
}

void res(node *&first, node *&last){
    if(first == NULL){
        printf("Список порожній.\n");
        return;
    }
    int firstl = delFirst(first, last);
    Cout(first, "Список після видалення першого елемента: ");
    addLast(first, last, firstl);
    Cout(first, "Список після додавання першого елемента в кінець: ");
}

void del(node *&first, node *&last){
    node *p;
    while(first != NULL){
        p = first->next;
        delete first;
        first = p;
    }
    last = NULL;
}

int main(){
    int n = inputCout();
    if(n == 0) return 0;
    node *first = NULL, *last = NULL;
    Cin(first, last, n);
    Cout(first, "Початковий список: ");
    res(first, last);
    del(first, last);

    return 0;
}