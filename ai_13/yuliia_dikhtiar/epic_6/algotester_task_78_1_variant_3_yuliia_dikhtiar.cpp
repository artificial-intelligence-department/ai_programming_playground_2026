/*
Назва задачі: Lab 78v3
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root = nullptr;
    int size = 0;
};

void insert(Node*& node, int value, int& size) {
    if (node == nullptr) {
        node = new Node{value, nullptr, nullptr};
        size++;
    } else if (value < node->value) {
        insert(node->left, value, size);
    } else if (value > node->value) {
        insert(node->right, value, size);
    }
}

bool contains(Node* node, int value) {
    while (node != nullptr) {
        if (value == node->value) {
            return true;
        }

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return false;
}

void print(ostream& out, Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    print(out, node->left, first);

    if (!first) {
        out << ' ';
    }

    out << node->value;
    first = false;

    print(out, node->right, first);
}

ostream& operator<<(ostream& out, Tree& tree) {
    bool first = true;
    print(out, tree.root, first);
    return out;
}

void clear(Node*& node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
    node = nullptr;
}

int main() {
    int q;
    cin >> q;

    Tree tree;
    string command;

    for (int i = 0; i < q; i++) {
        cin >> command;

        if (command == "insert") {
            int value;
            cin >> value;

            insert(tree.root, value, tree.size);
        } else if (command == "contains") {
            int value;
            cin >> value;

            if (contains(tree.root, value)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else if (command == "size") {
            cout << tree.size << '\n';
        } else if (command == "print") {
            cout << tree << '\n';
        }
    }

    clear(tree.root);

    return 0;
}