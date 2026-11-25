/*
Задача:  Алготестер Lab78v3 (структури)
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root;
    int count;
};

void insert(Tree& tree, int value);
bool contains(Tree& tree, int value);
void printInOrder(ostream& os, Node* node);
ostream& operator<<(ostream& os, Tree& tree);
void destroy(Node* node);

int main() {
    Tree tree{nullptr, 0};
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char command[16];
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            int value;
            cin >> value;
            insert(tree, value);
        }
        else if (strcmp(command, "contains") == 0) {
            int value;
            cin >> value;
            cout << (contains(tree, value) ? "Yes" : "No") << '\n';
        }
        else if (strcmp(command, "size") == 0) {
            cout << tree.count << '\n';
        }
        else if (strcmp(command, "print") == 0) {
            cout << tree << '\n';
        }
    }

    destroy(tree.root);
    return 0;
}

void insert(Tree& tree, int value) {
    Node** link = &tree.root;

    while (*link != nullptr) {
        if (value < (*link)->value) {
            link = &(*link)->left;
        }
        else if (value > (*link)->value) {
            link = &(*link)->right;
        }
        else {
            return;
        }
    }

    *link = new Node{value, nullptr, nullptr};
    tree.count++;
}

bool contains(Tree& tree, int value) {
    Node* node = tree.root;

    while (node != nullptr) {
        if (value == node->value) {
            return true;
        }
        if (value < node->value) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return false;
}

void printInOrder(ostream& os, Node* node) {
    if (node == nullptr) {
        return;
    }

    printInOrder(os, node->left);
    os << node->value << ' ';
    printInOrder(os, node->right);
}

ostream& operator<<(ostream& os, Tree& tree) {
    printInOrder(os, tree.root);
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
