#include <bits/stdc++.h>

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

    // повертає вузол за індексом, йдучи з ближчого кінця списку
    Node* getNode(int index) const {
        if (index < count / 2) {
            Node* p = head;
            for (int i = 0; i < index; i++) p = p->next;
            return p;
        }
        Node* p = tail;
        for (int i = count - 1; i > index; i--) p = p->prev;
        return p;
    }

    // вставляє новий вузол перед вузлом before (якщо before == nullptr - у кінець)
    void insertBefore(Node* before, const T& value) {
        Node* node = new Node;
        node->value = value;
        node->next = before;
        node->prev = (before != nullptr) ? before->prev : tail;

        if (node->prev != nullptr) node->prev->next = node;
        else head = node;

        if (before != nullptr) before->prev = node;
        else tail = node;

        count++;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    // вставляє масив arr з n елементів так, щоб перший з них став на позицію index
    void insert(int index, const T* arr, int n) {
        Node* before = (index < count) ? getNode(index) : nullptr;
        for (int i = 0; i < n; i++) {
            insertBefore(before, arr[i]);
        }
    }

    // видаляє n елементів, починаючи з індексу index
    void erase(int index, int n) {
        if (n <= 0) return;
        Node* p = getNode(index);
        for (int i = 0; i < n; i++) {
            Node* next = p->next;

            if (p->prev != nullptr) p->prev->next = p->next;
            else head = p->next;

            if (p->next != nullptr) p->next->prev = p->prev;
            else tail = p->prev;

            delete p;
            count--;
            p = next;
        }
    }

    int size() const {
        return count;
    }

    T& operator[](int index) {
        return getNode(index)->value;
    }

    const T& operator[](int index) const {
        return getNode(index)->value;
    }

    void clear() {
        Node* p = head;
        while (p != nullptr) {
            Node* next = p->next;
            delete p;
            p = next;
        }
        head = tail = nullptr;
        count = 0;
    }

    friend ostream& operator<<(ostream& os, const DoublyLinkedList& list) {
        for (Node* p = list.head; p != nullptr; p = p->next) {
            os << p->value << " ";
        }
        return os;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    DoublyLinkedList<int> list;
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
            list.insert(index, arr, n);
            delete[] arr;
        } else if (strcmp(cmd, "erase") == 0) {
            int index, n;
            cin >> index >> n;
            list.erase(index, n);
        } else if (strcmp(cmd, "size") == 0) {
            cout << list.size() << "\n";
        } else if (strcmp(cmd, "get") == 0) {
            int index;
            cin >> index;
            cout << list[index] << "\n";
        } else if (strcmp(cmd, "set") == 0) {
            int index, value;
            cin >> index >> value;
            list[index] = value;
        } else if (strcmp(cmd, "print") == 0) {
            cout << list << "\n";
        }
    }

    return 0;
}
