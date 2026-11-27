/*
Епік 6. Завдання з Алготестера. Лабораторна робота №78. Завдання №1. Варіант №1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
using namespace std;

struct Node {
    int key;
    Node* next;
    Node* prev;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
};

Node* findNode(List& list, int index) {

    Node* p = list.head;

    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    return p;
}

void insert (List& list, int index, int n, const int* arr) {

    if (index < 0 || index > list.size) return;

    Node* current;

    if (index == list.size) current = nullptr;
    else current = findNode(list, index);

    for (int i = 0; i<n; i++) {

        Node* newNode = new Node;
        newNode->key = arr[i];

        if (current == nullptr) {

            newNode->next = nullptr;
            newNode->prev = list.tail;

            if (list.tail != nullptr) list.tail->next = newNode;
            else list.head = newNode;

            list.tail = newNode;
        }

        else {
            newNode->next = current;
            newNode->prev = current->prev;
       
            if (current->prev != nullptr) current->prev->next = newNode;
            else list.head = newNode;

            current->prev = newNode;
        }

        list.size++;
    }
}

void erase (List& list, int index, int n) {

    if (index < 0 || n < 0 || index > list.size || n > list.size) return;
    if (n==0) return;

    Node* current = findNode(list, index);

    for (int i = 0; i<n; i++) {

        Node* nextN = current->next;

        if (current->prev != nullptr) current->prev->next = current->next;
        else list.head = current->next;

        if (current->next != nullptr) current->next->prev = current->prev;
        else list.tail = current->prev;
        
        delete current;
        current = nextN;

        list.size--;
    }
}

int get (List& list, int index) {

    Node* node = findNode(list, index);
    return node->key;

}

void set (List& list, int index, int value) {

    Node* node = findNode(list, index);
    node->key = value;

}

ostream& operator<<(ostream& out, const List& list) {

    Node* p = list.head;

    while (p != nullptr) {

        out << p->key;
        if (p->next != nullptr) out << " ";
        p = p->next;
    }

    return out;
}

void deleteList (List& list) {

    Node* p = list.head;

    while (p != nullptr) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }

    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

int main () {

    int Q;
    cin >> Q;

    List list;

    for (int i = 0; i<Q; i++) {

        string choice;
        cin >> choice;

        if (choice == "insert") {

            int index, N;
            cin >> index >> N;

            int* arr = new int[N];

            for (int i = 0; i<N; i++) {
                cin >> arr[i];
            }

            insert (list, index, N, arr);
            delete[] arr;
        }
   
        else if (choice == "erase") {

            int index, n;
            cin >> index >> n;

            erase(list, index, n);
        }

        else if (choice == "size") cout << list.size << "\n";
   
        else if (choice == "get") {

            int index;
            cin >> index;

            cout << get(list, index) << "\n";
        }
    
        else if (choice == "set") {

            int index, value;
            cin >> index >> value;
        
            set(list, index, value);
        }
    
        else if (choice == "print") cout << list << "\n";
    
    }

    deleteList(list);

    return 0;
}