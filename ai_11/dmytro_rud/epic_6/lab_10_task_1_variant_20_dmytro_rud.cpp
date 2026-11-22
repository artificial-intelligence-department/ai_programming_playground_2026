#include <iostream>
#include <cstring>

using namespace std;

struct DNode {
    char *key;
    DNode *prev = nullptr, *next = nullptr;
};

struct List {
    DNode *head = nullptr, *tail = nullptr;
};

ostream& operator<<(ostream& out, const List& L) {
    DNode *p = L.head;
    if (p == nullptr) out << "Список порожній";
    while (p != nullptr) {
        out << p->key;
        if (p->next != nullptr) out << " ";
        p = p->next;
    }
    out << "\n";
    return out;
}

int size(const List& L) {
    int n = 0;
    DNode *p = L.head;
    while (p != nullptr) {
        n++;
        p = p->next;
    }
    return n;
}

void insert(List& L, int index, const char *value) {
    DNode *p = L.head;
    for (int j = 0; j < index && p != nullptr; j++) {
        p = p->next;
    }
    DNode *left = (p != nullptr) ? p->prev : L.tail;

    int length = 0;
    while (value[length] != '\0') length++;
    char *copy = new char[length + 1];
    for (int j = 0; j <= length; j++) copy[j] = value[j];

    DNode *newNode = new DNode{copy, left, p};
    if (left != nullptr) left->next = newNode;
    else L.head = newNode;
    if (p != nullptr) p->prev = newNode;
    else L.tail = newNode;
}

void erase(List& L, int index) {
    DNode *p = L.head;
    for (int j = 0; j < index && p != nullptr; j++) {
        p = p->next;
    }
    if (p == nullptr) return;

    if (p->prev != nullptr) p->prev->next = p->next;
    else L.head = p->next;
    if (p->next != nullptr) p->next->prev = p->prev;
    else L.tail = p->prev;

    delete[] p->key;
    delete p;
}

int findIndex(const List& L, const char *wanted) {
    int index = 0;
    for (DNode *p = L.head; p != nullptr; p = p->next) {
        if (strcmp(p->key, wanted) == 0) return index;
        index++;
    }
    return -1;
}

void destroy(List& L) {
    DNode *cur = L.head;
    while (cur != nullptr) {
        DNode *nxt = cur->next;
        delete[] cur->key;
        delete cur;
        cur = nxt;
    }
    L.head = nullptr;
    L.tail = nullptr;
}

int main() {
    List L;
    int n;
    cin >> n;

    char word[256];
    for (int i = 0; i < n; i++) {
        cin >> word;
        insert(L, size(L), word);
    }
    cout << L;

    char wanted[256];
    cin >> wanted;
    int index = findIndex(L, wanted);
    if (index != -1) erase(L, index);
    cout << L;

    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> word;
        insert(L, 0, word);
        cout << L;
    }
    for (int i = 0; i < K; i++) {
        cin >> word;
        insert(L, size(L), word);
        cout << L;
    }

    destroy(L);
    return 0;
}
