/*
    Задача: Lab 10
    Варіант: 20
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Node {char* key; Node* prev; Node* next;};

Node* head = nullptr;
Node* tail = nullptr;

//Функція для створення нового вузла з копією рядка
Node* newNode(const char* text) {
    Node* p = new Node;

    p->key = new char[strlen(text) + 1];
    strcpy(p->key, text);

    p->prev = nullptr;
    p->next = nullptr;

    return p;
}

//Функція додавання на початок
void pushFront(const char* text) {
    Node* p = newNode(text);
    p->next = head;

    if (head != nullptr)
        head->prev = p;
    else
        tail = p;

    head = p;
}

//Функція додавання в кінець
void pushBack(const char* text) {
    Node* p = newNode(text);
    p->prev = tail;

    if (tail != nullptr)
        tail->next = p;
    else
        head = p;

    tail = p;
}

//Функція для створення списку
void createList(int n) {
    char text[100];

    for (int i = 0; i < n; i++) {
        cout << "Введіть рядок " << i + 1 << ": ";
        cin >> setw(100) >> text;
        pushBack(text);
    }
}

//Функція друку списку
void printList() {
    if (head == nullptr) {
        cout << "Список порожній\n";
        return;
    }

    cout << "Список: ";
    for (Node* p = head; p != nullptr; p = p->next)
        cout << p->key << " ";
    cout << "\n";
}

//Функція щоб видалити перший елемент із заданим ключем
void deleteByKey(const char* key) {
    Node* p = head;

    while (p != nullptr && strcmp(p->key, key) != 0)
        p = p->next;

    if (p == nullptr) {
        cout << "Елемент не знайдено\n";
        return;
    }

    if (p->prev != nullptr)
        p->prev->next = p->next;
    else
        head = p->next;

    if (p->next != nullptr)
        p->next->prev = p->prev;
    else
        tail = p->prev;

    delete[] p->key;
    delete p;
}

//Функція щоб знищити весь список
void deleteList() {
    while (head != nullptr) {
        Node* p = head;
        head = head->next;

        delete[] p->key;
        delete p;
    }
    tail = nullptr;
}

int main() {
    int n, k;
    char text[100];

    cout << "Кількість елементів списку: ";
    if (!(cin >> n) || n < 0)
        return 0;

    createList(n);
    printList();

    cout << "Ключ елемента для видалення: ";
    cin >> setw(100) >> text;

    deleteByKey(text);
    printList();

    cout << "Скільки елементів додати на початок і в кінець: ";
    if (!(cin >> k) || k < 0) {
        deleteList();
        return 0;
    }

    for (int i = 0; i < k; i++) {
        cout << "Новий рядок на початок: ";
        cin >> setw(100) >> text;
        pushFront(text);
        printList();
    }

    for (int i = 0; i < k; i++) {
        cout << "Новий рядок у кінець: ";
        cin >> setw(100) >> text;
        pushBack(text);
        printList();
    }
    deleteList();

    cout << "Після знищення списку:\n";
    printList();

    return 0;
}