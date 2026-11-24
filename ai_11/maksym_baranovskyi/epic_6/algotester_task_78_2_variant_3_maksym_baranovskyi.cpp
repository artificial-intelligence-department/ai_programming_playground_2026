#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T val;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root = nullptr;
    int count = 0;

    void clear(Node* n){
        if (!n){
            return;
        }
        clear(n->left);
        clear(n->right);
        delete n;
    }

    void printInOrder(ostream& os, const Node* n, bool& first) const{
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

public:
    BST() = default;
    ~BST() {clear(root);}

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool insert(const T& value){
        Node** cur = &root;
        while (*cur){
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

    bool contains(const T& value) const{
        const Node* cur = root;
        while(cur){
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

    void print(ostream& os) const{
        bool first = true;
        printInOrder(os, root, first);
    }
};

template <typename T>
ostream& operator<<(ostream& os, const BST<T>& tree){
    tree.print(os);
    return os;
}

int main(){

    int q;
    cin >> q;

    BST<int> tree;
    while (q--){
        string cmd;
        cin >> cmd;
        if(cmd == "insert"){
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