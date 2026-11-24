#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
struct Node {
    T val;
    Node<T>* left;
    Node<T>* right;

    Node(const T& v) : val(v), left(nullptr), right(nullptr) {
    }
};

template <typename T>
struct BST {
    Node<T>* root = nullptr;
    int count = 0;

    Node<T>* insertRec(Node<T>* node, const T& v) {
        if (node == nullptr) {
            count++;
            return new Node<T>(v);
        }
        if (v < node->val) {
            node->left = insertRec(node->left, v);
        } else if (node->val < v) {
            node->right = insertRec(node->right, v);
        }
        return node;
    }

    void insert(const T& v) {
        root = insertRec(root, v);
    }

    bool contains(const T& v) const {
        Node<T>* cur = root;
        while (cur != nullptr) {
            if (v < cur->val) {
                cur = cur->left;
            } else if (cur->val < v) {
                cur = cur->right;
            } else {
                return true;
            }
        }
        return false;
    }

    int size() const {
        return count;
    }

    void printRec(Node<T>* node, ostream& os, bool& first) const {
        if (node == nullptr) {
            return;
        }
        printRec(node->left, os, first);
        if (first == false) {
            os << ' ';
        }
        os << node->val;
        first = false;
        printRec(node->right, os, first);
    }

    friend ostream& operator<<(ostream& os, const BST<T>& t) {
        bool first = true;
        t.printRec(t.root, os, first);
        return os;
    }

    void destroy(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    ~BST() {
        destroy(root);
    }
};

int main() {
    int q;
    cin >> q;
    BST<int> tree;
    while (q--) {
        char cmd[20];
        cin >> cmd;
        if (strcmp(cmd, "insert") == 0) {
            int v;
            cin >> v;
            tree.insert(v);
        } else if (strcmp(cmd, "contains") == 0) {
            int v;
            cin >> v;
            if (tree.contains(v)) {
                cout << "Yes" << '\n';
            } else {
                cout << "No" << '\n';
            }
        } else if (strcmp(cmd, "size") == 0) {
            cout << tree.size() << '\n';
        } else if (strcmp(cmd, "print") == 0) {
            cout << tree << '\n';
        }
    }
    return 0;
}