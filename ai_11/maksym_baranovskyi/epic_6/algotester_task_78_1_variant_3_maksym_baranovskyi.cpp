#include <iostream>
#include <string>
using namespace std;

struct Node {
    int val = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

struct BST {
    Node* root = nullptr;
    int count = 0;

    ~BST() {clear(root);}

    void clear(Node* n){
        if (!n){
            return;
        }
        clear(n->left);
        clear(n->right);
        delete n;
    }

    bool insert(int value){
        Node** cur = &root;
        while (*cur) {
            if (value == (*cur)->val){
                return false;
            } 
            cur = (value < (*cur)->val) ? &(*cur)->left : &(*cur)->right;
        }
        *cur = new Node();
        (*cur)->val = value;
        count++;
        return true;
    }

    bool contains(int value) const{
        const Node* cur = root;
        while (cur){
            if (value == cur->val){
                return true;
            } 
            cur = (value < cur->val) ? cur->left : cur->right;
        }
        return false;
    }

    int size() const{ 
        return count; 
    }
};

void printInOrder(ostream& os, const Node* n, bool& first){
    if (!n){
        return;
    } 
    printInOrder(os, n->left, first);
    if (!first){
        os << ' ';
    } 
    os << n->val;
    first = false;
    printInOrder(os, n->right, first);
}

ostream& operator<<(ostream& os, const BST& tree){
    bool first = true;
    printInOrder(os, tree.root, first);
    return os;
}

int main() {

    int q;
    cin >> q;

    BST tree;
    while (q--){
        string cmd;
        cin >> cmd;
        if (cmd == "insert"){
            int v;
            cin >> v;
            tree.insert(v);
        } 
        else if (cmd == "contains"){
            int v;
            cin >> v;
            cout << (tree.contains(v) ? "Yes" : "No") << endl;
        } 
        else if (cmd == "size"){
            cout << tree.size() << endl;
        } 
        else if (cmd == "print"){
            cout << tree << endl;
        }
    }
    return 0;
}