/*
Задача:  Лабораторна робота 10
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Node {
    char* key;
    Node* prev;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

List createList();
Node* createNode(const char* key);
void append(List& list, const char* key);
void printList(List& list);
void deleteNode(List& list, Node* node);
int removeDuplicates(List& list);
bool insertAfter(List& list, const char* target, const char* value);
void destroyList(List& list);

int main() {
    List list = createList();
    int count;
    cout << "Кількість початкових елементів (0 або більше): ";
    if (!(cin >> count) || count < 0) {
        cout << "Помилка: введіть ціле невід'ємне число.\n";
        return 0;
    }
    string key;
    getline(cin, key);
    for (int i = 0; i < count; i++) {
        cout << "Ключ: ";
        if (!getline(cin, key)) {
            destroyList(list);
            return 0;
        }
        append(list, key.c_str());
        printList(list);
    }
    cout << "\nПочатковий список:\n";
    printList(list);
    cout << "\nВидалення повторів (перше входження залишається):\n";
    int removed = removeDuplicates(list);
    cout << "Видалено: " << removed << '\n';
    printList(list);
    if (list.head) {
        string target, value;
        cout << "\nПісля якого ключа вставити елемент: ";
        if (!getline(cin, target)) {
            destroyList(list);
            return 0;
        }
        cout << "Новий ключ: ";
        if (!getline(cin, value)) {
            destroyList(list);
            return 0;
        }
        if (insertAfter(list, target.c_str(), value.c_str())) {
            cout << "Після вставки:\n";
            printList(list);
        } else cout << "Ключ не знайдено. Список не змінено.\n";
    }
    destroyList(list);
    cout << "\nСписок знищено:\n";
    printList(list);
    return 0;
}

List createList() {
    List list;
    list.head = nullptr;
    list.tail = nullptr;
    return list;
}

Node* createNode(const char* key) {
    Node* node = new Node;
    node->key = new char[strlen(key) + 1];
    strcpy(node->key, key);
    node->prev = nullptr;
    node->next = nullptr;
    return node;
}

void append(List& list, const char* key) {
    Node* node = createNode(key);
    node->prev = list.tail;
    if (list.tail) list.tail->next = node;
    else list.head = node;
    list.tail = node;
}

void printList(List& list) {
    if (!list.head) {
        cout << "Список порожній.\n";
        return;
    }
    for (Node* p = list.head; p; p = p->next) {
        cout << '[' << p->key << ']';
        if (p->next) cout << " <-> ";
    }
    cout << '\n';
}

void deleteNode(List& list, Node* node) {
    if (node->prev) node->prev->next = node->next;
    else list.head = node->next;
    if (node->next) node->next->prev = node->prev;
    else list.tail = node->prev;
    delete[] node->key;
    delete node;
}

int removeDuplicates(List& list) {
    int removed = 0;
    for (Node* first = list.head; first; first = first->next) {
        Node* p = first->next;
        while (p) {
            Node* next = p->next;
            if (strcmp(first->key, p->key) == 0) {
                deleteNode(list, p);
                removed++;
                printList(list);
            }
            p = next;
        }
    }
    return removed;
}

bool insertAfter(List& list, const char* target, const char* value) {
    Node* p = list.head;
    while (p && strcmp(p->key, target) != 0) p = p->next;
    if (!p) return false;
    Node* node = createNode(value);
    node->prev = p;
    node->next = p->next;
    if (p->next) p->next->prev = node;
    else list.tail = node;
    p->next = node;
    return true;
}

void destroyList(List& list) {
    while (list.head) deleteNode(list, list.head);
}
