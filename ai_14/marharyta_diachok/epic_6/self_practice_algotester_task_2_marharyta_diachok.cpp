/*  
Задача: Self-practice. Завдання №2.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>

using namespace std;

struct Node {
    int city;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
};

const int MAXN = 100005;
LinkedList* city_list[MAXN];
int vidpovidi[MAXN];

int main() {
int n, m;
if (!(cin >> n >> m)) return 0;

for (int i = 1; i <= n; ++i) {
    Node* node = new Node{i, nullptr};
    city_list[i] = new LinkedList{node, node, 1};
    }

int components = n;

for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;

LinkedList* list_a = city_list[a];
LinkedList* list_b = city_list[b];

if (list_a != list_b) {
    if (list_a->size < list_b->size) {
        LinkedList* temp = list_a;
        list_a = list_b;
        list_b = temp;}

Node* curr = list_b->head;
while (curr != nullptr) {
    city_list[curr->city] = list_a;
    curr = curr->next;}

list_a->tail->next = list_b->head;
list_a->tail = list_b->tail;
list_a->size += list_b->size;

delete list_b;
components--;}

    vidpovidi[i] = components;
}

for (int i = 0; i < m; ++i) {
    cout << vidpovidi[i] << "\n";
}

for(int i = 1; i <= n; ++i) {
    if(city_list[i]->head->city == i) {
        Node* curr = city_list[i]->head;
        while(curr != nullptr) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }
}
    return 0;
}
