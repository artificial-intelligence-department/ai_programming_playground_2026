#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

struct BST {
    Node* root = nullptr;
    int count = 0;

    Node* insertRec(Node* node, int v) {
        if (node == nullptr) {
            count++;
            return new Node(v);
        }
        if (v < node->val) {
            node->left = insertRec(node->left, v);
        } else if (v > node->val) {
            node->right = insertRec(node->right, v);
        }
        return node;
    }

    void insert(int v) {
        root = insertRec(root, v);
    }

    bool contains(int v) const {
        Node* cur = root;
        while (cur != nullptr) {
            if (v == cur->val) {
                return true;
            }
            if (v < cur->val) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return false;
    }

    int size() const {
        return count;
    }

    void printRec(Node* node, ostream& os, bool& first) const {
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

    friend ostream& operator<<(ostream& os, const BST& t) {
        bool first = true;
        t.printRec(t.root, os, first);
        return os;
    }

    void destroy(Node* node) {
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
    BST tree;
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