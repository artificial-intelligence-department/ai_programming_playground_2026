#include <iostream>
#include <cstring>

using namespace std;

struct DNode {
    int key;
    DNode *prev = nullptr, *next = nullptr;
};

struct List {
    DNode *head = nullptr, *tail = nullptr;
};

ostream& operator<<(ostream& out, const List& L) {
    DNode *p = L.head;
    while (p != nullptr) {
        out << p->key;
        if (p->next != nullptr) {
            out << " ";
        }
        p = p->next;
    }
    out << "\n";
    return out;
}

int main() {

    List L;
    int Q;
    if (!(cin >> Q)) return 0;

    for (int i = 0; i < Q; i++) {
        char comand[16];
        cin >> comand;

        if (strcmp(comand, "insert") == 0) {
            int index, N;
            cin >> index >> N;

            DNode *p = L.head;
            for (int j = 0; j < index && p != nullptr; j++) {
                p = p->next;
            }

            DNode *left = (p != nullptr) ? p->prev : L.tail;

            for (int j = 0; j < N; j++) {
                int val;
                cin >> val;
                DNode *newNode = new DNode{val, left, nullptr};
                if (left != nullptr) {
                    left->next = newNode;
                } else {
                    L.head = newNode;
                }
                left = newNode;
            }

            if (N > 0) {
                left->next = p;
                if (p != nullptr) {
                    p->prev = left;
                } else {
                    L.tail = left;
                }
            }
        }
        else if (strcmp(comand, "erase") == 0) {
            int index, n;
            cin >> index >> n;

            if (n == 0) continue;

            DNode *p = L.head;
            for (int j = 0; j < index && p != nullptr; j++) {
                p = p->next;
            }
            if (p == nullptr) continue;

            int N = 0;
            while (p != nullptr && N < n) {
                DNode *nextNode = p->next;

                if (p->prev != nullptr) p->prev->next = p->next;
                else L.head = p->next;

                if (p->next != nullptr) p->next->prev = p->prev;
                else L.tail = p->prev;

                delete p;
                p = nextNode;
                N++;
            }
        }
        else if (strcmp(comand, "size") == 0) {
            int n = 0;
            DNode *p = L.head;
            while (p != nullptr) {
                n++;
                p = p->next;
            }
            cout << n << "\n";
        }
        else if (strcmp(comand, "get") == 0) {
            int index;
            cin >> index;
            DNode *p = L.head;
            for (int j = 0; j < index && p != nullptr; j++) {
                p = p->next;
            }
            if (p != nullptr) {
                cout << p->key << "\n";
            }
        }
        else if (strcmp(comand, "set") == 0) {
            int index, x;
            cin >> index >> x;
            DNode *p = L.head;
            for (int j = 0; j < index && p != nullptr; j++) {
                p = p->next;
            }
            if (p != nullptr) {
                p->key = x;
            }
        }
        else if (strcmp(comand, "print") == 0) {
            cout << L;
        }
    }

    DNode *cur = L.head;
    while (cur != nullptr) {
        DNode *nxt = cur->next;
        delete cur;
        cur = nxt;
    }

    return 0;
}