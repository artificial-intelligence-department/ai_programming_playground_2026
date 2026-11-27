/*
Назва задачі: Lab 78v3
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

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

    void insertNode(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node{value, nullptr, nullptr};
            count++;
        } else if (value < node->value) {
            insertNode(node->left, value);
        } else if (node->value < value) {
            insertNode(node->right, value);
        }
    }

    void printNodes(ostream& out, Node* node, bool& first) const {
        if (node == nullptr) {
            return;
        }

        printNodes(out, node->left, first);

        if (!first) {
            out << ' ';
        }

        out << node->value;
        first = false;

        printNodes(out, node->right, first);
    }

    void clearNodes(Node* node) {
        if (node == nullptr) {
            return;
        }

        clearNodes(node->left);
        clearNodes(node->right);

        delete node;
    }

public:
    Tree() {
        root = nullptr;
        count = 0;
    }

    ~Tree() {
        clearNodes(root);
    }

    void insert(const T& value) {
        insertNode(root, value);
    }

    bool contains(const T& value) {
        Node* current = root;

        while (current != nullptr) {
            if (value < current->value) {
                current = current->left;
            } else if (current->value < value) {
                current = current->right;
            } else {
                return true;
            }
        }

        return false;
    }

    int size() {
        return count;
    }

    friend ostream& operator<<(ostream& out, const Tree& tree) {
        bool first = true;
        tree.printNodes(out, tree.root, first);
        return out;
    }
};

int main() {
    int q;
    cin >> q;

    Tree<int> tree;
    string command;

    for (int i = 0; i < q; i++) {
        cin >> command;

        if (command == "insert") {
            int value;
            cin >> value;
            tree.insert(value);
        } else if (command == "contains") {
            int value;
            cin >> value;

            if (tree.contains(value)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else if (command == "size") {
            cout << tree.size() << '\n';
        } else if (command == "print") {
            cout << tree << '\n';
        }
    }

    return 0;
}