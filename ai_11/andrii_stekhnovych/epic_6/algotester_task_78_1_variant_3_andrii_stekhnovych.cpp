// Binary Search Tree Andrii Stekhnovych AI-11
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int value) {
        data=value;
    }

};

struct BinSearchTree {
    Node* root=nullptr;
    int count=0;

    int size() const {
        return count;
    }
    void clear(Node* node) {
        if(!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* insert(Node* node, int value) {
        if(!node) {
            count++;
            return new Node(value);
        }
        if( value < node->data) {
            node->left = insert (node->left, value);
        } else if ( value > node->data) {
            node->right=insert(node->right, value);
        } return node;
    }

    bool contains(Node* node, int target) {
        if (!node) {
            return false;
        }
        if (target == node->data) {
            return 1;
        }
        if(target < node->data) {
            return contains(node->left, target);
        } else {
            return contains(node->right, target);
        }
    }
    void print(Node* node, ostream& out) const {
        if(!node) {
            return;
        }
        print(node->left, out);
        out << node->data << " ";
        print(node->right, out);
    }

    

    friend ostream& operator<<(ostream& out, const BinSearchTree& tree) {
        tree.print(tree.root, out);
        return out;
    }

    ~BinSearchTree() {
        clear(root);
    }
    
};


int main() {
    int n;
    cin >> n;
    BinSearchTree tree;
    string cmd;
    for (int i =0; i<n; i++) {
        
        cin >> cmd;
        if (cmd=="size") {
            cout << tree.size() << endl;
        } else if (cmd=="insert") {
            int val;
            cin >> val;
            tree.root=tree.insert(tree.root, val);
        } else if (cmd=="print") {
            cout << tree << endl;
        } else if (cmd=="contains") {
            int val;
            cin >> val;
            if(tree.contains(tree.root, val)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        };
    }
    return 0;
}