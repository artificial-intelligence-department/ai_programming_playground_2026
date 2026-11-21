
#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char* key;
    Node* next;
    Node* prev;
};

struct List {
    int size;
    Node* head;
    Node* tail;
};

List* createList() {
    List* list = new List;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node* makeNode(const char* text) {
    Node* n = new Node;
    n->key = new char[strlen(text) + 1];
    strcpy(n->key, text);
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void pushBack(List* list, const char* text) {
    Node* n = makeNode(text);
    n->prev = list->tail;
    if (list->tail != NULL)
        list->tail->next = n;
    else
        list->head = n;
    list->tail = n;
    list->size++;
}

void fillList(List* list) {
    int n;
    char buf[100];
    cout << "Скільки елементів буде в списку? ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Елемент " << i << ": ";
        cin >> buf;
        pushBack(list, buf);
    }
}

void printList(List* list) {
    if (list->head == NULL) {
        cout << "Список порожній!" << endl;
        return;
    }
    Node* p = list->head;
    while (p != NULL) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << endl;
}

Node* getNth(List* list, int number) {
    if (number < 1 || number > list->size)
        return NULL;
    Node* p = list->head;
    for (int i = 1; i < number; i++)
        p = p->next;
    return p;
}

Node* findByKey(List* list, const char* key) {
    Node* p = list->head;
    while (p != NULL) {
        if (strcmp(p->key, key) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

bool deleteByNumber(List* list, int number) {
    Node* p = getNth(list, number);
    if (p == NULL)
        return false;

    if (p->prev != NULL)
        p->prev->next = p->next;
    else
        list->head = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;
    else
        list->tail = p->prev;

    delete[] p->key;
    delete p;
    list->size--;
    return true;
}

void insertBefore(List* list, Node* target, const char* text) {
    Node* n = makeNode(text);
    n->next = target;
    n->prev = target->prev;
    if (target->prev != NULL)
        target->prev->next = n;
    else
        list->head = n;
    target->prev = n;
    list->size++;
}

void insertAfter(List* list, Node* target, const char* text) {
    Node* n = makeNode(text);
    n->prev = target;
    n->next = target->next;
    if (target->next != NULL)
        target->next->prev = n;
    else
        list->tail = n;
    target->next = n;
    list->size++;
}

bool addBeforeKey(List* list, const char* key, int k) {
    Node* target = findByKey(list, key);
    if (target == NULL)
        return false;
    char buf[100];
    cout << "Введіть " << k << " елементів для додавання ПЕРЕД \"" << key << "\":" << endl;
    for (int i = 1; i <= k; i++) {
        cout << "Елемент " << i << ": ";
        cin >> buf;
        insertBefore(list, target, buf);
    }
    return true;
}

bool addAfterKey(List* list, const char* key, int k) {
    Node* target = findByKey(list, key);
    if (target == NULL)
        return false;
    char buf[100];
    cout << "Введіть " << k << " елементів для додавання ПІСЛЯ \"" << key << "\":" << endl;
    Node* cur = target;
    for (int i = 1; i <= k; i++) {
        cout << "Елемент " << i << ": ";
        cin >> buf;
        insertAfter(list, cur, buf);
        cur = cur->next;
    }
    return true;
}

void deleteList(List* list) {
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;
        delete[] p->key;
        delete p;
        p = next;
    }
    delete list;
}

int main() {
    List* list = createList();
    printList(list);

    fillList(list);
    printList(list);

    int number;
    cout << "Введіть номер елемента для видалення: ";
    cin >> number;
    if (deleteByNumber(list, number))
        printList(list);
    else
        cout << "Немає елемента з таким номером!" << endl;

    char key[100];
    int k;
    cout << "Введіть ключ: ";
    cin >> key;
    cout << "Введіть K: ";
    cin >> k;

    if (addBeforeKey(list, key, k)) {
        printList(list);
        addAfterKey(list, key, k);
        printList(list);
    }
    else
        cout << "Елемента з таким ключем немає!" << endl;

    deleteList(list);
    return 0;
}