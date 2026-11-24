#include <bits/stdc++.h>

using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
};

// повертає вузол за індексом, йдучи з ближчого кінця списку
Node* getNode(const List& list, int index) {
    if (index < list.size / 2) {
        Node* p = list.head;
        for (int i = 0; i < index; i++) p = p->next;
        return p;
    }
    Node* p = list.tail;
    for (int i = list.size - 1; i > index; i--) p = p->prev;
    return p;
}

// вставляє новий вузол перед вузлом before (якщо before == nullptr - у кінець)
void insertBefore(List& list, Node* before, int value) {
    Node* node = new Node;
    node->value = value;
    node->next = before;
    node->prev = (before != nullptr) ? before->prev : list.tail;

    if (node->prev != nullptr) node->prev->next = node;
    else list.head = node;

    if (before != nullptr) before->prev = node;
    else list.tail = node;

    list.size++;
}

// вставляє масив arr з n елементів так, щоб перший з них став на позицію index
void insert(List& list, int index, const int* arr, int n) {
    Node* before = (index < list.size) ? getNode(list, index) : nullptr;
    for (int i = 0; i < n; i++) {
        insertBefore(list, before, arr[i]);
    }
}

// видаляє n елементів, починаючи з індексу index
void erase(List& list, int index, int n) {
    if (n <= 0) return;
    Node* p = getNode(list, index);
    for (int i = 0; i < n; i++) {
        Node* next = p->next;

        if (p->prev != nullptr) p->prev->next = p->next;
        else list.head = p->next;

        if (p->next != nullptr) p->next->prev = p->prev;
        else list.tail = p->prev;

        delete p;
        list.size--;
        p = next;
    }
}

ostream& operator<<(ostream& os, const List& list) {
    for (Node* p = list.head; p != nullptr; p = p->next) {
        os << p->value << " ";
    }
    return os;
}

void clear(List& list) {
    Node* p = list.head;
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    List list;
    int q;
    cin >> q;

    char cmd[16];
    for (int t = 0; t < q; t++) {
        cin >> cmd;

        if (strcmp(cmd, "insert") == 0) {
            int index, n;
            cin >> index >> n;
            int* arr = new int[n];
            for (int i = 0; i < n; i++) cin >> arr[i];
            insert(list, index, arr, n);
            delete[] arr;
        } else if (strcmp(cmd, "erase") == 0) {
            int index, n;
            cin >> index >> n;
            erase(list, index, n);
        } else if (strcmp(cmd, "size") == 0) {
            cout << list.size << "\n";
        } else if (strcmp(cmd, "get") == 0) {
            int index;
            cin >> index;
            cout << getNode(list, index)->value << "\n";
        } else if (strcmp(cmd, "set") == 0) {
            int index, value;
            cin >> index >> value;
            getNode(list, index)->value = value;
        } else if (strcmp(cmd, "print") == 0) {
            cout << list << "\n";
        }
    }

    clear(list);
    return 0;
}
