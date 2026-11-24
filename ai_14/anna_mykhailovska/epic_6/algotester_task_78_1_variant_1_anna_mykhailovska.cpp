/*
    Задача: Algotester Lab 78(1)
    Варіант: 1
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
#include <cstring>
using namespace std;

struct Node { int value; Node* prev; Node* next;};

struct List {Node* head = nullptr; Node* tail = nullptr; int count = 0;

    Node* find(int index) {
        Node* p = head;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p;
    }

    void insert(int index, int value) {
        Node* right = find(index);
        Node* left;

        if (right != nullptr)
            left = right->prev;
        else
            left = tail;

        Node* p = new Node;
        p->value = value;
        p->prev = left;
        p->next = right;

        if (left != nullptr)
            left->next = p;
        else
            head = p;

        if (right != nullptr)
            right->prev = p;
        else
            tail = p;

        count++;
    }

    void erase(int index, int n) {
        Node* p = find(index);

        for (int i = 0; i < n; i++) {
            Node* next = p->next;

            if (p->prev != nullptr)
                p->prev->next = p->next;
            else
                head = p->next;

            if (p->next != nullptr)
                p->next->prev = p->prev;
            else
                tail = p->prev;

            delete p;
            p = next;
            count--;
        }
    }

    int size() {
        return count;
    }

    int get(int index) {
        return find(index)->value;
    }

    void set(int index, int value) {
        find(index)->value = value;
    }
};

ostream& operator<<(ostream& os, const List& list) {
    Node* p = list.head;
    while (p != nullptr) {
        os << p->value;

        if (p->next != nullptr)
            os << ' ';

        p = p->next;
    }
    return os;
}

int main() {
    List list;

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char command[10];
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            int index, n, value;
            cin >> index >> n;

            for (int j = 0; j < n; j++) {
                cin >> value;
                list.insert(index + j, value);
            }
        }
        else if (strcmp(command, "erase") == 0) {
            int index, n;
            cin >> index >> n;
            list.erase(index, n);
        }
        else if (strcmp(command, "size") == 0) {
            cout << list.size() << '\n';
        }
        else if (strcmp(command, "get") == 0) {
            int index;
            cin >> index;
            cout << list.get(index) << '\n';
        }
        else if (strcmp(command, "set") == 0) {
            int index, value;
            cin >> index >> value;
            list.set(index, value);
        }
        else if (strcmp(command, "print") == 0) {
            cout << list << '\n';
        }
    }
   
    list.erase(0, list.count);
    return 0;
}