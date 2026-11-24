#include <stdio.h>
#include <stdlib.h>

// Один елемент однозв'язного списку
struct point {
    int key;        
    point* next;    
};

// Крок 1: створення списку 
point* make_point(int n) {
    point *first = NULL, *p;
    for (int i = n; i > 0; i--) {
        p = new point;
        p->key = i;
        p->next = first;   
        first = p;        
    }
    return first;
}

// Крок 2: друк списку
void print_point(point* first) {
    if (first == NULL) {
        printf("Список порожній\n");
        return;
    }
    for (point* p = first; p != NULL; p = p->next)
        printf("%d ", p->key);
    printf("\n");
}

// Крок 3: видалення k елементів, починаючи з номера num 
point* delete_k(point* first, int num, int k) {
    if (first == NULL || num < 1 || k < 1)
        return first;

    
    if (num == 1) {
        for (int i = 0; i < k && first != NULL; i++) {
            point* t = first;       
            first = first->next;    
            delete t;               
        }
        return first;
    }

    // Шукаємо prev - елемент з номером num-1
    point* prev = first;
    for (int i = 1; i < num - 1; i++) {
        prev = prev->next;
        if (prev == NULL)           
            return first;
    }

    // Видаляємо k елементів після prev 
    for (int j = 0; j < k && prev->next != NULL; j++) {
        point* del = prev->next;    // елемент, який видаляємо
        prev->next = del->next;     // оминаємо його
        delete del;
    }
    return first;
}

// Крок 4: вставка k елементів, починаючи з номера num (нумерація з 1)
point* insert_k(point* first, int num, int k) {
    if (num < 1 || k < 1)
        return first;

    point* prev = NULL;            
    if (num > 1) {
        prev = first;
        for (int i = 1; i < num - 1 && prev != NULL; i++)
            prev = prev->next;
        if (prev == NULL) {         
            printf("Номер поза списком, вставка неможлива\n");
            return first;
        }
    }

    for (int j = 0; j < k; j++) {
        point* p = new point;       
        printf("Ключ нового елемента: ");
        scanf("%d", &p->key);

        if (prev == NULL) {         
            p->next = first;
            first = p;
        } else {                   
            p->next = prev->next;   
            prev->next = p;         
        }
        prev = p;                  
    }
    return first;
}

// Крок 5: знищення всього списку
void delete_list(point* first) {
    while (first != NULL) {
        point* t = first;
        first = first->next;        
        delete t;
    }
}

int main() {
    int n, num, k;
    printf("Кількість елементів: ");
    scanf("%d", &n);

    point* first = make_point(n);
    print_point(first);

    printf("Видалення. Номер, з якого видаляти: ");
    scanf("%d", &num);
    printf("Скільки елементів видалити: ");
    scanf("%d", &k);
    first = delete_k(first, num, k);
    print_point(first);

    printf("Вставка. Номер, з якого вставляти: ");
    scanf("%d", &num);
    printf("Скільки елементів вставити: ");
    scanf("%d", &k);
    first = insert_k(first, num, k);
    print_point(first);

    delete_list(first);
    first = NULL;
    print_point(first);             
    return 0;
}