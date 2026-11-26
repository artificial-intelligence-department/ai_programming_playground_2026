#include <iostream>
#include <cstring>
using namespace std;


struct Node {
    char *key;
    Node *prev;
    Node *next;
};
Node *head = nullptr;
Node *tail = nullptr;

Node *makeNode(char *s) {
    Node *n = new Node;
    n->key = new char[strlen(s) + 1];
    strcpy(n->key, s);
    n->prev = nullptr;
    n->next = nullptr;
    return n;
}

void pushFront(char *s) {
    Node *n = makeNode(s);
    n->next = head;
    if (head != nullptr) head->prev = n;
    head = n;
}

void printList() {
    if (head == nullptr) {
        cout << "Список порожній!" << endl;
        return;
    }
    Node *p = head;
    while (p != nullptr) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << endl;
}

void destroyList() {
    while (head != nullptr) {
        Node *t = head;
        head = head->next;
        delete[] t->key;
        delete t;
    }
    tail = nullptr;
}

void addK(int k) {
    char buf[100];
    for (int i = 0; i < k; i++) {
        cin >> buf;
        pushFront(buf);
    }
}
void deleteAt(int num) {
    Node *p = head;
    for (int i = 1; i < num && p != nullptr; i++) {
        p = p->next;
    }
    if (num < 1 || p == nullptr) {
        cout << "Елемента з таким номером немає" << endl;
        return;
    }
    if (p->prev != nullptr) p->prev->next = p->next;
    else head = p->next;
    if (p->next != nullptr) p->next->prev = p->prev;
    else tail = p->prev;
    delete[] p->key;
    delete p;
}

int main() {
    int n;
    cout << "Скільки слів у списку: ";
    cin >> n;
    addK(n);
    cout << "Список: ";
    printList();

    int k;
    cout << "Скільки слів додати на початок: ";
    cin >> k;
    addK(k);
    cout << "Список: ";
    printList();

    int num;
    cout << "Який номер видалити: ";
    cin >> num;
    deleteAt(num);
    cout << "Список: ";
    printList();

    destroyList();
    cout << "Список знищено. Список: ";
    printList();
}