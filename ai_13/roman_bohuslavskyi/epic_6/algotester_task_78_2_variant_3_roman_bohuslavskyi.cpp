/*
Задача:  Алготестер Lab78v3 (шаблон класу)
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class Tree {
    private:
        struct Node {
            T value;
            Node* left;
            Node* right;
        };

        Node* root;
        int count;

        void printInOrder(ostream& os, Node* node) {
            if (node == nullptr) {
                return;
            }

            printInOrder(os, node->left);
            os << node->value << ' ';
            printInOrder(os, node->right);
        }

        void destroy(Node* node) {
            if (node == nullptr) {
                return;
            }

            destroy(node->left);
            destroy(node->right);
            delete node;
        }

    public:
        Tree() {
            root = nullptr;
            count = 0;
        }

        ~Tree() {
            destroy(root);
        }

        void insert(T value) {
            Node** link = &root;

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
            count++;
        }

        bool contains(T value) {
            Node* node = root;

            while (node != nullptr) {
                if (value < node->value) {
                    node = node->left;
                }
                else if (value > node->value) {
                    node = node->right;
                }
                else {
                    return true;
                }
            }

            return false;
        }

        int size() {
            return count;
        }

        void print(ostream& os) {
            printInOrder(os, root);
        }
};

template <typename T>
ostream& operator<<(ostream& os, Tree<T>& tree);

int main() {
    Tree<int> tree;
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char command[16];
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            int value;
            cin >> value;
            tree.insert(value);
        }
        else if (strcmp(command, "contains") == 0) {
            int value;
            cin >> value;
            cout << (tree.contains(value) ? "Yes" : "No") << '\n';
        }
        else if (strcmp(command, "size") == 0) {
            cout << tree.size() << '\n';
        }
        else if (strcmp(command, "print") == 0) {
            cout << tree << '\n';
        }
    }

    return 0;
}

template <typename T>
ostream& operator<<(ostream& os, Tree<T>& tree) {
    tree.print(os);
    return os;
}