#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T key;
        Node *prev;
        Node *next;
        Node(const T &value) : key(value), prev(nullptr), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int count;

    Node *nodeAt(int index) const {
        Node *p;
        if (index < count / 2) {
            p = head;
            for (int i = 0; i < index; i++) p = p->next;
        } else {
            p = tail;
            for (int i = count - 1; i > index; i--) p = p->prev;
        }
        return p;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        Node *cur = head;
        while (cur != nullptr) {
            Node *nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    int size() const { return count; }

    void insert(int index, int n, const T *values) {
        if (n == 0) return;

        Node *right = (index == count) ? nullptr : nodeAt(index);
        Node *left = (right != nullptr) ? right->prev : tail;

        for (int i = 0; i < n; i++) {
            Node *node = new Node(values[i]);
            node->prev = left;
            if (left != nullptr) left->next = node;
            else head = node;
            left = node;
        }

        left->next = right;
        if (right != nullptr) right->prev = left;
        else tail = left;

        count += n;
    }

    void erase(int index, int n) {
        Node *p = nodeAt(index);
        for (int i = 0; i < n; i++) {
            Node *nxt = p->next;

            if (p->prev != nullptr) p->prev->next = p->next;
            else head = p->next;

            if (p->next != nullptr) p->next->prev = p->prev;
            else tail = p->prev;

            delete p;
            count--;
            p = nxt;
        }
    }

    T get(int index) const {
        return nodeAt(index)->key;
    }

    void set(int index, const T &value) {
        nodeAt(index)->key = value;
    }

    friend ostream &operator<<(ostream &out, const DoublyLinkedList &list) {
        for (Node *p = list.head; p != nullptr; p = p->next) {
            out << p->key;
            if (p->next != nullptr) out << " ";
        }
        out << "\n";
        return out;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DoublyLinkedList<int> list;
    int Q;
    cin >> Q;

    for (int q = 0; q < Q; q++) {
        char cmd[16];
        cin >> cmd;

        if (strcmp(cmd, "insert") == 0) {
            int index, n;
            cin >> index >> n;
            int *values = new int[n];
            for (int i = 0; i < n; i++) cin >> values[i];
            list.insert(index, n, values);
            delete[] values;
        } else if (strcmp(cmd, "erase") == 0) {
            int index, n;
            cin >> index >> n;
            list.erase(index, n);
        } else if (strcmp(cmd, "size") == 0) {
            cout << list.size() << "\n";
        } else if (strcmp(cmd, "get") == 0) {
            int index;
            cin >> index;
            cout << list.get(index) << "\n";
        } else if (strcmp(cmd, "set") == 0) {
            int index, x;
            cin >> index >> x;
            list.set(index, x);
        } else if (strcmp(cmd, "print") == 0) {
            cout << list;
        }
    }

    return 0;
}
