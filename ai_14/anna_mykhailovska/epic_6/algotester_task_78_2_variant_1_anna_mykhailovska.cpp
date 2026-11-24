/*
    Задача: Algotester Lab 78(2)
    Варіант: 1
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
struct Node { T value; Node<T>* prev; Node<T>* next;};

template <typename T>
class List {
public:
    Node<T>* head = nullptr; Node<T>* tail = nullptr; int count = 0;

    Node<T>* find(int index) {
        Node<T>* p = head;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p;
    }

    void insert(int index, T value) {
        Node<T>* right = find(index);
        Node<T>* left;

        if (right != nullptr)
            left = right->prev;
        else
            left = tail;

        Node<T>* p = new Node<T>;
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
        Node<T>* p = find(index);

        for (int i = 0; i < n; i++) {
            Node<T>* next = p->next;

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

    T get(int index) {
        return find(index)->value;
    }

    void set(int index, T value) {
        find(index)->value = value;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const List<T>& list) {
    Node<T>* p = list.head;
    while (p != nullptr) {
        os << p->value;

        if (p->next != nullptr)
            os << ' ';

        p = p->next;
    }
    return os;
}

int main() {
    List<int> list;
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