
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class Node {
public:
    T value;
    Node<T>* left;
    Node<T>* right;
};

template <typename T>
class Tree {
public:
    Node<T>* root = nullptr;
    int count = 0;

    void clear(Node<T>* node) {
        if (node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    ~Tree() { clear(root); }

    bool contains(T v) {
        Node<T>* cur = root;
        while (cur != nullptr) {
            if (v == cur->value)
                return true;
            if (v < cur->value)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return false;
    }

    void insert(T v) {
        if (contains(v))
            return;

        Node<T>* n = new Node<T>{v, nullptr, nullptr};
        count++;

        if (root == nullptr) {
            root = n;
            return;
        }

        Node<T>* cur = root;
        while (true) {
            if (v < cur->value) {
                if (cur->left == nullptr) {
                    cur->left = n;
                    return;
                }
                cur = cur->left;
            } else {
                if (cur->right == nullptr) {
                    cur->right = n;
                    return;
                }
                cur = cur->right;
            }
        }
    }

    int size() { return count; }
};

template <typename T>
void printNode(ostream& out, Node<T>* node, bool& first) {
    if (node == nullptr)
        return;
    printNode(out, node->left, first);
    if (!first)
        out << " ";
    out << node->value;
    first = false;
    printNode(out, node->right, first);
}

template <typename T>
ostream& operator<<(ostream& out, const Tree<T>& t) {
    bool first = true;
    printNode(out, t.root, first);
    return out;
}

int main() {
    Tree<int> tree;
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char cmd[20];
        cin >> cmd;

        if (strcmp(cmd, "insert") == 0) {
            int v;
            cin >> v;
            tree.insert(v);
        }
        else if (strcmp(cmd, "contains") == 0) {
            int v;
            cin >> v;
            if (tree.contains(v))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else if (strcmp(cmd, "size") == 0) {
            cout << tree.size() << endl;
        }
        else if (strcmp(cmd, "print") == 0) {
            cout << tree << endl;
        }
    }
    return 0;
}