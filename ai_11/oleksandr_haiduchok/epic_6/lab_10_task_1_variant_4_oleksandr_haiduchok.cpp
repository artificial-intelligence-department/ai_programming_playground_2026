#include <iostream>
#include <cstdio>
using namespace std;
struct point{
    int key;
    point *next;
    point(){
        key = 0;
        next = NULL;
    }
    point(int val){
        key = val;
        next = NULL;
    }
};
point* makepoint(int n){
    point *first;
    first = NULL;
    for(int i = n; i > 0; i--){
        point *p = new point;
        p->key = i;
        p->next=first;
        first=p;
    }
    return first;
}
point* printpoint(point *first){
    if(first == NULL){
        printf("Список пустий!");
        return NULL;
    }
    point *p = first;
    while(p!= NULL){
        printf("%d ", p->key);
        p=p->next;
    }
    printf("\n");
    return first;
}
void addpoint(point *&first, int b, int k, int *num, int &n){
    point *current = first;
    point *prev = NULL;
    if(b < 1 || b > n + 1 || k <= 0){
        return;
    }
    for(int i = 1; i < b; i++){
        prev = current;
        current= current->next;
    }
        for(int h = 0; h < k; h++){
            point *newnode = new point(num[h]);
            if(prev == NULL){
                newnode->next = first;
                first = newnode;
                prev = newnode;
            }
            else{
            newnode->next = current;
            prev->next = newnode;
            prev = newnode;
            }
    }
    n += k;
}
void deletenum(point *&first, int b, int &n){
    if(first == NULL || b < 1 || b > n){
        return;
    }
    point*p = first;
    point *prev = NULL;
    for(int i = 1; i < b; i++){
        prev = p;
        p = p->next;
    };
    if(p == NULL){
        return;
    };
    if(prev == NULL){
        first = p->next;
    }
    else{
        prev->next = p->next;
    }
    delete p;
    n -= 1;
}
void deletepoint(point *&first, int n){
    point *p = first;
    while(p != NULL){
        point *next = p->next;
        delete p;
        p = next;
    }
    first = NULL;
}
int main(){
    int n = 0;
    cout << "Розмір списку:";
    cin >> n;
    cout << "Який елемент видалити?: ";
    int pun = 0;
    cin >> pun;
    cout << "Яку кількість елементів додати?: ";
    int k = 0;
    cin >> k;
    cout << "Введіть елементи: ";
    int *num = new int[k];
    for(int j = 0; j < k; j++){
        cin >> num[j];
    }
    point *gen = makepoint(n);
    printpoint(gen);
    deletenum(gen, pun, n);
    printpoint(gen);
    addpoint(gen, pun, k, num, n);
    printpoint(gen);
    deletepoint(gen, n);
    printpoint(gen);
    delete[] num;

    return 0;
}