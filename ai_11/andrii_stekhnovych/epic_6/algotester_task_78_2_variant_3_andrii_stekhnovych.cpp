#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BinSearchTree {
    private:
    struct Node {
        T value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(T v) {
            value = v;
        }
    };

    Node *root = nullptr;
    int count = 0;
    public:
    bool empty() const {
        return root == nullptr;
    }

    int size() const {
        return count;
    }

    void insert(T v) {
        Node** cur = &root;
        while(*cur) {
            if (v == (*cur)->value) {
                return;
            }
            if (v<(*cur)->value) {
                cur = &(*cur)->left;
            } else {
                cur = &(*cur)->right;
            }
        }
        *cur = new Node(v);
        count++;
    }

    bool contains(T v) const{
        Node* cur = root;
        while(cur) {
            if(v==cur->value) {
                return true;
            }
            if(v < cur->value) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return false;
    }

    void clear(Node* node) {
        if(!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void print(ostream& os, Node* n) const {
        if(!n) {
            return;
        }
        print(os, n->left);
        os << n->value << " ";
        print(os, n->right);
    }

    friend ostream& operator<<(ostream& os, const BinSearchTree& t) {
        t.print(os, t.root);
        return os;
    }

    ~BinSearchTree() {
        clear(root);
    }


};


int main() {
    int q;
    cin >> q;
    BinSearchTree<int> tree;
    for (int i=0; i<q; i++) {
        string command;
        cin >> command;
        if (command == "insert") {
            int value;
            cin >> value;
            tree.insert(value);
        }
        if (command == "print") {
            cout << tree << endl;
        }
        if (command == "contains") {
            int value;
            cin >> value;
            if (tree.contains(value)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
        if (command == "size") {
            cout << tree.size() << endl;
        }
    }
    return 0;
}