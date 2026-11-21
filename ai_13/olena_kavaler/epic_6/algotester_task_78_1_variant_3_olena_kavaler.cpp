
#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root = nullptr;
    int count = 0;

    void clear(Node* node) {
        if (node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    ~Tree() { clear(root); }

    bool contains(int v) {
        Node* cur = root;
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

    void insert(int v) {
        if (contains(v))
            return;

        Node* n = new Node{v, nullptr, nullptr};
        count++;

        if (root == nullptr) {
            root = n;
            return;
        }

        Node* cur = root;
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

void printNode(ostream& out, Node* node, bool& first) {
    if (node == nullptr)
        return;
    printNode(out, node->left, first);
    if (!first)
        out << " ";
    out << node->value;
    first = false;
    printNode(out, node->right, first);
}

ostream& operator<<(ostream& out, const Tree& t) {
    bool first = true;
    printNode(out, t.root, first);
    return out;
}

int main() {
    Tree tree;
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